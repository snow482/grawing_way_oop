#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <memory>

class Character {
public:
    Character(std::string name, int hp, int armorClass);
    int initiativeAndAttackD20Throw() const;
    int getArmorClass() const;
    int getHPInfo() const;
    std::string getName() const;
    void setActionType(int number, int commandType);

    int getAttackerAttackType() const;
    void setAttackerAttackType(int number);
    int getAttackerBlockType() const;
    void setAttackerBlockType(int number);

    int getDefenderAttackType() const;
    void setDefenderAttackType(int number);
    int getDefenderBlockType() const;
    void setDefenderBlockType(int number);

    /*void setBlockType(int number, int commandType);*/
    int getBuffType() const;

    void getDamage(int damage);
    void infoPrinter();
    bool attackThrows (int attackThrowValue, int armorClassValue);
    int buffModifier (int commandNumber, int counterType, std::vector<int> buffTypeValue);
    int buff(int buffType, int );
    void attack(std::shared_ptr<Character> enemy /*!Character* enemy*/, int attackNumber);
    void action (int modifier, std::shared_ptr<Character> ptrType);

private:
    int damageTop() const;
    int damageMiddle() const;
    int damageLow() const;
    int damageLegendary() const;

private:
    std::string m_name;
    int m_hp, m_armorClass;
    int m_damageModifier = 1;
    int m_modificator = 0;

    std::vector<int> m_defenceBuffValue = {1, 1, 1};
    std::vector<int> m_attackBuffValue = {2, 3, 4};

    int m_attackerAttackCommand = 0;
/*
    int m_attackerBlockCommand = 0;
    int m_defenderAttackCommand = 0;
*/
    int m_defenderBlockCommand = 0;

    int m_buffType = 0;
    /*int m_defenderBuffType = 0;*/

    int m_attackCounter = 0;
    /*int m_attackerDefenceCounter = 0;*/
    int m_defenceCounter = 0;
    /*int m_defenderDefenceCounter = 0;*/
};