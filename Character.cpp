#include <iostream>
#include <vector>
#include "Character.hpp"
#include <iomanip>
#include <algorithm>
#include <memory>

/*!
 * 1) выбор персонажа
 * 2) броски инициативы (у кого бросок больше, тот первый)
 * 3) атакующему, выбор вариантов атак, 1- баф (атака/защита), 2- верхняя атака, 3- средняя
 *
 * атаки - 1) баф, выбор на атаку или защиту
 *       - 2) бросок атаки d20, если она >= armorClass'а противника = попадание = вычетание хп
 *       - 3) блок (выбрать какую атаку блокировать) если угадал тип атаки, то урона нет и нанесение удара
 *            легендарным действием в ответ
 *       - 4) легендарное действие у каждого персонажа свое
 */

class Character;
class Controller;

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
    Character(std::string name, int hp, int armorClass)
            : m_name(name), m_hp(hp), m_armorClass(armorClass)
            {};

    int initiativeThrow() const {
        return d20{}.Roll();
    }

    int attackThrow() const {
        return d20{}.Roll();
    }

    int getArmorClass() const {
        return m_armorClass;
    }

    int getHPInfo() const {
        return m_hp;
    }

    std::string getName() const {
        return m_name;
    }

    int getAttackType() const {
        return m_attackCommandNumber;
    }

    void setBlockType(int command, int ) {
        m_blockCommandNumber = command;
    }

    int getBlockType() const {
        return m_blockCommandNumber;
    }

    void getDamage(int damage) {
        m_hp -= damage;
    };

    void throws (int attackThrowValue, int armorClassValue) {

        if (attackThrowValue < armorClassValue) {
            std::cout << "attack throw: " << attackThrowValue
                      << " armor class: " << armorClassValue << std::endl;
            std::cout << "missing!" << std::endl;

            return;
        }
        std::cout << "attack throw: " << attackThrowValue
                  << " armor class: " << armorClassValue << std::endl;
    }

    int buffModifier (int commandNumber, int counterType, std::vector<int> buffTypeValue) {
        if  (commandNumber <= 3) {
            switch (commandNumber) {
                case 1: m_modificator = buffTypeValue[0]; break;
                case 2: m_modificator = buffTypeValue[1]; break;
                case 3: m_modificator = buffTypeValue[2]; break;
                default: std::cout << "please, enter the number from 1 to 3" << std::endl;
            }
            ++counterType;
        }
        else {
            std::cout << "full charge! " << std::endl; //! больше нельзя бафаться
        }
        std::cout << "counter level: " << commandNumber << std::endl;
        return m_modificator;
    }

    void action (int modifier, std::shared_ptr<Character> ptrType) {
        if  (modifier != ptrType->m_blockCommandNumber) {
            switch (modifier) {
                case 1: ptrType->getDamage(damageTop());
                break;
                case 2: ptrType->getDamage(damageMiddle());
                break;
                case 3: ptrType->getDamage(damageLow());
                break;
                default: std::cout << "please, chose the attack number" << std::endl;
            }
            return;
        }

        switch (modifier) {
            case 1: std::cout << "top attack blocked" << std::endl;
                setBlockType(0);
                break;
            case 2: std::cout << "middle attack blocked" << std::endl;
                setBlockType(0);
                break;
            case 3: std::cout << "low attack blocked"  << std::endl;
                setBlockType(0);
                break;
            default: std::cout << "You didn't block any attack" << std::endl;
        }
        //std::cout << "attack is blocked!" << std::endl;
    }
    void gettinActionInfo (int attackCommand, int blockCommand, int buffCommand = 0) {
        if(attackCommand > 0 && attackCommand <= 3) {

        }
    };
    void attack(std::shared_ptr<Character> enemy /*!Character* enemy*/) {
        throws(attackThrow(), enemy->getArmorClass());

        std::cout << "Please, enter the number of action" << " \n"
                  << "1) Attack (1- top, 2- middle, 3- low) \n"
                     "2) Buff (0- no buff, )\n"
                     "3- Block (1- block top, 2- block middle, 3- block low) \n"
                     "(if success, you can take extra damage to enemy by the legendary attack)" << std::endl;
        std::cout << std::endl;
        std::cout << "Please, enter - 0, if you don't want to buff \n"
                  << "1- Attack type, 2- Buff type, 3- Damage block \n"
                     "(if success, you can take extra damage to enemy by the legendary attack)" << std::endl;

        int commandNumber = 0;
        int attackCommand = 0;
        int buffNumber = 0;
        int buffType = 0;
        int blockCommand = 0;

        /*!
         * 1 атака, 2 бафф, 3 защита
         * персонажу, что ходит первым, дается выбор атаки, бафа,
         * вариант, какую атаку он хотел бы заблокировать
         */



        //1ый игрок списывает номер атаки, номер атаки для блока
        //затем 2ой и играется раунд
        std::cin >> commandNumber >> attackCommand >> blockCommand;
        m_attackCommandNumberFirstPlayer = attackCommand;
        m_blockCommandNumberFirstPlayer = blockCommand;
        /*blockCommandSecondPl*/


        /*std::cin >> commandNumber >> enemy->m_attackCommandNumber >> enemy->m_blockCommandNumber;*/

        if (commandNumber == 1) {
            action(m_attackCommandNumberFirstPlayer, enemy);
        }
        if (commandNumber == 2) {
            std::cout << "Please, enter the number of buff which you want to use: \n"
                         "1 - defence buff (adding 1 armor class score per level, max: 3) \n"
                         "2 - attack buff (modify damage modifier level, max: 3)" << std::endl;

            std::cin >> buffType;
            if(buffType == 1) {
                m_armorClass += buffModifier(buffType, m_defenceCounter, m_defenceBuffValue);
            }
            if(buffType == 2) {
                m_damageModifier = buffModifier(buffType, m_attackCounter, m_attackBuffValue);
            }
        }
        if (commandNumber == 3) {
            std::cout << "Please, enter the number of attack which you want to use: \n"
                         "1 - top attack, 2 - middle attack, 3 - low attack" << std::endl;
            action(0, nullptr);
        }

        switch (commandNumber) {
            case 3:
                std::cout << "Please, enter the number of attack which you want to block: \n"
                             "1 - top attack block, 2 - middle attack block, 3 - low attack block" << std::endl;
                std::cin >> blockCommand;
                setBlockType(blockCommand);

                //enemy->setBlockType(blockCommand);
                //enemy->m_blockType = blockCommand

                if(enemy->getBlockType() == getAttackType()) {
                    switch (getBlockType()) {
                        case 1: std::cout << "top attack blocked" << std::endl;
                            setBlockType(0);
                            break;
                        case 2: std::cout << "middle attack blocked" << std::endl;
                            setBlockType(0);
                            break;
                        case 3: std::cout << "low attack blocked"  << std::endl;
                            setBlockType(0);
                            break;
                        default: std::cout << "You didn't block any attack" << std::endl;
                    }
                }
                if(enemy->getBlockType() != getAttackType()) {
                    std::cout << "attacks aren't registered yet" << std::endl;
                }
                break;
            default: std::cout << "something goes wrong!" << std::endl;
        }

    }


private:
    int damageTop() const {
        int damageValue = d10{}.Roll() * m_damageModifier;
        std::cout << "Damage: " << damageValue << std::endl;
        return damageValue;
    }
    int damageMiddle() const {
        int damageValue = d8{}.Roll() * m_damageModifier;
        std::cout << "Damage: " << damageValue << std::endl;
        return damageValue;
    }
    int damageLow() const {
        int damageValue = d4{}.Roll() * m_damageModifier;
        std::cout << "Damage: " << damageValue << std::endl;
        return damageValue;
    }
    int damageLegendary() const {
        int damageValue = d12{}.Roll() * m_damageModifier * 2;
        std::cout << "legendary damage: " << damageValue << std::endl;
        return damageValue;
    }

    void armorBuff(int counterNumber) {
        switch (counterNumber) {
            case 1: m_armorClass += m_defenceBuffValue[0]; break;
            case 2: m_armorClass += m_defenceBuffValue[1]; break;
            case 3: m_armorClass += m_defenceBuffValue[2]; break;
            default: std::cout << "please, enter the number from 1 to 3" << std::endl;
        }
    }

    void attackBuff(int counterNumber) {
        switch (counterNumber) {
            case 1: m_damageModifier = m_attackBuffValue[0]; break;
            case 2: m_damageModifier = m_attackBuffValue[1]; break;
            case 3: m_damageModifier = m_attackBuffValue[2]; break;
            default: std::cout << "please, enter the number from 1 to 3" << std::endl;
        }
    }

private:
    std::string m_name;
    int m_hp, m_armorClass;
    int m_damageModifier = 1;
    int m_modificator = 0;
    std::vector<int> m_defenceBuffValue = {1, 1, 1};
    std::vector<int> m_attackBuffValue = {2, 3, 4};

    int m_attackCommandNumberFirstPlayer = 0;
    int m_attackCommandNumberSecondPlayer = 0;

    int m_blockCommandNumberFirstPlayer = 0;
    int m_blockCommandNumberSecondPlayer = 0;

    int m_defenceCounter = 0;
    int m_attackCounter = 0;
};

class Controller : Character {

};
void PlayersQueue (std::shared_ptr<Character> firstPlayer,
                   std::shared_ptr<Character> secondPlayer
                   /*! Character* firstPlayer, Character* secondPlayer */) {
    int characterChoise = 0;

    std::cout << "Hello! \n"
                 "Pleace, pick the character and write the number: "
                 "1 - Ranger (x_Ubiwator123_x) , 2 - Moroz (TheDeathMorozzz) " << std::endl;
    std::cin >> characterChoise;

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
                /*! via operator new - attack(Character*)   */

            std::cout << secondPlayer->getName() << " HP: " << secondPlayer->getHPInfo() << std::endl;
            std::cout << "\n";
            std::swap(firstPlayer, secondPlayer);
        }
        if(secondAttacker) {
            std::cout << secondPlayer->getName() << " taking damage to " << firstPlayer->getName() << std::endl;
            secondPlayer->attack(firstPlayer);
                /*! via operator new - attack(Character*)   */

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

/*! Character* characterPick (int variant) {
        std::cout << "Hello! Please, pick the character and write the number: "
                     "1 - Ranger (x_Ubiwator123_x) , 2 - Moroz (TheDeathMorozzz) " << std::endl;

        if(variant == 1) {
            return new Character {"x_Ubiwator123_x", 52, 14};
        }
        if(variant == 2) {
            return new Character {"TheDeathMorozzz", 46, 15};
        }
        else {
            std::cout << "please, chose 1 or 2" << std::endl;
        }
    }*/

std::shared_ptr<Character> pickCharacter (int variant) {

    if(variant == 1)
        return std::make_shared<Character>("x_Ubiwator123_x", 52, 14);
    if(variant == 2)
        return std::make_shared<Character>("TheDeathMorozzz", 46, 15);
}




int main() {
    srand(time(nullptr));
    /*! auto ranger = characterPick(1);
        auto moroz = characterPick(2);  */
    auto ranger = pickCharacter(1);
    auto moroz = pickCharacter(2);

    PlayersQueue(ranger, moroz);          //! &ranger - взятие адреса

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
