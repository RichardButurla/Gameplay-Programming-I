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
    virtual inline float returnHealthValue() = 0;
    virtual inline void takeDamage(float t_weaponDamage) = 0;

    virtual inline std::string returnCharacterType() = 0;
    WeaponTypes weaponChosen = WeaponTypes::None;
    Daggers m_daggerWeapon;


protected:
    float counterValue{0};
    float healthValue{ 50 };
    std::string characterName = " GameObject";
    //whatever variables

};

class Rogue : public GameObject
{
public:
    std::string printVoiceLine();
    virtual inline float returnCounterValue(){return this->counterValue;}
    virtual inline float returnHealthValue(){return this->healthValue;}
    virtual inline std::string returnCharacterType(){return this->characterName;}

    virtual inline void takeDamage(float t_weaponDamage){this->healthValue -= t_weaponDamage;}
private:
    float counterValue = 15;
    float healthValue = 35;
    std::string characterName = "Rogue";
};

class Knight : public GameObject
{
public:
    std::string printVoiceLine();
    virtual inline float returnCounterValue(){return this->counterValue;}
    virtual inline float returnHealthValue(){return this->healthValue;}
    virtual inline std::string returnCharacterType(){return this->characterName;}

    virtual inline void takeDamage(float t_weaponDamage){this->healthValue -= t_weaponDamage;}
private:
    float counterValue = 8;
    float healthValue = 50;
    std::string characterName = "Knight";
};

class Monk : public GameObject
{
public:
    std::string printVoiceLine();
    virtual inline float returnCounterValue(){return this->counterValue;}
    virtual inline float returnHealthValue(){return this->healthValue;}
    virtual inline std::string returnCharacterType(){return this->characterName;}

    virtual inline void takeDamage(float t_weaponDamage){this->healthValue -= t_weaponDamage;}
private:
    float counterValue = 5;
    float healthValue = 45;
    std::string characterName = "Monk";
};

class Fighter : public GameObject
{
public:
    std::string printVoiceLine();
    virtual inline float returnCounterValue(){return this->counterValue;}
    virtual inline float returnHealthValue(){return this->healthValue;}
    virtual inline std::string returnCharacterType(){return this->characterName;}

    virtual inline void takeDamage(float t_weaponDamage){this->healthValue -= t_weaponDamage;}
private:
    float counterValue = 8;
    float healthValue = 45;
    std::string characterName = "Fighter";
};

class Orc : public GameObject
{
public:
    std::string printVoiceLine();
    virtual inline float returnCounterValue(){return this->counterValue;}
    virtual inline float returnHealthValue(){return this->healthValue;}
    virtual inline std::string returnCharacterType(){return this->characterName;}
    
    virtual inline void takeDamage(float t_weaponDamage){this->healthValue -= t_weaponDamage;}
private:
    float counterValue = 8;
    float healthValue = 60;
    std::string characterName = "Orc";
};