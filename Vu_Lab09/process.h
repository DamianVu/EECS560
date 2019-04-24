
#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>

class Process {
public:
	Process();
	Process(int id, int p, int t);
	Process(const Process& p);

	int getPriority() { return priority; }
	int getTime() { return time; }

	void print();
	void printName();
	void run(int t);

	bool operator <(const Process& p);
	bool operator >(const Process& p);

private:
	int myId;
	int priority;
	int time;
};

#endif
