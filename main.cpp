// SFML IS GREAT
// INSTALL BLOWS

#include <iostream>
#include "OrbitalMechanics.h"
#include "SpaceObject.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include <vector>
#include <format>
#include <string>


int main() {

	unsigned int width = 720;
	unsigned int height = 720;
	double simulationSpace = 25000000.0;
	int satRad = 2;
	int centerX = width / 2;
	int centerY = height / 2;


	OrbitalMechanics model;

	std::vector <sf::CircleShape> drawCircles;

	sf::Mouse mickey;
	sf::Vector2i mousePos;
	sf::RenderWindow window(sf::VideoMode(width, height), "Space Object Tracker");
	double screenRatio = simulationSpace/width; //15 million meters divided by screen width 1024 == ratio of simulated meters to screen pixels
	int earthRad = model.EARTHR / screenRatio;
	std::cout << earthRad;
	sf::CircleShape earth(earthRad);
	earth.setPosition(width / 2 - (earthRad), height / 2 - (earthRad));
	sf::Event e;
	sf::Text pos;

	pos.setCharacterSize(20);
	pos.setFillColor(sf::Color::White);
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "Font read error.";
		return 0;
	}

	pos.setFont(font);
	pos.setPosition(1024-100, 0+20);


	SpaceObject sputnik = SpaceObject("Sputnik", 1000);

	sf::CircleShape sputnikDot(satRad);
	sputnikDot.setFillColor(sf::Color::Blue);
	sputnikDot.setPosition(centerX + (int)(sputnik.eciposition[0] / screenRatio), centerY);

	drawCircles.push_back(earth);
	drawCircles.push_back(sputnikDot);




	while (window.isOpen()) {

		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}
		mousePos = mickey.getPosition(window);
		int x = mousePos.x;

		if (x > width)
			x = width;
		if (x < 0)
			x = 0;
		int y = mousePos.y;
		if (y > height)
			y = height;

		pos.setString("Xpos: " + std::to_string(x) + "\nYpos: " + std::to_string(y));
		window.clear();

		for (int i = 0; i < drawCircles.size(); i++) {
			window.draw(drawCircles[i]);
		}
		window.draw(pos);
		window.display();
	}

	return 0;
}