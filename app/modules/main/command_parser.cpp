#include <string>
#include <iostream>
#include <iterator>
#include "command_parser.h"
#include "../../metaheaders/commands_meta.h"

std::string parse(std::string parsable, command commDS[100][100]){ // where commDS is the command data structure
	int commandId = -1;
	int foundComm = 0;
	std::string parsedComm = parsable;

	std::string commFlags[10];
	for (int flag = 0; flag < 10; flag++){ commFlags[flag] = std::string(""); }

	// separating input to command and flags
	int pos = 0;
	int thMember = 0;
	for (int i = 0; i <= parsable.size(); i++){
		if (parsable[i] == ' ' || i == parsable.size()){
			if (thMember == 0){
				parsedComm = parsable.substr(pos, i-pos);
			} else {
				commFlags[thMember-1] = std::string(parsable.substr(pos, i-pos));
			}
			pos = i+1;
			thMember++;
		}
	}

	// command validation
	for(int i = 0; i < 100; i++){ 		// For each module
		for(int j = 0; j < 100; j++){	// For each command in module i
			if (parsedComm == commDS[i][j].command) {
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

	// --- COMMAND PASSTHROUGH --- //
	// Passing commands through to execution environment of each module
	if(commandId < 0){
		return "Error: Command not recognized";
	} else if (0 <= commandId && commandId <= 99) {
		return mainCommands::execute(commandId, commDS);
	} else if (100 <= commandId && commandId <= 199) {
		return testCommands::execute(commandId);
	} else { // range 200 - 299
		return graphComms::execute(commandId, commFlags);
	}

	return "Error: Command ID could not be handled by command parser";
}
