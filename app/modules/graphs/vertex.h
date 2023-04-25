#ifndef VERTEXCLASS
#define VERTEXCLASS

#include <string>

class vertex {
	private:
		std::string name;
		float posX;
		float posY;
		int pathStatus;
		int visitedStatus;
	public:
		// Constructors
		vertex(std::string cName, float cX, float cY);
		vertex();

		// Getters & Setters
		std::string getName();
		float getPosX();
		float getPosY();
		int onPath();		// Should return 1 (true) if on path and 0 (false) otherwise
		int isVisited();	// Should return 1 (true) if visited and 0 (false) otherwise
		void setPathStatus(int ps);
		void setVisitedStatus(int vs);
};

#endif
