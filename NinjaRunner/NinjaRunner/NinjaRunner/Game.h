#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Events.h"
#include "Debug.h"

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

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen

	sf::Texture m_playerTexture;
	AnimatedSprite m_playerAnimatedSprite;
	Player m_player;

	gpp::Events & m_input;
	gpp::Events input;
	gpp::Events ai;

	bool m_exitGame; // control exiting game

};


