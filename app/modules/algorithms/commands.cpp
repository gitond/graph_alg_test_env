#include <string>
#include "../graphs/graph.h"

namespace algComms {
	std::string execute(int commandId, std::string commFlags[10], graph& g){
		switch(commandId){
			case 300:
				return "algComms used";
		}

		return "";
	}
}
