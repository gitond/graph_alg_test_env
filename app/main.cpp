#include <iostream>
#include <string>

int main() {
	std::string uInp;

	std::cout << "graph_alg_test_env v0.1.0.1 by Botond Ortutay \n";
	std::cout << "Please enter a command! \n";
	std::cout << "$ ";
	std::getline(std::cin, uInp);
	std::cout << "I got " << uInp << ".\n";

	return 0;
}
