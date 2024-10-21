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
    void addMember(Character* character)
        {
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                if (m_members[i]->getName() == character->getName())
                    return; // Prevent adding duplicate characters by name
            }

            // Resize if necessary
            Character** newMembers = new Character*[m_memberCount + 1];
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                newMembers[i] = m_members[i];
            }
            delete[] m_members;
            m_members = newMembers;

            // Increase maximum health by 300
            int newHealthMax = character->getHealthMax() + 300;
            character->setHealthMax(newHealthMax);

            m_members[m_memberCount++] = character;
        }

        // Remove Member
        void removeMember(const std::string& name)
        {
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                if (m_members[i]->getName() == name)
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
                std::cout << *m_members[i] << std::endl; //Yah, it works..
            }
        }
    }
}
