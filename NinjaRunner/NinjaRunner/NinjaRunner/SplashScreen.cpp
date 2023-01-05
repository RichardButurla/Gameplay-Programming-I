#include <iostream>
#include "SplashScreen.h"
#include "Game.h"
#include "Globals.h"

SplashScreen::SplashScreen()
{
}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::initialise(sf::Font& t_font)
{
	m_font = t_font;

	//m_splashBackgroundTexture.setRepeated(true); // might not be needed if the final background is a full screen image
	//m_splashBackground.setTexture(m_splashBackgroundTexture);
	//m_splashBackground.setTextureRect(sf::IntRect(0, 0, static_cast<int>(Game::s_screenWidth), static_cast<int>(Game::s_screenHeight))); // sets it to the size of the window
	//m_splashBackground.setPosition(0, 0);

	m_splashText.setFont(m_font); // Text seen on the screen
	m_splashText.setString("Press any button to continue");
	m_splashText.setCharacterSize(42);
	m_splashText.setFillColor(sf::Color::Red);
	m_splashText.setStyle(sf::Text::Bold);


	sf::FloatRect textSize = m_splashText.getGlobalBounds(); // will be used to put the text in the middle
	float xpos = (SCREEN_WIDTH / 2) - (textSize.width / 2);
	m_splashText.setPosition(xpos, SCREEN_HEIGHT * 0.5f - (textSize.height / 2));

	initializeTextures();
	m_anyKeyPressed = false;

	/*m_buttonSound.loadFromFile("ASSETS/SOUNDS/buttonsound.wav");
	m_sound.setBuffer(m_buttonSound);*/
}

void SplashScreen::update(sf::Time& t_deltaTime, sf::RenderWindow& t_window) // not necessary at the moment
{
	
}

void SplashScreen::processInput(sf::Event& t_event)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		m_anyKeyPressed = true;
		Game::currentState = GameState::MainMenu; // this could also be done in update but why not just include it here
	}
}

void SplashScreen::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_splashText);
}

void SplashScreen::initializeTextures()
{

}

void SplashScreen::setUpSpritePerFrame(sf::Sprite& t_currentFrameSprite)
{

}
