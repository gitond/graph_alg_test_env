#ifndef VERTEXCLASS
#define VERTEXCLASS

#include <string>
#include <array>

class vertex {
	private:
		std::string name;
		float posX;
		float posY;
		int pathStatus;
		int visitedStatus;
		std::string visitedFrom;
//		std::array<std::string, 100> visitedFrom;
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
		std::string getVisitations();
		void setPathStatus(int ps);

		// Functions
		void updateVisitedStatus(int vs, std::string visitCameFrom);

};

#endif
