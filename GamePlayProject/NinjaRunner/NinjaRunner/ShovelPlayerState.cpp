#include "ShovelPlayerState.h"
#include "RunRightPlayerState.h"
#include "DiedPlayerState.h"

PlayerState* ShovelPlayerState::handleInput(gpp::Events& input)
{
    if (input.getCurrent() == gpp::Events::Event::RUN_RIGHT_START_EVENT)
    {
        DEBUG_MSG("AttackPlayerState -> RunRightPlayerState");
		return new RunRightPlayerState();
    }
    else if (input.getCurrent() == gpp::Events::Event::SHOVEL_END_EVENT)
    {
        DEBUG_MSG("ShovelPlayerState -> IdlePlayerState");
		return new IdlePlayerState();
    }
	else if (input.getCurrent() == gpp::Events::Event::DIED_EVENT) {
		DEBUG_MSG("AttackPlayerState -> DiedPlayerState");
		return new DiedPlayerState();
	}
    return nullptr;
}

void ShovelPlayerState::update(Player &player)
{
    // DEBUG_MSG(typeid(player).name());
}

void ShovelPlayerState::enter(Player &player)
{
    DEBUG_MSG("Entering ShovelPlayerState");
	player.getAnimatedSprite().clearFrames();

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
	
	player.getAnimatedSprite().setTime(seconds(0.05f));
}

void ShovelPlayerState::exit(Player & player)
{
    DEBUG_MSG("Exiting ShovellingPlayerState");
	DEBUG_MSG(typeid(player).name());
}