#include "graph.h"
#include <iostream>

// This is the definition for the constructor of graph.
// The class definition as well as the declarations are in the header "graph.h"
graph::graph(std::array<std::array<float, 250>, 250> am, std::array<vertex,250> v2, int length){
	// Adjacency matrix validation
	int validMatrix = 1;
	for(int i = 0; i < length; i++){
		if (am[i][i] != 0) { validMatrix = 0; }	// weights between v1,v1 should always be 0
		for(int j = 0; j < length; j++){
			if (am[i][j] != am[j][i]) { validMatrix = 0; } // weights between v1,v2 = v2,v1 always
		}
	}

	if (validMatrix) {
		adjMatrix = am;
		vertices = v2;
		len = length;

		std::cout << "Graph constructor successful \n";
	} else {
		std::cout << "Graph constructor failed! Invalid matrix.";
	}
}

int main(){
	std::cout << "Graph test function \n";

	std::array<std::array<float, 250>, 250> am;
	std::array<vertex,250> v2;

	am[0][0] = 0;	am[0][1] = 1;	am[0][2] = 1;
	am[1][0] = 1;	am[1][1] = 0;	am[1][2] = 0;
	am[2][0] = 1;	am[2][1] = 0;	am[2][2] = 0;

	v2[0] = vertex("A",1,4);
	v2[1] = vertex("B",1,4);
	v2[2] = vertex("C",1,4);

	graph(am, v2, 3);
	return 0;
}
