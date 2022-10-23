#pragma once
#include "GameObjects.h"
#include <random>
#include <time.h>
#include <string>

enum class GameStates
{
    None,
    PlayerCharacterSelect,
    ComputerCharacterSelect,
    PlayersTurn,
    ComputersTurn,
    GameOver
};

enum class ActionTaken
{
    None,
    Attacking,
    Blocking,
    GuardBreak 
};


class Game
{

public:
    Game() = default;
    void run();

    void chooseWeapon();
    void choosePlayerCharacter();

    void randomiseComputerWeapon();
    void randomiseComputerCharacter();

    void chooseAction();
    void randomiseComputerAction( );

    void compareActions();

    void compareHealth();



private:
    GameStates m_currentGameState = GameStates::None;
    //Player pointers
    GameObject* m_player;
    WeaponObject* m_playerWeapon;

    ActionTaken m_playerAction = ActionTaken::None;

    //Computer pointers
    GameObject* m_computerCharacter;
    WeaponObject* m_computerWeapon;

    ActionTaken m_computerAction = ActionTaken::None;

};