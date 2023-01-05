#include "MainMenu.h"
#include "Globals.h"
#include "Game.h"
#include "GamePlay.h"
#include <iostream>

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::initialise(sf::Font& t_font)
{
	m_yOffset = 250;
	m_xOffset = ((SCREEN_WIDTH - m_buttonWidth) / 2) - 175;
	m_buttonSpacing = 120;
	m_buttonWidth = 300;
	m_buttonHeight = 100;
	int textDropOffset = 15;
	sf::String m_Texts[] = { "Start Game", "Help", "Exit Game" };

	m_font = t_font;

	if (!m_bgTextr.loadFromFile("ASSETS/IMAGES/TITLESCREEN.png"))
	{
		std::cout << "couldn't load bg texture for help screen" << std::endl;
	}

	m_bgSprite.setTexture(m_bgTextr);
	m_bgSprite.setPosition(0, -200);

	if (!m_buttonTxt.loadFromFile("ASSETS/IMAGES/PLAYBUTTON.png"))
	{
		std::cout << "Can't load button texture";
	}
	for (int i = 0; i < m_buttonCount; i++)
	{
		m_buttonSprite[i].setTexture(m_buttonTxt);
		m_buttonSprite[i].setPosition(m_xOffset, m_buttonSpacing * (i + m_yOffset));
		sf::Vector2u txtSize = m_buttonTxt.getSize();
		m_buttonSprite[i].setScale(m_buttonWidth / txtSize.x, m_buttonHeight / txtSize.y);

		m_text[i].setFont(m_font);
		m_text[i].setString(m_Texts[i]);
		m_text[i].setFillColor(sf::Color::White);
		m_text[i].setCharacterSize(52);
		sf::FloatRect textSize = m_text[i].getGlobalBounds();
		float textOffset = (m_buttonWidth - textSize.width) / (2);
		m_text[i].setPosition(m_xOffset + textOffset, m_buttonSpacing * i + m_yOffset + textDropOffset);
	}
	m_mainMenuMusic.openFromFile("ASSETS/MUSIC/mainmenu.wav");
	m_mainMenuMusic.play();
	m_mainMenuMusic.setVolume(50);
	m_mainMenuMusic.setLoop(true);
	m_buttonSound.loadFromFile("ASSETS/SOUNDS/buttonsound.wav");
	m_sound.setBuffer(m_buttonSound);
}

void MainMenu::update(sf::Time& t_deltaTime, sf::Window& t_window)
{
	sf::Vector2i mouseLocation;
	mouseLocation = sf::Mouse::getPosition(t_window);
	for (int i = 0; i < m_buttonCount; i++)
	{
		m_text[i].setFillColor(sf::Color::White);
	}
	if (mouseLocation.x > m_xOffset && mouseLocation.x < m_xOffset + m_buttonWidth)
	{
		if (mouseLocation.y > m_yOffset && mouseLocation.y < m_yOffset + m_buttonHeight)
		{
			m_text[0].setFillColor(sf::Color{ 75,75,75,255 });
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				m_sound.play();
				m_mainMenuMusic.stop();
				Game::currentState = GameState::GamePlay;
			}
		}
		if (mouseLocation.y > m_yOffset + m_buttonSpacing && mouseLocation.y < m_yOffset + m_buttonHeight + m_buttonSpacing)
		{
			m_text[1].setFillColor(sf::Color{ 75,75,75,255 });
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				m_sound.play();
				Game::currentState = GameState::Help;
			}
		}
		if (mouseLocation.y > m_yOffset + (m_buttonSpacing * 2) && mouseLocation.y < m_yOffset + m_buttonHeight + (m_buttonSpacing * 2))
		{
			m_text[2].setFillColor(sf::Color{ 75,75,75,255 });
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				m_sound.play();
				t_window.close();
			}
		}
	}
}

void MainMenu::render(sf::RenderWindow& t_window)
{

	t_window.draw(m_bgSprite);
	t_window.draw(m_buttonSprite[0]);
	t_window.draw(m_buttonSprite[1]);
	t_window.draw(m_buttonSprite[2]);
	for (int i = 0; i < m_buttonCount; i++)
	{
		t_window.draw(m_buttonSprite[i]);
		t_window.draw(m_text[i]);
	}
}
