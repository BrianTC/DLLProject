#pragma once
#ifdef PROCAPI_EXPORTS  
#define PROCAPI __declspec(dllexport)   
#else  
#define PROCAPI __declspec(dllimport)   
#endif 

#include "csv_load.h"
#include <sstream>
#include <iostream>
#include <iomanip>

namespace procAlgo {
	class  proc_algorithim {
	private:
		static const int IOWIDTH = 4;
		//Uniform output function to allow a controlled uniform output from the orginization types
		static void uniformOutput(ostringstream *ss, size_t clck, csvLoad::csv_load::proc *prc = nullptr) {
			if (prc == nullptr)
				*ss << "Cycle: " << setw(IOWIDTH) << clck << " EMPTY CYCLE" << endl;
			else
				*ss << "Cycle: " << setw(IOWIDTH) << clck << " PID: " << prc->pid << endl;
		}
	public:
		static PROCAPI ostringstream* HRRN(csvLoad::csv_load a);//Highest response ratio next
		static PROCAPI ostringstream* roundRobin(csvLoad::csv_load a, unsigned int quanta);
		static PROCAPI ostringstream* feedback(csvLoad::csv_load a);
		static PROCAPI ostringstream* shortestProcNext(csvLoad::csv_load a);
	};
};