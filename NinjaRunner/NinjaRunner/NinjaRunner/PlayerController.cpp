#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::update()
{
	m_position += m_velocity;
	if (inAir)
	{
		m_position.y += gravity;
	}
}
