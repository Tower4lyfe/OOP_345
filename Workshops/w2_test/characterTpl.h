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
        : Character(name), m_healthMax(healthMax)
    {
        // Initialize health based on the type of T
        m_health = healthMax;  // This will use operator= if T supports it
    }

    int getHealth() const override
    {
        return static_cast<int>(m_health);  // Use conversion operator to get health value as int
    }

    void setHealth(int health) override
    {
        // Assign health using operator= if T allows it
        m_health = std::max(0, std::min(health, m_healthMax));
    }

    int getHealthMax() const override { return m_healthMax; }

    void setHealthMax(int health) override
    {
        m_healthMax = health;
        m_health = health;  // Update current health to match new max, if applicable
    }

    void takeDamage(int dmg) override
    {
 

        // Apply damage using operator-= if T supports it
        m_health -= dmg;

        if(m_health <= 0) 
        {
            m_health = 0;
            std::cout << this->getName() << " has been defeated!\n";
        }else
        std::cout << this->getName() << " took "<< dmg << " damage, " << getHealth() << " health remaining.\n";
    }
};
}

#endif
