#include <string>
#include <cstring>
#include "../../metaheaders/commstruct.h"
#include "commands.h"
#include <iostream>
#include <stdexcept>
#include "vertex.h"
#include "rand_mat_gen.h"
#include <cmath>

// Command executions
namespace graphComms {
	std::string execute(int commandId, std::string flags[10], graph& g){
		std::array<vertex,250> sgv;
		int ffi = -1;
		std::array<std::array<float, 250>, 250> am;

		switch(commandId){
			case 200: //nvertex
				if (flags[0] == "" || flags[1] == "" || flags[2] == "") {
					return "Please use correct format: nvertex NAME X-VALUE Y-VALUE";
				}

				try {
					sgv = g.getVertices();

					for(int i = 0; i < 250; i++){
						if (sgv[i].getName() == ""){
							ffi = i;
							break;
						}
					}

					if (ffi == -1){ return "Maximum number of vertices reached (250)"; }
					else {
						sgv[ffi] = vertex(flags[0], std::stof(flags[1]), std::stof(flags[2]));
					}

					if (g.isNull() == -1) {
						g = graph(sgv, g.length()+1);
					} else {
						g = graph(g.getAdjMatrix(), sgv, g.length()+1);
					}

				} catch (const std::invalid_argument& ia) {
					return "Please give me numerical x and y values";
				}

				std::cout << "New vertex " << flags[0] << " at x: " << flags[1] << ", y: " << flags[2];
				return "";
			case 201:
				randomizeAdjMatrix(g);
				am = g.getAdjMatrix();

				std::cout << "Created new graph with the following adjacency matrix: \n";

				for(int i = 0; i < g.length(); i++){
					for(int j = 0;j < g.length();j++){
						std::cout << round(am[i][j]) << " ";
					}
					std::cout << "\n";
				}

				return"";
		}
	}
}
