#pragma once

class IAttackThrow {
    int attackThrow() {
        int throwValue = 0;
        throwValue = d20{}.Roll();
        std::cout << throwValue << std::endl;
        return throwValue;
    };
};

