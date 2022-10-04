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
    newMissile.target.coordinates.x = rand() % 21;
    newMissile.target.coordinates.y = rand() % 13;

do{
    std::cout << "= 0 = Exit program\n= 1 = Scan for enemy ships\n= 2 = Launch Missile \n= 3 = Choose missile type\n= 4 = Display launch code \n ";
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