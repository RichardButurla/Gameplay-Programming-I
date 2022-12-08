#include "Events.h"

#include "GlideRunningRightPlayerState.h"

#include "DiedPlayerState.h"
#include "IdlePlayerState.h"
#include "RunRightPlayerState.h"

PlayerState* GlideRunningRightPlayerState::handleInput(gpp::Events& input)
{
	if (input.getCurrent() == gpp::Events::Event::HIT_GROUND_EVENT)
	{
		DEBUG_MSG("GlideRunningRightPlayerState -> IdlePlayerState");
		return new RunRightPlayerState();
	}
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT)
	{
		DEBUG_MSG("GlideRunningRightPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
	return nullptr;
}
void GlideRunningRightPlayerState::update(Player& player) {
	DEBUG_MSG("GlideRunningRightPlayerState -> RunRightPlayerState");
	if (m_clock.getElapsedTime().asSeconds() > 1.2f) {
		PlayerState* temp = player.getPlayerState();
		PlayerState* state = new RunRightPlayerState();
		player.getPlayerState()->exit(player);
		player.setPlayerState(state);
		player.getPlayerState()->enter(player);
		delete temp;
	}
}
void GlideRunningRightPlayerState::enter(Player& player)
{
	DEBUG_MSG("Entering GlideRunningRightPlayerState");

	player.getAnimatedSprite().clearFrames();

	player.getAnimatedSprite().addFrame(sf::IntRect(0, 1992, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(443, 1992, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(886, 1992, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(0, 2446, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(443, 2446, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(886, 2446, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(0, 2900, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(443, 2900, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(886, 2900, 443, 454));
	player.getAnimatedSprite().addFrame(sf::IntRect(0, 3354, 443, 454));

	player.getAnimatedSprite().setTime(seconds(0.03f));
}
void GlideRunningRightPlayerState::exit(Player& player)
{
	DEBUG_MSG("Exiting GlideRunningRightPlayerState");
	DEBUG_MSG(typeid(player).name());
}