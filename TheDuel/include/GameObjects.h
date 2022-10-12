#pragma once
#include "WeaponObjects.h"

enum class CharacterTypes
{
    None,
    Rogue,
    Knight,
    Archer,
    Fighter,
    Orc
};
class GameObject
{
public:
    GameObject() = default;

    void attack();
    void block();
    void dodge();

   virtual void printVoiceLine();
    WeaponTypes weaponChosen = WeaponTypes::None;
    WeaponObject m_weaponObject;
    Daggers m_daggerWeapon;


private:
    float dodgechance{0};
    float health{ 0 };
    //whatever variables

};

class Rogue : public GameObject
{
public:
    void printVoiceLine();
private:
    float dodgechance = 10;
};

class Knight : public GameObject
{
public:
    void printVoiceLine();
private:
    float dodgechance = 5;
};

class Archer : public GameObject
{
public:
    void printVoiceLine();
private:
    float dodgechance = 3;
};

class Fighter : public GameObject
{
public:
    void printVoiceLine();
private:
    float dodgechance = 7;
};

class Orc : public GameObject
{
public:
    void printVoiceLine();
private:
    float dodgechance = 5;
};