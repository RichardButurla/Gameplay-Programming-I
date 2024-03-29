#include "Player.h"
#include "RunRightPlayerState.h"
#include "JumpRunningRightPlayerState.h"
#include "GlideRunningRightPlayerState.h"


Player::Player(const AnimatedSprite& sprite, const PlayerController& t_playerController) : 
	m_animated_sprite(sprite),
	m_playerController(t_playerController)
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

	if (timeSinceAttack.getElapsedTime().asSeconds() > 0.5)
	{
		attackPlayed = false;
	}

	if (!attackPlayed)
	{
		if (m_playerController.getVelocity().y > 1)
		{
			runPlayed = false;
			m_state = new GlideRunningRightPlayerState;
			m_state->enter(*this);
		}
		else if (!runPlayed && m_playerController.getVelocity().y == 0)
		{
			m_state = new RunRightPlayerState;
			m_state->enter(*this);
			runPlayed = true;
			m_animated_sprite.setLooped(true);
		}
	}

	m_animated_sprite.update();
	m_state->update(*this);
}

void Player::updatePlayer(double t_deltaTime)
{
	m_playerController.update(t_deltaTime);
	updateAnimationState();
	m_animated_sprite.setPosition(m_playerController.getPosition());
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

void Player::setPlayerScale(float t_x, float t_y)
{
	m_animated_sprite.setScale(t_x, t_y);
}


void Player::processKeyPress(sf::Event t_event)
{
	//No right or left, this is a endless runner
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_playerController.jump();
	}

}

void Player::processKeyRelease(sf::Event t_event)
{

}

