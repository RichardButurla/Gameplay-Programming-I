#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class GameOverScreen
{
public:
	GameOverScreen();
	~GameOverScreen();

	void initialise(sf::Font& t_font);
	void processInput(sf::Event& t_event);
	void update(sf::Time& t_deltatime, int  t_gameScore);
	void render(sf::RenderWindow& t_window);

protected:
	sf::Text m_gameOverText;
	sf::Font m_font;

	sf::Sprite m_bgSprite;
	sf::Texture m_bgTexture;

	sf::Sound m_sound;
	sf::SoundBuffer m_buttonSound;

	bool m_pressedExit{ false };
};

