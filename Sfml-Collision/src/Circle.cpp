#include "../include/Circle.h"
#include <math.h>

Circle::Circle(float t_x, float t_y, float t_radius = 50) : radius(t_radius)
{
    m_position.x = t_x;
    m_position.y = t_y;
}

Circle::Circle(sf::Vector2f t_position, float t_radius) : m_position(t_position), radius(t_radius)
{

}

void Circle::update()
{
    move();
}

void Circle::render(sf::RenderWindow& t_window)
{
    t_window.draw(circleShape);
}

void Circle::move()
{
    m_position += m_velocityVector;
    circleShape.setPosition(m_position);
}

void Circle::setupCircle(sf::Color t_color)
{
    circleShape.setFillColor(t_color);
    circleShape.setRadius(radius);
    circleShape.setPosition(m_position);
}

bool Circle::circle_to_circle(Circle* b)
{
    float distance;
    distance = sqrt((b->m_position.x - this->m_position.x) * (b->m_position.x - this->m_position.x) + ((b->m_position.y - this->m_position.y) * (b->m_position.y - this->m_position.y)));

    if (distance < this->radius + b->radius) {
        return true;
    }
    return false;
}
