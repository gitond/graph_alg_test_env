#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <stdexcept>
#include <array>
#include "graph.h"

enum renderMode {
	DEFAULT,
	PATH,
	SEARCHED
};

sf::CircleShape dot(int posX, int posY, std::string& labeldata, std::string what2render){
	sf::CircleShape dot(3.f);
	dot.setFillColor(sf::Color::White);
	dot.setPosition(posX,posY);
	labeldata.append(what2render);
	labeldata.append(",");
	labeldata.append(std::to_string(posX));
	labeldata.append(",");
	labeldata.append(std::to_string(posY-20));
	labeldata.append(",;");
	return dot;
}

sf::VertexArray line(int posX1, int posY1, int posX2, int posY2, std::string& labeldata, std::string what2render, renderMode rm){
	sf::VertexArray lines(sf::LinesStrip,2);
	lines[0].position = sf::Vector2f(posX1+2,posY1+2);
	lines[1].position = sf::Vector2f(posX2+2,posY2+2);
	labeldata.append(what2render);
	labeldata.append(",");
	labeldata.append(std::to_string((int)(((posX1+posX2)/2)-10)));
	labeldata.append(",");
	labeldata.append(std::to_string((int)(((posY1+posY2)/2)-20)));
	labeldata.append(",;");

	switch(rm){
		case DEFAULT:
			lines[0].color = sf::Color::White;
			lines[1].color = sf::Color::White;
			break;
		case PATH:
			lines[0].color = sf::Color::Red;
			lines[1].color = sf::Color::Red;
			break;
		case SEARCHED:
			lines[0].color = sf::Color::Blue;
			lines[1].color = sf::Color::Blue;
	}

	return lines;
}

int drawGraph(int dimensionX, int dimensionY, graph g){
	try {
		// Text rendering setup
		char current;
		const std::string STOP_CHAR = "~";
		sf::Text text;
		sf::Font font;
		text.setFont(font);
		text.setCharacterSize(12);
		text.setFillColor(sf::Color::White);
		std::string txt2render = "";
		std::string currentLabelData;
		std::string currentLabel;
		int currentLabelPosX;
		int currentLabelPosY;
		int level1Pos;
		int level2Pos;
		if(!font.loadFromFile("assets/fonts/LiberationMono-Regular.ttf")){
			std::cout << "visualisation.cpp couldn't load font \n";
			return 1;
		}

		// graph data variables
		std::array<sf::CircleShape, 250> vertexGraphicObjects;
		std::array<sf::VertexArray, 10000> currentVertexConnections; // max number of neighbors: 100²
		int NOVertices = 0;

		// --- GRAPHICS --- //
		sf::RenderWindow window(sf::VideoMode(dimensionX, dimensionY), "graph_alg_test_env_window");

		// vertices to renderables
		for(int i = 0; i < g.length(); i++){
			vertexGraphicObjects[i] = dot(g.getVertices()[i].getPosX(),g.getVertices()[i].getPosY(),txt2render,g.getVertices()[i].getName());
		}

		// edges to renderables from neighbor data
		int j;
		int neighborIndex;
		for(int i = 0; i < g.length(); i++){
			j = 0;
			for (vertex neighbor : g.neighbors(g.getVertices()[i])){
				for (int k = 0; k < g.length(); k++){
					if (g.getVertices()[k].getName() == neighbor.getName()){
						neighborIndex = k;
						break;
					}
				}
				if (neighbor.getName() == ""){ // Null vertex means no more neighbors
					NOVertices += j;
					break;
				} else {
					if (g.getVertices()[i].onPath() && neighbor.onPath()) {
						currentVertexConnections[NOVertices + j] = line(g.getVertices()[i].getPosX(),g.getVertices()[i].getPosY(),neighbor.getPosX(),neighbor.getPosY(),txt2render, std::to_string((int)(g.getAdjMatrix()[i][neighborIndex])), PATH);
					} else if (g.getVertices()[i].isVisited() && neighbor.isVisited()) {
						currentVertexConnections[NOVertices + j] = line(g.getVertices()[i].getPosX(),g.getVertices()[i].getPosY(),neighbor.getPosX(),neighbor.getPosY(),txt2render, std::to_string((int)(g.getAdjMatrix()[i][neighborIndex])), SEARCHED);
					} else {
						currentVertexConnections[NOVertices + j] = line(g.getVertices()[i].getPosX(),g.getVertices()[i].getPosY(),neighbor.getPosX(),neighbor.getPosY(),txt2render, std::to_string((int)(g.getAdjMatrix()[i][neighborIndex])), DEFAULT);
					}
				}
				j++;
			}
		}

		txt2render.append(STOP_CHAR);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				window.close();
			}

//			window.clear();	// If you want to use this, figure out a way to draw all text on each loop

			// Rendering all vertices
			for(int i = 0; i < g.length(); i++){
				window.draw(vertexGraphicObjects[i]);
			}

			// Rendering all edges
			for(int i = 0; i < NOVertices; i++){
				window.draw(currentVertexConnections[i]);
			}

			// Code for rendering text on screen
			while(current != STOP_CHAR[0]){
				level1Pos = 0;
				level2Pos = 0;
				for(int i = 0; i < txt2render.length(); i++){
					current = txt2render[i];
					if (current == ';'){
						currentLabelData = txt2render.substr(level1Pos, i-level1Pos);

						level1Pos = 0;
						level2Pos = 0;
						for(int j = 0; j < currentLabelData.length(); j++){
							current = currentLabelData[j];
							if (current == ','){
								switch(level1Pos){
									case 0:
										currentLabel = currentLabelData.substr(level2Pos, j-level2Pos);
										level1Pos++;
										break;
									case 1:
										currentLabelPosX = stoi(currentLabelData.substr(level2Pos, j-level2Pos));
										level1Pos++;
										break;
									case 2:
										currentLabelPosY = stoi(currentLabelData.substr(level2Pos, j-level2Pos));
										break;
								}
								level2Pos = j+1;
							}
						}

						text.setString(currentLabel);
						text.setPosition(currentLabelPosX,currentLabelPosY);
						window.draw(text);

						level1Pos = i+1;
					}
				}
			}

			window.display();
		}

		return 0;
	} catch (const std::invalid_argument& ia) {
		return 1;
	}
}

int main(){
	// Test graph
	std::array<std::array<float, 250>, 250> am;
	std::array<vertex,250> v2;
	am[0][0] = 0;	am[0][1] = 1;	am[0][2] = 1;	am[0][3] = 0;	am[0][4] = 0;	am[0][5] = 0;	am[0][6] = 0;
	am[1][0] = 1;	am[1][1] = 0;	am[1][2] = 0;	am[1][3] = 2;	am[1][4] = 1;	am[1][5] = 0;	am[1][6] = 0;
	am[2][0] = 1;	am[2][1] = 0;	am[2][2] = 0;	am[2][3] = 2;	am[2][4] = 0;	am[2][5] = 1;	am[2][6] = 0;
	am[3][0] = 0;	am[3][1] = 2;	am[3][2] = 2;	am[3][3] = 0;	am[3][4] = 0;	am[3][5] = 0;	am[3][6] = 3;
	am[4][0] = 0;	am[4][1] = 1;	am[4][2] = 0;	am[4][3] = 0;	am[4][4] = 0;	am[4][5] = 0;	am[4][6] = 2;
	am[5][0] = 0;	am[5][1] = 0;	am[5][2] = 1;	am[5][3] = 0;	am[5][4] = 0;	am[5][5] = 0;	am[5][6] = 2;
	am[6][0] = 0;	am[6][1] = 0;	am[6][2] = 0;	am[6][3] = 3;	am[6][4] = 2;	am[6][5] = 2;	am[6][6] = 0;
	v2[0] = vertex("A",140,440);
	v2[1] = vertex("B",40,340);
	v2[2] = vertex("C",240,340);
	v2[3] = vertex("D",140,240);
	v2[4] = vertex("E",40,140);
	v2[5] = vertex("F",240,140);
	v2[6] = vertex("H",140,40);

	v2[0].setVisitedStatus(1);
	v2[1].setVisitedStatus(1);
	v2[2].setVisitedStatus(1);
	v2[3].setVisitedStatus(1);
	v2[4].setVisitedStatus(1);
	v2[6].setVisitedStatus(1);

	v2[4].setPathStatus(1);
	v2[6].setPathStatus(1);

	const int LENGTH = 7;
	graph eg = graph(am, v2, LENGTH);

	// drawing graph
	return drawGraph(1280,720,eg);
}
