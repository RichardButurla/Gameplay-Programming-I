#include <SFML/Graphics.hpp>
#include "../include/Circle.h"
#include "../include/Rectangle.h"
#include "../include/cute_c2.h"

enum class CollisionType
{
	None,
	AABBToCapsule,
	AABBToPolygon,
	AABBToRay,
	CircleToAABB,
	CircleToCircle,
 	CircleToRay,
 	CircleToCapsule,
 	CircleToPolygon,
 	RayToAABB,
 	RayToCapsule,
	RayToCircle,
 	RayToPoly
};

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen

	CollisionType m_currentCollisionTest = CollisionType::AABBToPolygon; //Defaulted to first test

	Box playerBox;
	Circle playerCircle;

	Box enemyBox;
	Circle enemyCircle;

	c2AABB enemyAABB;
	c2Capsule playerCapsule;
	c2Poly playerPolygon;
	c2Ray playerRay;

	//Tetsing shapes






	sf::Vector2f circleOneVector;
	sf::Vector2f circleTwoVector;


	bool m_exitGame; // control exiting game

};


