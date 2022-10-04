#include "GameLogics.h"


const int maxLines = 15;
const int maxChars = 80;
const int MAX_ENEMIES = 5;
char textArray[maxLines][maxChars];
bool targetFound = false;
bool explosion = false;

enum class Warhead
{
    NONE,
    EXPLOSIVE,
    NUCLEAR
};


typedef struct Enemy
{
    Coordinates coordinates;
}Target;

struct Missile
{
    Warhead payload;
    Coordinates missileCoords;
    Target target[MAX_ENEMIES];


    bool armed = false;

    void arm() {
        if (armed) {
            armed = false;
        }
        else {
            armed = true;
        }
    }
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
    }
    void scanTarget() {

        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (isWithinRange(missileCoords, target[i].coordinates))
            {
                std::cout << "At least one target found! \n";
                textArray[static_cast<unsigned int>(target[i].coordinates.y)][static_cast<unsigned int>(target[i].coordinates.x)] = '*';
            }
        }
        drawTextArea();
    }
    void acquireTarget()
    {
        std::cout << "Enter target x location: \n";
        std::cin >> missileCoords.x;
        std::cout << "Enter target y location: \n";
        std::cin >> missileCoords.y;
    }
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
    }
    void drawTextExplosion(int x, int y, char textArray[][80])
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
    void checkCollision()
    {
        std::cout << "\n";
        char missileTextSymbol = '!';

        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (missileCoords.x == target[i].coordinates.x && missileCoords.y == target[i].coordinates.y) {
                std::cout << "Target hit ";
            }
            else {
                std::cout << "Missed ";
                textArray[static_cast<unsigned int>(missileCoords.y)][static_cast<unsigned int>(missileCoords.x)] = missileTextSymbol;
            }
        }



        for (int i = 0; i < MAX_ENEMIES; i++)
        {
            if (missileCoords.x == target[i].coordinates.x &&
                missileCoords.y == target[i].coordinates.y) {
                explosion = true;

                if (explosion)
                    drawTextExplosion(target[i].coordinates.x, target[i].coordinates.y, textArray);
            }
        }





        //draw text
        drawTextArea();
    }
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
        for (int i = 0; i < 5; i++) { //just for spacing
            std::cout << "\n";
        }
    }


};


