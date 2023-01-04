#include "EnemyController.h"
#include <math.h>
#include <iostream>

EnemyController::EnemyController(float t_x, float t_y, float t_width, float t_height, int t_numberOfBlocks) :
	x(t_x),
	y(t_y),
	width(t_width),
	height(t_height)
{
}

EnemyController::EnemyController()
{
}

EnemyController::~EnemyController()
{
}

void EnemyController::update(double t_deltaTime)
{
	x -= speed * t_deltaTime;
}

bool EnemyController::isOffscreen()
{
	if (x < 0)
	{
		return true;
	}
	return false;
}

/// <summary>
/// player should be on the same y level as an enemy to first check if they are close enough x wise to intereact.
/// </summary>
/// <param name="t_playerXPos"> players X position</param>
/// <param name="t_playerYPos"> players Y Position</param>
void EnemyController::trackPlayer(float t_playerXPos, float t_playerYPos)
{
	float yDetectionDistance = 20;
	float xDetectionDistance = 600;

	float attackDistance = 150;

	float xDistance = (t_playerXPos - x);
	float yDistance = ( t_playerYPos - y);

	if (fabs(xDistance) < xDetectionDistance && fabs(yDistance) < yDetectionDistance)
	{
		trackingPlayer = true;
		if (xDistance < 0)
		{
			speed = chaseSpeed;
		}
		else
		{
			speed = -chaseSpeed;
		}
		if (fabs(xDistance) < attackDistance && fabs(yDistance) < yDetectionDistance)
		{
			std::cout << "\nAttacking player: " << attackingPlayer;
			attackingPlayer = true;
			trackingPlayer = false;
			speed = 0;
		}
		else
		{
			attackingPlayer = false;
		}
	}
	else
	{
		trackingPlayer = false;
		attackingPlayer = false;
	}

	
}

