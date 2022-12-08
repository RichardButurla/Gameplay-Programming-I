#include "Events.h"

#include "JumpAttackPlayerState.h"

#include "RunRightPlayerState.h"
#include "GlidePlayerState.h"
#include "DiedPlayerState.h"

PlayerState* JumpAttackPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("JumpAttackPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}
void JumpAttackPlayerState::update(Player& player) {
	DEBUG_MSG("JumpAttackPlayerState::update");

	DEBUG_MSG("JumpThrowAttackPlayerState -> GlidePlayerState");
	if (m_clock.getElapsedTime().asSeconds() > 0.3f) {
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new GlidePlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
	DEBUG_MSG(typeid(player).name());
}
void JumpAttackPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering JumpAttackPlayerState");
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
void JumpAttackPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting JumpAttackPlayerState");
	DEBUG_MSG(typeid(player).name());
}