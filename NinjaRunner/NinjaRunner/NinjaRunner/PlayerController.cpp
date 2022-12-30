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


	if (m_position.y >= SCREEN_HEIGHT - 300)
	{
		m_velocity.y = 0;
		m_position.y = (SCREEN_HEIGHT - 300) - 1;
	}


	m_position.y += m_velocity.y * t_deltaTime;
}

void PlayerController::jump()
{
	m_velocity.y = JUMP_VELOCITY;
}
