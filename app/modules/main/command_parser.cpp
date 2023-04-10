#include <string>
#include <iterator>
#include "command_parser.h"
#include "../../metaheaders/commands_meta.h"

// For testing
#include <iostream>

std::string parse(std::string parsable, command commDS[100][100]){ // where commDS is the command data structure
	int commandId = -1;
	int foundComm = 0;

	// command validation
/*	for(int i = 0; i < std::size(comms); i++){
		if (parsable == comms[i].command){
			commandId = comms[i].id;
			break;
		}
	}*/

	for(int i = 0; i < 100; i++){ 		// For each module
		for(int j = 0; j < 100; j++){	// For each command in module i
			if (parsable == commDS[i][j].command) {
				commandId = commDS[i][j].id;
				foundComm = 1;
				break;
			} else if (commDS[i][j].command == ""){
				break;
			} else {
				continue;
			}
		}
		if (foundComm) {
			break;
		}
	}

	// Describe command behaviour here, return printables or quit message
	switch(commandId){
		case -1:
			return "Error: Command not recognized";
		case 0:	 //quit
			return parsable; // returns quit
		case 1: //dummy
			return "Dummy command entered.";
	}

	return parsable;
}
