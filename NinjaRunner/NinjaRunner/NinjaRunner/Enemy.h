#pragma once
#include "EnemyController.h"
#include "AnimatedSprite.h"
#include "PlayerState.h"
#include "IdlePlayerState.h"
#include "Globals.h"
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy(const AnimatedSprite&, EnemyController& t_enemyController);
	Enemy();
	~Enemy();

	virtual void updateAnimationState();
	AnimatedSprite& getAnimatedSprite();
	AnimatedSprite& getAnimatedSpriteFrame();
	void setAnimatedSprite(AnimatedSprite&);
	PlayerState* getEnemyState();
	void setEnemyState(PlayerState*);
	void setEnemyScale(float t_x, float t_y);


	void update(double t_deltaTime);
	void render(sf::RenderWindow& t_window);

	void trackPlayer(sf::Vector2f t_playerPos);
	bool isAttackingPlayer() { return m_enemyController.isAttackingPlayer(); }


	float getX() { return m_enemyController.getX(); }
	float getY() { return m_enemyController.getY(); }

	double getTimeSinceLastAttack() { return attackTimer.getElapsedTime().asSeconds(); }
	void restartAttackTimer() { attackTimer.restart(); }

	void setPos(int t_x, int t_y) { m_enemyController.setX(t_x); m_enemyController.setY(t_y); }
	void setScale(sf::Vector2f t_scale) { m_animated_sprite.setScale(t_scale); };
	void setSpeed(float t_speed) { m_enemyController.setSpeed(t_speed); }


private:

	bool runningAnimationPlayed{ false };
	bool attackingAniimationPlayed{ false };
	sf::Clock attackTimer;
	EnemyController m_enemyController;
	AnimatedSprite m_animated_sprite;
	PlayerState* m_state;

};

