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
        T m_health;

    public:
        CharacterTpl(const char* name, int healthMax)
            : Character(name), m_health(healthMax, healthMax) {} 

        int getHealth() const override { return m_health.getHealth(); }
        void setHealth(int health) override { m_health.setHealth(health); }
        int getHealthMax() const override { return m_health.getMaxHealth(); }
        void setHealthMax(int health) override { m_health.setHealth(health); }

        void takeDamage(int dmg) override
        {
            int reduced_dmg = dmg - getDefenseAmnt();
            if (reduced_dmg > 0)
                setHealth(getHealth() - reduced_dmg);
        }
    };
}

#endif