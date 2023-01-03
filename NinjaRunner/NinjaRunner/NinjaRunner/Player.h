#ifndef PLAYER_H
#define PLAYER_H
#include  "Events.h"
#include "PlayerState.h "
#include "AnimatedSprite.h"
#include <stdio.h>
#include "IdlePlayerState.h"
#include "PlayerController.h"
#include "Platform.h"
#include <SFML/Graphics.hpp>

class Player
{
private:
	PlayerState* m_state;
	AnimatedSprite m_animated_sprite;
	PlayerController m_playerController;
	bool runPlayed{ false };

public:
	Player(const AnimatedSprite&, const PlayerController& t_playerController);
	Player();
	~Player();
	virtual void handleAnimationInput(gpp::Events);
	virtual void updateAnimationState();
	AnimatedSprite& getAnimatedSprite();
	AnimatedSprite& getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite&);
	PlayerState* getPlayerState();
	void setPlayerState(PlayerState*);
	void setPlayerScale(float t_x, float t_y);

	void updatePlayer(double t_deltaTime);
	void renderPlayer(sf::RenderWindow& t_window);
	void processKeyPress(sf::Event t_event);
	void processKeyRelease(sf::Event t_event);

	//AnimatedSprite


	//Player Controller
	

	float getX() { return m_playerController.getPosition().x; }
	float getY() { return m_playerController.getPosition().y; }
	sf::Vector2f getVelocity() { return m_playerController.getVelocity(); }

	void setVelocity(sf::Vector2f t_velocity) { m_playerController.setVelocity(t_velocity); };
	void setPlayerGravity(float t_value) { m_playerController.setGravity(t_value); };

	void setX(float t_x) { m_playerController.setX(t_x); }
	void setY(float t_y) { m_playerController.setY(t_y); }

	void setInAir(bool t_boolean) { m_playerController.setInAir(t_boolean); }
	void setGrounded(bool t_boolean) { m_playerController.setGrounded(t_boolean); }

	bool isAirborne() { return m_playerController.isAirborne(); }
	bool isGrounded() { return m_playerController.isGrounded(); }


};
#endif

