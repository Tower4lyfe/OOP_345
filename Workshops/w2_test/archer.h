//archer.h
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

        int getAttackAmnt() const override
        {
            return static_cast<int>(1.3 * m_baseAttack);
        }

        int getDefenseAmnt() const override
        {
            return static_cast<int>(1.2 * m_baseDefense);
        }

        Character* clone() const override
        {
            return new Archer<Weapon_t>(*this);
        }

        void attack(Character* enemy) override
        {
            std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
            int total_attack = getAttackAmnt(); // Weapon is ignored in attack calculation as per instructions
            std::cout << "Archer deals " << total_attack << " ranged damage!\n";
            enemy->takeDamage(total_attack);
        }

        void takeDamage(int dmg) override
        {
            std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
            std::cout << "Archer has a defense of " << getDefenseAmnt() << ". Reducing damage received.\n";

            int reduced_dmg = dmg - getDefenseAmnt();
            reduced_dmg = std::max(0, reduced_dmg); // Damage cannot be less than 0

            CharacterTpl<seneca::SuperHealth>::takeDamage(reduced_dmg);
        }
    };
}

#endif