#include "Events.h"

#include "RunningJumpAttack.h"

#include "DiedPlayerState.h"
#include "JumpAttackPlayerState.h"
#include "RunningJumpThrowPlayerState.h"
#include "GlideRunningRightPlayerState.h"
#include "RunRightPlayerState.h"
#include "GlidePlayerState.h"

PlayerState* RunningJumpAttack::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("RunningJumpAttack -> DiedPlayerState");
		return new DiedPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::THROW_STOP_EVENT)
	{
		DEBUG_MSG("RunningJumpAttack -> GlidePlayerState");
		return new GlidePlayerState();
	}
	
	return nullptr;
}
void RunningJumpAttack::update(Player& player) {
	
    DEBUG_MSG("RunningJumpAttack -> GlideRunningRightPlayerState");
	if (m_clock.getElapsedTime().asSeconds() > 0.6f) {
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new GlideRunningRightPlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
}
void RunningJumpAttack::enter(Player& player)
{
	DEBUG_MSG("Entering RunningJumpAttack");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(1329, 1992, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(1851, 1992, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(2373, 1992, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(1329, 2514, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(1851, 2514, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(2373, 2514, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(1329, 3036, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(1851, 3036, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(2373, 3036, 504, 522));
	player.getAnimatedSprite().addFrame(sf::IntRect(1329, 3558, 504, 522));

	player.getAnimatedSprite().setTime(seconds(0.06f));
}
void RunningJumpAttack::exit(Player& player)
{
	DEBUG_MSG("Exiting RunningJumpAttack");
	player.getAnimatedSprite().setPlayed(false);
	player.getAnimatedSprite().setLooped(true);
}