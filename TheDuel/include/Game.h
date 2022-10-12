#pragma once
#include "GameObjects.h"

enum class GameStates
{
    None,
    PlayerCharacterSelect,
    ComputerCharacterSelect,
    PlayersTurn,
    ComputersTurn,
    GameOver
};


class Game
{

public:
    Game() = default;
    void run();

    void chooseWeapon();
    void choosePlayerCharacter();




private:
    GameStates m_currentGameState = GameStates::None;
    //Player pointers
    GameObject* m_player;
    WeaponObject* m_playerWeapon;

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