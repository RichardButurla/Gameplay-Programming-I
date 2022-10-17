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

    virtual inline float returnCounterValue(){return counterValue;}

    virtual void printVoiceLine();
    WeaponTypes weaponChosen = WeaponTypes::None;
    WeaponObject m_weaponObject;
    Daggers m_daggerWeapon;


private:
    float counterValue{0};
    float health{ 0 };
    //whatever variables

};

class Rogue : public GameObject
{
public:
    void printVoiceLine();
private:
    float counterValue = 7;
};

class Knight : public GameObject
{
public:
    void printVoiceLine();
private:
    float counterValue = 6;
};

class Archer : public GameObject
{
public:
    void printVoiceLine();
private:
    float counterValue = 3;
};

class Fighter : public GameObject
{
public:
    void printVoiceLine();
private:
    float counterValue = 8;
};

class Orc : public GameObject
{
public:
    void printVoiceLine();
private:
    float counterValue = 5;
};