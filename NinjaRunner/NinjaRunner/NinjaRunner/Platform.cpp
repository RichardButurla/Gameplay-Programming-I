#include "Platform.h"
#include <iostream>

Platform::Platform(sf::Texture& t_texture,PlatformController& t_platformController) : m_platformTexture(t_texture),
	m_platformController(t_platformController)
{
	for (int i = 0; i < numberOfBlocks; i++)
	{
		m_platformBlocks[i].setTexture(t_texture);
	}
	
}

Platform::Platform()
{

}

Platform::~Platform()
{

}

void Platform::update(double t_deltaTime)
{
	m_platformController.update(t_deltaTime);
	updateBlockPositions(t_deltaTime); 
	
}

void Platform::updateBlockPositions(double t_deltaTime)
{
	float blockXPos = 0;
	float blockYPos = 0;
	for (int i = 0; i < numberOfBlocks; i++)
	{
		blockXPos = m_platformController.getX() + (m_platformController.getWidth() * i);
		blockYPos = m_platformController.getY();
		m_platformBlocks[i].setPosition(blockXPos, blockYPos);
	}
}

void Platform::render(sf::RenderWindow& t_window)
{
	for (int i = 0; i < numberOfBlocks; i++)
	{
		t_window.draw(m_platformBlocks[i]);
	}
	
}

void Platform::setPos(int t_x, int t_y)
{
	float blockXPos = 0;
	float blockYPos = 0;
	m_platformController.setX(t_x);
	m_platformController.setY(t_y);
	for (int i = 0; i < numberOfBlocks; i++)
	{
		blockXPos = t_x + (m_platformController.getWidth() * i);
		blockYPos = t_y;
		m_platformBlocks[i].setPosition(blockXPos, blockYPos);
	}
}

void Platform::setNumberOfBlocks(int t_num)
{
	if (t_num <= MAX_BLOCKS)
	{
		numberOfBlocks = t_num;

		for (int i = 0; i < numberOfBlocks; i++)
		{
			m_platformBlocks[i].setTexture(m_platformTexture);
		}
	}
	else
	{
		std::cout << "over block limit, defaulted to 6.";
		numberOfBlocks = MAX_BLOCKS;
	}
}
