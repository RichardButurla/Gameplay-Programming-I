//Richard Buturla
//C00272345
//03/10/2022

#include "./include/GameStructs.h"
#include <cstdlib>
#include <time.h>

int maxXPos = 76;
int maxYPos = 12;

enum MenuStates {
    Exit,
    ScanForEnemies,
    LaunchMissile,
    ChooseMissileType,
    DisplayLaunchCode
};

int main()
{
    std::srand(static_cast<unsigned int>(time(0)));
    int userInput;
    MenuStates currentState;

    Missile newMissile;

    //test co-ordinates
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        newMissile.target[i].coordinates.x = rand() % maxXPos + 4;
        newMissile.target[i].coordinates.y = rand() % maxYPos + 1;

        std::cout << "Co-ords of Missile " << i << " X: " <<  newMissile.target[i].coordinates.x << " Y: " << newMissile.target[i].coordinates.y << "\n";
    }
    newMissile.setupMap();
    newMissile.setLaunchCode();

    do {
        std::cout << "\n= 0 = Exit program\n= 1 = Scan for enemy ships\n= 2 = Launch Missile \n= 3 = Choose missile type\n= 4 = Display launch code \n ";
        std::cin >> userInput;
        currentState = static_cast<MenuStates>(userInput);

        switch (currentState)
        {
        case MenuStates::Exit:
            break;

        case MenuStates::ScanForEnemies:
            newMissile.scanTarget();
            break;

        case MenuStates::LaunchMissile:
            newMissile.arm();
            break;

        case MenuStates::ChooseMissileType:
            newMissile.selectWarhead();

            break;

        case MenuStates::DisplayLaunchCode:
            newMissile.displayLaunchCode();
            break;

        default:
            break;
        }
    } while (currentState != MenuStates::Exit);



    return 0;
}