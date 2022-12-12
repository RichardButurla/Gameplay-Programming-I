#pragma once

#include "Player.h"
#include "PlayerState.h"

class HammeringPlayerState : public PlayerState
{
    public:
    virtual PlayerState *handleInput(gpp::Events &);
    virtual void update(Player &);
    virtual void enter(Player &);
    virtual void exit(Player &);

};