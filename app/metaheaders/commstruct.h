#include <string>

struct command {
	std::string command;
	int id;
	//std::string flags[10];	// Max limit of 10 flags, add if needed
	std::string desc;
};
