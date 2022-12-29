#ifndef PLAYER_H
#define PLAYER_H
#include  "Events.h"
#include "PlayerState.h "
#include "AnimatedSprite.h"
#include <stdio.h>
#include "IdlePlayerState.h"
#include "PlayerController.h"
#include <SFML/Graphics.hpp>

class Player
{
private:
	PlayerState* m_state;
	AnimatedSprite m_animated_sprite;
	PlayerController m_playerController;

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

	//Animator
	float getWidth() { return m_animated_sprite.getTextureRect().width; }
	float getHeight() { return m_animated_sprite.getTextureRect().height; }

	//Player Controller
	void updatePlayer(double t_deltaTime);
	void renderPlayer(sf::RenderWindow& t_window);
	void processKeyPress(sf::Event t_event);
	void processKeyRelease(sf::Event t_event);

	float getX() { return m_playerController.getPosition().x; }
	float getY() { return m_playerController.getPosition().y; }

	void setX(float t_x) { m_playerController.setX(t_x); }
	void setY(float t_y) { m_playerController.setY(t_y); }

	void setGrounded(bool t_boolean) { m_playerController.setGrounded(t_boolean); }


};
#endif

