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
    int getAttackType() const;
    void setAttackType(int number);
    int getBlockType() const;
    void setBlockType(int number);
    int getBuffType() const;

    void getDamage(int damage);
    void initiativeThrows (int attackThrowValue, int armorClassValue);
    int buffModifier (int commandNumber, int counterType, std::vector<int> buffTypeValue);
    std::vector<int> getActionInfo ();
    void attack(std::shared_ptr<Character> enemy /*!Character* enemy*/);
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

    int m_attackCommandNumber = 0;
    int m_blockCommandNumber = 0;
    int m_buffType = 0;

    int m_defenceCounter = 0;
    int m_attackCounter = 0;

};