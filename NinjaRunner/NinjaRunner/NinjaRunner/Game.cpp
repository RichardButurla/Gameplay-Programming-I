/// <summary>
/// @author Richard Buturla
/// C00272345

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1400U, 800U, 32U }, "SFML Game" },
	m_exitGame{false}, //when true game will exit
	m_input(input)
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
		switch (newEvent.type)
		{
			case sf::Event::Closed:
				// Close window : exit
				m_window.close();
				break;
				// Deal with KeyPressed
			case sf::Event::KeyPressed:
				processKeyPress(newEvent);
				break;

				// Deal with KeyReleased
			case sf::Event::KeyReleased:
				processKeyRelease(newEvent);
				break;

			default:
				//DEBUG_MSG("gpp::Events::Event::NONE");
				m_input.setCurrent(gpp::Events::Event::NONE);
				break;
		}
		m_player.handleAnimationInput(input);
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeyPress(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	m_player.processKeyPress(t_event);
	processKeyPressFSM(t_event);
}

/// <summary>
/// deal with key releases from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeyRelease(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	m_player.processKeyRelease(t_event);
	processKeyReleaseFSM(t_event);
}

void Game::processKeyPressFSM(sf::Event t_event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		DEBUG_MSG("gpp::Events::Event::DIED_EVENT");
		m_input.setCurrent(gpp::Events::Event::DIED_EVENT);
	}
	// Revieved Event
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		DEBUG_MSG("gpp::Events::Event::REVIVED_EVENT");
		m_input.setCurrent(gpp::Events::Event::REVIVED_EVENT);
	}
	// Running attack
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::Z)))
	{
		DEBUG_MSG("gpp::Events::Event::ATTACK_START");
		m_input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
	}
	// Attack
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		DEBUG_MSG("gpp::Events::Event::ATTACK_START_EVENT");
		m_input.setCurrent(gpp::Events::Event::ATTACK_START_EVENT);
	}
	// Throw attack
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::X) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::X)))
	{
		DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
		m_input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
	}
	// Throw Attack
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		DEBUG_MSG("gpp::Events::Event::THROW_START_EVENT");
		m_input.setCurrent(gpp::Events::Event::THROW_START_EVENT);
	}
	// Run Right
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
		m_input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
	}
	// Climb Up
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		DEBUG_MSG("gpp::Events::Event::MOVE_UP_START_EVENT");
		m_input.setCurrent(gpp::Events::Event::MOVE_UP_START_EVENT);
	}
	// Climb Down
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_START_EVENT");
		m_input.setCurrent(gpp::Events::Event::MOVE_DOWN_START_EVENT);
	}
	// Hit Bottom of Ladder Event
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		DEBUG_MSG("gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT");
		m_input.setCurrent(gpp::Events::Event::HIT_LADDER_BOTTOM_EVENT);
	}
	// Hit Top of Ladder Event
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		DEBUG_MSG("gpp::Events::Event::HIT_LADDER_TOP_EVENT");
		m_input.setCurrent(gpp::Events::Event::HIT_LADDER_TOP_EVENT);
	}
	// Jump Run
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
	{
		DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
		input.setCurrent(gpp::Events::Event::JUMP_UP_RUN_RIGHT_EVENT);
	}
	// Jump Event
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		DEBUG_MSG("gpp::Events::Event::JUMP_UP_EVENT");
		m_input.setCurrent(gpp::Events::Event::JUMP_UP_EVENT);
	}
	// Running Slide
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
	{
		DEBUG_MSG("gpp::Events::Event::SLIDE_EVENT");
		m_input.setCurrent(gpp::Events::Event::SLIDE_EVENT);
	}
	// Hit Ground Event
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
		m_input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
	}

	// Jump Attack Event
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
		m_input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
	}

	// Jump Throw Attack Event
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		DEBUG_MSG("gpp::Events::Event::HIT_GROUND_EVENT");
		m_input.setCurrent(gpp::Events::Event::HIT_GROUND_EVENT);
	}

	//Shovelling Event
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
	{
		DEBUG_MSG("gpp::Events::Event::SHOVEL_START_EVENT");
		m_input.setCurrent(gpp::Events::Event::SHOVEL_START_EVENT);
	}
	//Shovelling Event
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		DEBUG_MSG("gpp::Events::Event::HAMMERING_START_EVENT");
		m_input.setCurrent(gpp::Events::Event::HAMMERING_END_EVENT);
	}
	//Shovelling Event
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		DEBUG_MSG("Hammering");
		//input.setCurrent(gpp::Events::Event::SHOVEL_START_EVENT);
	}
}

void Game::processKeyReleaseFSM(sf::Event t_event)
{
	// Run and Stop Attack
	if (t_event.key.code == sf::Keyboard::Z &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
		m_input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
	}
	// Stop Attack
	else if (t_event.key.code == sf::Keyboard::Z)
	{
		DEBUG_MSG("gpp::Events::Event::ATTACK_STOP_EVENT");
		m_input.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
	}
	// Run and Stop Throw Attack
	else if (t_event.key.code == sf::Keyboard::X &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
		m_input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
	}
	// Stop Throw Attack
	else if (t_event.key.code == sf::Keyboard::X)
	{
		DEBUG_MSG("gpp::Events::Event::THROW_STOP_EVENT");
		m_input.setCurrent(gpp::Events::Event::THROW_STOP_EVENT);
	}
	else if (t_event.key.code == sf::Keyboard::J)
	{
		DEBUG_MSG("gpp::Events::Event::HAMMERING_END_EVENT");
		m_input.setCurrent(gpp::Events::Event::HAMMERING_END_EVENT);
	}
	// Stop Running Right
	else if (t_event.key.code == sf::Keyboard::Right)
	{
		DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_STOP_EVENT");
		m_input.setCurrent(gpp::Events::Event::RUN_RIGHT_STOP_EVENT);
	}
	// Stop Slide
	else if (t_event.key.code == sf::Keyboard::Down &&
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		DEBUG_MSG("gpp::Events::Event::RUN_RIGHT_START_EVENT");
		m_input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
	}
	// Stop Moving Up
	else if (t_event.key.code == sf::Keyboard::Up)
	{
		DEBUG_MSG("gpp::Events::Event::MOVE_UP_STOP_EVENT");
		m_input.setCurrent(gpp::Events::Event::MOVE_UP_STOP_EVENT);
	}
	// Stop Moving Down
	else if (t_event.key.code == sf::Keyboard::Down)
	{
		DEBUG_MSG("gpp::Events::Event::MOVE_DOWN_STOP_EVENT");
		m_input.setCurrent(gpp::Events::Event::MOVE_DOWN_STOP_EVENT);
	}
	else if (t_event.key.code == sf::Keyboard::V)
	{
		DEBUG_MSG("gpp::Events::Event::SHOVEL_END_EVENT");
		m_input.setCurrent(gpp::Events::Event::SHOVEL_END_EVENT);
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
	m_player.updatePlayer(t_deltaTime.asSeconds());
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_player.renderPlayer(m_window);
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
	// Load a sprite to display
	 if (!m_playerTexture.loadFromFile("ASSETS/IMAGES/PlayerSpriteSheet.png"))
	 {
		 std::cout << "error loading playerSpriteSheet";
	 }

	 m_playerAnimatedSprite = AnimatedSprite(m_playerTexture);
	 m_player = Player(m_playerAnimatedSprite);
	 m_player.setPlayerScale(0.5, 0.5);

}
