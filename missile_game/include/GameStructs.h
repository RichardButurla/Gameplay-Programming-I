#include <iostream>
#include <math.h>
#include "GameLogic.h"

enum class Warhead
{NONE,
EXPLOSIVE,
NUCLEAR};




typedef struct Position
{
    int x = 10;
    int y = 20;

    void print()
    {
        std::cout << x << y;
    }

}Coordinates;

typedef struct Enemy
{
    Coordinates coordinates;
}Target;

struct Missile
{
    Warhead payload;
    Coordinates coordinates;
    Target target;

    bool armed;

    void arm(){
        if(armed){
            armed = false;
        }
        else{
            armed = true;
        }
    }
    void update(){
        coordinates.x += 1;
        coordinates.y += 2;
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
    void acquireTarget()
    {
        std::cout << "Enter target x location: \n";
        std::cin >> coordinates.x;
        std::cout << "Enter target y location: \n";
        std::cin >> coordinates.y;
    }
    void checkCollision()
    {

        if(coordinates.x == target.coordinates.x && coordinates.y == target.coordinates.y)
        {
            std::cout << "Target hit \n";
        }
        else
        {
            std::cout << "Missed \n";
        }

        //what if we send text flyiong downwards at the enemy??
        //We need to make space in the terminal using textGapSize and a delay to make it look appealing.
        // int textGapSize = 70; //gap for space
        // int targetTextGapSize = textGapSize + target.coordinates.x; //where missile flies
        // int missileTextGapSize = textGapSize + coordinates.x;
        // int numberOfLines = 15;

        // std::string missileTextGap = "";
        // 

        // for (int i = 0; i < missileTextGapSize; i++)
        //     {
        //         missileTextGap += " ";
        //     }
        // 

        // for (int i = 0; i < numberOfLines; i++)
        // {
        //     std::cout << missileTextGap << "|" << "\n";
        //     delay(0.5);
        // }
        // std::cout << missileTextGap << "V" << "\n";
        // std::cout << "\n";

        // std::cout << targetTextGap << "*" << "\n";

        const int maxLines = 15;
        const int maxChars = 80;
        char missile = '!';
        char targetText = '*';
        char emptySpace = ' ';


        char textArray[maxLines][maxChars];
        for (int y = 0; y < maxLines; y++)
        {
            for(int x = 0; x < maxChars; x++)
            {
                textArray[y][x] = emptySpace;

                if (x == coordinates.x && y == coordinates.y){
                    textArray[y][x] = missile;
                }
                if(x == target.coordinates.x && y == target.coordinates.y){
                    textArray[y][x] = targetText;
                }
                if(coordinates.x == target.coordinates.x && 
                   coordinates.y == target.coordinates.y &&
                x == coordinates.x && y == coordinates.y){
                    textArray[y - 1][x - 1] = '&'; 
                    textArray[y - 1][x] = '&';
                    textArray[y - 1][x + 1] = '&';

                    textArray[y][x - 2] = '&';
                    textArray[y][x - 1] = '&';
                    textArray[y][x + 1] = '&';
                    textArray[y][x + 2] = '&';

                    textArray[y + 1][x - 1] = '&'; 
                    textArray[y + 1][x] = '&';
                    textArray[y + 1][x + 1] = '&';
                }
            }
        }
        
        //draw text
       for (int y = 0; y < maxLines; y++)
       {
            for(int x = 0; x < maxChars; x++)
            {
                std::cout << textArray[y][x];
            }
            std::cout << "\n";
       }
       
        
        
    
    }
};

