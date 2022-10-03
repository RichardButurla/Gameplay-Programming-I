//Richard Buturla
//C00272345
//03/10/2022

#include "./include/GameStructs.h"
#include <random>

enum class MenuStates{
    Exit,
    ScanForEnemies,
    LaunchMissile,
    ChooseMissileType,
    DisplayLaunhCode
};

int main()
{
    std::srand(static_cast<unsigned int>(time(nullptr)));
    int userInput;
    MenuStates currentState;
    
    Missile newMissile;
    
    //test co-ordinates
    newMissile.target.coordinates.x = rand() % 21;
    newMissile.target.coordinates.y = rand() % 21;

do{
    std::cout << "= 0 = Exit program\n= 1 = Scan for enemy ships\n= 2 = Launch Missile \n= 3 = Choose missile type\n= 4 = Display launch code \n ";
    std::cin >> userInput;
    currentState = static_cast<MenuStates>(userInput);

    switch (currentState)
            {
            case MenuStates::Exit:
                break;

            case MenuStates::ScanForEnemies:
                break;

            case MenuStates::LaunchMissile:
            newMissile.acquireTarget();
            newMissile.arm();
            newMissile.checkCollision();
                break;

            case MenuStates::ChooseMissileType:
            newMissile.selectWarhead();
                break;

            case MenuStates::DisplayLaunhCode:
                break;

            default:
                break;
            }
} while (currentState != MenuStates::Exit);
        


    return 0;
}