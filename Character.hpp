
class Character {
public:
    Character(std::string& name, int hp, int armorClass, int runRange);

    virtual void run();
    virtual int attackThrow() {
        int throwValue = 0;
        throwValue = d20{}.Roll();
        std::cout << throwValue << std::endl;
        return throwValue;
    };

    void setHP(int attackThrow, int attackNum);


    virtual int firstAttack() = 0;
    virtual int secondAttack() = 0;
    virtual double damageBlock(int skill_Or_Item) {

    };
    virtual int legendaryAttack() = 0;




private:
    std::string m_name;
    int m_hp, m_armorClass,  m_runRange;

private:
    /*
     * как реализовать правильно баф на защиту (ведь у меня нет такого показателя, как атака),
     * мб засунуть значения бафа в параметры - m_buff = 0; если апался, то ++m_buff
     * т.е. надо броски атак - % бафа (который стакается) сделать флаг, сколько раз он юзался, если
     * 1 - (-25% дамага) / (+25% к атаке)
     * 2 - (-50% дамага) / (+50% к атаке)
     * 3 - (-75% дамага) / (+75% к атаке)
     */
    int buff(int defence_or_attack) {
        if(defence_or_attack == 1) {

        }
        if(defence_or_attack == 2) {

        }
    }
};
