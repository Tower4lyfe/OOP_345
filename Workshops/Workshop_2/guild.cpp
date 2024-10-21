#include "guild.h"
#include <iostream>

namespace seneca
{

    Guild::Guild(const std::string& name) : m_name(name), m_memberCount(0)
    {
        m_members = new Character*[1]; 
    }


    Guild::~Guild()
    {
        delete[] m_members;
        m_memberCount = 0;
    }


    Guild::Guild(const Guild& other) : m_name(other.m_name), m_memberCount(other.m_memberCount)
    {
        m_members = new Character*[m_memberCount];
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            m_members[i] = other.m_members[i];
        }
    }


    Guild& Guild::operator=(const Guild& other)
    {
        if (this != &other)
        {
            delete[] m_members;

            m_name = other.m_name;
            m_memberCount = other.m_memberCount;
            m_members = new Character*[m_memberCount];
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                m_members[i] = other.m_members[i];
            }
        }
        return *this;
    }


    Guild::Guild(Guild&& other) noexcept : m_name(std::move(other.m_name)), m_members(other.m_members), m_memberCount(other.m_memberCount)
    {
        other.m_members = nullptr;
        other.m_memberCount = 0;
    }


    Guild& Guild::operator=(Guild&& other) noexcept
    {
        if (this != &other)
        {
            delete[] m_members;

            m_name = std::move(other.m_name);
            m_members = other.m_members;
            m_memberCount = other.m_memberCount;

            other.m_members = nullptr;
            other.m_memberCount = 0;
        }
        return *this;
    }

 
    void Guild::addMember(Character* c)
    {
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            if (m_members[i]->getName() == c->getName())
                return; 
        }


        Character** newMembers = new Character*[m_memberCount + 1];
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            newMembers[i] = m_members[i];
        }
        delete[] m_members;
        m_members = newMembers;


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

                // Resize the array
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
                std::cout <<"\t" << i+1 << ": " << *m_members[i] << std::endl;
            }
        }
    }
}
