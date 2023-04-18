#include "graph.h"
#include <iostream>

// This is the definition for the constructor of graph.
// The class definition as well as the declarations are in the header "graph.h"
graph::graph(std::array<std::array<float, 250>, 250> am, std::array<vertex,250> v2, int length){
	// Adjacency matrix validation
	int validMatrix = 1;
	for(int i = 0; i < length; i++){
		if (am[i][i] != 0) { validMatrix = 0; }	// weights between v1,v1 should always be 0
		if (v2[i].getName() == "") { validMatrix = -1; } // checking if length is not too long
		for(int j = 0; j < length; j++){
			if (am[i][j] != am[j][i]) { validMatrix = 0; } // weights between v1,v2 = v2,v1 always
		}
	}

	if (v2[length].getName() != "") { validMatrix = -2; } // checking if length is not too short

	switch (validMatrix) {
		case 1:	// Matrix valid
			adjMatrix = am;
			vertices = v2;
			len = length;
			nullcheck = 0;

			std::cout << "Graph constructor successful \n";
			break;
		case 0:
			std::cout << "Graph constructor failed! Invalid matrix. \n";
			break;
		case -1:
			std::cout << "Graph constructor failed! Incorrect length parameter (Too long). \n";
			break;
		case -2:
			std::cout << "Graph constructor failed! Incorrect length parameter (Too short). \n";
	}
}

// Null constructor
graph::graph(){ nullcheck = 1; }

// Constructor with no adjMatrix
// Used as container for vertex array in command passthrough
graph::graph(std::array<vertex,250> verts, int length){
	vertices = verts;
	len = length;
	nullcheck = -1;
}

float graph::price(vertex v1, vertex v2){
	switch (nullcheck) {
		case 0:{
			int v1index = -1;
			int v2index = -1;

			for(int i = 0; i < len; i++){
				if (vertices[i].getName() == v1.getName()) { v1index = i; }
				if (vertices[i].getName() == v2.getName()) { v2index = i; }
			}

			if (v1index == -1 || v2index == -1) {
				std::cout << "ERROR: graph.price(vertex v1, vertex v2) failed, because v1 or v2 not found in graph, returning -2 \n";
				return -2;
			}

			return adjMatrix[v1index][v2index];
		}
		default:
			std::cout << "ERROR: attempting to run graph.price() on invalid graph, returning -1 \n";
			return -1;
	}
}

float graph::maxPrice(){
	float currentMaximum = 0;

	if (nullcheck != 0) {
		std::cout << "ERROR: attempting to run graph.maxPrice() on invalid graph, returning -1 \n";
		return -1;
	}

	for(int i = 0; i < len; i++){
		for(int j = len; j >= i; j--){
			if (adjMatrix[i][j] > currentMaximum) { currentMaximum = adjMatrix[i][j]; }
		}
	}

	return currentMaximum;
}

int graph::length(){
	switch (nullcheck) {
		case 1:
			std::cout << "ERROR: attempting to run graph.length() on nullgraph, returning -1 \n";
			return -1;
		default:
			return len;
	}
}

std::array<vertex, 100> graph::neighbors(vertex v){
	std::array<vertex, 100> returnable;

	if (nullcheck == -1) {
		std::cout << "ERROR: attempting to run graph.neighbor() on graph with no adjacency matrix (vertex array container), returning nullarray of vertices \n";
		return returnable;
	}

	int vIndex = -1;
	int thNeighbor = 0;

	// looking for vertex v in graph
	for(int i = 0; i < len; i++){
		if (vertices[i].getName() == v.getName()){
			vIndex = i;
			break;
		}
	}

	// if a vertex n is the neighbor of v, adjMatrix[vIndex][nIndex] will have a nonzero value
	if (vIndex != -1){
		for(int i = 0; i < len; i++){
			if (adjMatrix[vIndex][i] != 0){
				returnable[thNeighbor] = vertices[i];
				thNeighbor++;
			}
		}
	} else {
		std::cout << "ERROR: graph.neighbors(vertex v) did not find v in graph. Returning nullarray of vertices. \n";
	}

	return returnable;
}

int graph::isNull(){ return nullcheck; }

/*
int main(){
	std::cout << "Graph test function \n";

	std::cout << "Constructor test \n";

	std::array<std::array<float, 250>, 250> am;
	std::array<vertex,250> v2;

	am[0][0] = 0;	am[0][1] = 1;	am[0][2] = 1;	am[0][3] = 0;	am[0][4] = 0;	am[0][5] = 0;	am[0][6] = 0;
	am[1][0] = 1;	am[1][1] = 0;	am[1][2] = 0;	am[1][3] = 2;	am[1][4] = 1;	am[1][5] = 0;	am[1][6] = 0;
	am[2][0] = 1;	am[2][1] = 0;	am[2][2] = 0;	am[2][3] = 2;	am[2][4] = 0;	am[2][5] = 1;	am[2][6] = 0;
	am[3][0] = 0;	am[3][1] = 2;	am[3][2] = 2;	am[3][3] = 0;	am[3][4] = 0;	am[3][5] = 0;	am[3][6] = 3;
	am[4][0] = 0;	am[4][1] = 1;	am[4][2] = 0;	am[4][3] = 0;	am[4][4] = 0;	am[4][5] = 0;	am[4][6] = 2;
	am[5][0] = 0;	am[5][1] = 0;	am[5][2] = 1;	am[5][3] = 0;	am[5][4] = 0;	am[5][5] = 0;	am[5][6] = 2;
	am[6][0] = 0;	am[6][1] = 0;	am[6][2] = 0;	am[6][3] = 3;	am[6][4] = 2;	am[6][5] = 2;	am[6][6] = 0;

	v2[0] = vertex("A",1,4);
	v2[1] = vertex("B",0,3);
	v2[2] = vertex("C",2,3);
	v2[3] = vertex("D",1,2);
	v2[4] = vertex("E",0,1);
	v2[5] = vertex("F",2,1);
	v2[6] = vertex("H",1,0);

	const int length = 7;

	v2[length+1] = vertex("G",10,10); // fake

	graph eg = graph(am, v2, length);

	std::cout << ".price() test \n";
	std::cout << ".price() of A and A: " << eg.price(v2[0],v2[0]) << "\n";
	std::cout << ".price() of A and B: " << eg.price(v2[0],v2[1]) << "\n";
	std::cout << ".price() of A and nonexistent: \n" << eg.price(v2[0],v2[length+1]) << "\n";

	std::cout << ".maxPrice() test \n";
	std::cout << ".maxPrice() of example graph: " << eg.maxPrice() << "\n";

	std::cout << ".length() test \n";
	std::cout << ".length() of example graph: " << eg.length() << "\n";

	std::cout << ".neighbors() test \n";
	std::array<vertex,100> neighborTest = eg.neighbors(v2[3]);
	for(vertex neighbor : neighborTest){
		if (neighbor.getName() == ""){ break; }
		std::cout << neighbor.getName() << " is a neighbor of " << v2[3].getName() << "\n";
	}

	std::cout << "Nullgraph test \n";
	graph ng = graph();
	std::cout << ng.price(v2[0],v2[1]) << "\n";
	std::cout << ng.maxPrice() << "\n";
	std::cout << ng.length() << "\n";
	std::array<vertex,100> ngn = ng.neighbors(v2[0]);
	(eg.isNull()) ? std::cout << "Example graph is null (BAD OUTCOME) \n" : std::cout << "Example graph is not null (GOOD OUTCOME) \n";
	(ng.isNull()) ? std::cout << "Nullgraph is null (GOOD OUTCOME) \n" : std::cout << "Nullgraph is not null (BAD OUTCOME) \n";

	std::cout << "Testing graph without adjacency martix \n";
	graph gwam = graph(v2, length);
	std::cout << gwam.price(v2[0],v2[1]) << "\n";
	std::cout << gwam.maxPrice() << "\n";
	std::cout << gwam.length() << "\n";
	std::array<vertex,100> gwamn = gwam.neighbors(v2[0]);
	(gwam.isNull() == 1) ? std::cout << "Graph without adjacency matrix is null (BAD OUTCOME) \n" : std::cout << "Graph without adjacency matrix is not null (GOOD OUTCOME) \n";

	return 0;
}
*/
