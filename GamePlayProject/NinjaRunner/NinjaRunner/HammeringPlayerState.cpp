#include "HammeringPlayerState.h"
#include "RunRightPlayerState.h"
#include "DiedPlayerState.h"

PlayerState* HammeringPlayerState::handleInput(gpp::Events& input)
{
    if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT)
    {
        DEBUG_MSG("HammeringPlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
    }
    else if (input.getCurrent() == gpp::Events::Event::HAMMERING_END_EVENT)
    {
        DEBUG_MSG("HammeringPlayerState -> IdlePlayerState");
		return new IdlePlayerState();
    }
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("HammeringPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
    return nullptr;
}

void HammeringPlayerState::update(Player &player)
{
    player.getAnimatedSprite().addFrame(sf::IntRect(0, 1485, 536, 495));
    player.getAnimatedSprite().addFrame(sf::IntRect(1072, 990, 536, 495));
    player.getAnimatedSprite().addFrame(sf::IntRect(536, 990, 536, 495));
    player.getAnimatedSprite().addFrame(sf::IntRect(0, 990, 536, 495));
    player.getAnimatedSprite().addFrame(sf::IntRect(1072, 495, 536, 495));
    player.getAnimatedSprite().addFrame(sf::IntRect(536, 495, 536, 495));
    player.getAnimatedSprite().addFrame(sf::IntRect(0, 495, 536, 495));
    player.getAnimatedSprite().addFrame(sf::IntRect(1072, 0, 536, 495));
    player.getAnimatedSprite().addFrame(sf::IntRect(536, 0, 536, 495));
    player.getAnimatedSprite().addFrame(sf::IntRect(0, 0, 536, 495));
	
	player.getAnimatedSprite().setTime(seconds(0.1f));
}

void HammeringPlayerState::enter(Player &player)
{
    DEBUG_MSG("Entering Hammering Player State");
	player.getAnimatedSprite().clearFrames();

    //animation
	
	player.getAnimatedSprite().setTime(seconds(0.05f));
}

void HammeringPlayerState::exit(Player & player)
{
    DEBUG_MSG("Exiting Hammering Player State");
	DEBUG_MSG(typeid(player).name());
}