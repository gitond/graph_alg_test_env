#ifndef DIJKSTRA
#define DIJKSTRA

#include "../graphs/graph.h"
#include <array>
#include <iostream>

std::array<vertex,250> dijkstra(graph g, vertex source, vertex dest);

#endif
