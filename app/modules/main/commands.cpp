#include <string>
#include "../../metaheaders/commstruct.h"
#include "commands.h"

// Command data
/*command comms[2]; // An array of 2 commands

comms[0] = {
	"quit",					// command
	0,					// id
	"Controlled shutdown of program"	// desc
};
comms[1] = {
	"dummy",
	1,
	"Dummy command for testing purposes"
};*/

// Command executions
namespace mainCommands {
	std::string execute(int commandId){
		switch(commandId){
			case 0:	 //quit
				return "quit";
			case 1: //dummy
				return "Dummy command entered.";
		}
	}
}
