#include "Game.h"
#include <iostream>


GameState Game::currentState = GameState::License;

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>

Game::Game() :
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT }, "SFML Game" },
	m_exitGame{ false } //when true game will exit
{

	initialiseScreens();

}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}


		switch (currentState)
		{
		case GameState::None:
			break;

		case GameState::Splash:
			m_splashScreen.processInput(newEvent);
			break;

		case GameState::Help:
			m_helpScreen.processInput(newEvent);
			break;

		case GameState::GamePlay:
			m_gamePlayScreen.processEvents(newEvent);
			break;

		default:
			break;
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	switch (currentState)
	{
	case GameState::None:
		break;

	case GameState::License:
		m_licenseScreen.update(t_deltaTime, m_window);
		break;


	case GameState::Splash:
		m_splashScreen.update(t_deltaTime,m_window);
		break;

	case GameState::MainMenu:
		m_mainMenuScreen.update(t_deltaTime, m_window);
		break;

	case GameState::Help:
		m_helpScreen.update(t_deltaTime);
		break;

	case GameState::GamePlay:
		m_gamePlayScreen.update(t_deltaTime);
		break;

	default:
		break;
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	switch (currentState)
	{
	case GameState::None:
		break;

	case GameState::GamePlay:
		m_gamePlayScreen.render(m_window);
		break;

	case GameState::License:
		m_licenseScreen.render(m_window);
		break;

	case GameState::Splash:
		m_splashScreen.render(m_window);
		break;

	case GameState::Help:
		m_helpScreen.render(m_window);
		break;

	case GameState::MainMenu:
		m_mainMenuScreen.render(m_window);
		break;

	default:
		break;
	}
	m_window.display();
}

void Game::initialiseScreens()
{
	if (!m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	// Load textures
	if (!m_playerTexture.loadFromFile("ASSETS/IMAGES/PlayerSpriteSheet.png"))
	{
		std::cout << "error loading playerSpriteSheet";
	}
	if (!m_platformTexture.loadFromFile("ASSETS/IMAGES/platform.png"))
	{
		std::cout << "error loading platform Tetxure";
	}
	if (!m_backgroundTexture.loadFromFile("ASSETS/IMAGES/background.png"))
	{
		std::cout << "error loading background Tetxure";
	}


	//load fonts and textures first, then initialise
	
	m_gamePlayScreen.initialise(m_font, m_backgroundTexture, m_playerTexture, m_platformTexture);
	m_licenseScreen.initialise(m_font);
	m_splashScreen.initialise(m_font);
	m_mainMenuScreen.initialise(m_font);
	m_helpScreen.initialise(m_font);
}