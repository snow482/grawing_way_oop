#include <iostream>
#include <vector>
#include "Character.hpp"
#include <iomanip>
#include <algorithm>

/*!
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
 void Rol (){
    rand() % 20;
}

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

    int initiativeThrow() {
        return d20{}.Roll();
    }

    int attackThrow() {
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

    int getAttackType(int commandNumber) {
        commandNumber = m_commandNumber;
        return commandNumber;
    }

    void getDamage(int damage) {
        m_hp -= damage;
    };

    void attack(Character* enemy) {
        int attackThrowValue = attackThrow();
        int armorClassValue = enemy->getArmorClass();

        if (attackThrowValue >= armorClassValue) {
            std::cout << "attack throw: " << attackThrowValue
                      << " armor class: " << armorClassValue << std::endl;

            std::cout << "Please, enter the number of action" << "\n"
                      << "1 - Buff, 2- Top attack, 3- Damage block "
                         "(if success, you can take extra damage to enemy by the legendary attack)" << std::endl;
            int commandNumber = 0;
            int commandBlock = 0;
            int attackCommandNumber = 0;
            int buffNumber = 0;
            std::cin >> commandNumber;

            switch (commandNumber) {
                case 1:
                    std::cin >> buffNumber;

                    // написать тут либо цикл либо что, чтобы верный номер вводить, а не 3 (к примеру)
                    // добавить присвоение для m_commandNumber, чтобы запоминать предыдущее значение команды атакующего
                    switch (buffNumber) {
                        case 1:
                            ++m_defenceCounter;
                            if(m_defenceCounter <= 3) {
                                armorBuff(m_defenceCounter);
                            }
                            else {
                                std::cout << "full charge! " << std::endl; //! больше нельзя бафаться
                            }
                            std::cout << "defence counter: " << m_defenceCounter << std::endl;
                            break;
                        case 2:
                            ++m_attackCounter;
                            if(m_attackCounter <= 3) {
                                attackBuff(m_attackCounter);
                                std::cout << "attack counter: " << m_attackCounter << std::endl;
                            }
                            else {
                                std::cout << "full charge! " << std::endl; //! больше нельзя бафаться
                            }
                            break;
                        default: std::cout << "something goes wrong!" << std::endl;
                            break;
                    }
                    break;
                case 2: std::cin >> attackCommandNumber;
                    std::cout << "Please, enter the number of attack which you want to block: \n"
                             "1 - top attack block, 2 - middle attack block, 3 - low attack block" << std::endl;
                    switch (attackCommandNumber) {
                        case 1: enemy->getDamage(damageTop()); break;
                        case 2: enemy->getDamage(damageMiddle()); break;
                        case 3: enemy->getDamage(damageLow()); break;
                        default: std::cout << "please, chose the attack number" << std::endl; break;
                    }
                    break;
                case 3: std::cin >> commandBlock;
                    switch (commandBlock) {
                        case 1:
                            if(commandBlock == enemy->getAttackType(attackCommandNumber)) {
                                std::cout << "top attack blocked" << std::endl;
                            }
                            else {
                                std::cout << "you block - missed" << std::endl;
                            }
                            break;
                        case 2:
                            if(commandBlock == enemy->getAttackType(attackCommandNumber)) {
                                std::cout << "middle attack blocked" << std::endl;
                            }
                            else {
                                std::cout << "you block - missed" << std::endl;
                            }
                            break;
                        case 3:
                            if(commandBlock == enemy->getAttackType(attackCommandNumber)) {
                                std::cout << "low attack blocked"  << std::endl;
                            }
                            else {
                                std::cout << "you block - missed" << std::endl;
                            }
                            break;
                        default: std::cout << "You didn't block any attack" << std::endl;
                            break;
                    }
                    break;
                default: std::cout << "something goes wrong!" << std::endl;
                commandNumber = 0;
                break;
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
    int damageTop() const {
        int damageValue = d10{}.Roll() * m_damageModificator;
        std::cout << "Damage: " << damageValue << std::endl;
        return damageValue;
    }
    int damageMiddle() const {
        int damageValue = d8{}.Roll() * m_damageModificator;
        std::cout << "Damage: " << damageValue << std::endl;
        return damageValue;
    }
    int damageLow() const {
        int damageValue = d4{}.Roll() * m_damageModificator;
        std::cout << "Damage: " << damageValue << std::endl;
        return damageValue;
    }
    int damageLegendary() const {
        int damageValue = d12{}.Roll() * m_damageModificator * 2;
        std::cout << "legendary damage: " << damageValue << std::endl;
        return damageValue;
    }

    void armorBuff(int counterNumber) {
        switch (counterNumber) {
            case 1: m_armorClass += m_defenceBuffValue[0]; break;
            case 2: m_armorClass += m_defenceBuffValue[1]; break;
            case 3: m_armorClass += m_defenceBuffValue[2]; break;
            default: std::cout << "please, enter the number from 1 to 3" << std::endl; break;
        }
    }

    void attackBuff(int counterNumber) {

        switch (counterNumber) {
            case 1: m_damageModificator = m_attackBuffValue[0]; break;
            case 2: m_damageModificator = m_attackBuffValue[1]; break;
            case 3: m_damageModificator = m_attackBuffValue[2]; break;
            default: std::cout << "please, enter the number from 1 to 3" << std::endl; break;
        }
    }

private:
    std::string m_name;
    int m_hp, m_armorClass, m_speed;
    int m_damageModificator = 1;
    std::vector<int> m_defenceBuffValue = {1, 1, 1};
    std::vector<int> m_attackBuffValue = {2, 3, 4};

    int m_commandNumber = 0;

    int m_defenceCounter = 0;
    int m_attackCounter = 0;

};
    //дописать "если бросок инициативы первого больше второго, 1ый выбирает атаку и бьет второго,
    //затем 2ой выбирает и бьет 1го" и так до победы кого то одного

void PlayersQueue (Character* firstPlayer, Character* secondPlayer) {
/*
    int characterChoise = 0;
    auto firstPlayerPtr = nullptr;

    std::cout << "please, chose you character, 1 - Ranger, 2 - Moroz" << std::endl;
    std::cin >> characterChoise;

    if(characterChoise == 1) {
       firstPlayerPtr = firstPlayer;
    }
    if(characterChoise == 2) {
        auto cha
    }*/

    int firstPlayerInitiativeThrowValue = firstPlayer->initiativeThrow();
    int secondPlayerInitiativeThrowValue = secondPlayer->initiativeThrow();
    bool firstAttacker = false;
    bool secondAttacker = false;

    std::cout << firstPlayer->getName() << " throw: " << firstPlayerInitiativeThrowValue << ","
              << secondPlayer->getName() << " throw: " << secondPlayerInitiativeThrowValue << std::endl;

    if(firstPlayerInitiativeThrowValue == secondPlayerInitiativeThrowValue) {
        std::cout << "Re-rolle" << std::endl;

        firstPlayerInitiativeThrowValue = firstPlayer->initiativeThrow();
        secondPlayerInitiativeThrowValue = secondPlayer->initiativeThrow();
    }
    if(firstPlayerInitiativeThrowValue > secondPlayerInitiativeThrowValue) {
        std::cout << firstPlayer->getName() << " is ATTACKER!" << std::endl;
        firstAttacker = true;
    }
    else {
        std::cout << secondPlayer->getName() << " is ATTACKER!" << std::endl;
        secondAttacker = true;
    }

    while(firstPlayer->getHPInfo() > 0 && secondPlayer->getHPInfo() > 0) {
        if(firstAttacker) {
            std::cout << firstPlayer->getName() << " taking damage to " << secondPlayer->getName() << std::endl;
            firstPlayer->attack(secondPlayer);

            std::cout << secondPlayer->getName() << " HP: " << secondPlayer->getHPInfo() << std::endl;
            std::cout << "\n";
            std::swap(firstPlayer, secondPlayer);
        }
        if(secondAttacker) {
            std::cout << secondPlayer->getName() << " taking damage to " << firstPlayer->getName() << std::endl;
            secondPlayer->attack(firstPlayer);

            std::cout << firstPlayer->getName() << " HP: " << firstPlayer->getHPInfo() << std::endl;
            std::cout << "\n";
            std::swap(firstPlayer, secondPlayer);
        }
    }
    if(firstPlayer->getHPInfo() > secondPlayer->getHPInfo()) {
        std::cout << firstPlayer->getName() << " - WIN !11!" << std::endl;
    } else {
        std::cout << secondPlayer->getName() << " - WIN !11!" << std::endl;
    }

    firstAttacker = false;
    secondAttacker = false;
}


int main() {
    srand(time(nullptr));
    Character ranger { "x_Ubiwator123_x", 52, 14, 35};
    Character moroz {"TheDeathMorozzz", 46, 15, 30};


    PlayersQueue(&ranger, &moroz);          //! &ranger - взятие адреса



    return 0;
}


/*
                    if (buffNumber == 1) {
                        ++m_defenceCounter;
                        if(m_defenceCounter <= 3) {
                            armorBuff(m_defenceCounter);
                        }
                        else {
                            std::cout << "full charge! " << std::endl; //! больше нельзя бафаться
                        }
                        std::cout << "defence counter: " << m_defenceCounter << std::endl;
                    }
                    if(buffNumber == 2) {
                        ++m_attackCounter;
                        if(m_attackCounter <= 3) {
                            attackBuff(m_attackCounter);
                        }
                        else {
                            std::cout << "full charge! " << std::endl; //! больше нельзя бафаться
                        }
                        std::cout << "attack counter: " << m_defenceCounter << std::endl;
                    }*/


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
