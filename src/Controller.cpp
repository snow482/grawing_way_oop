#include "../Inc/Controller.hpp"

Controller::Controller (std::shared_ptr<Character> firstPlayer, std::shared_ptr<Character> secondPlayer)
    : m_firstPlayer(firstPlayer), m_secondPlayer(secondPlayer)
{};
/*! Character* firstPlayer, Character* secondPlayer */



void Controller::attackTry (std::shared_ptr<Character> firstPlayer, std::shared_ptr<Character> secondPlayer) {
    firstPlayer;
};

void Controller::PlayersQueue (std::shared_ptr<Character> firstPlayer,
                   std::shared_ptr<Character> secondPlayer) {
    int characterChoise = 0;

    std::cout << "Hello! \n"
                 "Pleace, pick the character and write the number: "
                 "1 - Ranger (x_Ubiwator123_x) , 2 - Moroz (TheDeathMorozzz) " << std::endl;
    std::cin >> characterChoise;

    int firstPlayerInitiativeThrowValue = firstPlayer->initiative();
    int secondPlayerInitiativeThrowValue = secondPlayer->initiative();
    bool firstAttacker = false;
    bool secondAttacker = false;

    std::cout << firstPlayer->getName() << " throw: " << firstPlayerInitiativeThrowValue << ","
              << secondPlayer->getName() << " throw: " << secondPlayerInitiativeThrowValue << std::endl;

    if (firstPlayerInitiativeThrowValue == secondPlayerInitiativeThrowValue) {
        std::cout << "Re-rolle" << std::endl;

        firstPlayerInitiativeThrowValue = firstPlayer->initiative();
        secondPlayerInitiativeThrowValue = secondPlayer->initiative();
    }
    if (firstPlayerInitiativeThrowValue > secondPlayerInitiativeThrowValue) {
        std::cout << firstPlayer->getName() << " is ATTACKER!" << std::endl;
        firstAttacker = true;
    } else {
        std::cout << secondPlayer->getName() << " is ATTACKER!" << std::endl;
        secondAttacker = true;
    }

    while (firstPlayer->getHPInfo() > 0 && secondPlayer->getHPInfo() > 0) {
        if (firstAttacker) {
            std::cout << firstPlayer->getName() << " taking damage to " << secondPlayer->getName() << std::endl;
            firstPlayer->attack(secondPlayer);
            /*! via operator new - attack(Character*)   */

            std::cout << secondPlayer->getName() << " HP: " << secondPlayer->getHPInfo() << std::endl;
            std::cout << "\n";
            std::swap(firstPlayer, secondPlayer);
        }
        if (secondAttacker) {
            std::cout << secondPlayer->getName() << " taking damage to " << firstPlayer->getName() << std::endl;
            secondPlayer->attack(firstPlayer);
            /*! via operator new - attack(Character*)   */

            std::cout << firstPlayer->getName() << " HP: " << firstPlayer->getHPInfo() << std::endl;
            std::cout << "\n";
            std::swap(firstPlayer, secondPlayer);
        }
    }
    if (firstPlayer->getHPInfo() > secondPlayer->getHPInfo()) {
        std::cout << firstPlayer->getName() << " - WIN !11!" << std::endl;
    } else {
        std::cout << secondPlayer->getName() << " - WIN !11!" << std::endl;
    }

    firstAttacker = false;
    secondAttacker = false;


    std::shared_ptr<Character> Controller::pickCharacter (int variant) {

        if(variant == 1)
            return std::make_shared<Character>("x_Ubiwator123_x", 52, 14);
        if(variant == 2)
            return std::make_shared<Character>("TheDeathMorozzz", 46, 15);
        Controller::pickCharacter()
    }
}


