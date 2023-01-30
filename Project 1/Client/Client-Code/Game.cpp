#include "Game.h"
#include <iostream>


/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1200, 1200, 32U }, "Online Tag" },
	m_exitGame{ false }, myClient("127.0.0.1", 1111) //when true game will exit
{
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
	}
	// test
	if (!font.loadFromFile("ASSETS/FONTS/OldLondon.ttf"))
	{
		std::cout << "font is bad" << std::endl;
	}
	clockText.setFont(font);
	clockText.setCharacterSize(50);
	clockText.setPosition(600, 100);

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setPosition(600, 600);
	gameOverText.setString("Game Over");
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps

	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
			if (myPlayer.isPlayerCaught == false)
			{
				timer = clock2.getElapsedTime();
			}

		}
		render(); // as many as possible
	}
}

std::string Game::updatePlayersPos()
{
	return myPlayer.getPlayerPosition();
}

std::string Game::sendCheckedForPlayer()
{
	return myPlayer.getChecked();
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	if (!myPlayer.isIDSet())
	{
		myPlayer.init(myClient.getID_Message());
	}

	myPlayer.update();
	collisionDetection();

	myPlayer2.setPosition(getPositionFromServer(myClient.getPositionMessage()));

	if (!myClient.SendPosition(updatePlayersPos()))
	{
		std::cout << "Failed to send position" << std::endl;
	}

	if (!myClient.SendNum(sendCheckedForPlayer()))
	{
		std::cout << "Failed to receive number of player" << std::endl;
	}
	else
	{
		getPlayerNumber(myClient.getPlayerNum_Message());
	}

	if (!myPlayer2.isIDSet() && !enemy2Pos[0].empty())
	{
		std::cout << "Test" << std::endl;
		myPlayer2.init(enemy2Pos[0]);
	}

	clockText.setString("Timer: " + std::to_string(timer.asSeconds()));
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(135,145,155));
	myPlayer3.render(m_window);
	myPlayer2.render(m_window);
	myPlayer.render(m_window);
	if (myClient.getID_Message() != "0")
	{
		m_window.draw(clockText);
	}
	if (myPlayer.isGameOver == true)
	{
		m_window.draw(gameOverText);
	}
	m_window.display();
}

void Game::getPlayerNumber(std::string& string)
{
	if (!string.empty())
	{
		if (string == "1" || string == "2")
		{
			numberOfPlayer = std::stoi(string);
		}
	}
}

void Game::collisionDetection()
{
	myPlayer.collisionDetection(myPlayer2.getPlayer());
}

sf::Vector2f Game::getPositionFromServer(std::string& t_position)
{

	if (!t_position.empty())
	{
		splitString(t_position);
		return sf::Vector2f(std::stof(enemy2Pos[1]), std::stof(enemy2Pos[2]));
	}

	return sf::Vector2f(0, 0);
}

int Game::getLenght(std::string string)
{
	int length = 0;

	for (int i = 0; string[i] != '\0'; i++)
	{
		length++;
	}
	return length;
}

void Game::splitString(std::string string)
{
	int index = 0;
	int i = 0;
	int startIndex = 0;
	int endIndex = 0;

	while (i <= getLenght(string))
	{
		if (string[i] == ',' || i == getLenght(string))
		{
			endIndex = i;
			std::string s = "";
			s.append(string, startIndex, endIndex - startIndex);
			enemy2Pos[index] = s;
			index++;
			startIndex = endIndex + 1;
		}
		i++;
	}
}
