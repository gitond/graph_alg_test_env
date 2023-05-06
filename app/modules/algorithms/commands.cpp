#include <array>
#include <string>
#include "../graphs/graph.h"
#include "dijkstra.h"

// for testing
#include <iostream>

namespace algComms {
	std::string execute(int commandId, std::string commFlags[10], graph& g){
		switch(commandId){
			case 300: // dijkstr
				if (commFlags[1] == "") { return "please use correct format: dijkstr SOURCE DEST"; }

				// Variables
				vertex source;
				vertex dest;

				for (vertex v: g.getVertices()){
					if(v.getName() == commFlags[0]) { source = v; }
					if(v.getName() == commFlags[1]) { dest = v; }
					if(v.getName() == "") { break; }
				}

				std::array<vertex,250> results = dijkstra(g,source,dest);

				g = graph(g.getAdjMatrix(),results,g.length());

				return "";
		}

		return "";
	}
}
