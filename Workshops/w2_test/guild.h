#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <iostream>
#include <iomanip>
#include <string>

namespace seneca
{
    class Guild
    {
    private:
        std::string m_name;
        Character** m_members;  // Dynamically allocated array for storing members
        size_t m_memberCount = 0;  // Keeps track of the number of members

    public:
        // Constructor
        Guild(const std::string& name) : m_name(name), m_memberCount(0)
        {
            m_members = new Character*[1]; // Start with capacity of 1
        }

        // Destructor
        ~Guild()
        {
            delete[] m_members;
            m_memberCount = 0;
        }

        // Copy Constructor
        Guild(const Guild& other) : m_name(other.m_name), m_memberCount(other.m_memberCount)
        {
            m_members = new Character*[m_memberCount];
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                m_members[i] = other.m_members[i];
            }
        }

        // Copy Assignment Operator
        Guild& operator=(const Guild& other)
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

        // Move Constructor
        Guild(Guild&& other) noexcept : m_name(std::move(other.m_name)), m_members(other.m_members), m_memberCount(other.m_memberCount)
        {
            other.m_members = nullptr;
            other.m_memberCount = 0;
        }

        // Move Assignment Operator
        Guild& operator=(Guild&& other) noexcept
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

        // Add Member
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

        // Access Operator
        Character* operator[](size_t index) const
        {
            if (index < m_memberCount)
                return m_members[index];
            return nullptr;
        }

        // Show Members
        void showMembers()const
        {
            if(m_memberCount == 0)
                std::cout << "No Guild.\n";
            else
            {
                std::cout << "[Guild] " << m_name << "\n";
                for(size_t i = 0; i < m_memberCount; ++i)
                {
                    std::cout << *m_members[i] << std::endl;
                }
            }
        }
    };
}

#endif
