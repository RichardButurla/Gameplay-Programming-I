#include "Events.h"

#include "JumpRunningRightPlayerState.h"

#include "DiedPlayerState.h"
#include "JumpAttackPlayerState.h"
#include "JumpThrowAttackPlayerState.h"
#include "GlideRunningRightPlayerState.h"
#include "RunRightPlayerState.h"
#include "RunningJumpThrowPlayerState.h"
#include "RunningJumpAttack.h"

PlayerState* JumpRunningRightPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("JumpRunningRightPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::ATTACK_START_EVENT)
	{
		DEBUG_MSG("JumpRunningRightPlayerState -> JumpAttackPlayerState");
		return new RunningJumpAttack();
	}
	else if (input.getCurrent() == gpp::Events::Event::THROW_START_EVENT)
	{
		DEBUG_MSG("JumpRunningRightPlayerState -> RunningJumpThrowPlayerState");
		return new RunningJumpThrowPlayerState();
	}
	return nullptr;
}
void JumpRunningRightPlayerState::update(Player& player) {
	DEBUG_MSG("JumpRunningRightPlayerState -> GlideRunningRightPlayerState");
	/*if (m_clock.getElapsedTime().asSeconds() > 1.2f) {
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new GlideRunningRightPlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}*/
}
void JumpRunningRightPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering JumpRunningRightPlayerState");
	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().setPlayed(false);
	player.getAnimatedSprite().setLooped(false);

	player.getAnimatedSprite().addFrame(sf::IntRect(3900, 1756, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4262, 1756, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4624, 1756, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(3900, 2239, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4262, 2239, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4624, 2239, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(3900, 2722, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4262, 2722, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(4624, 2722, 362, 483));
	player.getAnimatedSprite().addFrame(sf::IntRect(3900, 3205, 362, 483));

	player.getAnimatedSpriteFrame().setTime(seconds(0.03f));
}
void JumpRunningRightPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting JumpRunningRightPlayerState");
	player.getAnimatedSprite().setPlayed(false);
	player.getAnimatedSprite().setLooped(true);
}