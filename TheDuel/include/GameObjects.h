#pragma once
#include "WeaponObjects.h"

enum class CharacterTypes
{
    None,
    Rogue,
    Knight,
    Monk,
    Fighter,
    Orc
};
class GameObject
{
public:
    GameObject() = default;

    virtual inline float returnCounterValue() = 0;

    virtual void printVoiceLine() = 0;
    WeaponTypes weaponChosen = WeaponTypes::None;
    Daggers m_daggerWeapon;


protected:
    float counterValue{0};
    float health{ 0 };
    //whatever variables

};

class Rogue : public GameObject
{
public:
    void printVoiceLine();
    virtual inline float returnCounterValue(){return this->counterValue;}
private:
    float counterValue = 7;
};

class Knight : public GameObject
{
public:
    void printVoiceLine();
    virtual inline float returnCounterValue(){return this->counterValue;}
private:
    float counterValue = 6;
};

class Monk : public GameObject
{
public:
    void printVoiceLine();
    virtual inline float returnCounterValue(){return this->counterValue;}
private:
    float counterValue = 3;
};

class Fighter : public GameObject
{
public:
    void printVoiceLine();
    virtual inline float returnCounterValue(){return this->counterValue;}
private:
    float counterValue = 8;
};

class Orc : public GameObject
{
public:
    void printVoiceLine();
    virtual inline float returnCounterValue(){return this->counterValue;}
private:
    float counterValue = 5;
};