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

	// Passing commands through to execution environment of each module
	if(commandId < 0){
		return "Error: Command not recognized";
	} else {
		return mainCommands::execute(commandId);
	}

	return "Error: Command ID could not be handled by command parser";
}
