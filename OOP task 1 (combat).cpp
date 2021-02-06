#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <string>
#include <ctime>

template<int min, int max>
struct Dice {
    int Roll() const {
        return rand() % (max - min) + max;
    }
};

// d20 dice from 1 to 20, where 20 critical hit / 1 critical failure
// d4 - d12 for weapon damage rate
using d20 = Dice<1,20>;
using d4 = Dice<1,4>;
using d6 = Dice<1,6>;
using d8 = Dice<1,8>;
using d10 = Dice<1,10>;
using d12 = Dice<1,12>;

int Iniciative() {
    return d20{}.Roll();
}

class Weapon {
public:
    Weapon(int weaponType, int weaponHp)
    : m_weaponType(weaponType), m_weaponHp(weaponHp)
    {}

private:
    int m_weaponType, m_weaponHp;
};


class Character {
public:
    Character(std::string& name, int hp, int armorClass, int runRange)
    :   m_name(name),
        m_hp(hp),
        m_armorClass(armorClass),
        m_runRange(runRange)
    {}

    virtual void run() {
        std::cout << "run" << std::endl;
    }

    virtual int attackThrow() {
        int throwValue = 0;
        throwValue = d20{}.Roll();
        std::cout << throwValue << std::endl;
        return throwValue;
    };

    void setHP(int attackThrow, int attackNum) {
        if (attackThrow > m_armorClass) {
            if(attackNum == 1) {
                m_hp -= firstAttack();
                m_weaponHP -= 5;
                std::cout << "weapon HP: " << m_weaponHP << std::endl;
            }
            if(attackNum == 2) {
                m_hp -= secondAttack();
                m_weaponHP -= 5;
                std::cout << "weapon HP: " << m_weaponHP << std::endl;
            }
            if(attackNum == 3) {
                //надо сделать механизм выбора уклонения от атаки (от номера атаки противника)
                //ввести номер соперника и не получаешь урон
                //в ответ legendaryAttack() и восстанавливает weaponHp до фула
            }

            std::cout << "hp: " << m_hp << std::endl;
        }
        else {
            std::cout << "missing attack" << std::endl;
        }
        if(m_hp <= 0) {
            std::cout << "DeathMorozzz is dead"<< std::endl;
        }
        Character::setHP(attackThrow, attackNum);
    }


    virtual int firstAttack() = 0;
    virtual int secondAttack() = 0;
    virtual double damageBlock(int skill_Or_Item) {

    };
    virtual int legendaryAttack() = 0;




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

class Ranger : public Character {
public:
    explicit Ranger(std::string name = "Ranger_x_Ubiwator123_x",
                    int hp = 44,
                    int armorClass = 13,

                    int weaponHp = 20,
                    int runRange = 35,
                    int shieldType = 0,
                    int bow = 2)
    : Character(name, hp, armorClass, shieldType, weaponHp,  runRange), m_longBow(bow)
    {}

    double damageBlock(int shield) override {

    }

    //first attack (sword attack)
    int firstAttack() override {
        return d6{}.Roll();
    }

    //second attack (bow attack)
    int secondAttack() override {
        return d10{}.Roll() * m_longBow;
    }

    //legendary attack (fire arrow)
    int legendaryAttack() override {
        return d10{}.Roll() + d10{}.Roll();
    }

    //setHp
    void setHP(int attackThrow, int damageThrow) override {
        damageThrow += m_longBow;
        Character::setHP(attackThrow, damageThrow);
    }
private:
    int m_longBow;

};

/*class DeathMorozzz : public Character {
public:
    explicit DeathMorozzz(std::string name = "The_DeathMorozzz",
                        int hp = 34,
                        int armorClass = 14,
                        int weaponType = 3,
                        int weaponHp = 20,
                        int runRange = 30,
                        int shield = 2)
    : Character(name, hp, armorClass, weaponType, weaponHp, runRange), m_shield(shield)
    {}

    void setHP(int attackThrow, int damageThrow) override {
        attackThrow -= m_shield;
    }

private:
    int m_shield;
};*/


Character* Turn (int v) {
    if(v == 1) {
        return new Ranger{};
    }
    /*else {
        return new DeathMorozzz{};
    }*/
}

int main() {

    std::cout << "Good day, dear gamers! Please, pick you hero for start: "
                 "number 1 - The_DeathMorozzz, 2 - Ranger_x_Ubiwator123_x" << std::endl;
    int heroVariant;
    std::cin >> heroVariant;


    /*Character* ch =*/


    std::cout << " " << std::endl;


    return 0;
}




