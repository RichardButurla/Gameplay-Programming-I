#include <iostream>
#include <math.h>

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
    void launchCode()
    {
        int launchCode;

        std::cout << "Enter secret launch code \n";
        std:: cin >> launchCode;
        std::cout << "Launching... \n";
    }
    float calculateDistance()
    {
        float sumOfSquares = (coordinates.x - target.coordinates.x) + (coordinates.y - target.coordinates.y);
        const float length = std::sqrt(sumOfSquares);
        return length;
    }
    void checkCollision()
    {
        if(coordinates.x == target.coordinates.x && coordinates.y == target.coordinates.y)
        {
            std::cout << "Target hit \n";
        }
        else
        {
            std::cout << "Missed by " << calculateDistance() << " miles squared \n";
        }
    }
};

