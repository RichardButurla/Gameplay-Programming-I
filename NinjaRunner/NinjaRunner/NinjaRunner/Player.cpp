#include "Player.h"

Player::Player(const AnimatedSprite& sprite) : m_animated_sprite(sprite)
{
	// Set the Player to Default to IdlePlayer State 
	// and Enter that State
	m_state = new IdlePlayerState();
	m_state->enter(*this);
}

Player::Player()
{
	m_state = new IdlePlayerState();
	m_state->enter(*this);
}

Player::~Player()
{
	DEBUG_MSG("~Player()");
}

void Player::handleAnimationInput(gpp::Events input) {
	PlayerState * state = m_state->handleInput(input);

	if (state != NULL) {
		m_state->exit(*this);
		delete m_state;
		m_state = state;
		m_state->enter(*this);
	}
}

void Player::updateAnimationState() {
	m_animated_sprite.update();
	m_state->update(*this);
}

void Player::updatePlayer()
{
	updateAnimationState();
	m_position += m_velocity;
	m_animated_sprite.setPosition(m_position);
}

void Player::renderPlayer(sf::RenderWindow& t_window)
{
	t_window.draw(this->getAnimatedSpriteFrame());
}


AnimatedSprite& Player::getAnimatedSprite() {
	return m_animated_sprite;
}

AnimatedSprite& Player::getAnimatedSpriteFrame() {
	int frame = m_animated_sprite.getCurrentFrame();
	m_animated_sprite.setTextureRect(m_animated_sprite.getFrame(frame));
	return m_animated_sprite;
}

void Player::setAnimatedSprite(AnimatedSprite& animated_sprite) {
	this->m_animated_sprite = animated_sprite;
}

PlayerState* Player::getPlayerState() { return this->m_state; }

void Player::setPlayerState(PlayerState* state) { this->m_state = state; }


void Player::processKeyPress(sf::Event t_event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_velocity = { 1,0 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_velocity = { -1,0 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_velocity = { 0,-1 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_velocity = { 0,1 };
	}
}

void Player::processKeyRelease(sf::Event t_event)
{
	
}
