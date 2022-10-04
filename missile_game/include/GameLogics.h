#include <iostream>
#include <math.h>

int minXRange = 5;
int minYRange = 6;

typedef struct Position
{
    float x = 10;
    float y = 20;

    void print()
    {
        std::cout << x << y;
    }

}Coordinates;

bool isWithinRange(struct Position t_missilePos, struct Position t_targetPos)
{
    float xDistance = t_targetPos.x - t_missilePos.x;
    float yDistance = t_targetPos.y - t_missilePos.y;

    xDistance = sqrt(xDistance * xDistance);
    yDistance = sqrt(yDistance * yDistance);

    if (xDistance < minXRange && yDistance < minYRange) {
        return true;
    }
    return false;
}