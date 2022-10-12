#include "../include/Game.h"

void Game::run()
{
    while (m_currentGameState != GameStates::GameOver)
    {
        int input = 0;

        chooseWeapon();
        choosePlayerCharacter();

        m_playerWeapon->inspect();
        m_player->printVoiceLine();

        std::cout << "5 FOR EXIT\n";
        std::cin >> input;
        m_currentGameState = static_cast<GameStates>(input);
    }
}


void Game::chooseWeapon()
{
    int input;
    std::cout << "Choose Weapon: \n -1- Daggers \n -2- Sword and Shield \n -3- Battle Axe\n -4- Bow\n";

    std::cin >> input;
    WeaponTypes weaponChosen = static_cast<WeaponTypes>(input);
    

    switch (weaponChosen)
    {
    case WeaponTypes::Daggers:
        m_playerWeapon = &m_daggers;
        break;

    case WeaponTypes::SwordAndShield:
        m_playerWeapon = &m_swordAndShield;
        break;

    case WeaponTypes::BattleAxe:
        m_playerWeapon = &m_battleAxe;
        break;

    case WeaponTypes::Bow:
        m_playerWeapon = &m_bow;
        break;

    default:
        break;
    }
}

void Game::choosePlayerCharacter()
{
    int input;
    std::cout << "Choose Character: \n -1- Rogue \n -2- Knight \n -3- Archer\n -4- Fighter\n -5- Orc\n";

    std::cin >> input;
    CharacterTypes characterChosen = static_cast<CharacterTypes>(input);


    switch (characterChosen)
    {
    case CharacterTypes::Rogue:
        m_player = &m_rogue;
        break;

    case CharacterTypes::Knight:
        m_player = &m_knight;
        break;

    case CharacterTypes::Archer:
        m_player = &m_archer;
        break;

    case CharacterTypes::Fighter:
        m_player = &m_fighter;
        break;

    case CharacterTypes::Orc:
        m_player = &m_orc;
        break;

    default:
        break;
    }
}
