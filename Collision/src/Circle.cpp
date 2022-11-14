#include "../include/Circle.h"
#include <math.h>

Circle::Circle(float t_x,float t_y, float t_radius) : x(t_x), y(t_y), radius(t_radius)
{

}

bool Circle::circle_to_circle( Circle* b)
{
float distance;
distance = sqrt((b->x - this->x ) * (b->x - this->x) + ( (b->y - this->y ) * (b->y - this->y) ));

if(distance < this->radius || distance < b->radius ){
    return true;
} 
return false;
}

