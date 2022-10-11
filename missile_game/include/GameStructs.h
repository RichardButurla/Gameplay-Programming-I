#pragma once
#include "GameLogics.h"
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
        std::cout << "Select Warhead: \n" "1 for Explosive, 2 for Nuclear ";

        std::cin >> warheadType;
        while (warheadType != 1 && warheadType != 2)
        {
            std::cout << "Please select Warhead: \n" "1 for Explosive, 2 for Nuclear";
            std::cin >> warheadType;
        }
        payload = static_cast<Warhead>(warheadType);
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
        std::cout << "Enter target x location: \n";
        std::cin >> missileCoords.x;
        std::cout << "Enter target y location: \n";
        std::cin >> missileCoords.y;
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

       
            
        //Different interactions based on Missile type
        if(payload == Warhead::EXPLOSIVE)
        {               

            //area of effect , we can almost reuse the insertTextExplosion() idea for area of effect
            for (int i = 0; i < MAX_ENEMIES; i++)
            {
                if((missileCoords.x + 1 == target[i].coordinates.x  && missileCoords.y == target[i].coordinates.y) ||
                    (missileCoords.x - 1 == target[i].coordinates.x  && missileCoords.y == target[i].coordinates.y) ||
                    (missileCoords.x == target[i].coordinates.x  && missileCoords.y + 1 == target[i].coordinates.y) ||
                    (missileCoords.x + 1 == target[i].coordinates.x  && missileCoords.y + 1 == target[i].coordinates.y) ||
                    (missileCoords.x - 1 == target[i].coordinates.x  && missileCoords.y + 1 == target[i].coordinates.y) ||
                    (missileCoords.x == target[i].coordinates.x  && missileCoords.y - 1 == target[i].coordinates.y) ||
                    (missileCoords.x + 1 == target[i].coordinates.x  && missileCoords.y - 1 == target[i].coordinates.y) ||
                    (missileCoords.x - 1 == target[i].coordinates.x  && missileCoords.y - 1 == target[i].coordinates.y)) //area of effect
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
        }
        if(payload == Warhead::INCENDIARY)
        {

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


