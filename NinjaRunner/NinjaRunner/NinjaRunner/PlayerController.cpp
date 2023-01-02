#include "PlayerController.h"
#include <iostream>

PlayerController::PlayerController(float t_x, float t_y)
{
	m_position.x = t_x;
	m_position.y = t_y;
}
PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::update(double t_deltaTime)
{
	std::cout << "\nplayer Gravity: " << playerGravity;
	m_velocity.y += playerGravity;

	m_position.x += m_velocity.x * t_deltaTime;
	m_position.y += m_velocity.y * t_deltaTime;
}

void PlayerController::jump()
{
	m_velocity.y = JUMP_VELOCITY;
}
