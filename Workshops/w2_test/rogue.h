#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "weapons.h"
#include "abilities.h"

namespace seneca
{
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T>
    {
    private:
        FirstAbility_t m_ability1;
        SecondAbility_t m_ability2;
        Dagger m_dagger;
        int m_baseAttack;
        int m_baseDefense;
    public:
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {}

        int getAttackAmnt() const override { return m_baseAttack; }
        int getDefenseAmnt() const override { return m_baseDefense; }

        Character* clone() const override { return new Rogue<T, FirstAbility_t, SecondAbility_t>(*this); }
    

        void attack(Character* enemy) override
        {
            int total_attack = this->getAttackAmnt() + static_cast<int>(m_dagger);
            m_ability1.transformDamageDealt(total_attack);
            m_ability2.transformDamageDealt(total_attack);
            std::cout << this->getName() << " attacks " << enemy->getName() << " with dagger for " << total_attack << " damage!\n";
            enemy->takeDamage(total_attack);
        }

        void takeDamage(int dmg) override
        {
            m_ability1.transformDamageReceived(dmg);
            m_ability2.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };
}

#endif