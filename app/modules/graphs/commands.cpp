#include <string>
#include <cstring>
#include "../../metaheaders/commstruct.h"
#include "commands.h"
#include <iostream>
#include <stdexcept>

// Command executions
namespace graphComms {
	std::string execute(int commandId, std::string flags[10]){

		switch(commandId){
			case 200: //nvertex
				if (flags[0] == "" || flags[1] == "" || flags[2] == "") {
					return "Please use correct format: nvertex NAME X-VALUE Y-VALUE";
				}

				try {
					std::stof(flags[1]);
					std::stof(flags[2]);
				} catch (const std::invalid_argument& ia) {
					return "Please give me numerical x and y values";
				}

				std::cout << "New vertex " << flags[0] << " at x: " << flags[1] << ", y: " << flags[2];
				return "";
		}
	}
}
