#include <array>
#include <iostream>
#include <string>
#include "metaheaders/commstruct.h"
#include "modules/main/command_parser.h"
#include "modules/main/module_loader.h"
#include "modules/graphs/graph.h"

int main() {
	// --- STATE MACHINE --- //
	std::string uInp;
	std::string commOutp;

	// 2d array where all command data is stored
	// Dimensions: support for 100 modules with 100 commands each
	command commDataStructure[100][100];

	// Filling unused module slot beginnings with "NULL" values
	for(int i = 1; i < 100; i++){
		commDataStructure[i][0] = {"",0,""};
	}

	// reference graph where all vertix data is stored
	// if a graph is created via the cli it will also be stored in this variable
	std::array<vertex,250> emptInpArray;	// To be used with constructor, should contain only nullvertices
	graph stateGraph = graph(emptInpArray,0);

	// Adjacency matrix below
	// can be used in graph constructors
	// uncomment if needed
	// std::array<std::array<float, 250>, 250> exAdjMatrix;

	// --- PROGRAM EXECUTION --- //
	std::cout << "graph_alg_test_env v0.2.5.10 by Botond Ortutay \n";
	std::cout << "Please enter a command! \n";

	if(loadModule("main", commDataStructure) == 1) { return 1; } // Loads the module and crashes if loading unsuccesful
	if(loadModule("graphs", commDataStructure) == 1) { return 1; } // Loads the module and crashes if loading unsuccesful
	if(loadModule("algorithms", commDataStructure) == 1) { return 1; } // Loads the module and crashes if loading unsuccesful

	while(1){
		std::cout << "$ ";
		std::getline(std::cin, uInp);
		commOutp = parse(uInp, commDataStructure, stateGraph);
		if(commOutp == "quit"){
			break;
		}
		std::cout << commOutp << "\n";
	}

	return 0;
}
