#include "./include/GameLogics.h"


const int maxLines = 15;
const int maxChars = 80;
char textArray[maxLines][maxChars];
bool targetFound = false;
bool explosion = false;

enum class Warhead
{NONE,
EXPLOSIVE,
NUCLEAR};


typedef struct Enemy
{
    Coordinates coordinates;
}Target;

struct Missile
{
    Warhead payload;
    Coordinates coordinates;
    Target target;

    bool armed = false;

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
    void scanTarget(){
        if(isWithinRange(coordinates,target.coordinates))
        {
            std::cout << "Target Found! ";
            targetFound = true;
            textArray[target.coordinates.y][target.coordinates.x] = '*';
            drawTextArea();
        }
        else{
            std::cout << "\nTarget not within impact area\n";
        }

    }
    void acquireTarget()
    {
        std::cout << "Enter target x location: \n";
        std::cin >> coordinates.x;
        std::cout << "Enter target y location: \n";
        std::cin >> coordinates.y;
    }
    void setupMap()
    {     
        char emptySpace = ' ';
        for (int y = 0; y < maxLines; y++)
        {
            for(int x = 0; x < maxChars; x++)
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

        if(coordinates.x == target.coordinates.x && coordinates.y == target.coordinates.y){
            std::cout << "Target hit ";
        }
        else{
            std::cout << "Missed \n";
        }

      
        textArray[coordinates.y][coordinates.x] = missileTextSymbol;
                
        if(coordinates.x == target.coordinates.x && 
            coordinates.y == target.coordinates.y){
            explosion = true;
        }

        if(explosion)
        drawTextExplosion(target.coordinates.x,target.coordinates.y,textArray);

        //draw text
       drawTextArea();
    }
    void drawTextArea()
    {
    for (int y = 0; y < maxLines; y++)
       {
            for(int x = 0; x < maxChars; x++)
            {
                std::cout << textArray[y][x];
            }
            std::cout << "\n";
       }
        for (int i = 0; i < 5; i++){ //just for spacing
        std::cout << "\n";
    }
    }
   
    
};

