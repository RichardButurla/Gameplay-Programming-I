/// <summary>
/// @author Richard Buturla
/// C00272345

#include "../include/Game.h"
#include "../include/cute_c2.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
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
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
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

	circleOne.update();
	circleTwo.update();

	player.update();
	enemy.update();
	
	//Test collisions
	
	// c2v pointA;
	// c2v pointB;
	// pointA.x = 0;
	// pointA.y = 0;
	// pointB.x = 10;
	// pointB.y = 10;


	// c2AABB AABB;
	// AABB.min = pointA;
	// AABB.max = pointB;

	// c2Capsule capsule;
	// capsule.a = pointA;
	// capsule.b = pointB;
	// capsule.r = 5;

	//update Player Collider, set sprite pos to something and sprite width/height to shape w/h.
	playerCapsule.a = {player.getX(),player.getY()};
	playerCapsule.b = {player.getX(),player.getY() + player.getHeight()}; //capsule.b is second point which is lower down.
	playerCapsule.r = player.getWidth();

	//update Enemy Collider
	enemyAABB.min = {enemy.getX(),enemy.getY()};
	enemyAABB.max = {enemy.getX() + enemy.getWidth(),enemy.getY() + enemy.getY()};

	//check collision
	c2Manifold m;

	c2CapsuletoCapsuleManifold(playerCapsule,playerCapsule,&m);

	// if(CUTE_C2_API::c2CapsuletoCapsule(playerCapsule,playerCapsule)) //if true
	// {
	// 	player.setVelocity({-player.getVelocity().x,player.getVelocity().y});
	// }
	


}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	circleOne.render(m_window);
	circleTwo.render(m_window);

	player.render(m_window);
	enemy.render(m_window);

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	// if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	// {
	// 	std::cout << "problem loading arial black font" << std::endl;
	// }
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	circleOne.setupCircle(sf::Color::Red);
	circleTwo.setupCircle(sf::Color::Blue);

	circleOne.setPosition({ 100,100 });
	circleTwo.setPosition({ 600,100 });

	circleOne.setVelocity({ 2,0 });
	circleTwo.setVelocity({ -2,0 });

	//Rectangles now
	player.setupRectangle(sf::Color::Black);
	enemy.setupRectangle(sf::Color::Green);

	player.setPosition({ 100, 300 });
	enemy.setPosition({ 600, 300 });

	player.setVelocity({ 2,0 });
	enemy.setVelocity({ -2,0 });

	
	enemy.setWidth(20);
	enemy.setHeight(40);
	enemy.setSize(20,40);

	player.setWidth(40);
	player.setHeight(100);
	player.setSize(40,100);


	//setup collision shapes.
	playerCapsule.a = {player.getX(),player.getY()};
	playerCapsule.b = {player.getX(),player.getY() - player.getHeight()}; //capsule.b is second point which is lower down.
	playerCapsule.r = player.getWidth();

}
