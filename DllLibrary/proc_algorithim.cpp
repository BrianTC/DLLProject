#include "proc_algorithim.h"
//#include "stdafx.h"
namespace procAlgo {
	using namespace csvLoad;
	ostringstream* proc_algorithim::shortestProcNext(csv_load a) {
		ostringstream *printOut = new ostringstream();
		*printOut << "ShortestProcessNext:\n";
		vector<csv_load::proc> procList = a.csv_getProcList();
		int clock = 0;
		vector<csv_load::proc> cProcList;
		while (procList.size() > 0 || cProcList.size() > 0) {
			//Queue processes ready to be run
			for (size_t i = 0; i < procList.size(); i++) {
				if (procList[i].t_start <= clock) {
					cProcList.push_back(procList[i]);
					procList.erase(procList.begin() + i);
					i--;
				}
			}
			//Process Shortest Process Next
			csv_load::proc shortestProcess;
			size_t shortestProcessLen, shortIndex;
			for (size_t i = 0; i < cProcList.size(); i++) {
				//initialize first value 
				if (i == 0) {
					shortestProcess = cProcList[0];
					shortIndex = 0;
					shortestProcessLen = shortestProcess.t_run;
				}
				//find next shortest value
				if (cProcList[i].t_run < shortestProcessLen) {
					shortestProcessLen = cProcList[i].t_run;
					shortestProcess = cProcList[i];
					shortIndex = i;
				}
			}
			if (cProcList.size() > 0) {
				cProcList.erase(cProcList.begin() + shortIndex);
				for (int i = 0; i < shortestProcessLen; i++) {
					uniformOutput(printOut, clock, &shortestProcess);
					clock++;
				}
			}
			else {
				uniformOutput(printOut, clock);
				clock++;
			}

		}//END WHILE
		return printOut;
	}

	//HRRN Priority = 1 + WAIT_TIME/RUN_TIM
	ostringstream* proc_algorithim::HRRN(csv_load a) {
		ostringstream *printOut = new ostringstream();
		*printOut << "HRRN:\n";
		vector<csv_load::proc> procList = a.csv_getProcList();
		int clock = 0;
		vector<csv_load::proc> cProcList;

		while (procList.size() > 0 || cProcList.size() > 0) {
			//Queue processes ready to be run
			for (size_t i = 0; i < procList.size(); i++) {
				if (procList[i].t_start <= clock) {
					cProcList.push_back(procList[i]);
					procList.erase(procList.begin() + i);
					i--;
				}
			}
			//Select Next Process to run
			csv_load::proc selectedProc;
			int selectedIndex = 0;
			double highestRatio;
			for (size_t i = 0; i < cProcList.size(); i++) {
				double currRatio = 1 + (clock - cProcList[i].t_start) / cProcList[i].t_run;
				if (i == 0) {
					highestRatio = currRatio;
				}
				else if (currRatio > highestRatio) {
					highestRatio = currRatio;
					selectedIndex = i;
				}
			}
			//"Run" the selected process, or just wait till a process is submitted
			if (cProcList.size() > 0) {
				selectedProc = cProcList[selectedIndex];
				cProcList.erase(cProcList.begin() + selectedIndex);
				for (int i = 0; i < selectedProc.t_run; i++) {
					uniformOutput(printOut, clock, &selectedProc);
					clock++;
				}
			}
			else {
				uniformOutput(printOut, clock);
				clock++;
			}

		}//END WHILE
		return printOut;
	}

	ostringstream* proc_algorithim::roundRobin(csv_load a, unsigned int quanta = 0) {
		ostringstream *printOut = new ostringstream();
		*printOut << "RoundRobin:\n";
		vector<csv_load::proc> procList = a.csv_getProcList();
		//if quanta is <= zero determing the average process time and use that as the quanta
		if (quanta == 0) {
			for (size_t i = 0; i < procList.size(); i++) {
				quanta += procList[i].t_run;
			}
			quanta /= procList.size();
		}
		int clock = 0;
		size_t procIndex = 0;
		vector<csv_load::proc> cProcList;
		while (procList.size() > 0 || cProcList.size() > 0) {

			//Queue processes ready to be run
			for (size_t i = 0; i < procList.size(); i++) {
				if (procList[i].t_start <= clock) {
					cProcList.push_back(procList[i]);
					procList.erase(procList.begin() + i);
					i--;
				}
			}
			for (size_t i = 0; i < quanta; i++) {
				if (cProcList.size() == 0) {
					uniformOutput(printOut, clock);
					clock++;
					break;
				}
				uniformOutput(printOut, clock, &cProcList[procIndex]);
				//Remove process and increment counter
				if (--cProcList[procIndex].t_run == 0) {
					cProcList.erase(cProcList.begin() + procIndex);
					procIndex = procIndex >= cProcList.size() ? 0 : procIndex;
				}
				clock++;

			}
			procIndex = procIndex + 1 >= cProcList.size() ? 0 : procIndex + 1;
		}//END WHILE
		return printOut;
	}

	ostringstream* proc_algorithim::feedback(csv_load a) {
		return nullptr;
	}
};