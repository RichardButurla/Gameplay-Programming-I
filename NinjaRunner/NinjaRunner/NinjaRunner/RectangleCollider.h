#pragma once
class RectangleCollider
{
public:
    RectangleCollider(float t_x, float t_y, float t_width, float t_height) : x(t_x), y(t_y), width(t_width), height(t_height) {};
    bool checkCollision(RectangleCollider& t_collider);
    bool checkXCollision(RectangleCollider& t_collider);

    float getXOverlap(RectangleCollider& t_collider);
    float getYOverlap(RectangleCollider& t_collider);

    bool valueInRange(float value, float min, float max) { return (value >= min) && (value <= max); }
private:
    float x;
    float y;
    float width;
    float height;
};
