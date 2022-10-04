//Richard Buturla
//C00272345
//03/10/2022

#include "./include/GameStructs.h"
#include <random>

int maxXPos = 19;
int maxYPos = 13;

enum class MenuStates{
    Exit,
    ScanForEnemies,
    LaunchMissile,
    ChooseMissileType,
    DisplayLaunchCode
};

int main()
{
    std::srand(static_cast<unsigned int>(time(nullptr)));
    int userInput;
    bool firedMissileFirst = false;
    MenuStates currentState;
    
    Missile newMissile;
    
    //test co-ordinates
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        newMissile.target[0].coordinates.x = 1;
        newMissile.target[0].coordinates.y = 1;

        newMissile.target[4].coordinates.x = 19;
        newMissile.target[4].coordinates.y = 13;

        newMissile.target[2].coordinates.x = 1;
        newMissile.target[2].coordinates.y = 13;

        newMissile.target[3].coordinates.x = 19;
        newMissile.target[3].coordinates.y = 1;

        newMissile.target[1].coordinates.x = 9;
        newMissile.target[1].coordinates.y =7;

    }
    newMissile.setupMap();

do{
    std::cout << "\n= 0 = Exit program\n= 1 = Scan for enemy ships\n= 2 = Launch Missile \n= 3 = Choose missile type\n= 4 = Display launch code \n ";
    std::cin >> userInput;
    currentState = static_cast<MenuStates>(userInput);

    switch (currentState)
            {
            case MenuStates::Exit:
                break;

            case MenuStates::ScanForEnemies:
            if(firedMissileFirst){
                newMissile.scanTarget();
            }
            else{
                std::cout << "Must fire one missile to configure scan area\n";
            }
                break;

            case MenuStates::LaunchMissile:
            if(newMissile.armed){
                newMissile.acquireTarget();
                newMissile.checkCollision();
                firedMissileFirst = true;
            }
            else{
                std::cout << "You must arm a missile with one type first!\n";
            }
                break;

            case MenuStates::ChooseMissileType:
            newMissile.selectWarhead();
            newMissile.arm();
                break;

            case MenuStates::DisplayLaunchCode:
                break;

            default:
                break;
            }
} while (currentState != MenuStates::Exit);
        


    return 0;
}