#include <iostream>
#include <math.h>

int minXRange = 7;
int minYRange = 5;

typedef struct Position
{
    int x = 10;
    int y = 20;

    void print()
    {
        std::cout << x << y;
    }

}Coordinates;

bool isWithinRange(struct Position t_missilePos, struct Position t_targetPos)
{
bool withinRange = false;
   if( sqrt((t_targetPos.x * t_targetPos.x)) - sqrt((t_missilePos.x * t_missilePos.x)) < minXRange &&
        sqrt((t_targetPos.y * t_targetPos.y)) - sqrt((t_missilePos.y * t_missilePos.y)) < minYRange){
    withinRange = true;
   }
   return withinRange;
}