#include <iostream>
#include <string>
#include "../../metaheaders/commstruct.h"
#include "commands.h"

// Command executions
namespace mainCommands {
	std::string execute(int commandId, command commDS[100][100]){
		switch(commandId){
			case 0:	 //quit
				return "quit";
			case 1: //dummy
				return "Dummy command entered.";
			case 2: //help
				for(int i = 0; i < 100; i++){		// For each module
					for(int j = 0; j < 100; j++){	// For each command in module i
						if (commDS[i][j].command == ""){
							break;
						} else {
							std::cout << commDS[i][j].command << "\t\t" << commDS[i][j].desc << "\n";
						}
					}
				}
				return "----";
		}
	}
}
