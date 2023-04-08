#include <iostream>
#include <string>
#include "metaheaders/commstruct.h"
#include "modules/main/command_parser.h"

int main() {
	std::string uInp;
	std::string commOutp;

	// 2d array where all command data is stored
	// Dimensions: support for 100 modules with 100 commands each
	command commDataStructure[100][100];

	// Program execution starts here
	std::cout << "graph_alg_test_env v0.1.0.2 by Botond Ortutay \n";
	std::cout << "Please enter a command! \n";

	while(1){
		std::cout << "$ ";
		std::getline(std::cin, uInp);
		commOutp = parse(uInp);
		if(commOutp == "quit"){
			break;
		}
		std::cout << commOutp << "\n";
	}

	return 0;
}
