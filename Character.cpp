#include <iostream>
#include "Character.hpp"

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
    Sword,
    LongBow,
    Spell
};

/*class Ranger;
class Morozzz;*/

class Character {
public:
    Character(std::string& name, int hp, int armorClass, int runRange)
    : m_name(name), m_hp(hp), m_armorClass(armorClass), m_runRange(runRange)
    {};
    int d20_Throw() {
        int throwValue = 0;
        throwValue = d20{}.Roll();
        return throwValue;
    }

    void getDamage(int d20_attackThrow, int attackNumber) {
        if(d20_attackThrow > m_armorClass) {
            attack(Character*, );
        }
    };


    void attack(Character* character, int attackNumber, int additionWeaponDamage) {
        if(attackNumber == 1) { //first attack
            m_hp -= d8{}.Roll() + additionWeaponDamage;
        }
        if(attackNumber == 2) { //second attack
            m_hp -= d8{}.Roll() + additionWeaponDamage;
        }
        if(attackNumber == 3) { //block
            // надо выбрать какую атаку я буду блочить и потом если заблочил, наношу атаку
            // легендарным действием
            m_hp -= d12{}.Roll() + d12{}.Roll();
        }

    };
    void run(int runingDistance) {
        int runingScoreValue = m_runRange;
        if(m_runRange >= runingDistance) {
            m_runRange -= runingDistance;
            std::cout << "runing to " << runingDistance << "ft, " << "\n"
                      << "also you have " << m_runRange << "ft" << std::endl;
        }
        else {
            std::cout << "you can't run" << std::endl;
        }
    };

private:
    std::string m_name;
    int m_hp, m_armorClass,  m_runRange;

private:

    /*
     * как реализовать правильно баф на защиту (ведь у меня нет такого показателя, как атака),
     * мб засунуть значения бафа в параметры - m_buff = 0; если апался, то ++m_buff
     * т.е. надо броски атак - % бафа (который стакается) сделать флаг, сколько раз он юзался, если
     * 1 - (-25% дамага) / (+25% к атаке)
     * 2 - (-50% дамага) / (+50% к атаке)
     * 3 - (-75% дамага) / (+75% к атаке)
     */
    int buff(int defence_or_attack) {
        if(defence_or_attack == 1) {

        }
        if(defence_or_attack == 2) {

        }
    }
};


int main() {

    


    return 0;
}