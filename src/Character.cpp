#include "../Inc/Character.hpp"
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

template<int min, int max>
struct Dice {
    int Roll() const {
        return rand() % (max - min) + min;
    }
};
void Roll (){
    rand() % 20;
}

using d20 = Dice<1,20>;
using d4 = Dice<1,4>;
using d6 = Dice<1,6>;
using d8 = Dice<1,8>;
using d10 = Dice<1,10>;
using d12 = Dice<1,12>;

Character::Character (std::string name, int hp, int armorClass)
        : m_name(name), m_hp(hp), m_armorClass(armorClass)
{};

int Character::initiativeAndAttackD20Throw() const {
    return d20{}.Roll();
}

int Character::getArmorClass() const {
    return m_armorClass;
}

int Character::getHPInfo() const {
    return m_hp;
}

std::string Character::getName() const {
    return m_name;
}
//-----------------------------------------------------------------//
int Character::getAttackerAttackType() const {
    return m_attackerAttackCommand;
}
void Character::setAttackerAttackType(int number) {
    m_attackerAttackCommand = number;
}

void Character::setAttackerBlockType(int number) {
    m_attackerBlockCommand = number;
}
//-----------------------------------------------------------------//

void Character::setDefenderAttackType(int number) {
    m_defenderAttackCommand = number;
}

int Character::getDefenderBlockType() const {
    return m_defenderBlockCommand;
}

void Character::setDefenderBlockType(int number) {
    m_defenderBlockCommand = number;
}
//-----------------------------------------------------------------//

void Character::getDamage(int damage) {
    m_hp -= damage;
};

void Character::infoPrinter() {
    std::cout << "\n" << "Please, enter the number of action" << " \n"
              << "1) Attack (1- top, 2- middle, 3- low) \n"
                 "2) Block (1- block top, 2- block middle, 3- block low) \n"
                 "(if success, you can do contr attack the enemy by the legendary attack) \n"
                 "3) Buff (0- no buff, 1- armor class buff, 2- attack buff)" << std::endl;
}

bool Character::attackThrows (int attackThrowValue, int armorClassValue) {

    if (attackThrowValue < armorClassValue) {
        std::cout << "attack throw: " << attackThrowValue
                  << " armor class: " << armorClassValue << std::endl;
        std::cout << "missing!" << std::endl;

        return false;
    }
    else {
        std::cout << "attack throw: " << attackThrowValue
                  << " armor class: " << armorClassValue << std::endl;
        return true;
    }
}

int Character::buffModifier (int commandNumber, int counterType, std::vector<int> buffTypeValue) {
    if (commandNumber <= 3) {
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

void Character::action (int modifier, std::shared_ptr<Character> ptrType) {
    switch (modifier) {
        case 1: ptrType->getDamage(damageTop());
            break;
        case 2: ptrType->getDamage(damageMiddle());
            break;
        case 3: ptrType->getDamage(damageLow());
            break;
        default: std::cout << "please, chose the attack number" << std::endl;

    }
}



void Character::attack(std::shared_ptr<Character> enemy, /*!Character* enemy*/int attackNumber) {

    /*if (attackThrows(initiativeAndAttackD20Throw(), enemy->getArmorClass())) {*/

        /*!
         * 1 атака, 2 бафф, 3 защита
         * персонажу, что ходит первым, дается выбор атаки, бафа,
         * вариант, какую атаку он хотел бы заблокировать
         */
        //TODO реализовать так, чтобы опрашивало обоих игроков, про бафф, если нет бафа то - 0,
        // если есть, то надо передать их в переменные (или контейнер) и записать 
        //! и доделать логику в Character.cpp, чтобы бафф апался, но при этом атаки не было (просто баф и дальше ход)
        if (attackNumber == 1) {
            action(m_attackerAttackCommand, enemy);
        }
        if (attackNumber == 3) {
            std::cout << "Enter the buff type" << std::endl;
            if(enemy)
            std::cin >> m_buffType;

            if (m_buffType == 1) {
                m_armorClass += buffModifier(m_buffType, m_defenceCounter, m_defenceBuffValue);
            }
            if (m_buffType == 2) {
                m_damageModifier = buffModifier(m_buffType, m_attackCounter, m_attackBuffValue);
            }
            std::cout << "buff up" << std:: endl;
        }
        else {

        }
    }
/*}*/



// private methods
    int Character::damageTop() const {
        int damageValue = d10{}.Roll() * m_damageModifier;
        std::cout << "Damage: " << damageValue << std::endl;
        return damageValue;
    }
    int Character::damageMiddle() const {
        int damageValue = d8{}.Roll() * m_damageModifier;
        std::cout << "Damage: " << damageValue << std::endl;
        return damageValue;
    }
    int Character::damageLow() const {
        int damageValue = d4{}.Roll() * m_damageModifier;
        std::cout << "Damage: " << damageValue << std::endl;
        return damageValue;
    }
    int Character::damageLegendary() const {
        int damageValue = d12{}.Roll() * m_damageModifier * 2;
        std::cout << "legendary damage: " << damageValue << std::endl;
        return damageValue;
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

