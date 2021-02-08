/*
#include <iostream>


template<int min, int max>
struct Dice {
    int Roll() const {
        return rand() % (max - min) + max;
    }
};

using d20 = Dice<1,20>;
using d4 = Dice<1,4>;
using d6 = Dice<1,6>;
using d8 = Dice<1,8>;
using d10 = Dice<1,10>;
using d12 = Dice<1,12>;

enum class Weapon {
   Sword, LongBow, Spell
};

// может быть лучше map сделать, типа выбрать тип оружия, 1 - sword или "sword" - sword

*/
/*virtual int damageThrow(WeaponType) {
    int damage = 0;
    if (m_weaponType == static_cast<int>(WeaponType::Icicle)) {
        damage = d6{}.Roll();
    }
    if (m_weaponType == static_cast<int>(WeaponType::SantaBag)) {
        damage = d8{}.Roll();
    }
    if (m_weaponType == static_cast<int>(WeaponType::Sleigh)) {
        damage = d10{}.Roll() + d10{}.Roll();
    }
    if (m_weaponType == static_cast<int>(WeaponType::Sword)) {
        damage = d8{}.Roll();
    }
    if (m_weaponType == static_cast<int>(WeaponType::LongBow)) {
        damage = d8{}.Roll();
    }
    if (m_weaponType == static_cast<int>(WeaponType::Spell)) {
        damage = d12{}.Roll() + d12{}.Roll();
    }
    return damage;
}*//*


*/
/*class Ranger;
class Morozzz;*//*


class Character {
public:
    Character(std::string& name, int hp, int armorClass, int runRange);

    int iniativeThrow() {
        int throwValue = 0;
        throwValue = d20{}.Roll();
        return throwValue;
    }
    int attackThrow(Weapon) {
        int damage = 0;
        if()
    };
    void getDamage(int attack);
    void run();

    int firstAttack();
    int secondAttack();
    double damageBlock(int skill_Or_Item);
    int legendaryAttack();

private:
    std::string m_name;
    int m_hp, m_armorClass,  m_runRange;

private:
    */
/*
     * как реализовать правильно баф на защиту (ведь у меня нет такого показателя, как атака),
     * мб засунуть значения бафа в параметры - m_buff = 0; если апался, то ++m_buff
     * т.е. надо броски атак - % бафа (который стакается) сделать флаг, сколько раз он юзался, если
     * 1 - (-25% дамага) / (+25% к атаке)
     * 2 - (-50% дамага) / (+50% к атаке)
     * 3 - (-75% дамага) / (+75% к атаке)
     *//*

    int buff(int defence_or_attack) {
        if(defence_or_attack == 1) {

        }
        if(defence_or_attack == 2) {

        }
    }
};
*/
