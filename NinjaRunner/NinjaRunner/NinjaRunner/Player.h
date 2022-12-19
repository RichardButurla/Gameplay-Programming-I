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
	Player(const AnimatedSprite&);
	Player();
	~Player();
	virtual void handleAnimationInput(gpp::Events);
	virtual void updateAnimationState();
	AnimatedSprite& getAnimatedSprite();
	AnimatedSprite& getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite&);
	PlayerState* getPlayerState();
	void setPlayerState(PlayerState*);

	void updatePlayer(double t_deltaTime);
	void renderPlayer(sf::RenderWindow& t_window);
	void processKeyPress(sf::Event t_event);
	void processKeyRelease(sf::Event t_event);
};
#endif

