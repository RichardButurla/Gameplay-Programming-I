#pragma once
#include <SFML/Graphics.hpp>
static constexpr double gravity = 9.8;

class PlayerController
{
public:
	PlayerController();
	~PlayerController();

	void update();
	void setVelocity(float t_x, float t_y) { m_velocity = { t_x,t_y }; }
	void setVelocity(sf::Vector2f t_velocity) { m_velocity = t_velocity; }
	void jump() { inAir = true; isGrounded = false; m_velocity.y -= m_jumpSpeed; }
	void decend() { m_velocity.y += m_decendSpeed; }

	sf::Vector2f getPosition() { return m_position; }

private:
	sf::Vector2f m_position{0.f,0.f};
	sf::Vector2f m_velocity;
	float m_jumpSpeed = 10;
	float m_maxJumpHeight = 100.f;
	float m_decendSpeed = 20;

	bool inAir = false;
	bool isGrounded = true;


};

