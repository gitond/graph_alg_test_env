#include <string>
#include <iterator>
#include "command_parser.h"

// For testing
#include <iostream>

std::string parse(std::string parsable){
	// may need to move command struct definition to separate header file later
	// may need to create metaheader with all project headers later
	struct command {
		std::string command;
		int id;
		//std::string flags[10];	// Max limit of 10 flags, add if needed
		std::string desc;
	};

	command comms[2]; // An array of 2 commands

	int commandId = -1;

	comms[0] = {
		"quit",					// command
		0,					// id
		"Controlled shutdown of program"	// desc
	};
	comms[1] = {
		"dummy",
		1,
		"Dummy command for testing purposes"
	};

	// command validation
	for(int i = 0; i < std::size(comms); i++){
		if (parsable == comms[i].command){
			commandId = comms[i].id;
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