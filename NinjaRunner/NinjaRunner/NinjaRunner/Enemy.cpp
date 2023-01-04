#include "Enemy.h"

Enemy::Enemy(const AnimatedSprite& sprite, EnemyController& t_enemyController) : 
	m_animated_sprite(sprite),
	m_enemyController(t_enemyController)
{
	m_state = new IdlePlayerState();
	m_state->enter(*this);
	sf::Vector2f offScreenPosition = { SCREEN_WIDTH,-500 };

	m_animated_sprite.setPosition(offScreenPosition);
}

Enemy::Enemy()
{
	m_state = new IdlePlayerState();
	m_state->enter(*this);
}

Enemy::~Enemy()
{
	DEBUG_MSG("~Player()");
}

void Enemy::updateAnimationState()
{
	m_animated_sprite.update();
	m_state->update(*this);
}

AnimatedSprite& Enemy::getAnimatedSprite()
{
	return m_animated_sprite;
}

AnimatedSprite& Enemy::getAnimatedSpriteFrame()
{
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	return m_animated_sprite;
}

void Enemy::setAnimatedSprite(AnimatedSprite& animated_sprite)
{
	this->m_animated_sprite = animated_sprite;
}

PlayerState* Enemy::getEnemyState()
{
	return this->m_state;
}

void Enemy::setEnemyState(PlayerState* state)
{
	this->m_state = state;
}

void Enemy::setEnemyScale(float t_x, float t_y)
{
	m_animated_sprite.setScale(t_x, t_y);
}

void Enemy::update(double t_deltaTime)
{
	m_enemyController.update(t_deltaTime);
	updateAnimationState();
	m_animated_sprite.setPosition(m_enemyController.getX(),m_enemyController.getY());
}

void Enemy::render(sf::RenderWindow& t_window)
{
	t_window.draw(this->getAnimatedSpriteFrame());
}

void Enemy::trackPlayer(sf::Vector2f t_playerPos)
{
	m_enemyController.trackPlayer(t_playerPos.x, t_playerPos.y);
}
