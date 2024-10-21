// guild.cpp
#include "guild.h"
#include <iostream>

namespace seneca
{
//The BIG FIVE:

//Change  team to Guild and you got yourself some RULE OF FIVE
    Guild::~Guild()
    {
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            delete m_members[i];
        }
        delete[] m_members;
        m_capacity = 0;
        m_memberCount = 0;
    }

    Guild::Guild(const Guild& other) : m_name(other.m_name), m_memberCount(other.m_memberCount), m_capacity(other.m_capacity)
    {
        m_members = new Character*[m_memberCount];
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            m_members[i] = other.m_members[i]->clone();
        }
    }

    Guild& Guild::operator=(const Guild& other)
    {
        if (this != &other)
            {
                // Delete existing members
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    delete m_members[i];
                }
                delete[] m_members;

                // Copy from other
                m_name = other.m_name;
                m_memberCount = other.m_memberCount;
                m_capacity = other.m_capacity;

                m_members = new Character*[m_capacity];
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    m_members[i] = other.m_members[i]->clone();
                }
            }
            return *this;
    }

    Guild::Guild(Guild&& other) noexcept : m_name(std::move(other.m_name)), m_members(other.m_members), m_memberCount(other.m_memberCount), m_capacity(other.m_capacity)
    {
        other.m_members = nullptr;
        other.m_memberCount = 0;
        other.m_capacity = 0;
    }

    Guild& Guild::operator=(Guild&& other) noexcept
    {
        if (this != &other)
            {
                // Delete existing members
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    delete m_members[i];
                }
                delete[] m_members;

                // Move from other
                m_name = std::move(other.m_name);
                m_members = other.m_members;
                m_memberCount = other.m_memberCount;
                m_capacity = other.m_capacity;

                other.m_members = nullptr;
                other.m_memberCount = 0;
                other.m_capacity = 0;
            }
            return *this;
    }

    //NOT THE BIG FIVE:
    //This one is actually different
    void Guild::addMember(Character* c)
    {
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            if (m_members[i]->getName() == c->getName())
                return;
        }
        
        if (m_memberCount == m_capacity)
        {
            size_t newCapacity = (m_capacity == 0) ? 2 : m_capacity * 2;
            resize(newCapacity);
        }

        //set the max health before cloning 
        int newHealthMax = c->getHealthMax() + 300;
        c->setHealthMax(newHealthMax);

        m_members[m_memberCount++] = c->clone();
    }


// same thing as team module, very tedious, probably better to use two variables for the array current size and optimal
    void Guild::removeMember(const std::string& c)
    {
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            if (m_members[i]->getName() == c)
            {
                delete m_members[i];

                for (size_t j = i; j < m_memberCount - 1; ++j)
                {
                    m_members[j] = m_members[j + 1];
                }
                --m_memberCount;

                if (m_memberCount > 0)
                {
                    Character** newMembers = new Character*[m_memberCount];
                    for (size_t k = 0; k < m_memberCount; ++k)
                    {
                        newMembers[k] = m_members[k];
                    }
                    delete[] m_members;
                    m_members = newMembers;
                }
                else
                {
                    delete[] m_members;
                    m_members = nullptr;
                }

                break;
            }
        }
    }


    Character* Guild::operator[](size_t index) const
    {
        if (index < m_memberCount)
            return m_members[index];
        return nullptr;
    }

    void Guild::showMembers() const
    {
        if (m_memberCount == 0)
            std::cout << "No Guild.\n";
        else
        {
            std::cout << "[Guild] " << m_name << "\n";
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                std::cout << *m_members[i] << std::endl; //Yah, it works..
            }
        }
    }
}
