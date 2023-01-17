#pragma once
#include <SFML/Graphics.hpp>
#include <string.h>
#include <iostream>
#include <sstream>

class Player
{
public:

	void init(std::string stringID);
	void render(sf::RenderWindow& m_window);
	void update();

	void movement();
	void collisionDetection(sf::CircleShape t_enemy);

	void setPosition(sf::Vector2f newPos);
	void setPlayerColor();

	sf::CircleShape getPlayer();

	bool isIDSet();

	int getPlayerID();

	std::string getPlayerPosition();
	std::string getChecked();

	void checkForBoundaries();

	bool isPlayerCaught = false;

	bool isGameOver = false;

private:

	sf::CircleShape playerShape;
	sf::Color color;

	int playerID;

	bool isColliding = false;
	bool IDSet = false;
};


