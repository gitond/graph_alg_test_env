#include <string>
#include "../../metaheaders/commstruct.h"
#include "commands.h"

// Command executions
namespace testCommands {
	std::string execute(int commandId){
		switch(commandId){
			case 100: //tdummy
				return "testmod dummy command";
		}
	}
}
