#include <string>
#include <iostream>
#include "vertex.h"

/*
Vertex structure:
private:
	std::string name;
	float posX;
	float posY;
public:
	vertex(std::string cName, float cX, float cY){}	// constructor
*/

// This is the definition for the constructor of vertex.
// The class definition as well as the declarations are in the header "vertex.h"
vertex::vertex(std::string cName, float cX, float cY){
	name = cName;
	posX = cX;
	posY = cY;
};

vertex::vertex(){	// Constructor for "null" vertex for arrays
	name = "";
	posX = 0;
	posY = 0;
}

std::string vertex::getName(){
	return name;
}
