#include <iostream>
#include <map>
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

class Ranger {
public:


private:


};

class Character {
public:
    Character(std::string& name, int hp, int armorClass, int runRange)
    : m_name(name), m_hp(hp), m_armorClass(armorClass), m_runRange(runRange)
    {};

    int initiativeThrow() const {
        return d20_throw();
    }

    int attackThrow() const {
        return d20_throw();
    }

    int getArmorClass() {
        return m_armorClass;
    }

    void armorBuff(int commandNumber) {
        for(auto& it : m_defenceBuffValue){
            if(commandNumber == it.first){
                m_armorClass += it.second;
            }
        }
    }

    int attackBuff(int commandNumber) {
        int damage = 0;
        for(auto& it : m_attackBuffValue) {
            if(commandNumber == it.first){
                damage = getDamage();
            }
        }
        return damage;
    }

    void getDamage(int damage) {
        m_hp -= damage;
    };

    void attack(Character* enemy) {
        int attackThrowValue = attackThrow();
        int getArmorClassValue = getArmorClass();

        if(attackThrowValue < getArmorClassValue) {
            std::cout << "attack throw: " << attackThrowValue
                      << "armor class: " << getArmorClassValue << std::endl;
            return;
        }

        int commandNumber = 0;
        std::cin >> commandNumber;

        switch (commandNumber) {
            case 1: buff;
            case 2: ;
            case 3: ;
        }
        getDamage(enemy->damage());
    }
    /*void buff(Character* enemy) {
        armorBuff(getArmorClass());
    }*/

    /*void attack(Character* character, int attackNumber, int additionWeaponDamage) {
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
    };*/

    void run(int runingDistance) {
        int runingRangeValue = m_runRange;
        if(m_runRange >= runingDistance) {
            m_runRange -= runingDistance;
            std::cout << "running to " << runingDistance << "ft, " << "\n"
                      << "also you have " << m_runRange << "ft" << std::endl;
        }
        else {
            std::cout << "you can't run" << std::endl;
        }
    };

private:
    std::string m_name;
    int m_hp, m_armorClass,  m_runRange;
    std::map<int, int> m_defenceBuffValue = {{1,1} ,
                                             {2, 2},
                                             {3, 3}};
    std::map<int, int> m_attackBuffValue = {{1, 2},
                                            {2, 3},
                                            {3, 4}};
private:
    int damage() const {
        int throwValue = 0;
        throwValue = d8{}.Roll();
        return throwValue;
    }

    int d20_throw() const {
        int throwValue = 0;
        throwValue = d20{}.Roll();
        return throwValue;
    }

    /*
     * как реализовать правильно баф на защиту (ведь у меня нет такого показателя, как атака),
     * мб засунуть значения бафа в параметры - m_buff = 0; если апался, то ++m_buff
     * т.е. надо броски атак - % бафа (который стакается) сделать флаг, сколько раз он юзался, если
     * 1 - (-25% дамага) / (+25% к атаке)
     * 2 - (-50% дамага) / (+50% к атаке)
     * 3 - (-75% дамага) / (+75% к атаке)
     */
    /*void buff(Character* player) {
        int buffNumber = 0;
        std::cout << "please, enter a buff number: 1 - Defence up, 2 - Attack up" << std::endl;
        std::cin >> buffNumber;
        std::map<int, int> attackBuffTable;
        int defenceBuff = 0;
        int attackBuff = 0;
        if(buffNumber == 1) {
            defenceBuff = player->getArmorClass() + attackBuffTable.;
        }
        if(buffNumber == 2) {
            attackBuff = player->damage() * 2;
        }
    }*/
};

void TurnQueue (Character* attacker, Character* defender) {

}


    //дописать "если бросок инициативы первого больше второго, 1ый выбирает атаку и бьет второго,
    //затем 2ой выбирает и бьет 1го" и так до победы кого то одного

void PlayersQueue (Character* firstPlayer, Character* secondPlayer) {
    int firstPlayerInitiativeThrowValue = firstPlayer->initiativeThrow();
    int secondPlayerInitiativeThrowValue = secondPlayer->initiativeThrow();
    std::cout << "first player throw: " << firstPlayerInitiativeThrowValue
              << ", second player throw: " << secondPlayerInitiativeThrowValue << std::endl;

    if(firstPlayerInitiativeThrowValue > secondPlayerInitiativeThrowValue) {
        std::cout << "first player is ATTACKER!" << std::endl;
        firstPlayer->attack(secondPlayer);
    }
    else {
        std::cout << "second player is ATTACKER!" << std::endl;
       secondPlayer->attack(firstPlayer);
    }
}

int main() {




    return 0;
}