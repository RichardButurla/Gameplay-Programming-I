#pragma once
#include "GameObjects.h"
#include <random>
#include <time.h>
#include <string>

enum class GameStates
{
    None,
    GameOver,
    Restart,
    Game
};

enum class GameMode
{
    None,
    SinglePlayer,
    TwoPlayer
};

enum class ActionTaken
{
    None,
    Attacking,
    Blocking,
    GuardBreak
};

enum class PlayerTurn
{
    None,
    PlayerOneTurn,
    PlayerTwoTurn
};

class Game
{

public:
    Game() = default;
    void run();
    void runSinglePlayer();
    void runTwoPlayer();

    void chooseWeapon();
    void chooseCharacter();

    void selectWeapon(WeaponObject*& t_playerWeapon);
    void selectCharacter(GameObject*& t_playerObject);
    void selectAction(ActionTaken& t_playerAction,GameObject* t_player);

    void compareActions(GameObject* t_objectOne, GameObject* t_objectTwo, WeaponObject* t_weaponObjectOne, WeaponObject* t_weaponObjectTwo, ActionTaken& t_objectActionTakenOne, ActionTaken& t_objectActionTakenTwo);
    void compareHealth(GameObject* t_objectOne, GameObject* t_objectTwo);
    void checkGameMode();

    void randomiseComputerWeapon();
    void randomiseComputerCharacter();

    void chooseAction();
    void randomiseComputerAction();

    void passTurn();
    void addName(GameObject*& t_playerObject);

private:

    //all enums which control the game
    GameStates m_currentGameState = GameStates::None;

    ActionTaken m_playerOneAction = ActionTaken::None;
    ActionTaken m_computerAction = ActionTaken::None;
    ActionTaken m_playerTwoAction = ActionTaken::None;

    GameMode m_gameMode = GameMode::None;

    PlayerTurn m_playerTurn = PlayerTurn::None;

    //Player pointers
    GameObject* m_playerOneObject;
    WeaponObject* m_PlayerOneWeapon;
    GameObject* m_playerTwoObject;
    WeaponObject* m_PlayerTwoWeapon;

    //Computer pointers
    GameObject* m_computerCharacter;
    WeaponObject* m_computerWeapon;

};