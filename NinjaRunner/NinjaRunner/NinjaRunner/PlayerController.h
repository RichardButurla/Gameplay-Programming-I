#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"

class PlayerController
{
public:
	PlayerController(float t_x, float t_y);
	PlayerController();
	~PlayerController();

	void update(double t_deltaTime);
	void setVelocity(float t_x, float t_y) { m_velocity = { t_x,t_y }; }
	void setVelocity(sf::Vector2f t_velocity) { m_velocity = t_velocity; }
	void setGravity(float t_value) { playerGravity = t_value; }

	void setInAir(bool t_boolean) { inAir = t_boolean; }
	void setGrounded(bool t_boolean) { onGround = t_boolean; }

	bool isAirborne() { return inAir; }
	bool isGrounded() { return onGround; }

	void setX(float t_x) { m_position.x = t_x; }
	void setY(float t_y) { m_position.y = t_y; }

	void jump();

	sf::Vector2f getPosition() { return m_position; }
	sf::Vector2f getVelocity() { return m_velocity; }

private:
	sf::Vector2f m_position{0.f,0.f};
	sf::Vector2f m_velocity;
	bool inAir{ true };
	bool onGround{ false };
	float playerGravity = gravity;

};

