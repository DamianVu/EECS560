
#include <iostream>
#include <fstream>
#include <cstdlib> 	// Same thing as stdlib.h
#include <ctime>	// Same thing as time.h
#include <iomanip>	// Rounding values to 2 decimal places

#include "bst.h"
#include "minfiveheap.h"
#include "maxfiveheap.h"

void test() {
	BST bst;
	MinFiveHeap min;
	MaxFiveHeap max;

	std::ifstream input("data.txt");

	int inp;
	while (input >> inp) {
		bst.insert(inp);
		min.insert(inp);
		max.insert(inp);
	}
	min.buildheap();
	max.buildheap();

	std::cout << "\nBST:\n";
	bst.levelorder();
	std::cout << "\nMin-5 Heap:\n";
	min.levelorder();
	std::cout << "\nMax-5 Heap:\n";
	max.levelorder();
}

void performanceComparison() {
	clock_t t;
	int m = 1000000;
	int range = 5 * m;
	int delRange = m * .001;

	float bstTimes[3][5];
	float minTimes[3][5];
	float maxTimes[3][5];

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++) {
			bstTimes[i][j] = 0.0f;
			minTimes[i][j] = 0.0f;
			maxTimes[i][j] = 0.0f;
		}

	std::cout << "Debug messages to show progress is being made:\n";

	for (int i = 0; i < 5; i++) {
		std::cout << "i=" << i << "\n";
		// Used to find averages
		float bstTemp[5][3];
		float minTemp[5][3];
		float maxTemp[5][3];

		for (int j = 0; j < 5; j++) {
			std::cout << "j=" << j << "\n";
			// New seed each time
			srand(time(NULL));

			int numbersToInsert = (i + 1) * m;
			int randNum;

			// Create
			BST bst;
			MinFiveHeap min;
			MaxFiveHeap max;

			float cumulativeBstBuildTime = 0.0f;
			float cumulativeMinBuildTime = 0.0f;
			float cumulativeMaxBuildTime = 0.0f;

			for (int k = 0; k < numbersToInsert; k++) {
				randNum = (rand() % range) + 1;

				t = clock();
				bst.insert(randNum);
				t = clock() - t;
				cumulativeBstBuildTime += (float)t;

				randNum = (rand() % range) + 1;

				t = clock();
				min.insert(randNum);
				t = clock() - t;
				cumulativeMinBuildTime += (float)t;

				randNum = (rand() % range) + 1;

				t = clock();
				max.insert(randNum);
				t = clock() - t;
				cumulativeMaxBuildTime += (float)t;
			}

			t = clock();
			min.buildheap();
			t = clock() - t;
			cumulativeMinBuildTime += (float)t;

			t = clock();
			max.buildheap();
			t = clock() - t;
			cumulativeMaxBuildTime += (float)t;

			bstTemp[j][0] = cumulativeBstBuildTime;
			minTemp[j][0] = cumulativeMinBuildTime;
			maxTemp[j][0] = cumulativeMaxBuildTime;

			float cumulativeBstDelMinTime = 0.0f;
			float cumulativeMinDelMinTime = 0.0f;
			float cumulativeMaxDelMinTime = 0.0f;
			float cumulativeBstDelMaxTime = 0.0f;
			float cumulativeMinDelMaxTime = 0.0f;
			float cumulativeMaxDelMaxTime = 0.0f;

			for (int k = 0; k < delRange; k++) {
				t = clock();
				bst.remove(bst.findMin());
				t = clock() - t;
				cumulativeBstDelMinTime += (float)t;

				t = clock();
				min.deletemin();
				t = clock() - t;
				cumulativeMinDelMinTime += (float)t;

				t = clock();
				max.deletemin();
				t = clock() - t;
				cumulativeMaxDelMinTime += (float)t;

				t = clock();
				bst.remove(bst.findMax());
				t = clock() - t;
				cumulativeBstDelMaxTime += (float)t;

				t = clock();
				min.deletemax();
				t = clock() - t;
				cumulativeMinDelMaxTime += (float)t;

				t = clock();
				max.deletemax();
				t = clock() - t;
				cumulativeMaxDelMaxTime += (float)t;
			}

			bstTemp[j][1] = cumulativeBstDelMinTime;
			bstTemp[j][2] = cumulativeBstDelMaxTime;
			minTemp[j][1] = cumulativeMinDelMinTime;
			minTemp[j][2] = cumulativeMinDelMaxTime;
			maxTemp[j][1] = cumulativeMaxDelMinTime;
			maxTemp[j][2] = cumulativeMaxDelMaxTime;
		}
		float bstAvgBuild = 0.0f;
		float bstAvgDelMin = 0.0f;
		float bstAvgDelMax = 0.0f;

		float minAvgBuild = 0.0f;
		float minAvgDelMin = 0.0f;
		float minAvgDelMax = 0.0f;

		float maxAvgBuild = 0.0f;
		float maxAvgDelMin = 0.0f;
		float maxAvgDelMax = 0.0f;

		for (int j = 0; j < 5; j++) {
			bstAvgBuild += bstTemp[j][0];
			bstAvgDelMin += bstTemp[j][1];
			bstAvgDelMax += bstTemp[j][2];

			minAvgBuild += minTemp[j][0];
			minAvgDelMin += minTemp[j][1];
			minAvgDelMax += minTemp[j][2];

			maxAvgBuild += maxTemp[j][0];
			maxAvgDelMin += maxTemp[j][1];
			maxAvgDelMax += maxTemp[j][2];
		}

		bstAvgBuild = bstAvgBuild / 5.0f;
		bstAvgDelMin = bstAvgDelMin / 5.0f;
		bstAvgDelMax = bstAvgDelMax / 5.0f;

		minAvgBuild = minAvgBuild / 5.0f;
		minAvgDelMin = minAvgDelMin / 5.0f;
		minAvgDelMax = minAvgDelMax / 5.0f;

		maxAvgBuild = maxAvgBuild / 5.0f;
		maxAvgDelMin = maxAvgDelMax / 5.0f;
		maxAvgDelMax = maxAvgDelMax / 5.0f;

		// Store all average times
		bstTimes[0][i] = bstAvgBuild / CLOCKS_PER_SEC * 1000;
		bstTimes[1][i] = bstAvgDelMin / CLOCKS_PER_SEC * 1000;
		bstTimes[2][i] = bstAvgDelMax / CLOCKS_PER_SEC * 1000;

		minTimes[0][i] = minAvgBuild / CLOCKS_PER_SEC * 1000;
		minTimes[1][i] = minAvgDelMin / CLOCKS_PER_SEC * 1000;
		minTimes[2][i] = minAvgDelMax / CLOCKS_PER_SEC * 1000;

		maxTimes[0][i] = maxAvgBuild / CLOCKS_PER_SEC * 1000;
		maxTimes[1][i] = maxAvgDelMin / CLOCKS_PER_SEC * 1000;
		maxTimes[2][i] = maxAvgDelMax / CLOCKS_PER_SEC * 1000;
	}

		// Print results
	std::cout << "\nResults (All times are in milliseconds)\n\n";
	std::cout << "Performance (BST):\n";
	std::cout << "Table Size\t1m\t2m\t3m\t4m\t5m\n\n";
	std::cout << std::fixed << std::setprecision(2) << "Build\t\t" << bstTimes[0][0] << "\t" << bstTimes[0][1] << "\t" << bstTimes[0][2] << "\t" << bstTimes[0][3] << "\t" << bstTimes[0][4] << "\n";
	std::cout << std::fixed << std::setprecision(2) << "DelMin\t\t" << bstTimes[1][0] << "\t" << bstTimes[1][1] << "\t" << bstTimes[1][2] << "\t" << bstTimes[1][3] << "\t" << bstTimes[1][4] << "\n";
	std::cout << std::fixed << std::setprecision(2) << "DelMax\t\t" << bstTimes[2][0] << "\t" << bstTimes[2][1] << "\t" << bstTimes[2][2] << "\t" << bstTimes[2][3] << "\t" << bstTimes[2][4] << "\n\n";

	std::cout << "Performance (Min-5 Heap):\n";
	std::cout << "Table Size\t1m\t2m\t3m\t4m\t5m\n\n";
	std::cout << std::fixed << std::setprecision(2) << "Build\t\t" << minTimes[0][0] << "\t" << minTimes[0][1] << "\t" << minTimes[0][2] << "\t" << minTimes[0][3] << "\t" << minTimes[0][4] << "\n";
	std::cout << std::fixed << std::setprecision(2) << "DelMin\t\t" << minTimes[1][0] << "\t" << minTimes[1][1] << "\t" << minTimes[1][2] << "\t" << minTimes[1][3] << "\t" << minTimes[1][4] << "\n";
	std::cout << std::fixed << std::setprecision(2) << "DelMax\t\t" << minTimes[2][0] << "\t" << minTimes[2][1] << "\t" << minTimes[2][2] << "\t" << minTimes[2][3] << "\t" << minTimes[2][4] << "\n\n";

	std::cout << "Performance (Max-5 Heap):\n";
	std::cout << "Table Size\t1m\t2m\t3m\t4m\t5m\n\n";
	std::cout << std::fixed << std::setprecision(2) << "Build\t\t" << maxTimes[0][0] << "\t" << maxTimes[0][1] << "\t" << maxTimes[0][2] << "\t" << maxTimes[0][3] << "\t" << maxTimes[0][4] << "\n";
	std::cout << std::fixed << std::setprecision(2) << "DelMin\t\t" << maxTimes[1][0] << "\t" << maxTimes[1][1] << "\t" << maxTimes[1][2] << "\t" << maxTimes[1][3] << "\t" << maxTimes[1][4] << "\n";
	std::cout << std::fixed << std::setprecision(2) << "DelMax\t\t" << maxTimes[2][0] << "\t" << maxTimes[2][1] << "\t" << maxTimes[2][2] << "\t" << maxTimes[2][3] << "\t" << maxTimes[2][4] << "\n\n";

}

int main() {

	bool running = true;

	while (running) {
		std::cout << "\n------------------------------------------------------------\nPlease choose one of the following commands:\n1- Test BST/Heaps\n2- Performance Comparison\n3- Exit\n>";

		int c;
		std::cin >> c;

		switch (c) {
			case 1:
				test();
			break;
			case 2:
				performanceComparison();
			break;
			case 3:
			default:
				running = false;
			break;
		}
	}

	return 0;
}
