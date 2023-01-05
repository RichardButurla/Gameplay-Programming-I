#include "HelpScreen.h"
#include "Globals.h"
#include "Game.h"
#include <iostream>

HelpScreen::HelpScreen()
{
}

HelpScreen::~HelpScreen()
{
}

void HelpScreen::initialise(sf::Font& t_font)
{
	m_font = t_font;

	m_helpText.setFont(m_font);
	m_helpText.setString("Press Spacebar to jump. Press again to double Jump\nPress Z to Attack\nPress Esc to return to Main Menu");
	m_helpText.setCharacterSize(40);
	m_helpText.setFillColor(sf::Color::White);

	if (!m_bgTexture.loadFromFile("ASSETS/IMAGES/TITLESCREEN.png"))
	{
		std::cout << "couldn't load bg texture for help screen" << std::endl;
	}

	m_bgSprite.setTexture(m_bgTexture);
	m_bgSprite.setPosition(0, -300);

	sf::FloatRect textSize = m_helpText.getGlobalBounds();
	float xpos = SCREEN_WIDTH / 2 - textSize.width / 2;
	m_helpText.setPosition(xpos, SCREEN_HEIGHT * 0.35f);
	m_pressedExit = false;
	m_buttonSound.loadFromFile("ASSETS/SOUNDS/buttonsound.wav");
	m_sound.setBuffer(m_buttonSound);
}

void HelpScreen::processInput(sf::Event& t_event)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::Escape == t_event.key.code)
		{
			m_sound.play();
			m_pressedExit = true;
		}
	}
}

void HelpScreen::update(sf::Time& t_deltatime)
{
	if (m_pressedExit == true)
	{
		Game::currentState = GameState::MainMenu;
	}
	m_pressedExit = false;
}

void HelpScreen::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_bgSprite);
	t_window.draw(m_helpText);
}
