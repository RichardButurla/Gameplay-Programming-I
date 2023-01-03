#pragma once

#include "Player.h"
#include "PlayerState.h"

class GlideRunningRightPlayerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);

	virtual void update(Enemy&);
	virtual void enter(Enemy&);
	virtual void exit(Enemy&);
private:
	sf::Clock m_clock;
};
