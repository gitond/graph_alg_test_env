#include "graph.h"
#include <random>
#include <iostream>

void randomizeAdjMatrix(graph& target){ // Changes existing graph, no return value!
	std::array<std::array<float, 250>, 250> generatedMatrix;
	std::default_random_engine rng;
	std::uniform_real_distribution<float> range(0.0,9.9);
	float current;

	switch(target.isNull()) {
		case 1:
			std::cout << "ERROR: attempting to randomize adjacency matrix of nullgraph \n";
			break;
		default:
			for(int i = 0; i < target.length(); i++){
				generatedMatrix[i][i] = 0;
				for(int j = target.length()-1; j > i; j--){
					current = range(rng);
					generatedMatrix[i][j] = current;
					generatedMatrix[j][i] = current;
				}
			}

			target = graph(generatedMatrix,target.getVertices(),target.length());
	}
}

/*
int main() {
	std::array<vertex,250> v2;

	v2[0] = vertex("A",1,4);
	v2[1] = vertex("B",0,3);
	v2[2] = vertex("C",2,3);
	v2[3] = vertex("D",1,2);
	v2[4] = vertex("E",0,1);
	v2[5] = vertex("F",2,1);
	v2[6] = vertex("H",1,0);

	graph eg = graph(v2, 7);

	randomizeAdjMatrix(eg);

	std::cout << ".maxPrice() of example graph: " << eg.maxPrice() << "\n";
}
*/
