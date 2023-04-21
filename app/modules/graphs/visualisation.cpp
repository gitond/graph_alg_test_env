#include <SFML/Graphics.hpp>

sf::CircleShape dot(int posX, int posY){
	sf::CircleShape dot(3.f);
	dot.setFillColor(sf::Color::Green);
	dot.setPosition(posX,posY);
	return dot;
}

int drawGraph(int dimensionX, int dimensionY){
	sf::RenderWindow window(sf::VideoMode(dimensionX, dimensionY), "graph_alg_test_env_window");
	sf::CircleShape dotOne = dot(200,40);
	sf::CircleShape dotTwo = dot(160,80);

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
		window.display();
	}

	return 0;
}

int main(){
	return drawGraph(1280,720);
}
