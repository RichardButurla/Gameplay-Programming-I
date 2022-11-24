#pragma once
#include <SFML/Graphics.hpp>

class Circle {

public:

	Circle() = default;
	Circle(float t_x, float t_y, float t_radius);
	Circle(sf::Vector2f t_position, float t_radius);
	

	float getX(){return m_position.x;}
	float getY(){return m_position.y;}
	float getRadius(){return radius;}
	sf::Vector2f getPosition(){return m_position;}

	void setRadius(float t_radius){circleShape.setRadius(t_radius); radius = t_radius;}
	void setPointCount(int t_points){circleShape.setPointCount(t_points);}
	sf::CircleShape returnShape(){return circleShape;}


	void update();
	void render(sf::RenderWindow & t_window);
	void move();

	void setVelocity(sf::Vector2f t_velocity) { m_velocityVector = t_velocity; }
	void setPosition(sf::Vector2f t_position) { m_position = t_position; }

	sf::Vector2f getVelocity() { return m_velocityVector; }

	void setupCircle(sf::Color t_color);
	bool circle_to_circle(Circle* b);

private:

	float radius{ 50 };
	sf::CircleShape circleShape;
	sf::Vector2f m_position{ 0.0f,0.0f };
	sf::Vector2f m_velocityVector{ 0,0 };

};