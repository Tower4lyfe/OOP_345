// characterTpl.h
#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"
#include "health.h"

namespace seneca
{
    template <typename T>
    class CharacterTpl : public Character
    {
    private:
        int m_healthMax;  // Maximum health of the character
        T m_health;       // Current health of the character

    public:
        CharacterTpl(const char* name, int healthMax)
            : Character(name), m_healthMax(healthMax), m_health(healthMax) {} 

        int getHealth() const override { return m_health.getHealth(); }
        void setHealth(int health) override { m_health.setHealth(std::max(0, health)); } // Ensure health doesn't go below 0
        int getHealthMax() const override { return m_healthMax; }
        void setHealthMax(int health) override 
        { 
            m_healthMax = health; 
            m_health.setHealth(health); 
        }

        void takeDamage(int dmg) override
        {
            int reduced_dmg = dmg - getDefenseAmnt();

            // Allow for 0 damage if defenses are high enough
            if (reduced_dmg > 0)
            {
                setHealth(getHealth() - reduced_dmg);
            }
            else
            {
                std::cout << this->getName() << " blocked all incoming damage!\n";
            }
        }
    };
}

#endif