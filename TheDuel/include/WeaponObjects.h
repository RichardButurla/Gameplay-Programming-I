#pragma once
#include <iostream>

enum class WeaponTypes
{
    None,
    Daggers,
    SwordAndShield,
    BattleAxe,
    Staff
};

class WeaponObject
{
public:
    WeaponObject() = default;
    virtual inline std::string returnWeaponName() = 0;
    virtual inline int returnDamageValue() = 0;
    virtual inline int returnBlockValue() = 0;

protected:

    int damageValue = 0;
    bool ranged = 0;
    float blockValue = 0;
    std::string weaponName = "Weapon Object";
    WeaponTypes m_weaponType = WeaponTypes::None;


};

class Daggers : public WeaponObject
{
public:

    void inspect() { std::cout << " Daggers\n"; }
    virtual inline int returnDamageValue(){return this->damageValue;} 
    virtual inline int returnBlockValue(){return this->blockValue;}
    virtual inline std::string returnWeaponName(){return this->weaponName;}

private:
    WeaponTypes m_weaponType = WeaponTypes::Daggers;
     int damageValue = 10;
     int blockValue = 2;
     std::string weaponName = "Daggers";

};

class SwordAndShield : public WeaponObject
{
public:

    void inspect() { std::cout << " Sword and Shield\n"; }
    virtual inline int returnDamageValue(){return this->damageValue;} 
    virtual inline int returnBlockValue(){return this->blockValue;}
    virtual inline std::string returnWeaponName(){return this->weaponName;}

private:
    WeaponTypes m_weaponType = WeaponTypes::SwordAndShield;
    int damageValue = 9;
    int blockValue = 9;
    std::string weaponName = "Sword and Shield";

};

class Staff : public WeaponObject
{
public:

    void inspect() { std::cout << " Staff\n"; }
    virtual inline int returnDamageValue(){return this->damageValue;} 
    virtual inline int returnBlockValue(){return this->blockValue;}
    virtual inline std::string returnWeaponName(){return this->weaponName;}

private:
    WeaponTypes m_weaponType = WeaponTypes::Staff;
    int damageValue = 7;
    int blockValue = 7;
    std::string weaponName = "Staff";

};

class BattleAxe : public WeaponObject
{
public:

    void inspect() { std::cout << " AXE\n"; }
    virtual inline int returnDamageValue(){return this->damageValue;} 
    virtual inline int returnBlockValue(){return this->blockValue;}
    virtual inline std::string returnWeaponName(){return this->weaponName;}

private:
    WeaponTypes m_weaponType = WeaponTypes::BattleAxe;
    int damageValue = 12;
    int blockValue = 5;
    std::string weaponName = "BattleAxe";
};