#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h"
namespace seneca
{
    template<typename Weapon_t>
    class Archer : public CharacterTpl<seneca::SuperHealth>
    {
        Weapon_t m_weapon;
        int m_baseAttack;
        int m_baseDefense;
        
        
        public:
        //constructor
            Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<seneca::SuperHealth>(name, healthMax), m_weapon(weapon), m_baseAttack(baseAttack), m_baseDefense(baseDefense){};

            int getAttackAmnt() const {return 1.3 * m_baseAttack;}

            int getDefenseAmnt() const {return 1.2 * m_baseDefense;}

            Character* clone() const 
            {
                return new Archer<Weapon_t>(*this);
            }

            void attack(Character* enemy)
            {
                std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
                int atk_dmg = this->getAttackAmnt();
                std::cout << "    Archer deals " << atk_dmg << " ranged damage!\n";
                //take that!
                enemy->takeDamage(atk_dmg);

            }

            //ouch
            void takeDamage(int dmg)
            {
                std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
                std::cout << "    Archer has a defense of " << m_baseDefense << ". Reducing damage received.\n";

                //shamelessly copying from barbarian..
                int reduced_dmg{};
                dmg - m_baseAttack < 0? reduced_dmg = 0: reduced_dmg = dmg -m_baseDefense;
                //well somehow archer is the one with superhealth
                CharacterTpl<seneca::SuperHealth>::takeDamage(reduced_dmg);
            }
    };
}


#endif