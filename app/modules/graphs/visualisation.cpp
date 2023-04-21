#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <stdexcept>

sf::CircleShape dot(int posX, int posY, std::string& labeldata, std::string what2render){
	sf::CircleShape dot(3.f);
	dot.setFillColor(sf::Color::Green);
	dot.setPosition(posX,posY);
	labeldata.append(what2render);
	labeldata.append(",");
	labeldata.append(std::to_string(posX));
	labeldata.append(",");
	labeldata.append(std::to_string(posY-20));
	labeldata.append(",;");
	return dot;
}

sf::VertexArray line(int posX1, int posY1, int posX2, int posY2, std::string& labeldata, std::string what2render){
	sf::VertexArray lines(sf::LinesStrip,2);
	lines[0].position = sf::Vector2f(posX1+2,posY1+2);
	lines[0].color = sf::Color::Green;
	lines[1].position = sf::Vector2f(posX2+2,posY2+2);
	lines[1].color = sf::Color::Green;
	labeldata.append(what2render);
	labeldata.append(",");
	labeldata.append(std::to_string((int)((posX1+posX2)/2)));
	labeldata.append(",");
	labeldata.append(std::to_string((int)((posY1+posY2)/2)));
	labeldata.append(",;");
	return lines;
}

int drawGraph(int dimensionX, int dimensionY){
	try {
		// Text rendering setup
		char current;
		const std::string STOP_CHAR = "~";
		sf::Text text;
		sf::Font font;
		text.setFont(font);
		text.setCharacterSize(12);
		text.setFillColor(sf::Color::Green);
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

		// graphics
		sf::RenderWindow window(sf::VideoMode(dimensionX, dimensionY), "graph_alg_test_env_window");

		sf::CircleShape dotA = dot(200,40,txt2render, "A");
		sf::CircleShape dotB = dot(160,80,txt2render, "B");

		sf::VertexArray AB = line(200,40,160,80,txt2render, "57");
		txt2render.append(STOP_CHAR);

		text.setString(txt2render);
		text.setPosition(200,20);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				window.close();
			}

			window.clear();
			window.draw(dotA);
			window.draw(dotB);
			window.draw(AB);

			while(current != STOP_CHAR[0]){
				level1Pos = 0;
				level2Pos = 0;
				for(int i = 0; i < txt2render.length(); i++){
					current = txt2render[i];
					if (current == ';'){
						currentLabelData = txt2render.substr(level1Pos, i-level1Pos);
						std::cout << currentLabelData << "\n";

						level1Pos = 0;
						level2Pos = 0;
						for(int j = 0; j < currentLabelData.length(); j++){
							current = currentLabelData[j];
							if (current == ','){
								switch(level1Pos){
									case 0:
										currentLabel = currentLabelData.substr(level2Pos, j-level2Pos);
										std::cout << currentLabel << "\n";
										level1Pos++;
										break;
									case 1:
										break;
									case 2:
										break;
								}
								level2Pos = j+1;
							}
						}

						level1Pos = i+1;
					}
				}
			}

			window.draw(text);
			window.display();
		}

		return 0;
	} catch (const std::invalid_argument& ia) {
		return 1;
	}
}

int main(){
	return drawGraph(1280,720);
}
