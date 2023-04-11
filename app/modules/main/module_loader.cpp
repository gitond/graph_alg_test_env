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

	// Checking if file exists
	if(!filein) {
		std::cout << "Error: Can't load module " << mPath << " , module may not exist \n";
		return 2; // Stops execution without crashing
	}

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
	command tempComm;
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
