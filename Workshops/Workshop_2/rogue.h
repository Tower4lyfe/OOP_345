#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H
#include "characterTpl.h"
#include "weapons.h"

namespace seneca
{
    template<typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T>
    {
        int m_baseDefense;
        int m_baseAttack;
        FirstAbility_t m_firstAbility;
        SecondAbility_t m_secondAbility;
        seneca::Dagger m_weapon; 

        public:
        Rogue(const char*name, int healthMax, int baseAttack, int baseDefense):
        CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense){};

        int getAttackAmnt()const {return m_baseAttack + 2 * static_cast<double>(m_weapon);}

        int getDefenseAmnt()const {return m_baseDefense;}

        //COPY PASTING
        Character* clone() const {return new Rogue<T, FirstAbility_t, SecondAbility_t>(*this);}

        //BACKSTABBBB!
        void attack(Character* enemy)
        {
            std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
            //Activating First Skill
            m_firstAbility.useAbility(this);
            m_secondAbility.useAbility(this);
            
            int atk_dmg = this->getAttackAmnt();
            //BIG DMG COMING UP
            m_secondAbility.transformDamageDealt(atk_dmg);

            std::cout << "    Rogue deals " << atk_dmg << " melee damage!\n";
            enemy->takeDamage(atk_dmg);
        }

        void takeDamage(int dmg) 
        {
            //this is a lot of copy pasting 
            std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
            std::cout << "    Rogue has a defense of " << m_baseDefense << ". Reducing damage received.\n";
            int reduced_dmg{};
            dmg - m_baseAttack < 0? reduced_dmg = 0: reduced_dmg = dmg -m_baseDefense;

            //Something that is not copy pasting
            m_firstAbility.transformDamageReceived(reduced_dmg);
            m_secondAbility.transformDamageReceived(reduced_dmg);

            //back to copy pasting
            CharacterTpl<T>::takeDamage(reduced_dmg);
        }

    };

}



#endif
