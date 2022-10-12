#pragma once
#include <iostream>

enum class StatusEffect
{
    None,
    Poison,
    Bleed,
    Stun,
    Heal
};

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

private:
    int damage{0};
    bool ranged{0};
    float parryChance{0};
    float blockChance{0};
    StatusEffect m_statusEffect = StatusEffect::None;
    WeaponTypes m_weaponType = WeaponTypes::None;


};

class Daggers : public WeaponObject
{
public:

    void inspect() { std::cout << "Shiny dagger\n"; }

private:
    WeaponTypes m_weaponType = WeaponTypes::Daggers;

};

class SwordAndShield : public WeaponObject
{
public:

    void inspect() { std::cout << "Shiny sword and shield\n"; }

private:
    WeaponTypes m_weaponType = WeaponTypes::SwordAndShield;

};

class Bow : public WeaponObject
{
public:

    void inspect() { std::cout << "Shiny Bow\n"; }

private:
    WeaponTypes m_weaponType = WeaponTypes::Bow;

};

class BattleAxe : public WeaponObject
{
public:

    void inspect() { std::cout << "Shiny AXE\n"; }

private:
    WeaponTypes m_weaponType = WeaponTypes::BattleAxe;

};