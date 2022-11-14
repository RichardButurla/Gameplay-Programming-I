#pragma once
class Rectangle
{
public:
    Rectangle() = default;
    Rectangle(float t_x, float t_y, float t_width, float t_height);
 bool rectangle_to_rectangle( Rectangle* b);
 bool valueInRange(float value, float min, float max);

private:
float x;
float y;
float width;
float height;
};