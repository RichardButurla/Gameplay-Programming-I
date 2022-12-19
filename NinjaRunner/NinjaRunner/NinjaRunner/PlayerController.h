#pragma once
#include <SFML/Graphics.hpp>
static constexpr double gravity = 9.8;
const int JUMP_VELOCITY = -500;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void update(double t_deltaTime);
	void setVelocity(float t_x, float t_y) { m_velocity = { t_x,t_y }; }
	void setVelocity(sf::Vector2f t_velocity) { m_velocity = t_velocity; }
	void jump();

	sf::Vector2f getPosition() { return m_position; }

private:
	sf::Vector2f m_position{0.f,0.f};
	sf::Vector2f m_velocity;
};

