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
 * @param[in] graafidata the graph data in which we want to run Dijkstra's algorithm called graafidata in ortutayBSc. Doesn't exist in applSciLawande
 * @paran[in] s the source vertex, called s in applSciLawande and lahtosolmu in ortutayBSc.
 * @param[in] maalisolmu the destination vertex, called maalisolmu in ortutayBSc. Does not exist in applSciLawande.
 * OUTPUTS:
 * @param[out] vertexDataCopy set of vertices in graafidata, modified to include path and visitation data
 * NOTE ABOUT OUTPUT:
 *
 * \note
 * user expected to run graph constructor again outside this function with function return values as vertex set
 *
 * ACADEMIC SOURCES:
 * \cite ortutayBSc
 * \cite applSciLawande
 *
 * NOTE ABOUT SOURCES:
 *
 * \note
 * before Doxygen citation commands can be used CITE_BIB_FILES needs to be setup in Doxygen config
 */
std::array<vertex,250> dijkstra(graph graafidata, vertex s, vertex maalisolmu){

	// VARIABLES
	// Pseudocode:
	std::array<edgePrice,250> S_DJK; // Array containing visited vertices (edgePrice.to), data where they got visited from (edgePrice.from) and the cheapest price. Called S_DJK in applSciLawande and vieraillut in ortutayBSc.
	vertex q; // Contains the vertex we currently want to examine. Called q in applSciLawande and kasiteltava in ortutayBSc.
	float hintaLogQ = 0; // Keeps track of current price. Called hintaLog[v] in ortutayBSc. Does not exist in applSciLawande
	int  polkuOK = 0; // Tells loop 1 (searching algorithm) when to stop. Called polkuOK in ortutayBSc. Does not exist in applSciLawande.
	// Non-pseudocode:
	std::array<edgePrice,250> potential; // Array containing next potential visits, data where they got visited from (edgePrice.from) and the cheapest price
	int SDJKCounter = 0; // we keep track of how many nodes we have visited
	std::string vertexStorage; // we store names of vertices here to make searching for them easier
	std::array<vertex,250> vertexDataCopy = graafidata.getVertices(); // we don't want to use the get vertices function too often for optimization purposes
	int qIndex; // so that it is easy to find currently examined index from dta structures
	std::string parent; // used to store the parent of the current vertex in path construction

	// SETUP
	q = s; // q is the currently examined node. In the beginning we want this to be the source.
	// q into data structure
	for(int i = 0; i < graafidata.length(); i++) {
		if (vertexDataCopy[i].getName() == q.getName()) {
			potential[i].from = vertex();
			potential[i].to = q;
			potential[i].price = hintaLogQ;
		}
	}


	// LOOP 1: VISITING AND EXAMINING VERITCES
	while ((SDJKCounter < graafidata.length() - 1) && (!(polkuOK)) ) { // algorithm should stop if all nodes have been examined. Therefore max no of connections: length -1
		// Adding neighbors of current vertex to be potential visit
		vertexStorage = "";
		for (vertex n : graafidata.neighbors(q)){ // All neighbors of currently visited vertex to easily searchable format
			if (n.getName() == "") { break; } // Null vertex, stop loop

			vertexStorage.append(n.getName().append(","));
		}

		// Marking all unvisited neighbors as potential future visits
		for(int i = 0; i < graafidata.length(); i++) {
			// Doing actions at the indexes of the neighbors of the current vertex
			if ((vertexStorage.find(vertexDataCopy[i].getName().append(",")) != std::string::npos) && (potential[i].to.getName() == "") ) {
				// Neighbor to potential
				potential[i].from = q;
				potential[i].to = vertexDataCopy[i];
				potential[i].price = hintaLogQ + graafidata.price(q,vertexDataCopy[i]);
			}
		}

		// setting as high as possible for upcoming operations
		// WARNING: This value being too low will cause serious issues in programme
		hintaLogQ = graafidata.maxPrice()*2; // Consider changing this to FLT_MAX in the future

		// Current vertex to visited and cheapest potential to new current
		for(int i = 0; i < graafidata.length(); i++) {

			// Finding current vertex in datastructure
			if (vertexDataCopy[i].getName() == q.getName()) {
				// marking current as visited
				S_DJK[i].from = potential[i].from;
				S_DJK[i].to = potential[i].to;
				S_DJK[i].price = potential[i].price;

				// removing current from potential
				potential[i].from = vertex();
				potential[i].to = vertex();
				potential[i].price = 0;
			}

			// Exit loop if current search is destination node
			if (q.getName() == maalisolmu.getName()) {
				polkuOK = 1;
				break;
			}

			// Finding cheapest potential
			if (
				(potential[i].price <= hintaLogQ)
				&&
				(potential[i].to.getName() != "") // excluding null vertices
				&&
				(S_DJK[i].to.getName() == "") // should be unvisited
				){
					qIndex = i;
					hintaLogQ = potential[i].price;
				}
		}

		// if destination found, do not do the next part
		if (polkuOK) { continue; }

		// Making the cheapest potential the next node to examine
		std::cout << "Next search: " << potential[qIndex].to.getName() << "\n";
		q = potential[qIndex].to;

		SDJKCounter++;
	}

	// LOOP 2: CONSTRUCTING VISITATION DATA
	std::cout << potential[qIndex].from.getName() << " -> " << q.getName();

	for(int i = 0; i < graafidata.length(); i++) {
		// Making sure q is in S_DJK
		if (potential[i].to.getName() == q.getName()) {
			S_DJK[i].from = potential[i].from;
			S_DJK[i].to = potential[i].to;
			S_DJK[i].price = potential[i].price;
		}

		if (S_DJK[i].to.getName() != "") { // Visited vertices
			vertexDataCopy[i].updateVisitedStatus(1,S_DJK[i].from.getName());
		}
	}

	// LOOP 3: CONSTRUCTING PATH DATA
/*	int pathLoopI = 0;
	do {
		// Putting current on path
		if (S_DJK[pathLoopI].to.getName() == q.getName()) {
			vertexDataCopy[pathLoopI].setPathStatus(1);
			q = vertex();

			// Parent to next to be checked
			if(S_DJK[pathLoopI].from.getName() != "") {
				q = S_DJK[pathLoopI].from;
				pathLoopI = 0;
			} else { // escaping loop at source
				q = vertex();
			}
		}

		pathLoopI++;
	} while (q.getName() != "");
*/

	// LOOP 3: ATTEMPT 2:
	// Tracing the path from the end to the beginning following the edges from destination to source
	while (1) {

		//When first here, q should be the destination

		// marking q as on path and saving it to vertex data structure
		for(int i = 0; i < graafidata.length(); i++) {
			if (vertexDataCopy[i].getName() == q.getName()) {
				parent = vertexDataCopy[i].getVisitations().substr(0,vertexDataCopy[i].getVisitations().find(",")); // Finding parent of current node
				vertexDataCopy[i].setPathStatus(1); // updating path data to vertex data structure
				break; // no need to loop through the rest of the vertices
			}
		}

		if (parent == "") { break; } // we arrive at the source

		for (vertex v : vertexDataCopy) {
			if (v.getName() == "") { break; } // Null vertex, stop loop

			// Making parent next node to examine
			if (v.getName() == parent){
				q = vertex(v.getName(),v.getPosX(),v.getPosY());
			}
		}

		//break;
	}


	// PRE-RETURN TESTING AREA
//	std::cout << "mtest \n";
//	std::cout << "Name of q:" << q.getName() << "\n";
//	std::cout << graafidata.neighbors(vertexDataCopy[12])[0].getName() << "\n";

	// WANTED GOOD RETURN
	if (polkuOK) { return vertexDataCopy; }

	// UNWANTED EMERGENCY RETURN
	std::cout << "WARNING: Dijkstra's algorithm didn't find path \n";
	std::array<vertex,250> nullVertArray;
	return nullVertArray;
}

/*
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
*/
