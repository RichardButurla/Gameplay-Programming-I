#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::update(double t_deltaTime)
{
	m_velocity.y * t_deltaTime;
	m_velocity.y += gravity * t_deltaTime;
	m_position += m_velocity;
	
	double SCREEN_HEIGHT = 500;
	if (m_position.y >= SCREEN_HEIGHT)
	{
		m_position.y = SCREEN_HEIGHT - 1;
	}
}

void PlayerController::jump()
{
	m_velocity.y = -13;
}
