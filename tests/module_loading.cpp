#include <iostream>
#include <string>
#include "../app/metaheaders/commstruct.h"
#include "../app/modules/main/command_parser.h"
#include "../app/modules/main/module_loader.h"
#include "../app/modules/graphs/graph.h"

int main() {
	// 2d array where all command data is stored
	// Dimensions: support for 100 modules with 100 commands each
	command commDataStructure[100][100];


	// Filling unused module slot beginnings with "NULL" values
	for(int i = 1; i < 100; i++){
		commDataStructure[i][0] = {"",0,""};
	}

	// Graph so parsing works
	graph tg = graph();

	if(loadModule("testmod", commDataStructure) == 1) { return 1; } // Loads the module and crashes if loading unsuccesful

	if(parse("tdummy", commDataStructure, tg) == "testmod dummy command") {
		std::cout << "Test module command used successfully" << "\n";
	} else {
		std::cout << "Test module command used unsuccessfully" << "\n";
		return 1;
	}

	if(loadModule("knee", commDataStructure) == 2) {
		std::cout << "Test reacted correctly to attempted loading of nonexistent module" << "\n";
	} else {
		std::cout << "Test reacted incorrectly to attempted loading of nonexistent module" << "\n";
		return 1;
	}

	return 0;
}
