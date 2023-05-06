#include "dijkstra.h"

// Structs used by algorithm
struct visitPrice {
	vertex v;
	float price;
};
struct edgePrice {
	vertex from;
	vertex to;
	float price;
};



/**
 * DIJKSTRA'S ALGORTIHM IMPLEMENTATION
 * Implementation of Dijkstra's algorithm that works with the graph class
 * defined in app/modules/graphs/graph.cpp. Finds the path in a graph between
 * the source and destination vertices
 * INPUTS:
 * @param[in] graafidata the graph data in which we want to run Dijkstra's algorithm called graafidata in [1]. Doesn't exist in [2]
 * @paran[in] s the source vertex, called s in [2] and lahtosolmu in [1].
 * @param[in] maalisolmu the destination vertex, called maalisolmu in [1]. Does not exist in [2].
 * OUTPUTS:
 * @param[out] vertexDataCopy set of vertices in graafidata, modified to include path and visitation data
 * NOTE:
 * \note
 * user expected to run graph constructor again outside this function with function return values as vertex set
 */
std::array<vertex,250> dijkstra(graph graafidata, vertex s, vertex maalisolmu){
	// PSEUDOCODE VARIABLES
	vertex q; // Called q in [2] and kasiteltava in [1].
	std::array<vertex,250> S_DJK; // Called S_DJK in [2] and vieraillut in [1].
	std::array<visitPrice,250> hintaLog; // Called hintaLog in [1]. Does not exist in [2].
	float hintaLogV = 0; // Called hintaLog[v] in [1]. Does not exist in [2]
	edgePrice minHinta; // Called minHinta in [1]. Does not exist in [2].
	int  polkuOK = 0; // Called polkuOK in [1]. Does not exist in [2].

	// NON-PSEUDOCODE VARIABLES
	int hLogCounter = 0; // we keep track of how many prices we know.
	int SDJKCounter = 0; // we keep track of how nodes in S_DJK.
	std::array<vertex,250> vertexDataCopy; // return a modified version of this
	graph updG; // updatable graph
	int nVisited;
	std::string parent; // used to store the parent of the current vertex in path construction

	// TESTING AREA
//	vertexDataCopy[0].updateVisitedStatus(1,"B");
//	graph
/*	if (vertexDataCopy[0].getVisitations().find(s.getName()) == std::string::npos) {
		std::cout << "Didn't find " << s.getName() << "\n";
	 }
*/
	// --- IMPLEMENTATION --- //
	// Copying vertices of current graph to "visited" datastructure becaus graph_alg_test_env vertices already have a property to store visitation data and we want to use that here instead of saving all visits to separate array.
	vertexDataCopy = graafidata.getVertices();

	q = s; // q is the currently examinend node. In the beginning we want this to be the source.
	q.updateVisitedStatus(1,""); // marking q as visited and the origin of the visit as null

	// Placing the source node in the price datastructure
	hintaLog[hLogCounter].v = q;
	hintaLog[hLogCounter].price = 0;
	hLogCounter++;

	while (SDJKCounter < graafidata.length() - 1) { // algorithm should stop if all nodes have been examined. Therefore max no of connections: length -1
		S_DJK[SDJKCounter] = q; // adding current node to visited

		// putting q into the updateable graph data structure
		// First modifying vertex data copy
		for(int i = 0; i < graafidata.length(); i++) {
			if (vertexDataCopy[i].getName() == q.getName()) {
				vertexDataCopy[i] = q; // replacing source vertex with updated source vertex
				break; // no need to loop through the rest of the vertices once the source has been found.
			}
		}

		if (polkuOK) { break; } // If path found, do not continue

		updG = graph(graafidata.getAdjMatrix(), vertexDataCopy, graafidata.length()); // Saving modified vertex data inro graph

		// Setting high minimum price so that iteration finds the smallest price and looping doesn't count problems
		minHinta.from = vertex(); // Calling null vertex constructor
		minHinta.to = vertex();
		minHinta.price = graafidata.maxPrice()+1;

		for (vertex v : S_DJK) { // All nodes already visited
			if (v.getName() == "") { break; } // Null vertex, stop loop

			hintaLogV = 0; // previous values shouldn't affect performance

			// Getting price data for current vertex
			for (visitPrice priceData : hintaLog){
				if (priceData.v.getName() == "") { break; } // Null vertex, stop loop
				if (priceData.v.getName() == v.getName()) {
					hintaLogV = priceData.price;
					break; // price data found, no reason to loop through the rest of the price data
				}
			}

			for (vertex n : updG.neighbors(v)){ // All neighbors of all nodes already visited
				if (n.getName() == "") { break; } // Null vertex, stop loop

				// Do not check visited vertices
				nVisited = 0; // Unvisited by default
				for (vertex visited : S_DJK) {
					if (visited.getName() == "") { break; } // Null vertex, stop loop
					if (n.getName() == visited.getName()){
						nVisited = 1;
						break; // No need to loop through the rest
					}
				}

				if (
					// Check if connection between neighbors already exists
					(n.getVisitations().find(v.getName()) == std::string::npos)
					&&
					// Check if possible connection between neighbors smaller than current minimum
					(hintaLogV + graafidata.price(v,n) < minHinta.price)
					&&
					// Check if neighbor is unvisited
					(!(nVisited))
					){
						// Update minimum price accordingly
						minHinta.from = v;
						minHinta.to = n;
						minHinta.price = hintaLogV + graafidata.price(v,n);

						// Debugging
						//std::cout << "Updated minimum price. From: " << minHinta.from.getName() << " , to: " << minHinta.to.getName() << " , costing : " << minHinta.price << "\n";
					}
			}
		}
		// Updating price data srtucture
		hintaLog[hLogCounter].v = minHinta.to;
		hintaLog[hLogCounter].price = minHinta.price;

		// Updating node to be examined
		q = minHinta.to; // The next node to be examined
		q.updateVisitedStatus(1,minHinta.from.getName()); // Origin of visit of next node to be examined
		// NOTE: all this gets saved to the relevant datastructures at the beginning of the loop

		// Debug
		std::cout << "Added edge " << minHinta.from.getName() << " - " << minHinta.to.getName() << "\n";

		// If path is found, stop looking after updating relevant data into data structures (beginning of loop).
		if (q.getName() == maalisolmu.getName()){
			std::cout << "Path from " << s.getName() << " to " << maalisolmu.getName() << " found \n";

			polkuOK = 1;
		}

		// Increasing counters
		SDJKCounter++;
		hLogCounter++;
	}

	// PATH CONSTRUCTION
	if (polkuOK) {
//		parent = "    "; // We assume "    " is not the name of any node. NOTE: If it is this code breaks. Document this if you ever write proper documentation

		// Tracing the path from the end to the beginning following the edges from destination to source
		while (polkuOK) {

			//When first here, q should be the destination

			// marking q as on path and saving it to vertex data structure
			for(int i = 0; i < graafidata.length(); i++) {
				if (vertexDataCopy[i].getName() == q.getName()) {
					parent = vertexDataCopy[i].getVisitations().substr(0,vertexDataCopy[i].getVisitations().find(",")); // Finding parent of current node
					q.setPathStatus(1);
					vertexDataCopy[i] = q; // updating path data to vertex data structure
					break; // no need to loop through the rest of the vertices
				}
			}

			if (parent == "") { break; } // we arrive at the source

			for (vertex v : vertexDataCopy) {
				if (v.getName() == "") { break; } // Null vertex, stop loop

				// Making parent next node to examine
				if (v.getName() == parent){
					q = vertex(v.getName(),v.getPosX(),v.getPosY());
					q.updateVisitedStatus(1,v.getVisitations().substr(0,v.getVisitations().find(",")));
				}
			}
		}
		// path data and visited data from algorithm saved to datastructure we return.
		return vertexDataCopy;
	}

	// in case path not found we return an array of nullvertices
	std::array<vertex,250> nullVertArray;
	return nullVertArray;

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

	if (dijkstra(eg, v2[1], v2[6])[4].isVisited()) {
		std::cout << "E is on path \n";
	}

	return 0;
}
