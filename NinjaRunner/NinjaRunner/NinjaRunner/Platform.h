#pragma once
#include "PlatformController.h"
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


private:
	static const int MAX_BLOCKS = 6;
	int numberOfBlocks = 2;
	sf::Sprite m_platformBlocks[MAX_BLOCKS];
	sf::Texture m_platformTexture;

	PlatformController m_platformController;

};

