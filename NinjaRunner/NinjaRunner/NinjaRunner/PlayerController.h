#pragma once
#include <SFML/Graphics.hpp>
static constexpr double gravity = 9.8;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void update();

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	bool inAir = false;


};

