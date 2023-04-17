#ifndef VERTEXCLASS
#define VERTEXCLASS

#include <string>

class vertex {
	private:
		std::string name;
		float posX;
		float posY;
	public:
		vertex(std::string cName, float cX, float cY);
		vertex();
		std::string getName();
};

#endif
