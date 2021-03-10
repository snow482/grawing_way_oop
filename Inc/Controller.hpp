#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <memory>
#include "Character.hpp"

class Controller {
public:

    Controller::Controller (std::shared_ptr<Character> firstPlayer,
                            std::shared_ptr<Character> secondPlayer);

    void attackTry(std::shared_ptr<Character> firstPlayer,
                   std::shared_ptr<Character> secondPlayer);

    void PlayersQueue (std::shared_ptr<Character> firstPlayer,
                       std::shared_ptr<Character> secondPlayer);

private:
    std::shared_ptr<Character> pickCharacter (int variant);
private:
    std::shared_ptr<Character> m_firstPlayer;
    std::shared_ptr<Character> m_secondPlayer;
};