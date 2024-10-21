#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include "character.h"

namespace seneca
{
    template<typename T>
    class CharacterTpl : public Character
    {
        int m_healthMax; //max health
        T m_health; //current health

        public:
        //custome constructor
        CharacterTpl(const char* name, int maxHealth):
        Character(name), m_healthMax(maxHealth)
        {
            m_health = maxHealth;//custom assignment operator
        }; 

        //take damage
        void takeDamage(int dmg) override
        {
            m_health-=dmg;

            if(m_health<=0)
            {
                m_health = 0;
                std::cout << "    " << this->getName() << " has been defeated!\n"; 
            }
            else 
            {
                std::cout <<"    "<< this->getName() << " took "
                << dmg << " damage, " << getHealth() << " health remaining.\n";
            }
        }

        //overriding functions (getter and setter)
        int getHealth() const override{return static_cast<int>(m_health);}
        int getHealthMax() const override{return m_healthMax;}
        void setHealth(int health)override{m_health = health;}
        //Basically to revive MERCY LESS
        void setHealthMax(int health) override
        {
            m_healthMax = health;
            m_health = m_healthMax;
        }
    };





}




#endif