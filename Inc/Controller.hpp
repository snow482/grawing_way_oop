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
    void setCharacter(int number);
    void PlayersQueue ();


private:
    std::shared_ptr<Character> pickCharacter (int variant);
private:
    int m_ch1, m_ch2;
    int firstPlayerScores = 0;
    int secondPlayerScores = 0;
    std::shared_ptr<Character> m_firstPlayer;
    std::shared_ptr<Character> m_secondPlayer;
};