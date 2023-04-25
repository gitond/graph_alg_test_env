#include <string>
#include <iostream>
#include "vertex.h"

// -- CONSTRUCTORS -- //
vertex::vertex(std::string cName, float cX, float cY){
	name = cName;
	posX = cX;
	posY = cY;
	pathStatus = 0;
	visitedStatus = 0;
	visitedFrom = "";
};

vertex::vertex(){	// Constructor for "null" vertex for arrays
	name = "";
	posX = 0;
	posY = 0;
	pathStatus = 0;
	visitedStatus = 0;
	visitedFrom = "";
}

// -- GETTERS AND SETTERS -- //
std::string vertex::getName(){
	return name;
}

float vertex::getPosX(){
	return posX;
}

float vertex::getPosY(){
	return posY;
}

int vertex::onPath(){
	return pathStatus;
}

int vertex::isVisited(){
	return visitedStatus;
}

std::string vertex::getVisitations(){
	return visitedFrom;
}

void vertex::setPathStatus(int ps){
	pathStatus = ps; // Not verified anywhere, but should always be 0 or 1
}

void vertex::updateVisitedStatus(int vs, std::string visitCameFrom){
	visitedStatus = vs; // Not verified anywhere, but should always be 0 or 1
	if (visitCameFrom != ""){
		visitedFrom.append(visitCameFrom);
		visitedFrom.append(",");
	}
}
