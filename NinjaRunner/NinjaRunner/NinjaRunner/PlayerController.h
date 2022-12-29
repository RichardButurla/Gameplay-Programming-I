#pragma once
#include <SFML/Graphics.hpp>
static constexpr double gravity = 12.8;
const int JUMP_VELOCITY = -500;

class PlayerController
{
public:
	PlayerController(float t_x, float t_y);
	PlayerController();
	~PlayerController();

	void update(double t_deltaTime);
	void setVelocity(float t_x, float t_y) { m_velocity = { t_x,t_y }; }
	void setVelocity(sf::Vector2f t_velocity) { m_velocity = t_velocity; }

	void setGrounded(bool t_boolean) { isGrounded = t_boolean; }

	void setX(float t_x) { m_position.x = t_x; }
	void setY(float t_y) { m_position.y = t_y; }

	void jump();

	sf::Vector2f getPosition() { return m_position; }

private:
	sf::Vector2f m_position{0.f,0.f};
	sf::Vector2f m_velocity;
	bool isGrounded{ true };

};

