#pragma once
#include <SFML/Graphics.hpp>



class Box
{
public:
	Box() = default;
	Box(float t_x, float t_y, float t_width, float t_height);
	Box(sf::Vector2f t_position, float t_width, float t_height);

	bool rectangle_to_rectangle(Box* b);
	bool valueInRange(float value, float min, float max);

	float getX() { return m_position.x; }
	float getY() { return m_position.y; }
	float getWidth() { return width; }
	float getHeight() { return height; }

	void setWidth(float t_width) { width = t_width; }
	void setHeight(float t_height) { height = t_height; }
	void setSize(float t_width, float t_height) { m_rectangleShape.setSize({ t_width,t_height }); }
	void setColor(sf::Color t_color) { m_rectangleShape.setFillColor(t_color);}


	void update();
	void render(sf::RenderWindow& t_window);
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

class RayLine
{
public:

	RayLine(sf::Vector2f t_start, sf::Vector2f t_end);
	RayLine();

	void draw(sf::RenderWindow& t_window);
	sf::Vector2f getEndPoint() const;
	sf::Vector2f getStartPoint() const;
	sf::Vector2f getDirection() const;
	float getDistance()const;
	void setColor(sf::Color t_color);
	void setStartPoint(sf::Vector2f t_position);
	void setEndPoint(sf::Vector2f t_position);
	void setPrimitiveType(sf::PrimitiveType t_type) { m_line.setPrimitiveType(t_type); }


private:
	sf::VertexArray m_line;
	sf::Vector2f m_points[2]; //2 beacuse a line has 2 points


};

class Polygon
{
public:

	Polygon() = default;
	Polygon(sf::Vector2f t_position, sf::Vector2f t_size);
	void draw(sf::RenderWindow& t_window);
	void update();
	void setPrimitiveType(sf::PrimitiveType t_type) { m_polygonPoints.setPrimitiveType(t_type); }
	sf::Vector2f getCenterPos(){return m_centerPoint;}
	sf::Vector2f getPointPosition(int t_pointIndex);
	void setColor(sf::Color t_color);

private:
	sf::Color m_color;
	sf::Vector2f m_centerPoint = {0,0};
	sf::Vector2f m_velocity{-1,0};
	sf::VertexArray m_polygonPoints; //we will only making a triangle polygon for now
	sf::Vector2f m_pointPositions[3]; //same here



};



