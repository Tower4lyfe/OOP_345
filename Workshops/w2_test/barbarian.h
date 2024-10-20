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
        Weapon_t m_weapon1;
        Weapon_t m_weapon2;
        int m_baseAttack;
        int m_baseDefense;
    public:
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpl<T>(name, healthMax), m_weapon1(primaryWeapon), m_weapon2(secondaryWeapon), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {}

        int getAttackAmnt() const override { return m_baseAttack; }
        int getDefenseAmnt() const override { return m_baseDefense; }

        Character* clone() const override { return new Barbarian<T, Ability_t, Weapon_t>(*this); }
    

        void attack(Character* enemy) override
        {
            int total_attack = this->getAttackAmnt() + static_cast<int>(m_weapon1) + static_cast<int>(m_weapon2);
            m_ability.transformDamageDealt(total_attack);
            std::cout << this->getName() << " attacks " << enemy->getName() << " with both weapons for " << total_attack << " damage!\n";
            enemy->takeDamage(total_attack);
        }

        void takeDamage(int dmg) override
        {
            m_ability.transformDamageReceived(dmg);
            CharacterTpl<T>::takeDamage(dmg);
        }
    };
}

#endif