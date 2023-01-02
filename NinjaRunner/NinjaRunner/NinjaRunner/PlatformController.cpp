#include "PlatformController.h"
#include "Globals.h"
#include <iostream>

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

bool PlatformController::checkBounds()
{
	if (x + (numberOfBlocks * width) < 0)
	{
		std::cout << "\nOUT OF BOUNDS \n";
		return true;
	}
	return false;
}

