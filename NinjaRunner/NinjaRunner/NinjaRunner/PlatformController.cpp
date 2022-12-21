#include "PlatformController.h"
#include "Globals.h"

PlatformController::PlatformController(float t_x, float t_y, float t_width, float t_height,int t_numberOfBlocks) :
	x(t_x),
	y(t_y),
	width(t_width),
	height(t_height),
	numberOfBlocks(t_numberOfBlocks)
{

}

PlatformController::PlatformController()
{
}


PlatformController::~PlatformController()
{

}

void PlatformController::update(double t_deltaTime)
{
	x -= speed * t_deltaTime;
	checkBounds();
}

void PlatformController::checkBounds()
{
	if (x + (numberOfBlocks * width) < 0)
	{
		x = SCREEN_WIDTH;
	}
}
