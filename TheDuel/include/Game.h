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

    //Weapon Objects
    Daggers m_daggers;
    BattleAxe m_battleAxe;
    SwordAndShield m_swordAndShield;
    Bow m_bow;

    //CharacterObjects
    Rogue m_rogue;
    Knight m_knight;
    Archer m_archer;
    Fighter m_fighter;
    Orc m_orc;

};