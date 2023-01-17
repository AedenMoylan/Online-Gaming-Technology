#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Client.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

	std::string updatePlayersPos();
	std::string sendCheckedForPlayer();
private:

	Client myClient;

	Player myPlayer;
	Player myPlayer2;
	Player myPlayer3;

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void getPlayerNumber(std::string& string);

	void collisionDetection();

	sf::Vector2f getPositionFromServer(std::string& t_position);
	int getLenght(std::string string);
	void splitString(std::string string);

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game

	sf::Clock clock2;
	sf::Time timer;
	sf::Font font;
	sf::Text clockText;
	sf::Text gameOverText;

	std::string enemy1Pos[3];
	std::string enemy2Pos[3];

	int numberOfPlayer = 0;
};

#endif // !GAME_HPP
