#pragma once
#include "RectangleCollider.h"

bool RectangleCollider::checkCollision(RectangleCollider& t_collider)
{
    bool xOverlap;
    bool yOverlap;

    xOverlap = valueInRange(this->x, t_collider.x, t_collider.x + t_collider.width) || valueInRange(t_collider.x, this->x, this->x + this->width);
    yOverlap = valueInRange(this->y, t_collider.y, t_collider.y + t_collider.height) || valueInRange(t_collider.y, this->y, this->y + this->height);

    return xOverlap && yOverlap;
}
bool RectangleCollider::checkXCollision(RectangleCollider& t_collider)
{
    bool xOverlap;

    xOverlap = valueInRange(this->x, t_collider.x, t_collider.x + t_collider.width) || valueInRange(t_collider.x, this->x, this->x + this->width);

    return xOverlap;
}

bool RectangleCollider::aboveRectCollision(RectangleCollider& t_other)
{
    return (this->y <= t_other.y);
}