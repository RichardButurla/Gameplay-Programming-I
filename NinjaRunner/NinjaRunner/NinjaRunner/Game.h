#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Player.h"
#include "Platform.h"
#include "Events.h"
#include "Debug.h"
#include "RectangleCollider.h"

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

	void checkPlatformOffScreen();
	void checkCollision();
	void checkPlatFormCollision(RectangleCollider& t_playerCollider, RectangleCollider t_platformCollider, int t_platfromIndex, int& t_numberOfCollisions);
	void checkPlatFormCollision();
	


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen

	sf::Vector2f singlePlayerTextureFrameSize = { 363, 458 };
	sf::Vector2f playerScale = { 0.3,0.3};
	sf::Texture m_playerTexture;
	AnimatedSprite m_playerAnimatedSprite;
	Player m_player;
	PlayerController m_playerController;

	sf::Vector2f m_platformScale{ 0.3,0.3 };
	Platform m_floorPlatform;
	PlatformController m_floorPlatFormController;

	static const int MAX_PLATFORMS = 3;
	Platform m_platforms[MAX_PLATFORMS];
	PlatformController m_platFormController;
	sf::Texture m_platformTexture;

	gpp::Events & m_input;
	gpp::Events input;
	gpp::Events ai;

	bool m_exitGame; // control exiting game

};


