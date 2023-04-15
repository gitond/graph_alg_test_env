#include <string>
#include <iostream>

class vertex {
	private:
		std::string name;
		float posX;
		float posY;
	public:
		vertex(std::string cName, float cX, float cY) {
			name = cName;
			posX = cX;
			posY = cY;

			std::cout << "I'm a vertex \n";
		}
};
