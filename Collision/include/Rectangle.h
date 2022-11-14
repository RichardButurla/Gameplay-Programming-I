#pragma once
class Rectangle
{
public:
 bool rectangle_to_rectangle( Rectangle* b);
 bool valueInRange(float value, float min, float max);

private:
float x;
float y;
float width;
float height;
};