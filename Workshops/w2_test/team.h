#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <string>
#include "character.h"

namespace seneca
{
    class Team
    {
    private:
        std::string m_name;
        Character** m_members;
        size_t m_size;
        size_t m_capacity;

        void resize(size_t newCapacity)
        {
            Character** newMembers = new Character*[newCapacity];
            for (size_t i = 0; i < m_size; ++i)
            {
                newMembers[i] = m_members[i];
            }
            delete[] m_members;
            m_members = newMembers;
            m_capacity = newCapacity;
        }

    public:
        // Constructor
        Team(const std::string& name) : m_name(name), m_members(nullptr), m_size(0), m_capacity(0) {}

        // Destructor
        ~Team()
        {
            for (size_t i = 0; i < m_size; ++i)
            {
                delete m_members[i];
            }
            delete[] m_members;
        }

        // Copy Constructor
        Team(const Team& other) : m_name(other.m_name), m_size(other.m_size), m_capacity(other.m_capacity)
        {
            m_members = new Character*[m_capacity];
            for (size_t i = 0; i < m_size; ++i)
            {
                m_members[i] = other.m_members[i]->clone();
            }
        }

        // Copy Assignment Operator
        Team& operator=(const Team& other)
        {
            if (this != &other)
            {
                // Delete existing members
                for (size_t i = 0; i < m_size; ++i)
                {
                    delete m_members[i];
                }
                delete[] m_members;

                // Copy from other
                m_name = other.m_name;
                m_size = other.m_size;
                m_capacity = other.m_capacity;

                m_members = new Character*[m_capacity];
                for (size_t i = 0; i < m_size; ++i)
                {
                    m_members[i] = other.m_members[i]->clone();
                }
            }
            return *this;
        }

        // Move Constructor
        Team(Team&& other) noexcept
            : m_name(std::move(other.m_name)), m_members(other.m_members), m_size(other.m_size), m_capacity(other.m_capacity)
        {
            other.m_members = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }

        // Move Assignment Operator
        Team& operator=(Team&& other) noexcept
        {
            if (this != &other)
            {
                // Delete existing members
                for (size_t i = 0; i < m_size; ++i)
                {
                    delete m_members[i];
                }
                delete[] m_members;

                // Move from other
                m_name = std::move(other.m_name);
                m_members = other.m_members;
                m_size = other.m_size;
                m_capacity = other.m_capacity;

                other.m_members = nullptr;
                other.m_size = 0;
                other.m_capacity = 0;
            }
            return *this;
        }

        // Add Member
        void addMember(Character* character)
        {
            for (size_t i = 0; i < m_size; ++i)
            {
                if (m_members[i]->getName() == character->getName())
                    return; // Prevent adding duplicate characters by name
            }

            if (m_size == m_capacity)
            {
                size_t newCapacity = (m_capacity == 0) ? 2 : m_capacity * 2;
                resize(newCapacity);
            }

            m_members[m_size++] = character->clone();
        }

        // Remove Member
        void removeMember(const std::string& name)
        {
            for (size_t i = 0; i < m_size; ++i)
            {
                if (m_members[i]->getName() == name)
                {
                    delete m_members[i];
                    for (size_t j = i; j < m_size - 1; ++j)
                    {
                        m_members[j] = m_members[j + 1];
                    }
                    --m_size;
                    break;
                }
            }
        }

        // Access Operator
        Character* operator[](size_t index) const
        {
            if (index < m_size)
                return m_members[index];
            return nullptr;
        }

        // Show Members
        void showMembers() const
        {
            std::cout << "[Team] " << m_name << "\n";
            for (size_t i = 0; i < m_size; ++i)
            {
                std::cout << "    " << m_members[i]->getName() << "\tHealth: " << m_members[i]->getHealth() << "\tAttack: " << m_members[i]->getAttackAmnt() << "\tDefense: " << m_members[i]->getDefenseAmnt() << "\n";
            }
        }
    };
}

#endif
