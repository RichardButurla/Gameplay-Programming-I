#include "../include/Game.h"

void Game::run()
{
    int input = 0;

        chooseWeapon();
        choosePlayerCharacter();

        m_playerWeapon->inspect();
        m_player->printVoiceLine();

        randomiseComputerCharacter();
        randomiseComputerWeapon();

        std::cout << "The computer is a ";
        m_computerCharacter->printVoiceLine();
        std::cout << "And has a ";
        m_computerWeapon->inspect();

        

    while (m_currentGameState != GameStates::GameOver)
    {
        chooseAction();
        compareActions();

        std::cout << "5 FOR EXIT, 1 TO CONTINUE\n";
        std::cin >> input;
        m_currentGameState = static_cast<GameStates>(input);


    }
}


void Game::chooseWeapon()
{
    int input;
    std::cout << "Choose Weapon: \n -1- Daggers \n -2- Sword and Shield \n -3- Battle Axe\n -4- Staff\n";

    std::cin >> input;
    WeaponTypes weaponChosen = static_cast<WeaponTypes>(input);
    

    switch (weaponChosen)
    {
    case WeaponTypes::Daggers:
        m_playerWeapon = new Daggers();
        break;

    case WeaponTypes::SwordAndShield:
        m_playerWeapon = new SwordAndShield();
        break;

    case WeaponTypes::BattleAxe:
        m_playerWeapon = new BattleAxe();
        break;

    case WeaponTypes::Staff:
        m_playerWeapon = new Staff();
        break;

    default:
        break;
    }
}

void Game::choosePlayerCharacter()
{
    int input;
    std::cout << "Choose Character: \n -1- Rogue \n -2- Knight \n -3- Monk\n -4- Fighter\n -5- Orc\n";

    std::cin >> input;
    CharacterTypes characterChosen = static_cast<CharacterTypes>(input);


    switch (characterChosen)
    {
    case CharacterTypes::Rogue:
        m_player = new Rogue();
        break;

    case CharacterTypes::Knight:
        m_player = new Knight();
        break;

    case CharacterTypes::Monk:
        m_player = new Monk();
        break;

    case CharacterTypes::Fighter:
        m_player = new Fighter();
        break;

    case CharacterTypes::Orc:
        m_player = new Orc();
        break;

    default:
        break;
    }
}

void Game::randomiseComputerWeapon()
{
    int randNum = std::rand() % 4 + 1; //1,2,3,4,5

    WeaponTypes weaponChosen = static_cast<WeaponTypes>(randNum);


   switch (weaponChosen)
    {
        case WeaponTypes::Daggers:
        m_computerWeapon = new Daggers();
        break;

        case WeaponTypes::SwordAndShield:
        m_computerWeapon = new SwordAndShield();
        break;

        case WeaponTypes::BattleAxe:
        m_computerWeapon = new BattleAxe();
        break;

        case WeaponTypes::Staff:
        m_computerWeapon = new Staff();
        break;

        default:
        break;
    }



}

void Game::randomiseComputerCharacter()
{
    int randNum = std::rand() % 5 + 1; //1,2,3,4,5

    CharacterTypes characterChosen = static_cast<CharacterTypes>(randNum);


    switch (characterChosen)
    {
    case CharacterTypes::Rogue:
        m_computerCharacter = new Rogue();
        break;

    case CharacterTypes::Knight:
        m_computerCharacter = new Knight();
        break;

    case CharacterTypes::Monk:
        m_computerCharacter = new Monk();
        break;

    case CharacterTypes::Fighter:
        m_computerCharacter = new Fighter();
        break;

    case CharacterTypes::Orc:
        m_computerCharacter = new Orc();
        break;

    default:
        break;
    }
}

void Game::chooseAction()
{
    int input;
    std::cout << "Choose your action \n";

    std::cout << "-1- Attack\n -2- Block\n -3-Guard Break\n";
    std::cin >> input;

    
    // 1 = Attack, 2 = Block, 3 = Dodge 
    switch (input)
    {
    case 1:
    m_playerAction = ActionTaken::Attacking;
        break;

    case 2:
    m_playerAction = ActionTaken::Blocking;
        break;

    case 3:
     m_playerAction = ActionTaken::GuardBreak;
        break;

    default:
        break;
    }

    randomiseComputerAction();

}

void Game::randomiseComputerAction( )
{
    int randNum = std::rand() % 3 + 1; //1,2,3


    //ComputerPicks, 1 = Attack, 2 = Block, 3 = Dodge
    switch (randNum)
    {
    case 1:
    m_computerAction = ActionTaken::Attacking;
    break;

    case 2:
    m_computerAction = ActionTaken::Blocking;
    break;

    case 3:
    m_computerAction = ActionTaken::GuardBreak;
        break;

    default:
        break;
    }


    

}

/// @brief Compare Actions of computer and player and decide what happens
void Game::compareActions()
{
    if(m_playerAction == ActionTaken::Attacking)
    {
        switch (m_computerAction)
        {
        case ActionTaken::Attacking:
            std::cout << "Player and opponent both clashed swords\n";
            break;
        case ActionTaken::Blocking:
            std::cout << "Opponent blocked Players attack! Player is staggered and counter-attacked for! " + std::to_string(m_computerWeapon->returnBlockValue()) +  "\n";
        break;
        case ActionTaken::GuardBreak:
            std::cout << "Player hit through Opponents guard break!, opponent hit for " + std::to_string(m_computerWeapon->returnDamageValue()) + " Damage!\n";
        break;
        default:
            break;
        }
    }
    if(m_playerAction == ActionTaken::Blocking)
    {
        switch (m_computerAction)
        {
        case ActionTaken::Attacking:
            std::cout << "Player blocked Opponents attack! Opoonent is staggered and counter-attacked for " + std::to_string(m_computerWeapon->returnDamageValue()) +  " Damage!\n";
            break;
        case ActionTaken::Blocking:
            std::cout << "Player and Opponent both blocked. \n";
        break;

        case ActionTaken::GuardBreak:
        std::cout << "Players guard is broken and is counter-attacked for! " + std::to_string(m_computerWeapon->returnBlockValue()) +  " Damage!\n";
        break;
        default:
            break;
        }
    }
    if(m_playerAction == ActionTaken::GuardBreak)
    {
        switch (m_computerAction)
        {
        case ActionTaken::Attacking:
            std::cout << "Opponent hit through Players guard break!, player hit for " + std::to_string(m_computerWeapon->returnDamageValue()) + " Damage!\n";
            break;
        case ActionTaken::Blocking:
        std::cout << "Oppoents guard is broken and is counter-attacked for! " + std::to_string(m_computerWeapon->returnBlockValue()) +  " Damage!\n";
        break;

        case ActionTaken::GuardBreak:
        std::cout << "Both Opponents bump into eachother\n";
        break;
        default:
            break;
        }
    }
}