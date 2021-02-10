#include <iostream>
#include <map>
#include "Character.hpp"


/*
 * 1) выбор персонажа
 *
 * 2) броски инициативы (у кого бросок больше, тот первый)
 *
 * 3) атакующему, выбор вариантов атак, 1- баф (атака/защита), 2- верхняя атака, 3- средняя
 *
 * атаки - 1) баф, выбор на атаку или защиту
 *       - 2) бросок атаки d20, если она >= armorClass'а противника = попадание = вычетание хп
 *       - 3) блок (выбрать какую атаку блокировать) если угадал тип атаки, то урона нет и нанесение удара
 *            легендарным действием в ответ
 *       - 4) легендарное действие у каждого персонажа свое
 */

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

class Character {
public:
    Character(std::string &name, int hp, int armorClass, int runRange)
            : m_name(name), m_hp(hp), m_armorClass(armorClass), m_runRange(runRange) {};

    int initiativeThrow() const {
        return d20_throw();
    }

    int attackThrow() const {
        return d20_throw();
    }

    int getArmorClass() {
        return m_armorClass;
    }


    void getDamage(int damage) {
        m_hp -= damage;
    };

    void attack(Character *enemy) {
        int attackThrowValue = attackThrow();
        int getArmorClassValue = getArmorClass();

        if (attackThrowValue < getArmorClassValue) {
            std::cout << "attack throw: " << attackThrowValue
                      << "armor class: " << getArmorClassValue << std::endl;
            return;
        }

        std::cout << "Please, enter the number of action" << "\n"
                  << "1 - Buff, 2- Top attack, 3- Damage block "
                     "(if success, you can take extra damage to enemy by the legendary attack" << std::endl;

        // код ниже перенести в тело верхнего if ????
        int commandNumber = 0;
        std::cin >> commandNumber;

        switch (commandNumber) {
            case 1:
                int defenceCounter = 0; // max = 3
                int attackCounter = 0;  // max = 3
                int buffType = 0;
                std::cin >> buffType;
                if (buffType == 1) {
                    ++defenceCounter;
                    if(defenceCounter <= 3) {
                        armorBuff(defenceCounter);
                    }
                    else {
                        std::cout << "full charge! " << std::endl; // больше нельзя бафаться
                    }
                    std::cout << "defence counter: " << defenceCounter << std::endl;
                }
                if(buffType == 2) {
                    ++attackCounter;
                    if(attackCounter <= 3) {
                        attackBuff(attackCounter);
                    }
                    else {
                        std::cout << "full charge! " << std::endl; // больше нельзя бафаться
                    }
                    std::cout << "attack counter: " << defenceCounter << std::endl;
                };
                return;
            case 2: getDamage(enemy->damage(); // damage without buff
            case 3:;
        }

    }

    void run(int runingDistance) {
        int runingRangeValue = m_runRange;
        if (m_runRange >= runingDistance) {
            m_runRange -= runingDistance;
            std::cout << "running to " << runingDistance << "ft, " << "\n"
                      << "also you have " << m_runRange << "ft" << std::endl;
        } else {
            std::cout << "you can't run" << std::endl;
        }
    };

private:
    std::string m_name;
    int m_hp, m_armorClass, m_runRange;
    std::map<int, int> m_defenceBuffValue = {{1, 1},
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

    void armorBuff(int counterNumber) {
        for (auto &it : m_defenceBuffValue) {
            if (counterNumber == it.first) {
                m_armorClass += it.second;
            }
        }
    }

    int attackBuff(int counterNumber) {
        int damage = 0;
        for (auto &it : m_attackBuffValue) {
            if (counterNumber == it.first) {
                damage = getDamage(it.second);
            }
        }
        return damage;
    }
};
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
