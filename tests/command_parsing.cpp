#include <iostream>
#include <string>
#include "../app/metaheaders/commstruct.h"
#include "../app/modules/main/command_parser.h"

int main() {

	// 2d array where all command data is stored
	// Dimensions: support for 100 modules with 100 commands each
	command commDataStructure[100][100];

	// Filling unused module slot beginnings with "NULL" values
	for(int i = 1; i < 100; i++){
		commDataStructure[i][0] = {"",0,""};
	}

	// TEMPORARY			

	commDataStructure[0][0] = {
		"quit",					// command
		0,					// id
		"Controlled shutdown of program"	// desc
	};
	commDataStructure[0][1] = {
		"dummy",
		1,
		"Dummy command for testing purposes"
	};
	commDataStructure[0][2] = {"",0,""};

	//				

	if(parse("dummy",commDataStructure) == "Dummy command entered."){
		std::cout << "Command parsing test successful \n";
		return 0;
	}
	std::cout << "Command parsing test unsuccessful \n";
	return 1;
}
