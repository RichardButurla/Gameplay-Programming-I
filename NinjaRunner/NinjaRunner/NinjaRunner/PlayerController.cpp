#include "PlayerController.h"

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
	if (!isGrounded)
	{
		m_velocity.y* t_deltaTime;
		m_velocity.y += gravity * t_deltaTime;
		m_position += m_velocity;
	}
	
	
	
	double SCREEN_HEIGHT = 500;
	if (m_position.y >= SCREEN_HEIGHT)
	{
		isGrounded = true;
	}
}

void PlayerController::jump()
{
	m_velocity.y = -13;
	isGrounded = false;
}
