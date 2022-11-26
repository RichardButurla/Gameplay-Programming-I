#include <iostream>
#include <math.h>
#include "../include/Rectangle.h"


Box::Box(float t_x, float t_y, float t_width, float t_height) : width(t_width), height(t_height)
{
    m_position.x = t_x;
    m_position.y = t_y;
}

Box::Box(sf::Vector2f t_position, float t_width, float t_height) : m_position(t_position), width(t_width), height(t_height)
{

}

void Box::update()
{
    move();
}

void Box::render(sf::RenderWindow& t_window)
{
    t_window.draw(m_rectangleShape);
}

void Box::move()
{
    m_position += m_velocityVector;
    m_rectangleShape.setPosition(m_position);
}

void Box::setupRectangle(sf::Color t_color)
{
    m_rectangleShape.setFillColor(t_color);
    m_rectangleShape.setSize({ width, height });
    m_rectangleShape.setPosition(m_position);
}

bool Box::rectangle_to_rectangle(Box* b)
{
    bool xOverlap;
    bool yOverlap;

    xOverlap = valueInRange(this->m_position.x, b->m_position.x, b->m_position.x + b->width) || valueInRange(b->m_position.x, this->m_position.x, this->m_position.x + this->width);
    yOverlap = valueInRange(this->m_position.y, b->m_position.y, b->m_position.y + b->height) || valueInRange(b->m_position.y, this->m_position.y, this->m_position.y + this->height);

    return xOverlap && yOverlap;
}

bool Box::valueInRange(float value, float min, float max)
{
    return (value >= min) && (value <= max);
}


///////////////////////////////////////////

RayLine::RayLine()
{
    
}

RayLine::RayLine(sf::Vector2f t_start, sf::Vector2f t_end) :
    m_points{ t_start, t_end }
{
    m_line.append({ t_start, sf::Color::Black });
    m_line.append({ t_end, sf::Color::Black });
}

void RayLine::draw(sf::RenderWindow& t_window)
{
    t_window.draw(m_line);
}

sf::Vector2f RayLine::getStartPoint() const
{
    return m_points[0];
}

sf::Vector2f RayLine::getEndPoint() const
{
    return m_points[1];
}

sf::Vector2f RayLine::getDirection() const
{
    const sf::Vector2f distanceVector = m_points[1] - m_points[0];
    const float magnitude = sqrtf((distanceVector.x * distanceVector.x) + (distanceVector.y * distanceVector.y));

    return distanceVector / magnitude;
}

float RayLine::getDistance() const 
{
    const sf::Vector2f distanceVector = m_points[1] - m_points[0];
    return sqrtf((distanceVector.x * distanceVector.x) + (distanceVector.y * distanceVector.y));
}

void RayLine::setColor(sf::Color t_color)
{
    m_line.clear();
    m_line.append({ m_points[0], t_color });
    m_line.append({ m_points[1], t_color });
}

void RayLine::setStartPoint(sf::Vector2f t_position)
{
    m_points[0] = t_position;
    sf::Color rayColor = m_line[0].color;

    m_line.clear();
    m_line.append({ m_points[0], rayColor });
    m_line.append({ m_points[1], rayColor });
}

void RayLine::setEndPoint(sf::Vector2f t_position)
{
    m_points[1] = t_position;
    sf::Color rayColor = m_line[0].color;

    m_line.clear();
    m_line.append({ m_points[0], rayColor });
    m_line.append({ m_points[1], rayColor });
}


Polygon::Polygon(sf::Vector2f t_position, sf::Vector2f t_size) : m_pointPositions{
        {t_position.x + (t_size.x / 2.0f), t_position.y},
        {t_position.x + t_size.x, t_position.y + t_size.y},
        {t_position.x, t_position.y + t_size.y}}, m_centerPoint(t_position)
{
    m_polygonPoints.append({ {m_pointPositions[0]}, sf::Color::Black });
    m_polygonPoints.append({ {m_pointPositions[1]}, sf::Color::Black });
    m_polygonPoints.append({ {m_pointPositions[2]}, sf::Color::Black });
}

void Polygon::update()
{
    m_pointPositions[0] += m_velocity;
    m_pointPositions[1] += m_velocity;
    m_pointPositions[2] += m_velocity;

    m_polygonPoints.clear();
    for (int i = 0; i < 3; i++)
    {
        m_polygonPoints.append({ m_pointPositions[i], m_color });
    }
}

void Polygon::draw(sf::RenderWindow& t_window)
{
    t_window.draw(m_polygonPoints);
}

sf::Vector2f Polygon::getPointPosition(int t_pointIndex)
{
    return m_pointPositions[t_pointIndex];
}

void Polygon::setColor(sf::Color t_color)
{
    m_color = t_color;
    m_polygonPoints.clear();
    for (int i = 0; i < 3; i++)
    {
        m_polygonPoints.append({ m_pointPositions[i], m_color });
    }
}

