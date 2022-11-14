#pragma once
#include "GameLogics.h"
#include "Rectangle.h"
#include <random>

const int maxLines = 15;
const int maxChars = 80;
const int MAX_ENEMIES = 5;
char textArray[maxLines][maxChars];
bool targetFound = false;
bool explosion = false;
bool missileTypeChosen = false;

enum Warhead
{
    NONE,
    EXPLOSIVE,
    INCENDIARY
};


typedef struct Enemy
{
    Coordinates coordinates;
    bool hit = false;
}Target;

struct Missile
{
    Warhead payload;
    Coordinates missileCoords;
    Target target[MAX_ENEMIES];

    int launchCode = 0;
    bool armed = false;

    void arm() {
        if (missileTypeChosen)
        {
            //insert launch code function
            insertLaunchCode();
            if (armed) {
                acquireTarget();
                checkCollision();
            }
            if (armed) {
                armed = false;
            }
            else {
                armed = true;
            }
        }
        else {
            std::cout << "Must choose missile type first! \n";
        }

    }

    void insertLaunchCode()
    {
        int input;
        std::cout << "Insert Launch Code: \n";
        std::cin >> input;
        if(input == launchCode){
            armed = true;
        }
        else{
            armed = false;
            std::cout << "Incorrect Launch Code! \n";
        }

    }

    /// @brief randomizes launch code every time we run the program
    void setLaunchCode() {
        launchCode = ((rand() % 9) * 1000) + ((rand() % 9) * 100) + ((rand() % 9) * 10) + (rand() % 10);
    }

    void displayLaunchCode() {
        std::cout << "Launch Code: " << launchCode << " \n";
    }

    //Allows player to change missile type
    void selectWarhead()
    {
        int warheadType;
        std::cout << "Select Warhead: \n" "1 for Explosive, 2 for Incendiary ";
               
        
        while(!(std::cin >> warheadType))
        {
            std::cin.clear();
            while(std::cin.get() != '\n')
            {
                continue;
            }

            std::cout << "Please select Warhead: \n" "1 for Explosive, 2 for Incendiary ";
        }

        payload = static_cast<Warhead>(warheadType);
        if(payload == Warhead::EXPLOSIVE){
            std::cout << "Explosive chosen \n";
        }
        if(payload == Warhead::INCENDIARY){
            std::cout << "Incendiary chosen \n";
        }
        missileTypeChosen = true;
    }

    void scanTarget() {

        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (isWithinRange(missileCoords, target[i].coordinates) && !target[i].hit)
            {
                std::cout << "At least one target found! \n";
                //this is the targets character which is added into the text array
                if(!target[i].hit) // No need to reveal where hit targets are
                {
                    textArray[static_cast<unsigned int>(target[i].coordinates.y)][static_cast<unsigned int>(target[i].coordinates.x)] = '*';
                }
                
            }
        }
        drawTextArea();
    }

    /// @brief sets up the map border
    void setupMapBorder()
    {
        //top side
        for (int x = 0; x < maxChars; x++) {
            textArray[0][x] = '#';
        }
        //left side
        for (int y = 0; y < maxLines; y++) {
            textArray[y][0] = '#';
        }
        //bottom side
        for (int x = 0; x < maxChars; x++) {
            textArray[maxLines - 1][x] = '#';
        }
        //right side
        for (int y = 0; y < maxLines; y++) {
            textArray[y][maxChars - 1] = '#';
        }

    }

    void acquireTarget()
    {
        std::cout << "Enter target x location between 1 - 80 inclusive: \n";

        while(!(std::cin >> missileCoords.x) || missileCoords.x < 1 || missileCoords.x > 80)
        {
            std::cin.clear();
            while(std::cin.get() != '\n')
            {
                continue;
            }

            std::cout << "Please enter target x location between 1 - 80 inclusive: \n";
        }
        std::cout << "Enter target y location between 1 - 14 inclusive: \n";

        while(!(std::cin >> missileCoords.y) || missileCoords.y < 1 || missileCoords.y > 14)
        {
            std::cin.clear();
            while(std::cin.get() != '\n')
            {
                continue;
            }

            std::cout << "Please enter target y location between 1 - 14 inclusive: \n";
        }
    }

    /// @brief sets up the map with spaces
    void setupMap()
    {
        char emptySpace = ' ';

        for (int y = 0; y < maxLines; y++)
        {
            for (int x = 0; x < maxChars; x++)
            {
                textArray[y][x] = emptySpace;
            }
        }
        setupMapBorder();
    }

    /// @brief Edits the text array to include explosion characters around the target that was destroyed
    /// @param x The targets x Position
    /// @param y The targets y Posiiton
    /// @param textArray The text Array
    void insertTextExplosion(int x, int y, char textArray[][80])
    {
        textArray[y][x - 2] = '&';
        textArray[y][x - 1] = '&';
        textArray[y][x + 1] = '&';
        textArray[y][x + 2] = '&';

        textArray[y + 1][x - 1] = '&';
        textArray[y + 1][x] = '&';
        textArray[y + 1][x + 1] = '&';

        textArray[y - 1][x - 1] = '&';
        textArray[y - 1][x] = '&';
        textArray[y - 1][x + 1] = '&';
    }

    /// @brief checks collison and leaves a missile where fired on the map
    void checkCollision()
    {
        std::cout << "\n";
        char missileTextSymbol = '!';
        int noOfTargetsMissed = 0;

       
        for (int i = 0; i < MAX_ENEMIES; i++)
        {
             //Different interactions based on Missile type. Explosive will have an area of effect
            if(payload == Warhead::EXPLOSIVE)
            {               

                //area of effect , we can almost reuse the insertTextExplosion() idea for area of effect
                //create 2 rectangles and check intersection for area of effect.
                Rectangle missileBlastRadius(missileCoords.x,missileCoords.y,2,2);
                Rectangle targetSquare(target[i].coordinates.x,target[i].coordinates.y,1,1);
                Rectangle* p_targetSquare = &targetSquare;
                    if((missileBlastRadius.rectangle_to_rectangle(p_targetSquare)) == true) //area of effect
                        {
                        target[i].hit = true;
                        std::cout << "Target hit within blast radius! \n";
                        insertTextExplosion(missileCoords.x, missileCoords.y , textArray);
                        break;
                        }

                else if (missileCoords.x == target[i].coordinates.x  && missileCoords.y == target[i].coordinates.y) //nice little touch when target is hit directly
                    { 
                        target[i].hit = true;
                        std::cout << "Target hit directly! \n";
                        insertTextExplosion(missileCoords.x, missileCoords.y , textArray);
                    }                                          
                                    
            }
            //Incendiary will be a horizontal line "spreading fire" Draw "Fire" first, then check collison and change character"
            if(payload == Warhead::INCENDIARY)
            {
                int fireLineDistance = 6;
                int plusXOffset = 1;
                int minusXOffset = 1;
                for (int f = 0; f < fireLineDistance; f++) //check postively forwards in a line
                {               
                    textArray[static_cast<unsigned int>(missileCoords.y)][static_cast<unsigned int>(missileCoords.x + plusXOffset)] = '~';
                    plusXOffset++;
                }
                for (int f = 0; f < fireLineDistance; f++) //check negatively backwards in a line
                {
                    textArray[static_cast<unsigned int>(missileCoords.y)][static_cast<unsigned int>(missileCoords.x + minusXOffset)] = '~';                   
                    minusXOffset--;
                }
            }
        } 

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if(payload == Warhead::INCENDIARY)
        {
            for (int i = 0; i < MAX_ENEMIES; i++)
            {
                int fireLineDistance = 6;
                int plusXOffset = 1;
                int minusXOffset = 1;
                for (int f = 0; f < fireLineDistance; f++) //check postively forwards in a line
                {               
                    if(missileCoords.x + plusXOffset == target[i].coordinates.x  && missileCoords.y == target[i].coordinates.y)
                    {
                            textArray[static_cast<unsigned int>(target[i].coordinates.y)][static_cast<unsigned int>(target[i].coordinates.x)] = '@';
                            target[i].hit = true;
                            std::cout << "Hit with fire";
                            break;
                    }
                    plusXOffset++;
                }
                for (int f = 0; f < fireLineDistance; f++) //check negatively backwards in a line
                {
                    if(missileCoords.x + minusXOffset == target[i].coordinates.x  && missileCoords.y == target[i].coordinates.y)
                    {
                        textArray[static_cast<unsigned int>(target[i].coordinates.y)][static_cast<unsigned int>(target[i].coordinates.x)] = '@';
                        target[i].hit = true;
                        std::cout << "Hit with fire";
                    }                 
                    minusXOffset--;
                }
                if (missileCoords.x == target[i].coordinates.x  && missileCoords.y == target[i].coordinates.y) //nice little touch when target is hit directly
                { 
                    target[i].hit = true;
                    std::cout << "Target hit directly! \n";
                    insertTextExplosion(missileCoords.x, missileCoords.y , textArray);
                }            
            }  
        } 
       
        for (int i = 0; i< MAX_ENEMIES; i++)
        {
            if(!target[i].hit) 
            {
                noOfTargetsMissed++;
                textArray[static_cast<unsigned int>(missileCoords.y)][static_cast<unsigned int>(missileCoords.x)] = missileTextSymbol;

            }
        }
        
        std::cout << noOfTargetsMissed << " Targets Left \n";
        //draw text array
        drawTextArea();
    }

    //Just draws the map
    void drawTextArea()
    {
        for (int y = 0; y < maxLines; y++)
        {
            for (int x = 0; x < maxChars; x++)
            {
                std::cout << textArray[y][x];
            }
            std::cout << "\n";
        }
        for (int i = 0; i < 2; i++) { //just for spacing
            std::cout << "\n";
        }
    }


};


