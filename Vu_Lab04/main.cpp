// EECS 560 Lab 04
// 
// Author: Damian Vu
// Experimental Profiling on Hash tables from Labs 2 and 3

#include "openhashtable.h"
#include "dhhashtable.h"
#include "qphashtable.h"

#include <iostream>
#include <fstream>
#include <ctime> // Same thing as time.h
#include <cstdlib> // Same thing as stdlib.h
#include <iomanip> // For rounding values to 2 decimal places

void runTests() {
	int m = 7;
	int r = 5;
	int k = 10;
	OpenHashTable opht(m);
	DoubleHashHashTable dhht(m, r, k);
	QuadProbeHashTable qpht(m, r, k);

	std::ifstream input("test.txt");
	int x;
	while (input >> x) {
		opht.insert(x);
		dhht.insert(x);
		qpht.insert(x);
	}
	std::cout << "\n";
	opht.print();
	qpht.print();
	dhht.print();
}

void performanceComparison() {
	clock_t t;
	int m = 1000003;
	int r = 100003;
	int k = 20;
	float oTimes[3][5];
	float qTimes[3][5];
	float dTimes[3][5];

	int numbersToFind = m * .01;
	int range = 5 * m; // Random numbers generated will be from 1 to this range value

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 5; j++) {
			oTimes[i][j] = 0.0f;
			qTimes[i][j] = 0.0f;
			dTimes[i][j] = 0.0f;
		}

	for (int i = 0; i < 5; i++) {
		// Used to find averages
		float oTemp[5][3];
		float qTemp[5][3];
		float dTemp[5][3];

		for (int j = 0; j < 5; j++) {
			// New random seed each time
			srand(time(NULL));

			int numbersToInsert = (((float)(i + 1)) * 0.1f) * m;

			int randNum;


			// Build Tables
			t = clock();
			OpenHashTable opht(m);
			t = clock() - t;
			float cumulativeOBuildTime = ((float)t) / CLOCKS_PER_SEC * 1000;
			
			t = clock();
			QuadProbeHashTable qpht(m, r, k);
			t = clock() - t;
			float cumulativeQBuildTime = ((float)t) / CLOCKS_PER_SEC * 1000;
			
			t = clock();
			DoubleHashHashTable dhht(m, r, k);
			t = clock() - t;
			float cumulativeDBuildTime = ((float)t) / CLOCKS_PER_SEC * 1000;

			for (int k = 0; k < numbersToInsert; k++) {
				// Generate random number from 1 to 5m
				randNum = (rand() % range) + 1;

				t = clock();
				while (!opht.insert(randNum)) {
					// Can't insert. Discard allocated time and get a new number
					randNum = (rand() % range) + 1;
					t = clock();
				}
				t = clock() - t;
				cumulativeOBuildTime += ((float)t) / CLOCKS_PER_SEC * 1000;

				randNum = (rand() % range) + 1;

				t = clock();
				while (!qpht.insert(randNum)) {
					// Can't insert. Discard allocated time and get a new number
					randNum = (rand() % range) + 1;
					t = clock();
				}
				t = clock() - t;
				cumulativeQBuildTime += ((float)t) / CLOCKS_PER_SEC * 1000;

				randNum = (rand() % range) + 1;

				t = clock();
				while (!dhht.insert(randNum)) {
					// Can't insert. Get a new number and discard allocated time
					randNum = (rand() % range) + 1;
					t = clock();
				}
				t = clock() - t;
				cumulativeDBuildTime += ((float)t) / CLOCKS_PER_SEC * 1000;
			}
			oTemp[j][0] = cumulativeOBuildTime;
			qTemp[j][0] = cumulativeQBuildTime;
			dTemp[j][0] = cumulativeDBuildTime;

			float cumulativeOFindTime = 0.0f;
			float cumulativeQFindTime = 0.0f;
			float cumulativeDFindTime = 0.0f;
			float cumulativeONFTime = 0.0f;
			float cumulativeQNFTime = 0.0f;
			float cumulativeDNFTime = 0.0f;

			for (int k = 0; k < numbersToFind; k++) {

				// Search each table and store cumulative time
				int randNum;
				bool found;

				// Open table find
				randNum = (rand() % range) + 1;

				t = clock();
				found = opht.find(randNum);
				t = clock() - t;

				if (found) {
					cumulativeOFindTime += ((float)t) / CLOCKS_PER_SEC * 1000;
				}
				else {
					cumulativeONFTime += ((float)t) / CLOCKS_PER_SEC * 1000;
				}


				// Quad table find
				randNum = (rand() % range) + 1;

				t = clock();
				found = qpht.find(randNum);
				t = clock() - t;

				if (found) {
					cumulativeQFindTime += ((float)t) / CLOCKS_PER_SEC * 1000;
				}
				else {
					cumulativeQNFTime += ((float)t) / CLOCKS_PER_SEC * 1000;
				}


				// Double table find
				randNum = (rand() % range) + 1;

				t = clock();
				found = dhht.find(randNum);
				t = clock() - t;

				if (found) {
					cumulativeDFindTime += ((float)t) / CLOCKS_PER_SEC * 1000;
				}
				else {
					cumulativeDNFTime += ((float)t) / CLOCKS_PER_SEC * 1000;
				}
			}

			// Store cumulative find times
			oTemp[j][1] = cumulativeOFindTime;
			oTemp[j][2] = cumulativeONFTime;
			qTemp[j][1] = cumulativeQFindTime;
			qTemp[j][2] = cumulativeQNFTime;
			dTemp[j][1] = cumulativeDFindTime;
			dTemp[j][2] = cumulativeDNFTime;
		}

		// Calculate averages
		float oAvgBuild = 0;
		float qAvgBuild = 0;
		float dAvgBuild = 0;
		for (int j = 0; j < 5; j++) {
			oAvgBuild += oTemp[j][0];
			qAvgBuild += qTemp[j][0];
			dAvgBuild += dTemp[j][0];
		}
		oAvgBuild = oAvgBuild / 5.0f;
		qAvgBuild = qAvgBuild / 5.0f;
		dAvgBuild = dAvgBuild / 5.0f;

		float oAvgFind = 0;
		float oAvgNF = 0;
		float qAvgFind = 0;
		float qAvgNF = 0;
		float dAvgFind = 0;
		float dAvgNF = 0;
		for (int j = 0; j < 5; j++) {
			oAvgFind += oTemp[j][1];
			oAvgNF += oTemp[j][2];
			qAvgFind += qTemp[j][1];
			qAvgNF += qTemp[j][2];
			dAvgFind += dTemp[j][1];
			dAvgNF += dTemp[j][2];
		}
		oAvgFind = oAvgFind / 5.0f;
		oAvgNF = oAvgNF / 5.0f;
		qAvgFind = qAvgFind / 5.0f;
		qAvgNF = qAvgNF / 5.0f;
		dAvgFind = dAvgFind / 5.0f;
		dAvgNF = dAvgNF / 5.0f;

		// Store all average times
		oTimes[0][i] = oAvgBuild;
		oTimes[1][i] = oAvgFind;
		oTimes[2][i] = oAvgNF;
		qTimes[0][i] = qAvgBuild;
		qTimes[1][i] = qAvgFind;
		qTimes[2][i] = qAvgNF;
		dTimes[0][i] = dAvgBuild;
		dTimes[1][i] = dAvgFind;
		dTimes[2][i] = dAvgNF;
	}

	// Print results
	std::cout << "\nResults (All times are in milliseconds)\n\n";
	std::cout << "Performance (Open Hashing):\n";
	std::cout << "Table Size\t0.1m\t0.2m\t0.3m\t0.4m\t0.5m\n\n";
	std::cout << std::fixed << std::setprecision(2) << "Build\t\t" << oTimes[0][0] << "\t" << oTimes[0][1] << "\t" << oTimes[0][2] << "\t" << oTimes[0][3] << "\t" << oTimes[0][4] << "\n";
	std::cout << std::fixed << std::setprecision(2) << "Found\t\t" << oTimes[1][0] << "\t" << oTimes[1][1] << "\t" << oTimes[1][2] << "\t" << oTimes[1][3] << "\t" << oTimes[1][4] << "\n";
	std::cout << std::fixed << std::setprecision(2) << "Not Found\t" << oTimes[2][0] << "\t" << oTimes[2][1] << "\t" << oTimes[2][2] << "\t" << oTimes[2][3] << "\t" << oTimes[2][4] << "\n\n";

	std::cout << "Performance (Quad Hashing):\n";
	std::cout << "Table Size\t0.1m\t0.2m\t0.3m\t0.4m\t0.5m\n\n";
	std::cout << std::fixed << std::setprecision(2) << "Build\t\t" << qTimes[0][0] << "\t" << qTimes[0][1] << "\t" << qTimes[0][2] << "\t" << qTimes[0][3] << "\t" << qTimes[0][4] << "\n";
	std::cout << std::fixed << std::setprecision(2) << "Found\t\t" << qTimes[1][0] << "\t" << qTimes[1][1] << "\t" << qTimes[1][2] << "\t" << qTimes[1][3] << "\t" << qTimes[1][4] << "\n";
	std::cout << std::fixed << std::setprecision(2) << "Not Found\t" << qTimes[2][0] << "\t" << qTimes[2][1] << "\t" << qTimes[2][2] << "\t" << qTimes[2][3] << "\t" << qTimes[2][4] << "\n\n";

	std::cout << "Performance (Double Hashing):\n";
	std::cout << "Table Size\t0.1m\t0.2m\t0.3m\t0.4m\t0.5m\n\n";
	std::cout << std::fixed << std::setprecision(2) << "Build\t\t" << dTimes[0][0] << "\t" << dTimes[0][1] << "\t" << dTimes[0][2] << "\t" << dTimes[0][3] << "\t" << dTimes[0][4] << "\n";
	std::cout << std::fixed << std::setprecision(2) << "Found\t\t" << dTimes[1][0] << "\t" << dTimes[1][1] << "\t" << dTimes[1][2] << "\t" << dTimes[1][3] << "\t" << dTimes[1][4] << "\n";
	std::cout << std::fixed << std::setprecision(2) << "Not Found\t" << dTimes[2][0] << "\t" << dTimes[2][1] << "\t" << dTimes[2][2] << "\t" << dTimes[2][3] << "\t" << dTimes[2][4] << "\n\n";
}

int main() {

	bool running = true;

	while (running) {
		int choice;
		std::cout << "------------------------------------------------------------\nPlease choose one of the following commands:\n1- Test HashTables\n2- Performance Comparison\n3- Exit\n>";
		std::cin >> choice;
		switch (choice) {
			case 1:
				runTests();
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
