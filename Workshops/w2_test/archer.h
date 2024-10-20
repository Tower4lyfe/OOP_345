#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "weapons.h"

namespace seneca
{
    template <typename Weapon_t>
    class Archer : public CharacterTpl<seneca::SuperHealth>
    {
    private:
        Weapon_t m_weapon;
        int m_baseAttack;
        int m_baseDefense;
    public:
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<seneca::SuperHealth>(name, healthMax), m_weapon(weapon), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {}

        int getAttackAmnt() const override { return m_baseAttack; }
        int getDefenseAmnt() const override { return m_baseDefense; }

        Character* clone() const override { return new Archer<Weapon_t>(*this); }
    

        void attack(Character* enemy) override
        {
            int total_attack = this->getAttackAmnt() + static_cast<int>(m_weapon);
            std::cout << this->getName() << " shoots an arrow at " << enemy->getName() << " for " << total_attack << " damage!\n";
            enemy->takeDamage(total_attack);
        }

        void takeDamage(int dmg) override
        {
            CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
        }
    };
}

#endif