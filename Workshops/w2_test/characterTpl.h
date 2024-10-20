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
        if constexpr (std::is_constructible_v<T, int>)
        {
            m_health = T(healthMax); // For types that can be constructed with an int
        }
        else
        {
            m_health = T(); // For types that require a default constructor
        }
    }

    int getHealth() const override
    {
        if constexpr (std::is_class_v<T>)
        {
            return m_health.getHealth();
        }
        else
        {
            return m_health;
        }
    }

    void setHealth(int health) override
    {
        if constexpr (std::is_class_v<T>)
        {
            m_health.setHealth(std::max(0, health));
        }
        else
        {
            m_health = std::max(0, health);
        }
    }

    int getHealthMax() const override { return m_healthMax; }

    void setHealthMax(int health) override
    {
        m_healthMax = health;
        if constexpr (std::is_class_v<T>)
        {
            m_health.setHealth(health);
        }
        else
        {
            m_health = health;
        }
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