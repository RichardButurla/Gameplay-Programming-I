#include <iostream>
#include "../include/Rectangle.h"


Rectangle::Rectangle(float t_x, float t_y, float t_width, float t_height) : width(t_width), height(t_height)
{
    m_position.x = t_x;
    m_position.y = t_y;
}

Rectangle::Rectangle(sf::Vector2f t_position, float t_width, float t_height) : m_position(t_position), width(t_width), height(t_height)
{

}

void Rectangle::update()
{
    move();
}

void Rectangle::render(sf::RenderWindow& t_window)
{
    t_window.draw(m_rectangleShape);
}

void Rectangle::move()
{
    m_position += m_velocityVector;
    m_rectangleShape.setPosition(m_position);
}

void Rectangle::setupRectangle(sf::Color t_color)
{
    m_rectangleShape.setFillColor(t_color);
    m_rectangleShape.setSize({ width, height });
    m_rectangleShape.setPosition(m_position);
}

bool Rectangle::rectangle_to_rectangle(Rectangle* b)
{
    bool xOverlap;
    bool yOverlap;

    xOverlap = valueInRange(this->m_position.x, b->m_position.x, b->m_position.x + b->width) || valueInRange(b->m_position.x, this->m_position.x, this->m_position.x + this->width);
    yOverlap = valueInRange(this->m_position.y, b->m_position.y, b->m_position.y + b->height) || valueInRange(b->m_position.y, this->m_position.y, this->m_position.y + this->height);

    return xOverlap && yOverlap;
}

bool Rectangle::valueInRange(float value, float min, float max)
{
    return (value >= min) && (value <= max);
}

