#include <string>
#include "../../metaheaders/commstruct.h"
#include "commands.h"

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
