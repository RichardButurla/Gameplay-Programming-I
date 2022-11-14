//Richard Buturla
//C00272345
//03/10/2022

#include "./include/GameStructs.h"
#include <cstdlib>
#include <time.h>

//Map Size, Max values are actually a bit bigger but we need to avoid 0 and 80 becaus eof our array
int maxXPos = 76; //Max is 80
int maxYPos = 12; //Max is 14

// Controls what actions we are performing in the game
enum MenuStates {
    Exit,
    ScanForEnemies,
    LaunchMissile,
    ChooseMissileType,
    DisplayLaunchCode
};

int main()
{
    ////////////////////////////////////////////
    //////////// Testing ///////////////////////
    //////////////////////////////////////////// 
    std::cout << "Testing Circles: \n";
    Circle a(5,5,5);
    Circle b(5,5,6);

    Circle* p_b = &b;


     if(a.circle_to_circle(p_b) == true)
         std::cout << "Collision\n";

    Circle c(3,3,3);
    Circle d(7,7,5);

    Circle* p_d = &d;
    if(c.circle_to_circle(p_d) == false)
         std::cout << " No Collision\n";


    std::cout <<"Testing Rectangles: \n";
    Rectangle rectA(10,10,5,5);
    Rectangle rectB(5,5,5,5);

    Rectangle* p_rectB = &rectB;

    if(rectA.rectangle_to_rectangle(p_rectB) == true)
    {
        std::cout << "Collision\n";
    }

    Rectangle rectC(15,15,3,3);
    Rectangle rectD(5,5,5,5);

    Rectangle* p_rectD = &rectD;

    if(rectC.rectangle_to_rectangle(p_rectD) == false)
    {
        std::cout << "No Collision\n";
    }

    ///////////////////////////////////////////


    std::srand(static_cast<unsigned int>(time(0))); //seed for generation
    int userInput;
    MenuStates currentState;

    Missile newMissile;

    //randomises co-ordinates of targets
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

        while (!(std::cin >> userInput)){
                std::cin.clear();
                while (std::cin.get() != '\n') //Skips over bad data and reads new input
                continue;
                std::cout << "Enter a number from 0 - 4: ";  
                }
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