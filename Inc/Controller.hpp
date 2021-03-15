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

    Controller() = default;

    void characterFabric();
    void playersQueue ();
    void fight();

private:
    std::shared_ptr<Character> pickCharacter (int variant);
private:
    int firstPlayerScores = 0;
    int secondPlayerScores = 0;
    std::shared_ptr<Character> m_attacker;
    std::shared_ptr<Character> m_defender;
};