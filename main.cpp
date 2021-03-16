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

/*!
 * ДОДЕЛАТЬ
 * атаку после удачного блока
 * после бафа не бросать бросок атаки, тк это баф, а не атака
 *
 *
 * */