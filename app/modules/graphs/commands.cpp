#include <string>
#include "../../metaheaders/commstruct.h"
#include "commands.h"

// Command executions
namespace graphComms {
	std::string execute(int commandId){
		switch(commandId){
			case 200: //nvertex
				return "created new vertex";
		}
	}
}
