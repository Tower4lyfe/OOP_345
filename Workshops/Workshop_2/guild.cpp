// Guild.cpp
#include "Guild.h"
#include <iostream>

namespace seneca
{
    // Constructor
    Guild::Guild(const std::string& name) : m_name(name), m_memberCount(0)
    {
        m_members = new Character*[1];
    }

    // Destructor
    Guild::~Guild()
    {
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            delete m_members[i];
        }
        delete[] m_members;
    }

    // Copy Constructor
    Guild::Guild(const Guild& other) : m_name(other.m_name), m_memberCount(other.m_memberCount)
    {
        m_members = new Character*[m_memberCount];
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            m_members[i] = other.m_members[i]->clone();
        }
    }

    // Copy Assignment Operator
    Guild& Guild::operator=(const Guild& other)
    {
        if (this != &other)
        {
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                delete m_members[i];
            }
            delete[] m_members;

            m_name = other.m_name;
            m_memberCount = other.m_memberCount;
            m_members = new Character*[m_memberCount];
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                m_members[i] = other.m_members[i]->clone();
            }
        }
        return *this;
    }

    // Move Constructor
    Guild::Guild(Guild&& other) noexcept : m_name(std::move(other.m_name)), m_members(other.m_members), m_memberCount(other.m_memberCount)
    {
        other.m_members = nullptr;
        other.m_memberCount = 0;
    }

    // Move Assignment Operator
    Guild& Guild::operator=(Guild&& other) noexcept
    {
        if (this != &other)
        {
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                delete m_members[i];
            }
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
    void Guild::addMember(Character* character)
    {
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            if (m_members[i]->getName() == character->getName())
                return;
        }

        Character** newMembers = new Character*[m_memberCount + 1];
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            newMembers[i] = m_members[i];
        }
        delete[] m_members;
        m_members = newMembers;

        int newHealthMax = character->getHealthMax() + 300;
        character->setHealthMax(newHealthMax);

        m_members[m_memberCount++] = character->clone();
    }

    // Remove Member
    void Guild::removeMember(const std::string& name)
    {
        for (size_t i = 0; i < m_memberCount; ++i)
        {
            if (m_members[i]->getName() == name)
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

    // Access Operator
    Character* Guild::operator[](size_t index) const
    {
        if (index < m_memberCount)
            return m_members[index];
        return nullptr;
    }

    // Show Members
    void Guild::showMembers() const
    {
        if (m_memberCount == 0)
            std::cout << "No Guild.\n";
        else
        {
            std::cout << "[Guild] " << m_name << "\n";
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                std::cout << *m_members[i] << std::endl;
            }
        }
    }
}
