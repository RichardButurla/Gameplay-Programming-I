#pragma once
#include <iostream>

enum class WeaponTypes
{
    None,
    Daggers,
    SwordAndShield,
    BattleAxe,
    Bow
};

class WeaponObject
{
public:
    WeaponObject() = default;
    virtual void inspect() { std::cout << "inspectWeapon\n"; }
    virtual inline float returnDamageValue() = 0;
    virtual inline float returnBlockValue() = 0;

protected:

    int damageValue = 0;
    bool ranged = 0;
    float blockValue = 0;
    WeaponTypes m_weaponType = WeaponTypes::None;


};

class Daggers : public WeaponObject
{
public:

    void inspect() { std::cout << "Shiny dagger\n"; }
    virtual inline float returnDamageValue(){return this->damageValue;} 
    virtual inline float returnBlockValue(){return this->blockValue;}

private:
    WeaponTypes m_weaponType = WeaponTypes::Daggers;

};

class SwordAndShield : public WeaponObject
{
public:

    void inspect() { std::cout << "Shiny sword and shield\n"; }
    virtual inline float returnDamageValue(){return this->damageValue;} 
    virtual inline float returnBlockValue(){return this->blockValue;}

private:
    WeaponTypes m_weaponType = WeaponTypes::SwordAndShield;

};

class Bow : public WeaponObject
{
public:

    void inspect() { std::cout << "Shiny Bow\n"; }
    virtual inline float returnDamageValue(){return this->damageValue;} 
    virtual inline float returnBlockValue(){return this->blockValue;}

private:
    WeaponTypes m_weaponType = WeaponTypes::Bow;

};

class BattleAxe : public WeaponObject
{
public:

    void inspect() { std::cout << "Shiny AXE\n"; }
    virtual inline float returnDamageValue(){return this->damageValue;} 
    virtual inline float returnBlockValue(){return this->blockValue;}

private:
    WeaponTypes m_weaponType = WeaponTypes::BattleAxe;

};