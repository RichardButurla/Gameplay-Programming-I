#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Player.h"
#include "Platform.h"
#include "Events.h"
#include "Debug.h"
#include "RectangleCollider.h"
#include "Enemy.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeyPress(sf::Event t_event);
	void processKeyRelease(sf::Event t_event);
	void processKeyPressFSM(sf::Event t_event);
	void processKeyReleaseFSM(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void checkTimers();

	void enemyAttackPlayer();

	void checkGameText();
	void checkPlatformOffScreen();
	void checkCollision();
	void checkPlatFormCollision(RectangleCollider& t_playerCollider, RectangleCollider& t_platformCollider, int& t_numberOfCollisions, Platform& t_platform);
	void checkFloorCollision(RectangleCollider& t_playerCollider, RectangleCollider& t_platformCollider, int& t_numberOfCollisions, Platform& t_platform);
	void checkEnemyCollision(RectangleCollider& t_playerCollider, RectangleCollider& t_enemyCollider);
	void checkPlayerAttack();
	void checkPlayerOffPosition();
	void checkPlayerEnemyDistance();
	


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_gameScoreText; // text used for message on screen
	double m_gameScore = 0;
	float scoreIncrement = 0.032;
	float scoreMultiplier = 1;
	sf::Clock m_scoreClock;
	sf::Time m_scoreTime;

	sf::RectangleShape testShape;

	sf::Sprite m_background;
	sf::Texture m_backgroundTexture;

	sf::Clock gameRunClock;
	sf::Time gameRunTime;

	sf::Vector2f m_playerSize{ singlePlayerTextureFrameSize.x * playerScale.x ,singlePlayerTextureFrameSize.y * playerScale.y };
	sf::Vector2f singlePlayerTextureFrameSize = { 363, 500 }; //363x
	sf::Vector2f playerScale = { 0.3,0.3};
	sf::Texture m_playerTexture;
	AnimatedSprite m_playerAnimatedSprite;
	Player m_player;
	PlayerController m_playerController;
	sf::Vector2f m_playerOriginalPosition{ 300,0 };

	static const int MAX_FLOOR_PLATFORMS = 2;
	sf::Vector2f m_platformScale{ 0.2,0.2 };
	Platform m_floorPlatforms[MAX_FLOOR_PLATFORMS];
	PlatformController m_floorPlatFormController;

	static const int MAX_PLATFORMS = 3;
	Platform m_platforms[MAX_PLATFORMS];
	PlatformController m_platFormController;
	sf::Texture m_platformTexture;
	sf::Vector2u m_platformTextureSize;
	sf::Clock m_startOfPlatformsClock;
	sf::Clock m_floorPlatformClock;
	sf::Time m_floorPlatformTime;
	float m_platformSpeed = 400;
	float m_floorPlatformSpeed = 400;
	bool platformsInOrder{ false };
	int platformNumber = 0;
	bool firstOffscreenOccurance{ false };

	sf::Texture m_enemyTexture;
	sf::Vector2f m_enemyScale{ -playerScale.x,playerScale.y };
	Enemy m_enemy;
	EnemyController m_enemyController;

	gpp::Events & m_input;
	gpp::Events input;
	gpp::Events ai;

	bool m_exitGame; // control exiting game

};


