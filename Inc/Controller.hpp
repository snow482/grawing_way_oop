#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
#include <memory>
#include "Character.hpp"

class Controller {
public:

    Controller::Controller (std::shared_ptr<Character> firstPlayer,
                            std::shared_ptr<Character> secondPlayer);

    int actionInfo(std::queue<int> actions);
    void attackTry();

    void checkBuff();

    void PlayersQueue ();


private:
    std::shared_ptr<Character> pickCharacter (int variant);
private:
    std::shared_ptr<Character> m_firstPlayer;
    std::shared_ptr<Character> m_secondPlayer;
};