#include "EnemyController.h"

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
