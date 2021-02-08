#pragma once
#include <string>

enum class Skills {
    BuffAttack, BuffDefence, FirstAttack, SecondAttack, DamageBlock, LegendaryAttack
};


class Skill {
public:
    explicit Skill(std::string skillName);
    virtual ~Skill() = default;

    std::string getSkillName() const {
        return m_skillName;
    }



private:
    std::string m_skillName;

};
