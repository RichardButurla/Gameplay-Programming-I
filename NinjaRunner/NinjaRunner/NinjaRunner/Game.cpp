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
	m_window{ sf::VideoMode{ SCREEN_WIDTH, SCREEN_HEIGHT, 32U }, "SFML Game" },
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
				//m_input.setCurrent(gpp::Events::Event::RUN_RIGHT_START_EVENT);
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
	if (sf::Keyboard::Z == t_event.key.code)
	{
		checkPlayerAttack();
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
		//m_input.setCurrent(gpp::Events::Event::ATTACK_STOP_EVENT);
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
	checkPlatformTimes();


	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		m_platforms[i].update(t_deltaTime.asSeconds());
	}
	for (int i = 0; i < MAX_FLOOR_PLATFORMS; i++)
	{
		m_floorPlatforms[i].update(t_deltaTime.asSeconds());
	}

	m_player.updatePlayer(t_deltaTime.asSeconds());
	m_enemy.update(t_deltaTime.asSeconds());
	m_enemy.setSpeed(m_platformSpeed);

	checkCollision();
	checkPlatformOffScreen();
	checkPlayerEnemyDistance();
	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_background);
	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		m_platforms[i].render(m_window);
	}
	for (int i = 0; i < MAX_FLOOR_PLATFORMS; i++)
	{
		m_floorPlatforms[i].render(m_window);
	}


	/*testShape.setSize(m_playerSize);
	testShape.setFillColor(sf::Color::Green);
	testShape.setPosition({ m_player.getX(), m_player.getY() });
	m_window.draw(testShape);

	testShape.setSize({m_playerSize.x + 100, m_playerSize.y});
	testShape.setFillColor(sf::Color::Red);
	testShape.setPosition({ m_enemy.getX() - 100, m_enemy.getY()});
	m_window.draw(testShape);*/


	m_player.renderPlayer(m_window);
	m_enemy.render(m_window);
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
	 if (!m_enemyTexture.loadFromFile("ASSETS/IMAGES/PlayerSpriteSheet.png"))
	 {
		 std::cout << "error loading background Tetxure";
	 }
	 m_background.setTexture(m_backgroundTexture);
	 m_background.setScale(1.2, 1.5);

	 //Setup Player
	 m_playerAnimatedSprite = AnimatedSprite(m_playerTexture);

	 testShape.setFillColor(sf::Color::Blue);
	 testShape.setOutlineColor(sf::Color::Black);

	 //players texture width heigth
	 m_playerSize = { singlePlayerTextureFrameSize.x * playerScale.x ,singlePlayerTextureFrameSize.y * playerScale.y };

	 m_playerController.setX(m_playerOriginalPosition.x);
	 m_playerController.setY(m_playerOriginalPosition.y);
	 m_player = Player(m_playerAnimatedSprite,m_playerController);
	 m_player.setPlayerScale( playerScale.x,playerScale.y );

	 

	 //Setup Platform
	 m_platformTextureSize = m_platformTexture.getSize();
	 //scale set up in header
	 m_platformTextureSize.x *= m_platformScale.x;
	 m_platformTextureSize.y *= m_platformScale.y;

	 
	 sf::Vector2f testPos[MAX_FLOOR_PLATFORMS]
	 {
		 {0, static_cast<float>(SCREEN_HEIGHT - m_platformTextureSize.y)},
		 {static_cast<float>((MAX_PLATFORM_BLOCKS) * m_platformTextureSize.x) ,static_cast<float>(SCREEN_HEIGHT - m_platformTextureSize.y)}
	 };
	 
	 int platformSize = MAX_FLOOR_PLATFORMS; //amount of tiles/blocks
	 m_platFormController = PlatformController(testPos[0].x, testPos[0].y, m_platformTextureSize.x, m_platformTextureSize.y, platformSize);
	 //m_platFormController.setSpeed(m_platformSpeed);

	 for (int i = 0; i < MAX_FLOOR_PLATFORMS; i++)
	 {
		 m_floorPlatforms[i] = Platform(m_platformTexture, m_platFormController);
		 m_floorPlatforms[i].setPos( testPos[i].x,testPos[i].y );
		 m_floorPlatforms[i].setNumberOfBlocks(MAX_PLATFORM_BLOCKS);
		 m_floorPlatforms[i].setPlatformScale(m_platformScale);
	 }
	 

	 sf::Vector2f initialPlatformPos[MAX_PLATFORMS] //set initial positiions off screen
	 {
		 {SCREEN_WIDTH,100},
		 {SCREEN_WIDTH,325},
		 {SCREEN_WIDTH,550}
	 };

	 platformSize = 6;

	 for (int i = 0; i < MAX_PLATFORMS; i++)
	 {
		 
		 m_platFormController = PlatformController(initialPlatformPos[i].x, initialPlatformPos[i].y, m_platformTextureSize.x, m_platformTextureSize.y, platformSize);
		 m_platFormController.setSpeed(0);
		 m_platforms[i] = Platform(m_platformTexture, m_platFormController);
		 m_platforms[i].setNumberOfBlocks(platformSize);
		 m_platforms[i].setPlatformScale(m_platformScale);
	 }

	 //Setup Enemy
	 m_enemyController.setX(m_floorPlatforms[1].getX());
	 m_enemyController.setY(m_floorPlatforms[1].getY() - m_playerSize.y + 20);
	 m_enemyController.setSpeed(m_floorPlatforms[1].getPlatformSpeed());	
	 m_enemy = Enemy(m_playerAnimatedSprite, m_enemyController);
	 m_enemy.setScale(m_enemyScale);

	 m_startOfPlatformsClock.restart();
	 
}

void Game::checkPlatformTimes()
{
	if (platformNumber < 3)
	{
		if (m_startOfPlatformsClock.getElapsedTime().asSeconds() >= 3)
		{
			m_platforms[platformNumber].setSpeed(m_platformSpeed);
			platformNumber++;
			m_startOfPlatformsClock.restart();
		}
	}
	if (platformNumber == 3)
	{
		platformsInOrder = true;
	}
	gameRunTime = gameRunClock.getElapsedTime();

	if (platformsInOrder)
	{
		if (gameRunTime.asSeconds() > 1)
		{
			gameRunClock.restart();
			m_platformSpeed+= 3;
			m_floorPlatformSpeed += 1;
		}
		std::cout << "\nPlatform Speed: " << m_platformSpeed;

		for (int i = 0; i < MAX_PLATFORMS; i++)
		{
			m_platforms[i].setSpeed(m_platformSpeed);
		}
		for (int i = 0; i < MAX_FLOOR_PLATFORMS; i++)
		{
			m_floorPlatforms[i].setSpeed(m_floorPlatformSpeed);
		}
	}


	
}

void Game::enemyAttackPlayer()
{
	float enemyAttackCooldownTimer = 1;
	double attackTimer = 0;

	if (m_enemy.isAttackingPlayer())
	{
		attackTimer = m_enemy.getTimeSinceLastAttack();
		if (attackTimer > 1.5)
		{
			m_enemy.restartAttackTimer();
			m_player.takeDamage(1);
			m_enemy.setEnemyAttacking();

		}
	}
}

void Game::checkPlatformOffScreen()
{
	int newNumberOfPlatformBlocks = 0;
	sf::Vector2f newPlatformPosition{ 0.f,0.f };

	sf::Vector2f startPos{ SCREEN_WIDTH,static_cast<float>(SCREEN_HEIGHT - (m_platformTextureSize.y * 2)) - m_playerSize.y };

	//newPlatformPosition.y = std::rand() % static_cast<int>((SCREEN_HEIGHT - m_platforms[i].getHeight()) + m_platforms[i].getHeight());    //old code
	sf::Vector2f possiblePlatformPositions[MAX_PLATFORMS]
	{
		{SCREEN_WIDTH, startPos.y},
		{SCREEN_WIDTH, startPos.y - m_playerSize.y * 1.4f},
		{SCREEN_WIDTH, startPos.y - m_playerSize.y * 2.4f}
	};

	//chekc platform off screen
	int randNum = 0;
	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		if (m_platforms[i].isOffScreen())
		{
			newNumberOfPlatformBlocks = std::rand() % 2 + 4;
			randNum = std::rand() % 3;

			m_platforms[i].setNumberOfBlocks(newNumberOfPlatformBlocks);
			m_platforms[i].setPos(possiblePlatformPositions[randNum].x, possiblePlatformPositions[randNum].y);

			if (m_enemy.getAlive() == false)
			{
				m_enemy.setPos(m_platforms[i].getX(), m_platforms[i].getY() - m_playerSize.y + 20);
				m_enemy.setSpeed(m_platformSpeed);
				m_enemy.setEnemyState(new IdlePlayerState);
				m_enemy.setAlive(true);
			}
			if (m_enemy.isOffscreen())
			{
				m_enemy.setAlive(false);
			}

		}
	}
	for (int i = 0; i < MAX_FLOOR_PLATFORMS; i++)
	{
		if (m_floorPlatforms[i].isOffScreen())
		{
			newNumberOfPlatformBlocks = std::rand() % (MAX_PLATFORM_BLOCKS - MIN_FLOOR_BLOCKS) + MIN_FLOOR_BLOCKS;
			newPlatformPosition.x = SCREEN_WIDTH + 12; // constant here is the offset that closes gap between 2 floors.
			newPlatformPosition.y = SCREEN_HEIGHT - (m_platformTextureSize.y);
			m_floorPlatforms[i].setNumberOfBlocks(newNumberOfPlatformBlocks);
			m_floorPlatforms[i].setPos(newPlatformPosition.x, newPlatformPosition.y);
		}
	}

	

}

void Game::checkCollision()
{
	m_playerSize = { singlePlayerTextureFrameSize.x * playerScale.x ,singlePlayerTextureFrameSize.y * playerScale.y };

	RectangleCollider playerCollider(m_player.getX(), m_player.getY(), m_playerSize.x, m_playerSize.y);
	RectangleCollider enemyCollider(m_enemy.getX() - 100, m_enemy.getY(), m_playerSize.x + 100, m_playerSize.y); //well give enemy a bigger collider for attacking to the left
	RectangleCollider floorPlatformCollider[MAX_FLOOR_PLATFORMS];
	RectangleCollider platformCollider[MAX_PLATFORMS];

	int numberOfPlatformCollision = 0; //we will use this to default player to his gravity since without this he starts to sink through platforms

	//platforms in the air
	for (int i = 0; i < MAX_PLATFORMS; i++)
	{
		platformCollider[i] = RectangleCollider(m_platforms[i].getX(), m_platforms[i].getY(), m_platforms[i].getPlatformWidth(), m_platforms[i].getHeight());
		checkPlatFormCollision(playerCollider, platformCollider[i], numberOfPlatformCollision,m_platforms[i]);
	}
	//floor platforms. one is followed by another for smooth changing of holes in ground
	for (int i = 0; i < MAX_FLOOR_PLATFORMS; i++)
	{
		floorPlatformCollider[i] = RectangleCollider(m_floorPlatforms[i].getX(), m_floorPlatforms[i].getY(), m_floorPlatforms[i].getPlatformWidth(), m_floorPlatforms[i].getHeight());
		checkFloorCollision(playerCollider, floorPlatformCollider[i], numberOfPlatformCollision, m_floorPlatforms[i]);
	}
	
	if (numberOfPlatformCollision == 0)
	{
		m_player.setPlayerGravity(gravity);
		m_player.setVelocity({ 0,m_player.getVelocity().y });
		
	}

	checkEnemyCollision(playerCollider, enemyCollider);
	
}

void Game::checkPlatFormCollision(RectangleCollider& t_playerCollider, RectangleCollider& t_platformCollider, int& t_numberOfCollisions, Platform& t_platform)
{
	float xOverlap = t_playerCollider.getXOverlap(t_platformCollider);
	float yOverlap = t_playerCollider.getYOverlap(t_platformCollider);

	//first check actual collision
	if (t_playerCollider.checkCollision(t_platformCollider))
	{
		t_numberOfCollisions++;
		std::cout << "\nCOLLISION\n";
		//check above platform
		if (yOverlap > 0)
		{
			m_player.setVelocity({ 0, 0 });
			m_player.setPlayerGravity(0);
		}
		if (yOverlap < 0) //check below
		{
			m_player.setVelocity({ 0, 0 });
			m_player.setPlayerGravity(gravity);
		}
		//check left
		if (xOverlap > 90) //add in a range so that only on the edge do we get pushed back
		{

			m_player.setVelocity({ -(t_platform.getPlatformSpeed()),m_player.getVelocity().y});
			m_player.setPlayerGravity(300);
		}
		else
		{
			checkPlayerOffPosition();
		}
		
	}

}

void Game::checkFloorCollision(RectangleCollider& t_playerCollider, RectangleCollider& t_platformCollider, int& t_numberOfCollisions, Platform& t_platform)
{
	float yOverlap = t_playerCollider.getYOverlap(t_platformCollider);
	float xOverlap = t_playerCollider.getXOverlap(t_platformCollider);

	//first check actual collision
	if (t_playerCollider.checkCollision(t_platformCollider))
	{
		t_numberOfCollisions++;
		//check above platform
		if (yOverlap > 0)
		{
			m_player.setVelocity({ 0, 0 });
			m_player.setPlayerGravity(0);
		}
		if (yOverlap < 0) //check below
		{
			m_player.setVelocity({ 0, 0 });
			m_player.setPlayerGravity(gravity);
		}
		//check left
		if (xOverlap > 110) //add in a range so that only on the edge do we get pushed back
		{

			m_player.setVelocity({ -(t_platform.getPlatformSpeed()),m_player.getVelocity().y });
			m_player.setPlayerGravity(0);
		}
		else
		{
			checkPlayerOffPosition();
		}
		
		
	}
}

void Game::checkEnemyCollision(RectangleCollider& t_playerCollider, RectangleCollider& t_enemyCollider)
{
	std::cout << "\nPlayer Health: " << m_player.getHealth();
	if (m_enemy.getAlive() == true)
	{
		if (t_playerCollider.checkCollision(t_enemyCollider))
		{
			enemyAttackPlayer();
		}
	}
	
}

void Game::checkPlayerAttack()
{
	m_player.setAttacking(true);

	RectangleCollider playerCollider(m_player.getX(), m_player.getY(), m_playerSize.x, m_playerSize.y);
	RectangleCollider enemyCollider(m_enemy.getX() - 100, m_enemy.getY(), m_playerSize.x + 100, m_playerSize.y); //well give enemy a bigger collider for attacking to the left

	if (playerCollider.checkCollision(enemyCollider))
	{
		m_enemy.setAlive(false);
		m_enemy.setEnemyState(new IdlePlayerState);
	}
	
}

void Game::checkPlayerOffPosition()
{
	float returningPlayerSpeed = 50;
	if (m_player.getX() < m_playerOriginalPosition.x)
	{
		m_player.setVelocity({ returningPlayerSpeed, m_player.getVelocity().y });
	}
	else
	{
		m_player.setVelocity({ 0,m_player.getVelocity().y });
	}
}

void Game::checkPlayerEnemyDistance()
{
	m_enemy.trackPlayer({ m_player.getX(), m_player.getY() },m_platformSpeed );
}
	


