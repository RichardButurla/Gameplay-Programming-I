//Richard Buturla
//C00272345
//03/10/2022

#include "./include/GameStructs.h"

enum class MenuStates{
    Exit,
    ScanForEnemies,
    LaunchMissile,
    ChooseMissileType,
    DisplayLaunhCode
};

int main()
{
    int userInput;
    MenuStates currentState;
    
    Missile newMissile;
    
    //test co-ordinates
    newMissile.target.coordinates.x = 10;
    newMissile.target.coordinates.y = 10;

do{
    std::cout << "= 0 = Exit program \n = 1 = Scan for enemy ships = 2 \n= Launch Missile = 3 \n = Choose missile type = 4 \n= Display launch code \n ";
    std::cin >> userInput;
    currentState = static_cast<MenuStates>(userInput);

    switch (currentState)
            {
            case MenuStates::Exit:
                break;

            case MenuStates::ScanForEnemies:
                break;

            case MenuStates::LaunchMissile:
            newMissile.launchCode();
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