#pragma once
#include "../include/cute_c2.h"
#include <SFML/Graphics.hpp>



class Box
{
public:
    Box() = default;
    Box(float t_x, float t_y, float t_width, float t_height);
	Box(sf::Vector2f t_position, float t_width, float t_height);

    bool rectangle_to_rectangle(Box* b);
    bool valueInRange(float value, float min, float max);

	float getX(){return m_position.x;}
	float getY(){return m_position.y;}

	void setWidth(float t_width){width = t_width;}
	void setHeight(float t_height){height = t_height;}


	void update();
	void render(sf::RenderWindow & t_window);
	void move();

	void setVelocity(sf::Vector2f t_velocity) { m_velocityVector = t_velocity; }
	void setPosition(sf::Vector2f t_position) { m_position = t_position; }

	sf::Vector2f getVelocity() { return m_velocityVector; }

	void setupRectangle(sf::Color t_color);

private:
	float width{ 25 };
	float height{ 25 };

	sf::RectangleShape m_rectangleShape;
	sf::Vector2f m_position{ 0.0f,0.0f };
	sf::Vector2f m_velocityVector{ 2,2 };
};
