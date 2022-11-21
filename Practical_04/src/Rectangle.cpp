#include <iostream>
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



