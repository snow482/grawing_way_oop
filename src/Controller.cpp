#include "../Inc/Controller.hpp"

Controller::Controller (std::shared_ptr<Character> firstPlayer, std::shared_ptr<Character> secondPlayer)
    : m_firstPlayer(firstPlayer), m_secondPlayer(secondPlayer)
{};
/*! Character* firstPlayer, Character* secondPlayer */

void Controller::attackTry () {

}

std::shared_ptr<Character> Controller::pickCharacter (int variant) {

    if(variant == 1)
        return std::make_shared<Character>("x_Ubiwator123_x", 52, 14);
    if(variant == 2)
        return std::make_shared<Character>("TheDeathMorozzz", 46, 15);
}

void Controller::PlayersQueue () {
    int characterChoise = 0;
    std::cout << "Hello! \n"
                 "Pleace, pick the character and write the number: "
                 "1 - Ranger (x_Ubiwator123_x) , 2 - Moroz (TheDeathMorozzz) " << std::endl;
    std::cin >> characterChoise;
    m_firstPlayer = pickCharacter(characterChoise);
    m_secondPlayer = pickCharacter(characterChoise);

    int firstPlayerInitiativeThrowValue = m_firstPlayer->initiativeAndAttackD20Throw();
    int secondPlayerInitiativeThrowValue = m_secondPlayer->initiativeAndAttackD20Throw();
    bool firstAttacker = false;
    bool secondAttacker = false;

    std::cout << m_firstPlayer->getName() << " throw: " << firstPlayerInitiativeThrowValue << ","
              << m_secondPlayer->getName() << " throw: " << secondPlayerInitiativeThrowValue << std::endl;

    if (firstPlayerInitiativeThrowValue == secondPlayerInitiativeThrowValue) {
        std::cout << "Re-rolle" << std::endl;

        firstPlayerInitiativeThrowValue = m_firstPlayer->initiativeAndAttackD20Throw();
        secondPlayerInitiativeThrowValue = m_secondPlayer->initiativeAndAttackD20Throw();
    }
    if (firstPlayerInitiativeThrowValue > secondPlayerInitiativeThrowValue) {
        std::cout << m_firstPlayer->getName() << " is ATTACKER!" << std::endl;
        firstAttacker = true;
    } else {
        std::cout << m_secondPlayer->getName() << " is ATTACKER!" << std::endl;
        secondAttacker = true;
    }

    while (m_firstPlayer->getHPInfo() > 0 && m_secondPlayer->getHPInfo() > 0) {
        if (firstAttacker) {
            std::cout << m_firstPlayer->getName() << " taking damage to " << m_secondPlayer->getName() << std::endl;
            m_firstPlayer->attack(m_secondPlayer);
            /*! via operator new - attack(Character*)   */

            std::cout << m_secondPlayer->getName() << " HP: " << m_secondPlayer->getHPInfo() << std::endl;
            std::cout << "\n";
            std::swap(m_firstPlayer, m_secondPlayer);
        }
        if (secondAttacker) {
            std::cout << m_secondPlayer->getName() << " taking damage to " << m_firstPlayer->getName() << std::endl;
            m_secondPlayer->attack(m_firstPlayer);
            /*! via operator new - attack(Character*)   */

            std::cout << m_firstPlayer->getName() << " HP: " << m_firstPlayer->getHPInfo() << std::endl;
            std::cout << "\n";
            std::swap(m_firstPlayer, m_secondPlayer);
        }
    }
    if (m_firstPlayer->getHPInfo() > m_secondPlayer->getHPInfo()) {
        std::cout << m_firstPlayer->getName() << " - WIN !11!" << std::endl;
    } else {
        std::cout << m_secondPlayer->getName() << " - WIN !11!" << std::endl;
    }

    firstAttacker = false;
    secondAttacker = false;


}


