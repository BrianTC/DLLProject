#pragma once
#ifdef CSVAPI_EXPORTS  
#define CSVAPI __declspec(dllexport)   
#else  
#define CSVAPI __declspec(dllimport)   
#endif 

#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <iostream>
using namespace std;
namespace csvLoad {
	class CSVAPI csv_load {
	public:
		csv_load(string filename);
		~csv_load();

		struct proc {
			int t_start;
			int t_run;
			string pid;
		};
		vector<string> csv_get_pid();
		vector<int> csv_get_tstart();
		vector<int> csv_get_trun();
		///list of proc types
		vector<proc> csv_getProcList();
	};
};

