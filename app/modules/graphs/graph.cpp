#include "graph.h"
#include <iostream>

// This is the definition for the constructor of graph.
// The class definition as well as the declarations are in the header "graph.h"
graph::graph(std::array<std::array<float, 250>, 250> am, std::array<vertex,250> v2, int length){
	adjMatrix = am;
	vertices = v2;
	len = length;

	std::cout << "Graph constructor called \n";
}

int main(){
	std::cout << "Graph test function \n";

	std::array<std::array<float, 250>, 250> am;
	std::array<vertex,250> v2;

	v2[0] = vertex("A",1,4);
	v2[1] = vertex("B",1,4);
	v2[2] = vertex("C",1,4);

	graph(am, v2, 3);
	return 0;
}
