#include "dijkstra.h"

// For testing. Either remove it or move it to header file after done.
#include <iostream>

struct visitPrice {
	vertex v;
	float price;
};

struct edgePrice {
	vertex from;
	vertex to;
	float price;
};



// -- DIJKSTRA'S ALGORITHM IMPLEMENTATION -- //

std::array<vertex,250> dijkstra(graph g, vertex s, vertex dest){
	// s is the source vertex. Called s in [2] and lahtosolmu in [1].

	// PSEUDOCODE VARIABLES
	vertex q; // Called q in [2] and kasiteltava in [1].
	std::array<vertex,250> S_DJK; // Called S_DJK in [2] and vieraillut in [1].
	std::array<visitPrice,250> hintaLog; // Called hintaLog in [1]. Does not exist in [2].
	edgePrice minHinta; // Called minHinta in [1]. Does not exist in [2].

	// OUR OWN VARIABLES
	int hLogCounter = 0; // we keep track of how many prices we know.
	int SDJKCounter = 0; // we keep track of how nodes in S_DJK.
	std::array<vertex,250> vertexDataCopy = g.getVertices(); // return a modified version of this

	// --- IMPLEMENTATION --- //
	// Copying vertices of current graph to "visited" datastructure becaus graph_alg_test_env vertices already have a property to store visitation data and we want to use that here instead of saving all visits to separate array.

	q = s; // q is the currently examinend node. In the beginning we want this to be the source.
	q.updateVisitedStatus(1,""); // marking q as visited and the origin of the visit as null

	// Placing the source node in the price datastructure
	hintaLog[hLogCounter].v = q;
	hintaLog[hLogCounter].price = 0;

	while (hLogCounter != g.length()) { // algorithm should stop if all nodes have been examined
		S_DJK[SDJKCounter] = q; // adding current node to visited

		// Setting high minimum price so that iteration finds the smallest price and looping doesn't count problems
		minHinta.from = vertex(); // Calling null vertex constructor
		minHinta.to = vertex();
		minHinta.price = g.maxPrice()+1;

		for (vertex v : S_DJK) { // All nodes already visited
			if (v.getName() == "") { break; } // Null vertex, stop loop

			for (vertex n : g.neighbors(v)){ // All neighbors of all nodes already visited
				if (n.getName() == "") { break; } // Null vertex, stop loop

				//TODO: Continue here

			}
		}

		// Increasing counters
		SDJKCounter++;
		hLogCounter++;
	}


	return vertexDataCopy;
}



// -- DRIVER FOR TESTING -- //

int main() {
	std::cout << "Dijkstra test function \n";

	// Graph to be operated on
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

	const int LENGTH = 7;

	graph eg = graph(am, v2, LENGTH);

	std::cout << dijkstra(eg, v2[1], v2[3])[1].getName() << "\n";

	return 0;
}
