#include <iostream>
#include <math.h>

int minXRange = 10;
int minYRange = 5;

typedef struct Position
{
    float x = 10;
    float y = 20;

    void print()
    {
        std::cout << x << y;
    }

}Coordinates;

/// @brief checks whether the missile fired and a target are within range of eacthother using distance formula
/// @param t_missilePos Missile position
/// @param t_targetPos Target position
/// @return a boolean stating whether the parameters are within range of eachother
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