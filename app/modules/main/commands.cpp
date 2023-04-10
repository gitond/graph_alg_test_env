#include "../../metaheaders/commstruct.h"

command comms[2]; // An array of 2 commands

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
