#include <iostream>
#include <string>
#include "modules/main/command_parser.h"

int main() {
	std::string uInp;
	std::string commOutp;

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
