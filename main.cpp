// SFML IS GREAT

#include <iostream>
#include "OrbitalMechanics.h"
#include "SpaceObject.h"
#include "SFML/Graphics.hpp"
#include "SFML/Window/Mouse.hpp"
#include <vector>
#include <format>
#include <string>
#include <Windows.h>
#include <random>


int main() {

	unsigned int width = 720;
	unsigned int height = 720;
	double simulationSpace = 25000000.0; // total width of screen in meters
	static int satRad = 2; // Radius of satellite in pixels
	static int clickedSatRad = 4; // clicked satelite radius
	int centerX = width / 2;
	int centerY = height / 2;

	static double simTime = 0; //How many seconds since simulation started
	static double timeMult = 1.0; // represents the time multiplier of the simulation

	static bool lock_click;
	static bool showCoords = false;
	static int x, y;
	static double satScreenPosY;
	static double satScreenPosX;
	static double satScreenPosY2;
	static double satScreenPosX2;
	double screenRatio = simulationSpace / width; //15 million meters divided by screen width 1024 == ratio of simulated meters to screen pixels
	SpaceObject* showsat = nullptr;
	sf::Text* redText = nullptr;
	sf::Text* prevredText = nullptr;


	std::vector < sf::Color > colorlist = {sf::Color::Yellow, sf::Color::Cyan, sf::Color::Green, sf::Color::Magenta, sf::Color::Red};
 	
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(0, colorlist.size() - 1);



	OrbitalMechanics model;
	int earthRad = model.EARTHR / screenRatio;
	std::cout << "Radius earth pixels: " << earthRad << "\n";

	std::vector <sf::CircleShape> drawCircles;
	std::vector <sf::Text> texts;

	
	sf::RenderWindow window(sf::VideoMode(width, height), "Space Object Tracker");
	
	sf::CircleShape earth(earthRad);
	sf::Texture earthText;
	if (!earthText.loadFromFile("Earth.png")) {
		std::cout << "Texture load error";
		return 0;
	}

	earth.setOrigin(earthRad, earthRad);
	earth.setTexture(&earthText);
	earth.setPosition(width / 2, height / 2);
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
	pos.setPosition(width-270, 0+20);

	sf::Text tim;

	tim.setCharacterSize(20);
	tim.setFillColor(sf::Color::White);

	tim.setFont(font);
	tim.setPosition(0 + 50, 0 + 20);


	SpaceObject sputnik = SpaceObject("Sputnik", 1500);
	//std::cout << "Sputnik starting alt: " << sputnik.eciposition[0] << " m\n";
	//std::cout << "Sputnik Theta per sec: " << sputnik.thetaPerSec << " deg/s\n";
	SpaceObject* sputnikPoint = &sputnik;
	model.addSatellite(sputnikPoint);

	sf::CircleShape sputnikDot(satRad);
	sputnikDot.setFillColor(colorlist[distrib(gen)]);
	sputnikDot.setPosition(centerX + (sputnik.eciposition[0] / screenRatio), centerY);

	SpaceObject sputnik2 = SpaceObject("Sputnik2", 3500);
	//std::cout << "Sputnik2 starting alt: " << sputnik2.eciposition[0] << " m\n";
	SpaceObject* sputnikPoint2 = &sputnik2;
	model.addSatellite(sputnikPoint2);

	sf::CircleShape sputnikDot2(satRad);
	sputnikDot2.setFillColor(colorlist[distrib(gen)]);
	sputnikDot2.setPosition(centerX + (sputnik2.eciposition[0] / screenRatio), centerY);
	drawCircles.push_back(sputnikDot);
	drawCircles.push_back(sputnikDot2);

	SpaceObject iss = SpaceObject("ISS", 480);
	//std::cout << "ISS starting alt: " << iss.eciposition[0] << " m\n";
	SpaceObject* issptr = &iss;
	model.addSatellite(issptr);

	sf::CircleShape issdot(satRad);
	issdot.setFillColor(colorlist[distrib(gen)]);
	issdot.setPosition(centerX + (iss.eciposition[0] / screenRatio), centerY);
	drawCircles.push_back(sputnikDot);
	drawCircles.push_back(sputnikDot2);
	drawCircles.push_back(issdot);

	sf::Mouse mickey;
	sf::Vector2i mousePos;

	static char posstring[150];

	sf::Text oneTimes;

	oneTimes.setCharacterSize(15);
	oneTimes.setFillColor(sf::Color::White);
	oneTimes.setFont(font);
	oneTimes.setString("1X");
	oneTimes.setPosition(20, 40);

	sf::Text tenTimes;

	tenTimes.setCharacterSize(15);
	tenTimes.setFillColor(sf::Color::White);
	tenTimes.setFont(font);
	tenTimes.setString("10X");
	tenTimes.setPosition(20, 60);


	sf::Text twentyTimes;

	twentyTimes.setCharacterSize(15);
	twentyTimes.setFillColor(sf::Color::White);
	twentyTimes.setFont(font);
	twentyTimes.setString("20X");
	twentyTimes.setPosition(20, 80);
	
	texts.push_back(oneTimes);
	texts.push_back(tenTimes);
	texts.push_back(twentyTimes);


	while (window.isOpen()) {

		window.clear();

		window.draw(earth);

		mousePos = mickey.getPosition(window);

		x = mousePos.x;
		y = mousePos.y;

		while (window.pollEvent(e))
		{

			if (e.type == sf::Event::MouseButtonPressed) //Mouse button Pressed
			{
				if (e.mouseButton.button == sf::Mouse::Left && lock_click != true) //specifies
				{

					bool anyCircleClicked = false;
					// check to see if mouse is over a satellite, if is within 5 then get posn and blow up satellite sprite
					for (std::size_t i = 0; i < model.satelliteList.size(); i++) {
						SpaceObject* currentSat = model.satelliteList[i];
						satScreenPosX = centerX + currentSat->eciposition[0] / screenRatio;
						satScreenPosY = centerY + currentSat->eciposition[1] / screenRatio;
						double distance = sqrt(pow(x - satScreenPosX, 2) + pow(y - satScreenPosY, 2));
						if (distance < 5) {
							anyCircleClicked = true;
							showCoords = true;
							drawCircles[i].setRadius(clickedSatRad);
							showsat = currentSat;
						}
						if(!anyCircleClicked) {
							showCoords = false;
							pos.setString(" ");
							drawCircles[i].setRadius(satRad);

						}
					}

					if (x < 45 && x > 20) {
						if (prevredText != nullptr) {
							prevredText->setFillColor(sf::Color::White);
						}

						if (y > 40 && y < 60) {
							timeMult = 1.0;
							oneTimes.setFillColor(sf::Color::Red);
							redText = &oneTimes;
						}
						if (y > 60 && y < 80) {
							timeMult = 10.0;
							tenTimes.setFillColor(sf::Color::Red);
							redText = &tenTimes;
						}
						if (y > 80 && y < 100) {
							timeMult = 20.0;
							twentyTimes.setFillColor(sf::Color::Red);
							redText = &twentyTimes;
						}
						prevredText = redText;
					}

					//std::cout << "lmb-pressed" << std::endl; 
					//std::cout << "mouseX " << x << std::endl;
					//std::cout << "mouseY " << y << std::endl;
					lock_click = true; //this will lock the loop and not print "lmb" in a x held time. 
				}
			}

			if (e.type == sf::Event::MouseButtonReleased) //Mouse button Released now.
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					lock_click = false; //unlock when the button has been released.
				}
			}

			if (e.type == sf::Event::Closed)
				window.close();
		}
		
		

		if (showCoords) {
			sprintf_s(posstring, "Altitude: %.1f km\nOrbital Velocity: %4.2f m/s\nName: %s\nOrbital Period: %4.0f sec\nOrbits: %1.2f", showsat->altitude, showsat->orbVel, showsat->name.c_str(), showsat->period, showsat->currentAngle / 360);
			//pos.setString("Xpos: " + std::to_string(showsat->eciposition[0] / screenRatio) + "\nZpos: " + std::to_string(showsat->eciposition[1] / screenRatio) + "\nName: " + showsat->name);
			pos.setString(posstring);
		}

		
		for (std::size_t i = 0; i < model.satelliteList.size(); i++) {
			model.updatePositionVelocity(model.satelliteList[i], simTime);
			drawCircles[i].setPosition(centerX + (int)(model.satelliteList[i]->eciposition[0] / screenRatio), centerY + (int)(model.satelliteList[i]->eciposition[1] / screenRatio));
			sf::CircleShape currentShape = drawCircles[i];
			window.draw(currentShape);
		}

		//redText->


		window.draw(pos);
		window.draw(oneTimes);
		window.draw(tenTimes);
		window.draw(twentyTimes);
		
		
		
		tim.setString("Simulation Time: " + std::to_string(simTime) + " sec");
		window.draw(tim);
		window.display();
		earth.rotate(.0042 * timeMult);
		Sleep(1000 / timeMult); // screen framerate must increase as time multiplier increases, to limit satellites "skipping" at higher speed
		simTime += (1 * timeMult);
	}

	return 0;
}