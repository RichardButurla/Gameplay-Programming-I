#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class SplashScreen
{
public:
	SplashScreen();
	~SplashScreen();

	void initialise(sf::Font& t_font);
	void update(sf::Time& t_deltaTime, sf::RenderWindow& t_window);
	void processInput(sf::Event& t_event);
	void render(sf::RenderWindow& t_window);
	void initializeTextures();
	void setUpSpritePerFrame(sf::Sprite& t_currentFrameSprite);

protected:
	sf::Font m_font;
	sf::Text m_splashText;

	sf::Sprite m_splashBackground;
	sf::Texture m_splashBackgroundTexture[88];

	sf::Texture m_spScreen[89];
	sf::Sprite m_bgSprite;

	sf::Sound m_sound;
	sf::SoundBuffer m_buttonSound;

	bool m_anyKeyPressed{ false }; //boolean for splash screen to close
	int count = 1;
};




