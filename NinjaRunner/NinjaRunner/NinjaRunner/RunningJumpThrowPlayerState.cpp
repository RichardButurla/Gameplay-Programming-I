#include "Events.h"

#include "JumpRunningRightPlayerState.h"

#include "DiedPlayerState.h"
#include "JumpAttackPlayerState.h"
#include "RunningJumpThrowPlayerState.h"
#include "GlideRunningRightPlayerState.h"
#include "RunRightPlayerState.h"
#include "GlidePlayerState.h"

PlayerState* RunningJumpThrowPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("RunningJumpThrowPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::THROW_STOP_EVENT)
	{
		DEBUG_MSG("RunningJumpThrowPlayerState -> GlidePlayerState");
		return new GlidePlayerState();
	}
	
	return nullptr;
}
void RunningJumpThrowPlayerState::update(Player& player) {
	
    DEBUG_MSG("JumpThrowAttackPlayerState -> GlideRunningRightPlayerState");
	if (m_clock.getElapsedTime().asSeconds() > 0.6f) {
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new GlideRunningRightPlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
}
void RunningJumpThrowPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering RunningJumpThrowPlayerState");
	player.getAnimatedSprite().clearFrames();

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

	player.getAnimatedSprite().setTime(seconds(0.06f));
}
void RunningJumpThrowPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting RunningJumpThrowPlayerState");
	player.getAnimatedSprite().setPlayed(false);
	player.getAnimatedSprite().setLooped(true);
}

void RunningJumpThrowPlayerState::update(Enemy&)
{
}

void RunningJumpThrowPlayerState::enter(Enemy&)
{
}

void RunningJumpThrowPlayerState::exit(Enemy&)
{
}
