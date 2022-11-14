#pragma once
class Circle{

public:

Circle() = default;
Circle(float t_x,float t_y, float t_radius);

bool circle_to_circle( Circle* b);

private:

float x;
float y;
float radius;

};