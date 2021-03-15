#include "../Inc/Controller.hpp"


std::shared_ptr<Character> Controller::pickCharacter (int variant)  {

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
    std::cin >> characterChoise;
    m_attacker = pickCharacter(characterChoise);
    std::cin >> characterChoise;
    m_deffender = pickCharacter(characterChoise);
}

void Controller::playersQueue () {
    int attackerInitiative = m_attacker->initiativeAndAttackD20Throw();
    int deffenderInitiative = m_deffender->initiativeAndAttackD20Throw();

    std::cout << m_attacker->getName() << " throw: " << attackerInitiative << ","
              << m_deffender->getName() << " throw: " << deffenderInitiative << std::endl;

    while (attackerInitiative == deffenderInitiative) {
        std::cout << "Re-rolle" << std::endl;

        attackerInitiative = m_attacker->initiativeAndAttackD20Throw();
        deffenderInitiative = m_deffender->initiativeAndAttackD20Throw();
    }
    if (attackerInitiative < deffenderInitiative) {
        std::swap(m_attacker, m_deffender);
    }
    std::cout << m_attacker->getName() << " is ATTACKER!" << std::endl;
}

void Controller::fight() {
    while (m_attacker->getHPInfo() > 0 && m_deffender->getHPInfo() > 0) {
        std::cout << m_attacker->getName() << " taking damage to " << m_deffender->getName() << std::endl;
        if (m_attacker->getAttackType() == m_deffender->getBlockType()) {
            std::cout << "you attack blocked" << std::endl;
        } else {
            m_attacker->attack(m_deffender);
            /*! via operator new - attack(Character*)   */
        }

        std::cout << m_attacker->getName() << " HP: " << m_deffender->getHPInfo() << std::endl;
        std::cout << m_deffender->getName() << " HP: " << m_deffender->getHPInfo() << std::endl;
        std::cout << "\n";

        std::swap(m_attacker, m_deffender);
    }

    if (m_attacker->getHPInfo() > m_deffender->getHPInfo()) {
        std::cout << m_attacker->getName() << " - WIN !11!" << std::endl;
    }
    else {
        std::cout << m_deffender->getName() << " - WIN !11!" << std::endl;
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
