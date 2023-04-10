#include <string>

#ifndef COMMSTRUCT_H
#define COMMSTRUCT_H

struct command {
	std::string command;
	int id;
	//std::string flags[10];	// Max limit of 10 flags, add if needed
	std::string desc;
};

#endif
