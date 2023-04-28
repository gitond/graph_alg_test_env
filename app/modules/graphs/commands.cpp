#include <string>
#include <cstring>
#include "../../metaheaders/commstruct.h"
#include "commands.h"
#include <iostream>
#include <stdexcept>
#include "vertex.h"
#include "rand_mat_gen.h"
#include "visualisation.h"
#include "graph_file_operations.h"
#include <cmath>

// Command executions
namespace graphComms {
	std::string execute(int commandId, std::string flags[10], graph& g){
		std::array<vertex,250> sgv;
		std::array<vertex,100> na;
		std::array<vertex,2> dva;
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
			case 201: //rgraph
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
			case 202: //price
				if (flags[0] == "" || flags[1] == "") {
					return "Please use correct format: price VERTEX_1_NAME VERTEX_2_NAME";
				}

				sgv = g.getVertices();
				ffi++;

				for(int i = 0; i < g.length(); i++){
					if (sgv[i].getName() == flags[0] || sgv[i].getName() == flags[1]){
						dva[ffi] = sgv[i];
						ffi++;
					}
				}

				if (dva[1].getName() == "") { return "ERROR: At least one of the vertices you entered doesn't exist in the graph."; }

				am[0][0] = g.price(dva[0],dva[1]);

				if (am[0][0] == -1) { return ""; } // Error already printed by .price()

				std::cout << "Price betweeen " << dva[0].getName() << " and " << dva[1].getName() << " in graph: " << am[0][0];

				return "";
			case 203: //maxp
				am[0][0] = g.maxPrice();
				if (am[0][0] == -1) { return ""; } // Error already printed by .maxPrice()
				std::cout << "Current maximum price in graph: " << am[0][0];
				return "";
			case 204: //glength
				std::cout << "The current length of the graph is " << g.length();
				return "";
			case 205: //connsto
				if (flags[0] == "") {
					return "Please use correct format: conncto VERTEX_NAME";
				}


				sgv = g.getVertices();
				for(int i = 0; i < g.length(); i++){
					if (sgv[i].getName() == flags[0]){
						dva[0] = sgv[i];
						break;
					}
				}

				if (dva[0].getName() == "") { return "ERROR: The vertex you entered doesn't exist in the graph."; }

				na = g.neighbors(dva[0]);

				if (na[0].getName() == "") {
					/*
						Means array of nullvertices returned from .neighbors
						.neighbors already printed error message
					*/
					return "";
				}

				std::cout << "The neighbors of vertex " << dva[0].getName() << " are: ";

				for(int i = 0; i < 100; i++){
					if (na[i].getName() == "") {
						break;
					} else {
						std::cout << na[i].getName() << " ";
					}
				}

				return "";
			case 206: //visual
				if (flags[0] == ""){
					ffi = drawGraph(1280,720,g,0);
					switch(ffi){
						case 0:
							return "visualising graph";
						case 1:
							return "ERROR: Graph visualisation failed to load font";
						case 2:
							// This should never happen here btw
							return "ERROR: Graph visualisation failed to create image file";
						case 3:
							return "ERROR: Invalid argument exception in graph visualisation";
						default:
							return "ERROR: Unknown error in graph visualisation";
					}
				} else if (flags[0] == "IMF"){
					ffi = drawGraph(1280,720,g,1);
					switch(ffi){
						case 0:
							return "Picture of graph saved to output/image.png (without background)";
						case 1:
							return "ERROR: Graph visualisation failed to load font";
						case 2:
							// This should never happen here btw
							return "ERROR: Graph visualisation failed to create image file";
						case 3:
							return "ERROR: Invalid argument exception in graph visualisation";
						default:
							return "ERROR: Unknown error in graph visualisation";
					}
				} else {
					return "Correct uses of this command are: \n visual \n visual IMF";
				}

				return "";
			case 207: //load
				if (flags[0] == ""){
					return "Please use correct format: load FILE.graph";
				}

				std::cout << "Attempting to load graph from " << flags[0] << "\n";

				g = graphFromFile(flags[0]);

				return "";
		}
	}
}
