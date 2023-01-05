#pragma once
#include <SFML/Graphics.hpp>
#include "GamePlay.h"
#include "LicenseScreen.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "HelpScreen.h"



/// <summary>
/// different states for game
/// </summary>


enum class
	GameState
{
	None,
	License,
	Splash,
	MainMenu,
	Help,
	GamePlay,
	InventoryScreen
};

class Game
{

public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	static GameState currentState;

protected:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();

	void initialiseScreens();


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_font; // apocalyptic style font

	GamePlay m_gamePlayScreen;
	LicenseScreen m_licenseScreen;
	SplashScreen m_splashScreen;
	MainMenu m_mainMenuScreen;
	HelpScreen m_helpScreen;

	sf::Texture m_playerTexture;
	sf::Texture m_backgroundTexture;
	sf::Texture m_platformTexture;




	//Textures that we load once and pass into the screens and objects
	


	bool m_exitGame; // control exiting game

};