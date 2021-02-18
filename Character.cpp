#include <iostream>
#include <vector>
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
class Character;

template<int min, int max>
struct Dice {
    int Roll() const {
        return rand() % (max - min) + min;
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
    Character(std::string name, int hp, int armorClass, int speed)
            : m_name(name), m_hp(hp), m_armorClass(armorClass), m_speed(speed) {};

    int initiativeThrow() const {
        return d20{}.Roll();
    }

    int attackThrow() const {
        return d20{}.Roll();
    }

    int getArmorClass() {
        return m_armorClass;
    }
    int getHPInfo() {
        return m_hp;
    }
    std::string getName() {
        return m_name;
    }

    void getDamage(int damage) {
        m_hp -= damage;
    };

    void attack(Character *enemy) {
        int attackThrowValue = attackThrow();
        int armorClassValue = getArmorClass();

        int defenceCounter = 0; // max = 3
        int attackCounter = 0;  // max = 3

        if (attackThrowValue >= armorClassValue) {
            std::cout << "attack throw: " << attackThrowValue
                      << " armor class: " << armorClassValue << std::endl;

            std::cout << "Please, enter the number of action" << "\n"
                      << "1 - Buff, 2- Top attack, 3- Damage block "
                         "(if success, you can take extra damage to enemy by the legendary attack)" << std::endl;
            int commandNumber = 0;
            std::cin >> commandNumber;
            switch (commandNumber) {
                case 1:
                    std::cin >> commandNumber;
                    if (commandNumber == 1) {
                        ++defenceCounter;
                        if(defenceCounter <= 3) {
                            armorBuff(defenceCounter);
                        }
                        else {
                            std::cout << "full charge! " << std::endl; // больше нельзя бафаться
                        }
                        std::cout << "defence counter: " << defenceCounter << std::endl;
                    }
                    if(commandNumber == 2) {
                        ++attackCounter;
                        if(attackCounter <= 3) {
                            attackBuff(attackCounter);
                        }
                        else {
                            std::cout << "full charge! " << std::endl; // больше нельзя бафаться
                        }
                        std::cout << "attack counter: " << defenceCounter << std::endl;
                    }
                    break;
                case 2: getDamage(enemy->damage()); // damage without buff
                        std::cout << "SUCCESS" << std::endl;
                        break;

                case 3: std::cin >> commandNumber;
                    switch (commandNumber) {
                        case 1: std::cout << "top attack blocked" << std::endl; break;
                        case 2: std::cout << "middle attack blocked" << std::endl; break;
                        case 3: std::cout << "low attack blocked" << std::endl; break;
                        default: getDamage(enemy->damage()); break;
                    }
                    break;
                default: std::cout << "something goes wrong!" << std::endl;
            }
        }
        else {
            std::cout << "attack throw: " << attackThrowValue
                      << " armor class: " << armorClassValue << std::endl;
            std::cout << "missing!" << std::endl;
        }
    }

    void run(int distance) {
        int characterSpeed = m_speed;
        if (m_speed >= distance) {
            m_speed -= distance;
            std::cout << "running to " << distance << "ft, " << "\n"
                      << "also you have " << m_speed << "ft" << std::endl;
        } else {
            std::cout << "you can't run" << std::endl;
        }
    };

private:
    std::string m_name;
    int m_hp, m_armorClass, m_speed;
    int m_damageModificator = 1;
    std::vector<std::vector<int>> m_defenceBuffValue = {{1, 1},
                                                        {2, 2},
                                                        {3, 3}};
    std::vector<std::vector<int>> m_attackBuffValue = {{1, 2},
                                                       {2, 3},
                                                       {3, 4}};

private:
    int damage() const {
        int damage = 0;
        damage = d8{}.Roll();
        std:: cout << "damage: " << damage << std::endl;
        return damage;

    }

    void armorBuff(int counterNumber) {
        for(int i = 0; i < m_defenceBuffValue.size(); ++i) {
            for(int j = 0; j < m_defenceBuffValue.size(); ++j) {
                if(i == counterNumber) {
                    m_armorClass += j;
                }
            }
        }
    }

    int attackBuff(int counterNumber) {
        int damage = 0;
        for (int i = 0; i < m_attackBuffValue.size(); ++i)
            for (int j = 0; j < m_attackBuffValue.size(); ++j)
                if(i == counterNumber) {
                    m_damageModificator = j;
                }
        return damage * m_damageModificator;
    }
};
    //дописать "если бросок инициативы первого больше второго, 1ый выбирает атаку и бьет второго,
    //затем 2ой выбирает и бьет 1го" и так до победы кого то одного

void PlayersQueue (Character* firstPlayer, Character* secondPlayer) {
    int firstPlayerInitiativeThrowValue = firstPlayer->initiativeThrow();
    int secondPlayerInitiativeThrowValue = secondPlayer->initiativeThrow();
    std::cout << firstPlayer->getName() << " throw: " << firstPlayerInitiativeThrowValue << ","
              << secondPlayer->getName() << " throw: " << secondPlayerInitiativeThrowValue << std::endl;
    if(firstPlayerInitiativeThrowValue > secondPlayerInitiativeThrowValue) {
        std::cout << firstPlayer->getName() << " is ATTACKER!" << std::endl;

        while(!(firstPlayer->getHPInfo() <= 0 && secondPlayer->getHPInfo() <= 0)) {
            firstPlayer->attack(secondPlayer);
            std::cout << secondPlayer->getName() << " HP: " << secondPlayer->getHPInfo() << std::endl;

            secondPlayer->attack(firstPlayer);
            std::cout << firstPlayer->getName() << " HP: " << secondPlayer->getHPInfo() << std::endl;
        }
    }

    else {
        std::cout << secondPlayer->getName() << " is ATTACKER!" << std::endl;

        while(!(firstPlayer->getHPInfo() <= 0 && secondPlayer->getHPInfo() <= 0)) {

            secondPlayer->attack(firstPlayer);
            std::cout << firstPlayer->getName() << " HP: " << secondPlayer->getHPInfo() << std::endl;

            firstPlayer->attack(secondPlayer);
            std::cout << secondPlayer->getName() << " HP: " << secondPlayer->getHPInfo() << std::endl;

        }
    }
}

int main() {
    Character ranger { "x_Ubiwator123_x", 52, 14, 35};
    Character moroz {"TheDeathMorozzz", 46, 15, 30};
    PlayersQueue(&ranger, &moroz);          //&ranger - взятие адреса




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
