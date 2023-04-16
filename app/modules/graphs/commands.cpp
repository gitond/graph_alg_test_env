#include <string>
#include <cstring>
#include "../../metaheaders/commstruct.h"
#include "commands.h"
#include <iostream>

// Command executions
namespace graphComms {
	std::string execute(int commandId, std::string flags[10]){

		switch(commandId){
			case 200: //nvertex
				if (flags[0] == "" || flags[1] == "" || flags[2] == "") {
					return "Please use correct format: nvertex NAME X-VALUE Y-VALUE";
				}
				std::cout << "New vertex " << flags[0] << " at x: " << flags[1] << ", y: " << flags[2];
				return "";
		}
	}
}
