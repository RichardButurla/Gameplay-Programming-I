#include "GameOverScreen.h"
#include "GamePlay.h"
#include "Globals.h"
#include "Game.h"
#include <iostream>

bool GamePlay::isGameReset;

GameOverScreen::GameOverScreen()
{
}

GameOverScreen::~GameOverScreen()
{
}

void GameOverScreen::initialise(sf::Font& t_font)
{
	m_font = t_font;

	m_gameOverText.setFont(m_font);
	m_gameOverText.setString("Game Over!\nTotal Score: ");
	m_gameOverText.setCharacterSize(60);
	m_gameOverText.setOutlineColor(sf::Color::Black);
	m_gameOverText.setFillColor(sf::Color::White);

	if (!m_bgTexture.loadFromFile("ASSETS/IMAGES/TITLESCREEN.png"))
	{
		std::cout << "couldn't load bg texture for help screen" << std::endl;
	}

	m_bgSprite.setTexture(m_bgTexture);
	m_bgSprite.setPosition(0, -300);

	sf::FloatRect textSize = m_gameOverText.getGlobalBounds();
	float xpos = SCREEN_WIDTH / 2 - textSize.width / 2 ;
	m_gameOverText.setPosition(xpos, SCREEN_HEIGHT * 0.15f);
	m_pressedExit = false;
	m_buttonSound.loadFromFile("ASSETS/SOUNDS/buttonsound.wav");
	m_sound.setBuffer(m_buttonSound);
}

void GameOverScreen::processInput(sf::Event& t_event)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::R == t_event.key.code)
		{
			m_sound.play();
			GamePlay::isGameReset = true;
		}
		if (sf::Keyboard::Escape == t_event.key.code)
		{
			m_sound.play();
			m_pressedExit = true;
		}
	}
}

void GameOverScreen::update(sf::Time& t_deltatime, int t_gameScore)
{
	if (m_pressedExit == true)
	{
		Game::currentState = GameState::MainMenu;
	}
	m_gameOverText.setString("Game Over! \nTotal Score: \n   " + std::to_string(t_gameScore) + "\n\n  Press R \n  to Restart\n Press Esc to Exit") ;
	m_pressedExit = false;
}

void GameOverScreen::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_bgSprite);
	t_window.draw(m_gameOverText);
}
