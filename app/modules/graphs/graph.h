#ifndef GRAPH
#define GRAPH

#include "vertex.h"
#include <array>

class graph {
	private:
		std::array<std::array<float, 250>, 250> adjMatrix; // This limits the graph to contain 1000 vertices max and allocates 4 MB of storage for it.
		std::array<vertex,250> vertices;
		int nullcheck;
		int len;
	public:
		// Constructor
		graph(std::array<std::array<float, 250>, 250> adjMatrix, std::array<vertex,250> vertices, int len);

		// Functions
		float price(vertex v1, vertex v2);
		float maxPrice();
		int length();
		std::array<vertex,100> neighbors(vertex v); // NOTE: Only 100 neighbors get returned
		int isNull();
};

#endif
