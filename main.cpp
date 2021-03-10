#include <iomanip>
#include <algorithm>


int main() {

    srand(time(nullptr));
    /*! auto ranger = characterPick(1);
        auto moroz = characterPick(2);  */
    auto ranger = pickCharacter(1);
    auto moroz = pickCharacter(2);

    Controller (ranger, moroz);          //! &ranger - взятие адреса



    return 0;
}

