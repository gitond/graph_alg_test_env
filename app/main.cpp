#include <iostream>
#include <string>
#include "metaheaders/commstruct.h"
#include "modules/main/command_parser.h"
#include "modules/main/module_loader.h"
#include "modules/graphs/graph.h"

int main() {
	std::string uInp;
	std::string commOutp;

	// 2d array where all command data is stored
	// Dimensions: support for 100 modules with 100 commands each
	command commDataStructure[100][100];

	// Filling unused module slot beginnings with "NULL" values
	for(int i = 1; i < 100; i++){
		commDataStructure[i][0] = {"",0,""};
	}

	// Program execution starts here
	std::cout << "graph_alg_test_env v0.2.1.8 by Botond Ortutay \n";
	std::cout << "Please enter a command! \n";

	if(loadModule("main", commDataStructure) == 1) { return 1; } // Loads the module and crashes if loading unsuccesful
	if(loadModule("graphs", commDataStructure) == 1) { return 1; } // Loads the module and crashes if loading unsuccesful

	while(1){
		std::cout << "$ ";
		std::getline(std::cin, uInp);
		commOutp = parse(uInp, commDataStructure);
		if(commOutp == "quit"){
			break;
		}
		std::cout << commOutp << "\n";
	}

	return 0;
}
