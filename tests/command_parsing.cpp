#include <iostream>
#include <string>
#include "../app/modules/main/command_parser.h"

int main() {
	if(parse("dummy") == "Dummy command entered."){
		std::cout << "Command parsing test successful \n";
		return 0;
	}
	std::cout << "Command parsing test unsuccessful \n";
	return 1;
}
