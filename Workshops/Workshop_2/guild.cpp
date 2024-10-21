#include "guild.h"
#include <iostream>

namespace seneca
{

    Guild::Guild(const std::string& name) : m_name(name), m_memberCount(0),m_capacity(1)
    {
        m_members = new Character*[1]; 
    }


    Guild::~Guild()
    {
        //you never really own the objects, so you don't delete them in for loop
        delete[] m_members;
        m_memberCount = 0;
        m_capacity = 0;
    }


    Guild::Guild(const Guild& other) : m_name(other.m_name), m_memberCount(other.m_memberCount), m_capacity(other.m_capacity)
    {
        m_members = new Character*[m_capacity];
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            m_members[i] = other.m_members[i]; // it should be clone
        }
    }


    Guild& Guild::operator=(const Guild& other)
    {
        if (this != &other)
        {
            delete[] m_members;

            //shallow
            m_name = other.m_name;
            m_memberCount = other.m_memberCount;
            m_capacity = other.m_capacity;

            //deep
            m_members = new Character*[m_capacity];         
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                m_members[i] = other.m_members[i];
            }
        }
        return *this;
    }


    Guild::Guild(Guild&& other) noexcept 
    : m_name(std::move(other.m_name)), m_members(other.m_members), m_memberCount(other.m_memberCount), m_capacity(other.m_capacity)
    {
        other.m_members = nullptr;
        other.m_memberCount = 0;
        other.m_capacity = 0;
    }


    Guild& Guild::operator=(Guild&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_members;

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

 
    void Guild::addMember(Character* c)
    {
        //no duplicate
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            if (m_members[i]->getName() == c->getName())
                return; 
        }

        if (m_memberCount == m_capacity)
            resize(m_capacity*2);


        int newHealthMax = c->getHealthMax() + 300;
        c->setHealthMax(newHealthMax);

        m_members[m_memberCount++] = c;
    }

    // I HATE VALGRIND
    void Guild::removeMember(const std::string& c)
    {
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            if (m_members[i]->getName() == c)
            {
                // Decrease maximum health by 300
                int reducedHealthMax = (m_members[i]->getHealthMax() > 300) ? (m_members[i]->getHealthMax() - 300) : 0;
                m_members[i]->setHealthMax(reducedHealthMax);

                // Shift the remaining members to fill the gap
                for (size_t j = i; j < m_memberCount - 1; ++j)
                {
                    m_members[j] = m_members[j + 1];
                }
                
                --m_memberCount;
                m_members[m_memberCount] = nullptr; // no duplicate at the end

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
        if (m_capacity == 0)
            std::cout << "No Guild.\n";
        else
        {
            std::cout << "[Guild] " << m_name << "\n";
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                std::cout <<"    " << i+1 << ": " << *m_members[i] << std::endl;
            }
        }
    }
}
