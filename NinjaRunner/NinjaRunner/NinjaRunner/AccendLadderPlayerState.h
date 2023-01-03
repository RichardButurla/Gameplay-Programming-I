#ifndef ACCEND_LADDER_PLAYER_STATE_H
#define ACCEND_LADDER_PLAYER_STATE_H

#include "Player.h"
#include "PlayerState.h"
#include "Enemy.h"

class AccendLadderPlayerState : public PlayerState {
public:
	virtual PlayerState* handleInput(gpp::Events& input);
	virtual void update(Player&);
	virtual void enter(Player&);
	virtual void exit(Player&);

	virtual void update(Enemy&);
	virtual void enter(Enemy&);
	virtual void exit(Enemy&);
};

#endif
