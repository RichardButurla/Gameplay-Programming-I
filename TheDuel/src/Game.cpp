#include "../include/Game.h"

void Game::run()
{
    system("clear");
    int input = 0;
    std::cout << "Choose Game Mode: \n -1- Single Player\n -2- Two Player\n";
    std::cin >> input;
    m_gameMode = static_cast<GameMode>(input);
    m_playerTurn = PlayerTurn::PlayerOneTurn;
    system("clear");

    switch (m_gameMode)
    {
    case GameMode::SinglePlayer:
        runSinglePlayer();
        break;

    case GameMode::TwoPlayer:
        runTwoPlayer();
        break;

    default:
        break;
    }

}

void Game::runSinglePlayer()
{
    m_playerTurn = PlayerTurn::PlayerOneTurn;
    std::cout << "Player 1 ";
    chooseWeapon();
    chooseCharacter();
    addName(m_playerOneObject);
    system("clear");
    std::cout << "Player Character: " << m_playerOneObject->returnCharacterName() << ", Player Weapon: " << m_PlayerOneWeapon->returnWeaponName() << "\n";

    randomiseComputerCharacter();
    randomiseComputerWeapon();
    std::cout << "Opponent Character: " << m_computerCharacter->returnCharacterName() << ", Opponent Weapon: " << m_computerWeapon->returnWeaponName() << "\n";

    while (m_currentGameState != GameStates::GameOver)
    {
        chooseAction();
        randomiseComputerAction();
        checkGameMode();

        if (m_currentGameState == GameStates::Restart)
        {
            chooseWeapon();
            chooseCharacter();
            std::cout << "Player Character: " << m_playerOneObject->returnCharacterType() << ", Player Weapon: " << m_PlayerOneWeapon->returnWeaponName() << "\n";

            randomiseComputerCharacter();
            randomiseComputerWeapon();
            std::cout << "Opponent Character: " << m_computerCharacter->returnCharacterType() << ", Opponent Weapon: " << m_computerWeapon->returnWeaponName() << "\n";
        }
    }
}

void Game::runTwoPlayer()
{
    std::cout << "Player 1 ";
    chooseWeapon();
    chooseCharacter();
    addName(m_playerOneObject);
    system("clear");
    std::cout << "Player One Character: " << m_playerOneObject->returnCharacterType() << ", Player One Weapon: " << m_PlayerOneWeapon->returnWeaponName() << "\n";

    passTurn();
    std::cout << "Player 2 ";
    chooseWeapon();
    chooseCharacter();
    addName(m_playerTwoObject);
    system("clear");
    std::cout << "Player One Character: " << m_playerOneObject->returnCharacterType() << ", Player One Weapon: " << m_PlayerOneWeapon->returnWeaponName() << "\n";
    std::cout << "Player Two Character: " << m_playerTwoObject->returnCharacterType() << ", Player Two Weapon: " << m_PlayerTwoWeapon->returnWeaponName() << "\n";

    while (m_currentGameState != GameStates::GameOver)
    {
        passTurn();
        chooseAction();
        passTurn();
        chooseAction();

        checkGameMode();

        if (m_currentGameState == GameStates::Restart)
        {
            std::cout << "\n\nPlayer 1 ";
            chooseWeapon();
            chooseCharacter();
            std::cout << "Player Character: " << m_playerOneObject->returnCharacterName() << ", Player Weapon: " << m_PlayerOneWeapon->returnWeaponName() << "\n";

            passTurn();
            std::cout << "\n\nPlayer 2 ";
            chooseWeapon();
            chooseCharacter();
            std::cout << "Player Two Character: " << m_playerTwoObject->returnCharacterName() << ", Player Two Weapon: " << m_PlayerTwoWeapon->returnWeaponName() << "\n";
        }
    }
}

void Game::selectCharacter(GameObject*& t_playerObject)
{
    int input;
    std::cout << "Choose Character: \n -1- Rogue \n -2- Knight \n -3- Monk\n -4- Fighter\n -5- Orc\n";

    std::cin >> input;
    CharacterTypes characterChosen = static_cast<CharacterTypes>(input);

    switch (characterChosen)
    {
    case CharacterTypes::Rogue:
        t_playerObject = new Rogue();
        break;

    case CharacterTypes::Knight:
        t_playerObject = new Knight();
        break;

    case CharacterTypes::Monk:
        t_playerObject = new Monk();
        break;

    case CharacterTypes::Fighter:
        t_playerObject = new Fighter();
        break;

    case CharacterTypes::Orc:
        t_playerObject = new Orc();
        break;

    default:
        break;
    }
}

void Game::selectWeapon(WeaponObject*& t_playerWeapon)
{
    int input;
    std::cout << "Choose a Weapon: \n-1- Daggers \n-2- Sword and Shield \n-3- Battle Axe\n-4- Staff\n";

    std::cin >> input;
    WeaponTypes weaponChosen = static_cast<WeaponTypes>(input);

    switch (weaponChosen)
    {
    case WeaponTypes::Daggers:
        t_playerWeapon = new Daggers();
        break;

    case WeaponTypes::SwordAndShield:
        t_playerWeapon = new SwordAndShield();
        break;

    case WeaponTypes::BattleAxe:
        t_playerWeapon = new BattleAxe();
        break;

    case WeaponTypes::Staff:
        t_playerWeapon = new Staff();
        break;

    default:
        break;
    }
}

void Game::chooseCharacter()
{
    switch (m_playerTurn)
    {
    case PlayerTurn::PlayerOneTurn:
        selectCharacter(m_playerOneObject);
        break;

    case PlayerTurn::PlayerTwoTurn:
        selectCharacter(m_playerTwoObject);
        break;

    default:
        break;
    }
}

void Game::chooseWeapon()
{
    switch (m_playerTurn)
    {
    case PlayerTurn::PlayerOneTurn:
        selectWeapon(m_PlayerOneWeapon);
        break;

    case PlayerTurn::PlayerTwoTurn:
        selectWeapon(m_PlayerTwoWeapon);
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
    switch (m_playerTurn)
    {
    case PlayerTurn::PlayerOneTurn:
        selectAction(m_playerOneAction,m_playerOneObject);
        break;

    case PlayerTurn::PlayerTwoTurn:
        selectAction(m_playerTwoAction,m_playerTwoObject);
        break;

    default:
        break;
    }
}

void Game::selectAction(ActionTaken& t_playerAction,GameObject* t_player)
{
    int input;
    std::cout << t_player->returnCharacterName() << " choose your action: \n\n";

    std::cout << "-1- Attack\n-2- Block\n-3-Guard Break\n\n";
    std::cin >> input;
    system("clear");

    // 1 = Attack, 2 = Block, 3 = guardBreak
    switch (input)
    {
    case 1:
        t_playerAction = ActionTaken::Attacking;
        break;

    case 2:
        t_playerAction = ActionTaken::Blocking;
        break;

    case 3:
        t_playerAction = ActionTaken::GuardBreak;
        break;

    default:
        break;
    }
}

void Game::passTurn()
{
    if (m_playerTurn == PlayerTurn::PlayerOneTurn) {
        m_playerTurn = PlayerTurn::PlayerTwoTurn;
    }
    else {
        m_playerTurn = PlayerTurn::PlayerOneTurn;
    }
}

void Game::addName(GameObject*& t_playerObject)
{
    std::cout << "Enter name \n";
    std::string nameInputted = "";
    std::cin >> nameInputted;
    t_playerObject->setGameObjectName(nameInputted);
}

void Game::randomiseComputerAction()
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


void Game::checkGameMode()
{
    switch (m_gameMode)
    {
    case GameMode::SinglePlayer:
        compareActions(m_playerOneObject, m_computerCharacter, m_PlayerOneWeapon, m_computerWeapon, m_playerOneAction, m_computerAction);
        compareHealth(m_playerOneObject, m_computerCharacter);
        break;

    case GameMode::TwoPlayer:
        compareActions(m_playerOneObject, m_playerTwoObject, m_PlayerOneWeapon, m_PlayerTwoWeapon, m_playerOneAction, m_playerTwoAction);
        compareHealth(m_playerOneObject, m_playerTwoObject);
        break;

    default:
        break;
    }
}
/// @brief Compare Actions of computer and player and decide what happens
void Game::compareActions(GameObject* t_objectOne, GameObject* t_objectTwo, WeaponObject* t_weaponObjectOne, WeaponObject* t_weaponObjectTwo, ActionTaken& t_objectActionTakenOne, ActionTaken& t_objectActionTakenTwo)
{


    if (t_objectActionTakenOne == ActionTaken::Attacking)
    {
        switch (t_objectActionTakenTwo)
        {
        case ActionTaken::Attacking:
            std::cout << "Both Opponents clashed swords\n";
            break;
        case ActionTaken::Blocking:
            std::cout << t_objectTwo->returnCharacterName() << " blocked " << t_objectOne->returnCharacterName() << "'s attack! " << t_objectOne->returnCharacterName() << " is staggered and counter-attacked for! " + std::to_string(t_weaponObjectTwo->returnBlockValue()) + "\n";
            t_objectOne->takeDamage(t_weaponObjectTwo->returnBlockValue());
            break;
        case ActionTaken::GuardBreak:
            std::cout << t_objectOne->returnCharacterName() << " hit through " << t_objectTwo->returnCharacterName() << "'s guard break!, opponent hit for " + std::to_string(t_weaponObjectOne->returnDamageValue()) + " Damage!\n";
            t_objectTwo->takeDamage(t_weaponObjectOne->returnDamageValue());
            break;
        default:
            break;
        }
    }
    if (t_objectActionTakenOne == ActionTaken::Blocking)
    {
        switch (t_objectActionTakenTwo)
        {
        case ActionTaken::Attacking:
            std::cout << t_objectOne->returnCharacterName() << " blocked " << t_objectTwo->returnCharacterName() << "'s attack! " << t_objectTwo->returnCharacterName() << " is staggered and counter-attacked for " + std::to_string(t_weaponObjectOne->returnBlockValue()) + " Damage!\n";
            t_objectTwo->takeDamage(t_weaponObjectOne->returnBlockValue());
            break;
        case ActionTaken::Blocking:
            std::cout << "Both Opponents blocked. \n";
            break;

        case ActionTaken::GuardBreak:
            std::cout << t_objectOne->returnCharacterName() << "'s guard is broken and is counter-attacked for! " + std::to_string(t_objectTwo->returnCounterValue()) + " Damage!\n";
            t_objectOne->takeDamage(t_objectTwo->returnCounterValue());
            break;
        default:
            break;
        }
    }
    if (t_objectActionTakenOne == ActionTaken::GuardBreak)
    {
        switch (t_objectActionTakenTwo)
        {
        case ActionTaken::Attacking:
            std::cout << t_objectTwo->returnCharacterName() << " hit through " << t_objectOne->returnCharacterName() << "'s guard break!, " << t_objectOne->returnCharacterName() << " hit for " << t_weaponObjectTwo->returnDamageValue() << " Damage!\n";
            t_objectOne->takeDamage(t_weaponObjectTwo->returnDamageValue());
            break;
        case ActionTaken::Blocking:
            std::cout << t_objectTwo->returnCharacterName() << "'s guard is broken and is counter-attacked for " << t_objectOne->returnCounterValue() << " Damage!\n";
            t_objectTwo->takeDamage(t_objectOne->returnCounterValue());
            break;

        case ActionTaken::GuardBreak:
            std::cout << "Both Opponents bump into eachother\n";
            break;
        default:
            break;
        }
    }
}

void Game::compareHealth(GameObject* t_objectOne, GameObject* t_objectTwo)
{
    int input = 0;

    if (t_objectOne->returnHealthValue() <= 0)
    {
        std::cout << t_objectOne->returnCharacterName() << " died\nGAME OVER!";
        std::cout << "1 FOR EXIT, 2 TO RESTART\n";
        std::cin >> input;
        m_currentGameState = static_cast<GameStates>(input);
    }
    if (t_objectTwo->returnHealthValue() <= 0)
    {
        std::cout << t_objectTwo->returnCharacterName() << " died\nGAME OVER!";
        std::cout << "1 FOR EXIT, 2 TO RESTART\n";
        std::cin >> input;
        m_currentGameState = static_cast<GameStates>(input);
    }
    else if (input == 0)
    {

        std::cout << t_objectOne->returnCharacterName() << "'s Health: " <<  t_objectOne->returnHealthValue() << " " <<t_objectTwo->returnCharacterName() << "'s Health: " << t_objectTwo->returnHealthValue() << "\n\n";
        std::cout << "1 FOR EXIT, 3 TO CONTINUE\n";
        std::cin >> input;
        m_currentGameState = static_cast<GameStates>(input);
    }
    system("clear");

}

