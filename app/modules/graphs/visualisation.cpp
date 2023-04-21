#include <SFML/Graphics.hpp>

sf::CircleShape dot(int posX, int posY){
	sf::CircleShape dot(3.f);
	dot.setFillColor(sf::Color::Green);
	dot.setPosition(posX,posY);
	return dot;
}

sf::VertexArray line(int posX1, int posY1, int posX2, int posY2){
	sf::VertexArray lines(sf::LinesStrip,2);
	lines[0].position = sf::Vector2f(posX1+2,posY1+2);
	lines[0].color = sf::Color::Green;
	lines[1].position = sf::Vector2f(posX2+2,posY2+2);
	lines[1].color = sf::Color::Green;
	return lines;
}

int drawGraph(int dimensionX, int dimensionY){
	sf::RenderWindow window(sf::VideoMode(dimensionX, dimensionY), "graph_alg_test_env_window");
	sf::CircleShape dotOne = dot(200,40);
	sf::CircleShape dotTwo = dot(160,80);

	sf::VertexArray AB = line(200,40,160,80);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
		}

		window.clear();
		window.draw(dotOne);
		window.draw(dotTwo);
		window.draw(AB);
		window.display();
	}

	return 0;
}

int main(){
	return drawGraph(1280,720);
}
