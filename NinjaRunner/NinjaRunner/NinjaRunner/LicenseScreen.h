#pragma once
#include <SFML/Graphics.hpp>
class LicenseScreen
{
public:
	LicenseScreen();
	~LicenseScreen();
	void initialise(sf::Font& t_font);
	void render(sf::RenderWindow& t_window);
	void update(sf::Time& t_deltaTime, sf::RenderWindow& t_window);
	void initialiseTextures();

protected:
	sf::Font m_font;
	sf::Text m_text;
	sf::Time m_licenseTime;

	sf::Clock m_clock;

};



