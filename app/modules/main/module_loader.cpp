#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "../../metaheaders/commstruct.h"

void loadModule(std::string module){
	// File input
	std::string mPath;
	mPath = "app/modules/" + module + "/commands.csv";
	std::ifstream filein(mPath);

	// File parsing
	int pos;
	for (std::string line; std::getline(filein, line);){
		pos = 0;
		for (int i = 0; i <= line.size(); i++){
			if (line[i] == ',' || i == line.size()){
				std::cout << line.substr(pos, i-pos) << "\n";
				pos = i+1;
			}
		}
	}
}

int main(){
	loadModule("main");
	return 0;
}
