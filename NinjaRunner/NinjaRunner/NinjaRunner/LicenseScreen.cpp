#include "LicenseScreen.h"
#include "Game.h"
#include "Globals.h"
#include <string>
#include <iostream>

LicenseScreen::LicenseScreen()
{
}

LicenseScreen::~LicenseScreen()
{
}

void LicenseScreen::initialise(sf::Font& t_font)
{
	m_font = t_font;
	m_text.setFont(m_font);
	m_text.setCharacterSize(60U);
	m_text.setFillColor(sf::Color::Red);
	m_text.setString("Developed by Richard Buturla");

	initialiseTextures();
	sf::FloatRect textSize = m_text.getGlobalBounds();
	float xPosition = SCREEN_WIDTH / 2.0f - textSize.width / 2; //middle of text put on middle of screen
	float yPosisiton = SCREEN_HEIGHT * 0.4f;
	m_text.setPosition(xPosition, yPosisiton);
}

void LicenseScreen::update(sf::Time& t_deltaTime, sf::RenderWindow& t_window)
{
	m_licenseTime = m_clock.getElapsedTime();
	if (m_licenseTime.asSeconds() > 6)
	{
		Game::currentState = GameState::Splash;
	}
}

void LicenseScreen::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_text);
}

void LicenseScreen::initialiseTextures()
{
	
}


