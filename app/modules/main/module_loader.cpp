#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "module_loader.h"
#include "../../metaheaders/commstruct.h"

int loadModule(std::string module, command commDS[100][100]){
	// File input
	std::string mPath;
	mPath = "app/modules/" + module + "/commands.csv";
	std::ifstream filein(mPath);
	command tempComm;

	// First free slot in commDS
	int current = -1;
	for (int i=0; i < 100; i++){
		switch(i){
			case 99:
				if (commDS[i][0].command != "") {
					std::cout << "Error: max module capacity reached";
					return 1;
				} else { current = 99; }
				break;
			default:
				if (commDS[i][0].command == "") { current = i; }
				break;
		}
		if (current != -1){ break; }
	}

	// File parsing
	int pos;
	int commSHelper; // 0 for command 1 for id 2 for desc
	int lineno = 0;
	for (std::string line; std::getline(filein, line);){
		pos = 0;
		commSHelper = 0;
		for (int i = 0; i <= line.size(); i++){
			if (line[i] == ',' || i == line.size()){
				switch(commSHelper){
					case 0:
						tempComm.command =  line.substr(pos, i-pos);
						break;
					case 1:
						tempComm.id = stoi(line.substr(pos, i-pos));
						break;
					case 2:
						tempComm.desc =  line.substr(pos, i-pos);
						break;
				}
				pos = i+1;
				commSHelper++;
			}
		}
		commDS[current][lineno] = tempComm;
		lineno++;
	}
	return 0;
}

/*
int main(){
	// 2d array where all command data is stored
	// Dimensions: support for 100 modules with 100 commands each
	command commDataStructure[100][100];

	// Filling unused module slot beginnings with "NULL" values
	for(int i = 0; i < 100; i++){
		commDataStructure[i][0] = {"",0,""};
	}

	loadModule("main", commDataStructure);

	std::cout << commDataStructure[0][0].command << "\n";
	std::cout << commDataStructure[0][1].command << "\n";

	return 0;
}
*/
