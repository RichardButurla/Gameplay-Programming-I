#include "Events.h"

#include "JumpThrowAttackPlayerState.h"

#include "RunRightPlayerState.h"
#include "GlidePlayerState.h"
#include "DiedPlayerState.h"
#include "RunRightPlayerState.h"
#include "GlideRunningRightPlayerState.h"
#include "IdlePlayerState.h"

PlayerState* JumpThrowAttackPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("JumpThrowAttackPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_STOP_EVENT)
	{
		DEBUG_MSG("JumpThrowAttackPlayerState -> GlidePlayerState");
		return new GlideRunningRightPlayerState();
	}
	return nullptr;
}
void JumpThrowAttackPlayerState::update(Player& player) {
	DEBUG_MSG("JumpThrowAttackPlayerState -> GlidePlayerState");
	if (m_clock.getElapsedTime().asSeconds() > 0.3f) {
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new GlidePlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
}
void JumpThrowAttackPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering JumpThrowAttackPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(4596, 0, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4956, 0, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(5316, 0, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4596, 431, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4956, 431, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(5316, 431, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4596, 862, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4956, 862, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(5316, 862, 360, 431));
	player.getAnimatedSprite().addFrame(sf::IntRect(4596, 1293, 360, 431));

	player.getAnimatedSprite().setTime(seconds(0.03f));
}
void JumpThrowAttackPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting JumpThrowAttackPlayerState");
	DEBUG_MSG(typeid(player).name());
}