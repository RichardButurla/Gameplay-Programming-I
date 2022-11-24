/// <summary>
/// @author Richard Buturla
/// C00272345

#include "../include/Game.h"
#define CUTE_C2_IMPLEMENTATION
#include "../include/cute_c2.h"

#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	
	

	//update Player Collider and enemy Colliders based on Tests
	switch (m_currentCollisionTest)
	{
	case CollisionType::AABBToCapsule:

		playerCapsule.a = {playerBox.getX(),playerBox.getY()};
		playerCapsule.b = {playerBox.getX(),playerBox.getY() + playerBox.getHeight()}; //capsule.b is second point which is lower down.
		playerCapsule.r = playerBox.getWidth();

		//update Enemy Collider
		enemyAABB.min = {enemyBox.getX(),enemyBox.getY()};
		enemyAABB.max = {enemyBox.getX() + enemyBox.getWidth(),enemyBox.getY() + enemyBox.getY()};

		//check collision AABB TO CAPSULE
	 	if(c2AABBtoCapsule(enemyAABB,playerCapsule)) //if true
	 	{
	 		playerBox.setVelocity({-playerBox.getVelocity().x,playerBox.getVelocity().y});
			enemyBox.setVelocity({-enemyBox.getVelocity().x,enemyBox.getVelocity().y});
	 	}
		break;
	case CollisionType::AABBToPolygon:

		std::cout << "Collision x: " << playerPolygon.verts[0].x << "Collision y: " << playerPolygon.verts[0].y << "\n"; 

		playerPolygon.count = 1;
		playerPolygon.verts[0] = {playerCircle.getPosition().x, playerCircle.getPosition().y - playerCircle.getRadius()}; //above radius so x is same as center point
		playerPolygon.verts[1] = {playerCircle.getPosition().x - playerCircle.getRadius(), playerCircle.getPosition().y + playerCircle.getRadius()}; //to the left of the centre
		playerPolygon.verts[2] = {playerCircle.getPosition().x + playerCircle.getRadius(), playerCircle.getPosition().y + playerCircle.getRadius()}; //to the right of the centre
		playerPolygon.norms[0] = {playerCircle.getPosition().x,playerCircle.getPosition().y}; //only one normal on our 2d polygon at centre point

		enemyAABB.min = {enemyBox.getX(),enemyBox.getY()};
		enemyAABB.max = {enemyBox.getX() + enemyBox.getWidth(),enemyBox.getY() + enemyBox.getY()};

		// c2r collisionAngles;
		// collisionAngles.c = 1;
		// collisionAngles.s = 0;

		// c2v collisionCheckPoint;
		// collisionCheckPoint.x = playerCircle.getX();
		// collisionCheckPoint.y = playerCircle.getY();

		// c2x idk;
		// idk.p = collisionCheckPoint;
		// idk.r = collisionAngles;

		// if(c2AABBtoPoly(enemyAABB,&playerPolygon,&idk))
		// {
		// 	playerBox.setVelocity({-playerBox.getVelocity().x,playerBox.getVelocity().y});
		// 	enemyBox.setVelocity({-enemyBox.getVelocity().x,enemyBox.getVelocity().y});
		// }

		

		break;

	case CollisionType::AABBToRay:

		playerRay.t = 250; //the distance of the ray
		playerRay.p.x = playerBox.getX();
		playerRay.p.y = playerBox.getY();
		playerRay.d.x = playerBox.getVelocity().x; //direction vector(normalised) use default velocity for now
		playerRay.d.y = playerBox.getVelocity().y; //direction vector(normalised) use default velocity for now

		enemyAABB.min = {enemyBox.getX(),enemyBox.getY()};
		enemyAABB.max = {enemyBox.getX() + enemyBox.getWidth(),enemyBox.getY() + enemyBox.getY()};

		c2Raycast raycast;
		raycast.n.x = 1; //normal of surface at impact (unit length)
		raycast.n.y = 1;
		raycast.t = 1; //time of impact

		if(c2RaytoAABB(playerRay,enemyAABB,&raycast))
		{
			playerBox.setVelocity({-playerBox.getVelocity().x,playerBox.getVelocity().y});
			enemyBox.setVelocity({-enemyBox.getVelocity().x,enemyBox.getVelocity().y});
		}


		break;
	case CollisionType::CircleToAABB:

		playerCircleCollider.p.x = playerCircle.getPosition().x;
		playerCircleCollider.p.y = playerCircle.getPosition().y;
		playerCircleCollider.r = playerCircle.getRadius();

		enemyAABB.min.x = enemyBox.getX();
		enemyAABB.min.y = enemyBox.getY() + enemyBox.getHeight();

		enemyAABB.max.x = enemyAABB.min.x + enemyBox.getWidth();
		enemyAABB.max.y = enemyBox.getY(); 


		//std::cout << "Circle Sprite x: " << playerCircle.getX() << "Circle Collider X: " << playerCircleCollider.p.x << "\n";
		//std::cout << "Circle Sprite r: " << playerCircle.getRadius() << "Circle Collider r: " << playerCircleCollider.r << "\n";

		std::cout << "Box Sprite x: " << enemyBox.getX() << "Box Collider min X: " << enemyAABB.min.x << "\n";
		std::cout << "Box Sprite y: " << enemyBox.getY() + enemyBox.getHeight() << "Box Collider y: " << enemyAABB.min.y << "\n";

		if(c2CircletoAABB(playerCircleCollider,enemyAABB))
		{
			playerCircle.setVelocity({-playerCircle.getVelocity().x,playerCircle.getVelocity().y});
			enemyBox.setVelocity({-enemyBox.getVelocity().x,enemyBox.getVelocity().y});
		}

		break;
	case CollisionType::CircleToCircle:
		playerCircleCollider.p.x = playerCircle.getPosition().x;
		playerCircleCollider.p.y = playerCircle.getPosition().y;
		playerCircleCollider.r = playerCircle.getRadius();

		enemyCircleCollider.p.x = enemyCircle.getPosition().x;
		enemyCircleCollider.p.y = enemyCircle.getPosition().y;
		enemyCircleCollider.r = enemyCircle.getRadius();

		if(c2CircletoCircle(playerCircleCollider,enemyCircleCollider))
		{
			playerCircle.setVelocity({-playerCircle.getVelocity().x,playerCircle.getVelocity().y});
			enemyCircle.setVelocity({-enemyCircle.getVelocity().x,enemyCircle.getVelocity().y});
		}

		break;
	case CollisionType::CircleToRay:

		playerRay.t = 250; //the distance of the ray
		playerRay.p.x = playerBox.getX();
		playerRay.p.y = playerBox.getY();
		playerRay.d.x = playerBox.getVelocity().x; //direction vector(normalised) use default velocity for now
		playerRay.d.y = playerBox.getVelocity().y; //direction vector(normalised) use default velocity for now

		c2Raycast raycast2;
		raycast2.n.x = 1; //normal of surface at impact (unit length)
		raycast2.n.y = 1;
		raycast2.t = 1; //time of impact

		enemyCircleCollider.p.x = enemyCircle.getPosition().x;
		enemyCircleCollider.p.y = enemyCircle.getPosition().y;
		enemyCircleCollider.r = enemyCircle.getRadius();	

		if(c2RaytoCircle(playerRay,enemyCircleCollider,&raycast2))
		{
			playerBox.setVelocity({-playerCircle.getVelocity().x,playerCircle.getVelocity().y});
			enemyCircle.setVelocity({-enemyCircle.getVelocity().x,enemyCircle.getVelocity().y});
		}

		std::cout << "Enemy Circle x: " << enemyCircle.getPosition().x << "\n";

		break;
	case CollisionType::CircleToCapsule:
	
		break;
	case CollisionType::CircleToPolygon:

		playerPolygon.count = 1;
		playerPolygon.verts[0] = {playerCircle.getPosition().x, playerCircle.getPosition().y - playerCircle.getRadius()}; //above radius so x is same as center point
		playerPolygon.verts[1] = {playerCircle.getPosition().x - playerCircle.getRadius(), playerCircle.getPosition().y + playerCircle.getRadius()}; //to the left of the centre
		playerPolygon.verts[2] = {playerCircle.getPosition().x + playerCircle.getRadius(), playerCircle.getPosition().y + playerCircle.getRadius()}; //to the right of the centre
		playerPolygon.norms[0] = {playerCircle.getPosition().x,playerCircle.getPosition().y};

		c2r collisionAngles;
		collisionAngles.c = 1;
		collisionAngles.s = 0;

		c2v collisionCheckPoint;
		collisionCheckPoint.x = playerCircle.getX();
		collisionCheckPoint.y = playerCircle.getY();

		c2x idk;
		idk.p = collisionCheckPoint;
		idk.r = collisionAngles;

		enemyCircleCollider.p.x = enemyCircle.getPosition().x;
		enemyCircleCollider.p.y = enemyCircle.getPosition().y;
		enemyCircleCollider.r = enemyCircle.getRadius();


		if(c2CircletoPoly(enemyCircleCollider,&playerPolygon,&idk))
		{
			playerCircle.setVelocity({-playerCircle.getVelocity().x,playerCircle.getVelocity().y});
			enemyCircle.setVelocity({-enemyCircle.getVelocity().x,enemyCircle.getVelocity().y});
		}


		break;

	case CollisionType::RayToCapsule:
		
		playerRay.t = 250; //the distance of the ray
		playerRay.p.x = playerBox.getX();
		playerRay.p.y = playerBox.getY();
		playerRay.d.x = playerBox.getVelocity().x; //direction vector(normalised) use default velocity for now
		playerRay.d.y = playerBox.getVelocity().y; //direction vector(normalised) use default velocity for now

		
		raycast3.n.x = 1; //normal of surface at impact (unit length)
		raycast3.n.y = 1;
		raycast3.t = 1; //time of impact

		enemyCircleCollider.p.x = enemyCircle.getPosition().x;
		enemyCircleCollider.p.y = enemyCircle.getPosition().y;
		enemyCircleCollider.r = enemyCircle.getRadius();	

		if(c2RaytoCapsule(playerRay,enemyCapsule,&raycast3))
		{
			playerBox.setVelocity({-playerBox.getVelocity().x,playerBox.getVelocity().y});
			enemyBox.setVelocity({-enemyBox.getVelocity().x,playerBox.getVelocity().y});
			std::cout << "collision";
		}

		break;

	case CollisionType::RayToPoly:
	
		break;	

	default:
		break;
	}
	

	 //Check collisionh AABB TO POLYGON
	  
	
    playerBox.update();
	enemyBox.update();

	playerCircle.update();
	enemyCircle.update();

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	switch (m_currentCollisionTest)
	{
	case CollisionType::AABBToCapsule:
		playerBox.render(m_window);
		enemyBox.render(m_window);
		break;

	case CollisionType::AABBToPolygon:
		enemyBox.render(m_window);
		playerCircle.render(m_window);
		break;
	case CollisionType::AABBToRay:
		enemyBox.render(m_window);
		playerBox.render(m_window);
		break;
	case CollisionType::CircleToAABB:
		playerCircle.render(m_window);
		enemyBox.render(m_window);
		break;
	case CollisionType::CircleToCircle:
		enemyCircle.render(m_window);
		playerCircle.render(m_window);
		break;
	case CollisionType::CircleToRay:
		playerBox.render(m_window);
		enemyCircle.render(m_window);
		break;
	case CollisionType::CircleToCapsule:

		break;
	case CollisionType::CircleToPolygon:
		enemyCircle.render(m_window);
		playerCircle.render(m_window);
		break;

	case CollisionType::RayToCapsule:
		playerBox.render(m_window);
		enemyBox.render(m_window);
		break;

	case CollisionType::RayToPoly:
	
		break;									
	default:
		break;
	}

	
	//enemyCircle.render(m_window);
	//playerCircle.render(m_window);

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	// if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	// {
	// 	std::cout << "problem loading arial black font" << std::endl;
	// }
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	//Rectangles now
	playerBox.setupRectangle(sf::Color::Black);
	enemyBox.setupRectangle(sf::Color::Green);
	enemyCircle.setupCircle(sf::Color::Red);
	playerCircle.setupCircle(sf::Color::Blue);

	playerBox.setVelocity({ 1,0 });
	enemyBox.setVelocity({ -1,0 });
	enemyCircle.setVelocity({ 1,0 });
	playerCircle.setVelocity({-1,0});


	

	//if enemy == Circle
	enemyCircle.setRadius( 50);

	enemyBox.setWidth(20);
	enemyBox.setHeight(40);
	enemyBox.setSize(20,40);

	playerBox.setWidth(40);
	playerBox.setHeight(100);
	playerBox.setSize(40,100);

	switch (m_currentCollisionTest)
	{
	case CollisionType::AABBToCapsule:
		enemyBox.setPosition({ 600, 100 });
		playerBox.setPosition({ 100, 100 });

		enemyAABB.min = {enemyBox.getX(),enemyBox.getY()};
		enemyAABB.max = {enemyBox.getX() + enemyBox.getWidth(),enemyBox.getY() + enemyBox.getY()};

		enemyAABB.min = {enemyBox.getX(),enemyBox.getY()};
		enemyAABB.max = {enemyBox.getX() + enemyBox.getWidth(),enemyBox.getY() + enemyBox.getY()};

		

		playerCapsule.a = {playerBox.getX(),playerBox.getY()};
		playerCapsule.b = {playerBox.getX(),playerBox.getY() - playerBox.getHeight()}; //capsule.b is second point which is lower down.
		playerCapsule.r = playerBox.getWidth();	
		break;

	case CollisionType::AABBToPolygon:
		playerCircle.setPointCount(3);

		playerCircle.setPosition({600,100});
		enemyBox.setPosition({100,120});

		enemyBox.setVelocity({1,0});
		playerCircle.setVelocity({-1,0});

		enemyAABB.min = {enemyBox.getX(),enemyBox.getY()};
		enemyAABB.max = {enemyBox.getX() + enemyBox.getWidth(),enemyBox.getY() + enemyBox.getY()};

		enemyAABB.min = {enemyBox.getX(),enemyBox.getY()};
		enemyAABB.max = {enemyBox.getX() + enemyBox.getWidth(),enemyBox.getY() + enemyBox.getY()};

		playerPolygon.count = 1;
		playerPolygon.verts[0] = {playerCircle.getPosition().x, playerCircle.getPosition().y - playerCircle.getRadius()}; //above radius so x is same as center point
		playerPolygon.verts[1] = {playerCircle.getPosition().x - playerCircle.getRadius(), playerCircle.getPosition().y + playerCircle.getRadius()}; //to the left of the centre
		playerPolygon.verts[2] = {playerCircle.getPosition().x + playerCircle.getRadius(), playerCircle.getPosition().y + playerCircle.getRadius()}; //to the right of the centre
		playerPolygon.norms[0] = {playerCircle.getPosition().x,playerCircle.getPosition().y};
		break;
	case CollisionType::AABBToRay:
		enemyBox.setPosition({ 600, 100 });
		playerBox.setPosition({ 100, 100 });

	//player will be skinny rectangle that looks like ray
		playerBox.setWidth(250);
		playerBox.setHeight(1);
		playerBox.setSize(250,1);

		playerRay.t = 250; //the distance of the ray
		playerRay.p.x = playerBox.getX();
		playerRay.p.y = playerBox.getY();
		playerRay.d.x = playerBox.getVelocity().x; //direction vector(normalised) use default velocity for now
		playerRay.d.y = playerBox.getVelocity().y; //direction vector(normalised) use default velocity for now

		enemyAABB.min = {enemyBox.getX(),enemyBox.getY()};
		enemyAABB.max = {enemyBox.getX() + enemyBox.getWidth(),enemyBox.getY() + enemyBox.getY()};

		enemyAABB.min = {enemyBox.getX(),enemyBox.getY()};
		enemyAABB.max = {enemyBox.getX() + enemyBox.getWidth(),enemyBox.getY() + enemyBox.getY()};

		break;
	case CollisionType::CircleToAABB:

		playerCircle.setPosition({600,100});
		enemyBox.setPosition({ 100, 100 });

		playerCircle.setVelocity({-1,0});
		enemyBox.setVelocity({1,0});

		enemyBox.setWidth(20);
		enemyBox.setHeight(40);
		enemyBox.setSize(20,40);

		enemyAABB.min = {enemyBox.getX(),enemyBox.getY()};
		enemyAABB.max = {enemyBox.getX() + enemyBox.getWidth(),enemyBox.getY() + enemyBox.getY()};

		enemyAABB.min = {enemyBox.getX(),enemyBox.getY()};
		enemyAABB.max = {enemyBox.getX() + enemyBox.getWidth(),enemyBox.getY() + enemyBox.getY()};

		playerCircle.setRadius(50);

		playerCircleCollider.p.x = playerCircle.getPosition().x;
		playerCircleCollider.p.y = playerCircle.getPosition().y;
		playerCircleCollider.r = playerCircle.getRadius();



		break;
	case CollisionType::CircleToCircle:
		playerCircle.setPosition({600,100});
		enemyCircle.setPosition({100,100});

		playerCircle.setVelocity({-1,0});
		enemyCircle.setVelocity({1,0});

		playerCircle.setRadius(50);
		enemyCircle.setRadius(50);

		playerCircleCollider.p.x = playerCircle.getPosition().x;
		playerCircleCollider.p.y = playerCircle.getPosition().y;
		playerCircleCollider.r = playerCircle.getRadius();

		enemyCircleCollider.p.x = enemyCircle.getPosition().x;
		enemyCircleCollider.p.y = enemyCircle.getPosition().y;
		enemyCircleCollider.r = enemyCircle.getRadius();


		break;
	case CollisionType::CircleToRay:
		playerBox.setPosition({ 100, 120 });
		enemyCircle.setPosition({600,100});

		playerBox.setVelocity({1,0});
		enemyCircle.setVelocity({-1,0});

	//player will be skinny rectangle that looks like ray
		playerBox.setWidth(250);
		playerBox.setHeight(1);
		playerBox.setSize(250,1);

		enemyCircle.setRadius(50);

		playerRay.t = 250; //the distance of the ray
		playerRay.p.x = playerBox.getX();
		playerRay.p.y = playerBox.getY();
		playerRay.d.x = playerBox.getVelocity().x; //direction vector(normalised) use default velocity for now
		playerRay.d.y = playerBox.getVelocity().y; //direction vector(normalised) use default velocity for now


		enemyCircleCollider.p.x = enemyCircle.getPosition().x;
		enemyCircleCollider.p.y = enemyCircle.getPosition().y;
		enemyCircleCollider.r = enemyCircle.getRadius();		
		



		break;
	case CollisionType::CircleToCapsule:
	
		break;
	case CollisionType::CircleToPolygon:
	
		playerCircle.setPointCount(3);
		//enemy circle is a full circle

		playerCircle.setPosition({600,100});
		enemyCircle.setPosition({100,120});

		enemyCircle.setVelocity({1,0});
		playerCircle.setVelocity({-1,0});

		playerPolygon.count = 1;
		playerPolygon.verts[0] = {playerCircle.getPosition().x, playerCircle.getPosition().y - playerCircle.getRadius()}; //above radius so x is same as center point
		playerPolygon.verts[1] = {playerCircle.getPosition().x - playerCircle.getRadius(), playerCircle.getPosition().y + playerCircle.getRadius()}; //to the left of the centre
		playerPolygon.verts[2] = {playerCircle.getPosition().x + playerCircle.getRadius(), playerCircle.getPosition().y + playerCircle.getRadius()}; //to the right of the centre
		playerPolygon.norms[0] = {playerCircle.getPosition().x,playerCircle.getPosition().y};

		enemyCircleCollider.p.x = enemyCircle.getPosition().x;
		enemyCircleCollider.p.y = enemyCircle.getPosition().y;
		enemyCircleCollider.r = enemyCircle.getRadius();

		break;

	case CollisionType::RayToCapsule:
		playerBox.setPosition({ 100, 120 });
		enemyBox.setPosition({600,100});

		playerBox.setVelocity({1,0});
		enemyBox.setVelocity({-1,0});
		//player will be skinny rectangle that looks like ray
		playerBox.setWidth(250);
		playerBox.setHeight(1);
		playerBox.setSize(250,1);

		enemyBox.setWidth(30);
		enemyBox.setHeight(60);
		enemyBox.setSize(30,60);


		playerRay.t = 250; //the distance of the ray
		playerRay.p.x = playerBox.getX();
		playerRay.p.y = playerBox.getY();
		playerRay.d.x = playerBox.getVelocity().x; //direction vector(normalised) use default velocity for now
		playerRay.d.y = playerBox.getVelocity().y; //direction vector(normalised) use default velocity for now

		c2Raycast raycast3;
		raycast3.n.x = 1; //normal of surface at impact (unit length)
		raycast3.n.y = 1;
		raycast3.t = 1; //time of impact

		enemyCapsule.a = {playerBox.getX(),playerBox.getY()};
		enemyCapsule.b = {playerBox.getX(),playerBox.getY() - playerBox.getHeight()}; //capsule.b is second point which is lower down.
		enemyCapsule.r = playerBox.getWidth();	
		break;

		break;

	case CollisionType::RayToPoly:
		
		break;									
	default:
		break;
	}



}
