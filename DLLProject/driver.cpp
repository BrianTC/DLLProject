#ifdef _WIN32
	const bool pause = true;

#else
	const bool pause = false;
#endif // _WIN32

#include "csv_load.h"
#include "proc_algorithim.h"
#include <iostream>
//#include <Mspthrd.h>
using namespace std;
int main() {
	try {
		csvLoad::csv_load a = csvLoad::csv_load("Text.csv");
		cout << "LOAD" << endl;
		cout << procAlgo::proc_algorithim::shortestProcNext(a)->str();
		cout << endl;
		cout << procAlgo::proc_algorithim::HRRN(a)->str();
		cout << endl;
		cout << procAlgo::proc_algorithim::roundRobin(a,3)->str();
	}
	catch (const exception &e) {
		cout << "Check Input File" << endl;
	}
	if (pause) {
		system("pause");
	}
	return 0;
}