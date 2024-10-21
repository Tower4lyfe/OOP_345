#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H
#include "character.h"
#include "characterTpl.h"

namespace seneca 
{
    template<typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T>
    {
        int m_baseAttack;
        int m_baseDefense;    
        Ability_t m_ability;
        Weapon_t m_weapon[2];

        public:
        //constructor
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon):
        CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense),m_weapon{primaryWeapon, secondaryWeapon}{};

        int getAttackAmnt()const
        {
            return m_baseAttack + static_cast<double>(m_weapon[0])/2 + static_cast<double>(m_weapon[1])/2;
        }

        int getDefenseAmnt() const{return m_baseDefense;}

        //returning a new object base on this object
        Character* clone() const
        {
            return new Barbarian<T, Ability_t, Weapon_t>(*this);
        }
        
        //ATTTAAAAACK!!
        void attack(Character* enemy)
        {
            std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
            //ACTIVATING ME SUPA POWER
            m_ability.useAbility(this);

            int atk_dmg = getAttackAmnt();
            m_ability.transformDamageDealt(atk_dmg);

            std::cout << "    Barbarian deals " << atk_dmg << " melee damage!\n";
            enemy->takeDamage(atk_dmg);
        }

        //OHNO, I'VE BEEN HIT 
        void takeDamage(int dmg) 
        {
            std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
            std::cout << "    Barbarian has a defense of " << m_baseDefense << ". Reducing damage received.\n";

            //Cooler If statement
            int reduced_dmg{};
            dmg - m_baseAttack < 0? reduced_dmg = 0: reduced_dmg = dmg -m_baseDefense;
            //almost forgot
            m_ability.transformDamageReceived(reduced_dmg);

            //need to specify
            CharacterTpl<T>::takeDamage(reduced_dmg);

        }

    };

}


#endif
