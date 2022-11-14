#include <iostream>
#include "../include/Rectangle.h"

 Rectangle::Rectangle(float t_x, float t_y, float t_width, float t_height) : x(t_x), y(t_y), width(t_width), height(t_height)
 {

 }

 bool Rectangle::rectangle_to_rectangle( Rectangle* b)
 {
     bool xOverlap;
     bool yOverlap;

     xOverlap = valueInRange(this->x,b->x, b->x + b->width) || valueInRange(b->x,this->x, this->x + this->width);
     yOverlap = valueInRange(this->y,b->y, b->y + b->height) || valueInRange(b->y,this->y, this->y + this->height);

     return xOverlap && yOverlap;
 }

  bool Rectangle::valueInRange(float value, float min, float max)
  {
      return (value>=min) && (value <= max);
  }