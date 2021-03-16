#include "../Inc/Controller.hpp"


std::shared_ptr<Character> Controller::pickCharacter(int variant) {

    if(variant == 1)
        return std::make_shared<Character>("x_Ubiwator123_x", 52, 14);
    if(variant == 2)
        return std::make_shared<Character>("TheDeathMorozzz", 46, 15);
}

void Controller::characterFabric() {
    int characterChoise = 0;
    std::cout << "Hello! \n"
                 "Pleace, pick the character and write the number: "
                 "1 - Ranger (x_Ubiwator123_x) , 2 - Moroz (TheDeathMorozzz) " << std::endl;
    std::cout << "who is first? pick you character" << std::endl;
    std::cin >> characterChoise;
    m_attacker = pickCharacter(characterChoise);

    std::cout << "who is second? pick you character" << std::endl;
    std::cin >> characterChoise;
    m_defender = pickCharacter(characterChoise);

}

void Controller::playersQueue() {
    int attackerInitiative, defenderInitiative;
    do {
        std::cout << "Roll" << std::endl;

        attackerInitiative = m_attacker->initiativeAndAttackD20Throw();
        defenderInitiative = m_defender->initiativeAndAttackD20Throw();
    } while (attackerInitiative == defenderInitiative);

    std::cout << m_attacker->getName() << " throw: " << attackerInitiative << " ,"
              << m_defender->getName() << " throw: " << defenderInitiative << std::endl;

    if (attackerInitiative < defenderInitiative) {
        std::swap(m_attacker, m_defender);
    }
    std::cout << m_attacker->getName() << " is ATTACKER!" << std::endl;
}

void Controller::fight() {
    while (m_attacker->getHPInfo() > 0 && m_defender->getHPInfo() > 0) {
        std::cout << m_attacker->getName() << " taking damage to " << m_defender->getName() << std::endl;
        int attackerAttackNumber = 0;
        int attackerBlockNumber = 0;
        int defenderAttackNumber = 0;
        int defenderBlockNumber = 0;
        m_attacker->infoPrinter();

        std::cout << "Attacker, please write number of attack "
                     "and which attack you want to block" << std::endl;

        std::cin >> attackerAttackNumber >> attackerBlockNumber;
        m_attacker->setAttackerAttackType(attackerAttackNumber);
        m_attacker->setAttackerBlockType(attackerBlockNumber);

        std::cout << "Defender, please write number of attack "
                    "and which attack you want to block" << std::endl;
        std::cin >> defenderAttackNumber >> defenderBlockNumber;
        m_defender->setDefenderAttackType(defenderAttackNumber);
        m_defender->setDefenderBlockType(defenderBlockNumber);


        if (m_attacker->getAttackerAttackType() == m_defender->getDefenderBlockType()) {
            std::cout << m_attacker->getName() << ", you attack blocked" << std::endl;
        }
        else {
            m_attacker->attack(m_defender, m_attacker->getAttackerAttackType());
            /*! via operator new - attack(Character*)   */
        }

        std::cout << m_attacker->getName() << " HP: " << m_attacker->getHPInfo() << std::endl;
        std::cout << m_defender->getName() << " HP: " << m_defender->getHPInfo() << std::endl;
        std::cout << "\n";

        std::swap(m_attacker, m_defender);
    }

    if (m_attacker->getHPInfo() > m_defender->getHPInfo()) {
        std::cout << m_attacker->getName() << " - WIN !11!" << std::endl;
    }
    else {
        std::cout << m_defender->getName() << " - WIN !11!" << std::endl;
    }
}

/*while (m_firstPlayer->getHPInfo() > 0 && m_secondPlayer->getHPInfo() > 0) {
    /*if (firstAttacker) {
        std::cout << m_firstPlayer->getName() << " taking damage to " << m_secondPlayer->getName() << std::endl;
        if (m_firstPlayer->getAttackType() == m_secondPlayer->getBlockType()) {
            std::cout << "you attack blocked" << std::endl;
        }
        else {
            m_firstPlayer->attack(m_secondPlayer);
            *//*! via operator new - attack(Character*)   *//*
            }

            std::cout << m_secondPlayer->getName() << " HP: " << m_secondPlayer->getHPInfo() << std::endl;
            std::cout << "\n";
            std::swap(m_firstPlayer, m_secondPlayer);
        }
        else {
            std::cout << m_secondPlayer->getName() << " taking damage to " << m_firstPlayer->getName() << std::endl;
            m_secondPlayer->attack(m_firstPlayer);
            *//*! via operator new - attack(Character*)   *//*

            std::cout << m_firstPlayer->getName() << " HP: " << m_firstPlayer->getHPInfo() << std::endl;
            std::cout << "\n";
            std::swap(m_firstPlayer, m_secondPlayer);
        }*/
