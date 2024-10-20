#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "characterTpl.h"
#include "weapons.h"
#include "abilities.h"

namespace seneca
{
    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T>
    {
    private:
        Ability_t m_ability;
        Weapon_t m_weapons[2];
        int m_baseAttack;
        int m_baseDefense;

    public:
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense)
        {
            m_weapons[0] = primaryWeapon;
            m_weapons[1] = secondaryWeapon;
        }

        int getAttackAmnt() const override
        {
            return m_baseAttack + static_cast<int>(m_weapons[0]) / 2 + static_cast<int>(m_weapons[1]) / 2;
        }

        int getDefenseAmnt() const override { return m_baseDefense; }

        Character* clone() const override { return new Barbarian<T, Ability_t, Weapon_t>(*this); }

        void attack(Character* enemy) override
        {
            std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
            m_ability.useAbility(this);  // Use ability to activate beneficial effects

            int total_attack = getAttackAmnt();
            m_ability.transformDamageDealt(total_attack);  // Enhance damage with ability effects

            std::cout << "Barbarian deals " << total_attack << " melee damage!\n";
            enemy->takeDamage(total_attack);
        }

        void takeDamage(int dmg) override
{
    std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
    std::cout << "Barbarian has a defense of " << m_baseDefense << ". Reducing damage received.\n";

    CharacterTpl<T>::takeDamage(dmg);  // The reduction is handled by CharacterTpl
}

    };
}

#endif
