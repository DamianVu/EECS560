
#include "process.h"

Process::Process() {

}

Process::Process(int id, int p, int t) {
	myId = id;
	priority = p;
	time = t;
}

Process::Process(const Process& p) {
	myId = p.myId;
	priority = p.priority;
	time = p.time;
}

void Process::print() {
	printName();
	std::cout << "(" << priority << "," << time << ")";
}

void Process::printName() {
	std::cout << "P" << myId;
}

void Process::run(int t) {
	// Run this process
	time -= t;
}

bool Process::operator <(const Process & p) {
	if (priority == p.priority)
		return time < p.time;
	return priority < p.priority;
}

bool Process::operator >(const Process & p) {
	if (priority == p.priority)
		return time > p.time;
	return priority > p.priority;
}
