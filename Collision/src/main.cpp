//Richard Buturla
//C00272345
//03/10/2022

#include <iostream>
#include "../include/Circle.h"
#include "../include/Rectangle.h"

int main()
{
    Circle a(5,5,5);
    Circle b(5,5,6);

    Circle* p_b = &b;


     if(a.circle_to_circle(p_b) == true)
         std::cout << "Collision";

    Circle c(3,3,3);
    Circle d(7,7,5);

    Circle* p_d = &d;
    if(c.circle_to_circle(p_d) == false)
         std::cout << " No Collision";



    return 0;
}