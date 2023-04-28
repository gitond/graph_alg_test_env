#include "graph_file_operations.h"

enum parseMode {
	VERTEX,
	MATRIX
};

graph graphFromFile(std::string file){

	// File input
	std::ifstream filein(file);

	// Checking if file exists
	if(!filein) {
		std::cout << "ERROR: Problem with loading file " << file << " , please check if file exists! \n";
	}

	// Variables for graph constructor
	std::array<std::array<float, 250>, 250> adjMatrix;
	std::array<vertex,250> vertices;
	int matrixRowNo = 0;

	// File parsing
	try {
		parseMode currentPM = VERTEX;
		int pos;
		int vertexParsingIterator;
		std::string currVertName;
		float currVertX;
		float currVertY;
		int MatrixColumnNo;

		for (std::string line; std::getline(filein,line);){
			pos = 0;
			if (line == "-----") {
				currentPM = MATRIX;
				matrixRowNo = 0;
				continue;
			}
			switch (currentPM) {
				case VERTEX:
					vertexParsingIterator = 0;
					for(int i = 0; i <= line.size(); i++){
						if (line[i] == ',' || i == line.size()){
							switch(vertexParsingIterator){
								case 0:
									currVertName = line.substr(pos,i-pos);
									pos = i+1;
									break;
								case 1:
									currVertX = std::stof(line.substr(pos,i-pos));
									pos = i+1;
									break;
								case 2:
									currVertY = std::stof(line.substr(pos,i-pos));
							}
							vertexParsingIterator++;
						}
					}
					vertices[matrixRowNo] = vertex(currVertName,currVertX,currVertY);
					matrixRowNo++;
					break;
				case MATRIX:
					MatrixColumnNo = 0;
					for(int i = 0; i <= line.size(); i++){
						if (line[i] == ',' || i == line.size()){
							adjMatrix[matrixRowNo][MatrixColumnNo] = std::stof(line.substr(pos,i-pos));
							//std::cout << adjMatrix[matrixRowNo][i] << " ";
							MatrixColumnNo++;
							pos = i+1;
						}
					}
					matrixRowNo++;
			}
		}
	} catch (const std::invalid_argument& ia) {
		std::cout << "ERROR: Invalid argument detected in graph loader.";
		return graph();
	}

	return graph(adjMatrix,vertices,matrixRowNo);

}

int main() {
	graph g = graphFromFile("planning/file_format_plan/example.graph");
	return 0;
}
