#include "Inc/Controller.hpp"
#include <iomanip>
#include <algorithm>


int main() {
    srand(time(nullptr));

    Controller controller;
    controller.characterFabric();
    controller.playersQueue();
    controller.fight();

    return 0;
}

