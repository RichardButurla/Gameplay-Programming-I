#pragma once
#include "PlatformController.h"
#include "Globals.h"
#include <SFML/Graphics.hpp>

class Platform
{
public:
	Platform(sf::Texture& t_texture, PlatformController& t_platformController);
	Platform();
	~Platform();

	void update(double t_deltaTime);
	void updateBlockPositions(double t_deltaTime);
	void render(sf::RenderWindow& t_window);

	int getNumberOfBlocks() { return numberOfBlocks; }
	float getX() { return m_platformController.getX(); }
	float getY() { return m_platformController.getY(); }
	float getWidth() { return m_platformController.getBlockWidth(); }
	float getPlatformWidth() { return m_platformController.getPlatformWidth(); }
	float getHeight() { return m_platformController.getBlockHeight(); }
	float getPlatformSpeed() { return m_platformController.getSpeed(); }

	void setPos(int t_x, int t_y);
	void setNumberOfBlocks(int t_num);
	void setPlatformScale(sf::Vector2f t_scale);

	bool isOffScreen() { return m_platformController.checkBounds();}


private:
	int numberOfBlocks = 2;
	sf::Sprite m_platformBlocks[MAX_PLATFORM_BLOCKS];
	sf::Texture m_platformTexture;

	PlatformController m_platformController;

};

