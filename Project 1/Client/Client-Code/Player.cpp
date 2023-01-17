#include "Player.h"

void Player::init(std::string stringID)
{
	std::istringstream stream(stringID);
	stream >> playerID;
	IDSet = true;

	std::cout << playerID;
	setPlayerColor();

	if (playerID == 0)
	{
		playerShape.setRadius(50);
		playerShape.setPosition(sf::Vector2f(100, 600));
	}
	else if (playerID == 1)
	{
		playerShape.setRadius(30);
		playerShape.setPosition(sf::Vector2f(1100, 200));
	}
	else if (playerID == 2)
	{
		playerShape.setRadius(30);
		playerShape.setPosition(sf::Vector2f(1100, 1000));
	}
}

void Player::render(sf::RenderWindow& m_window)
{
	m_window.draw(playerShape);
}

void Player::update()
{
	movement();
	checkForBoundaries();
}

void Player::movement()
{

	switch (playerID)
	{
	case 0:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			playerShape.move(0, -10);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			playerShape.move(0, 10);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			playerShape.move(-10, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			playerShape.move(10, 0);
		}
		break;
	case 1:
		if (isPlayerCaught == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				playerShape.move(0, -10);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				playerShape.move(0, 10);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				playerShape.move(-10, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				playerShape.move(10, 0);
			}
		}
		break;

	case 2:
		if (isPlayerCaught == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{
				playerShape.move(0, -10);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			{
				playerShape.move(0, 10);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
			{
				playerShape.move(-10, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
				playerShape.move(10, 0);
			}
		}
		break;
	}
}

void Player::collisionDetection(sf::CircleShape t_enemy)
{
		if (playerShape.getGlobalBounds().intersects(t_enemy.getGlobalBounds()))
		{
			isPlayerCaught = true;
			isGameOver = true;
		}

		if (getPlayerID() == 0)
		{
			isPlayerCaught = false;
			isGameOver = false;
		}
}

sf::CircleShape Player::getPlayer()
{
	return playerShape;
}

std::string Player::getPlayerPosition()
{
	return std::to_string(getPlayerID()) + "," + std::to_string(playerShape.getPosition().x) + "," + std::to_string(playerShape.getPosition().y);
}


void Player::checkForBoundaries()
{
	if (playerShape.getPosition().x > 1200)
	{
		playerShape.setPosition(1, playerShape.getPosition().y);
	}
	else if (playerShape.getPosition().x < 0)
	{
		playerShape.setPosition(1199, playerShape.getPosition().y);
	}

	if (playerShape.getPosition().y > 1200)
	{
		playerShape.setPosition(playerShape.getPosition().x,1);
	}
	else if (playerShape.getPosition().y < 0)
	{
		playerShape.setPosition(playerShape.getPosition().x, 1199);
	}
}

void Player::setPosition(sf::Vector2f t_pos)
{
	playerShape.setPosition(t_pos);
}

void Player::setPlayerColor()
{
	switch (playerID)
	{
	case 1:
		color = sf::Color::Blue;
		break;
	case 2:
		color = sf::Color::Magenta;
		break;
	default:
		color = sf::Color::Red;
		break;
	}

	playerShape.setFillColor(color);
}

int Player::getPlayerID()
{
	return playerID;
}

bool Player::isIDSet()
{
	return IDSet;
}

std::string Player::getChecked()
{
	return std::to_string(10);
}


