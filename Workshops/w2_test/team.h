#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <vector>
#include "character.h"

namespace seneca
{
    class Team
    {
    private:
        std::string m_name;
        std::vector<Character*> m_members;

    public:
        // Constructor
        Team(const std::string& name) : m_name(name) {}

        // Destructor
        ~Team()
        {
            // Properly deallocate memory for each member owned by the team
            for (auto member : m_members)
            {
                delete member;
            }
            m_members.clear();
        }

        // Copy Constructor
        Team(const Team& other)
            : m_name(other.m_name)
        {
            for (const auto& member : other.m_members)
            {
                m_members.push_back(member->clone());
            }
        }

        // Copy Assignment Operator
        Team& operator=(const Team& other)
        {
            if (this != &other)
            {
                // Delete existing members
                for (auto member : m_members)
                {
                    delete member;
                }
                m_members.clear();

                // Copy from other
                m_name = other.m_name;
                for (const auto& member : other.m_members)
                {
                    m_members.push_back(member->clone());
                }
            }
            return *this;
        }

        // Move Constructor
        Team(Team&& other) noexcept
            : m_name(std::move(other.m_name)), m_members(std::move(other.m_members))
        {
            other.m_members.clear();
        }

        // Move Assignment Operator
        Team& operator=(Team&& other) noexcept
        {
            if (this != &other)
            {
                // Delete existing members
                for (auto member : m_members)
                {
                    delete member;
                }
                m_members.clear();

                // Move from other
                m_name = std::move(other.m_name);
                m_members = std::move(other.m_members);
                other.m_members.clear();
            }
            return *this;
        }

        // Add Member
        void addMember(Character* character)
        {
            for (const auto& member : m_members)
            {
                if (member->getName() == character->getName())
                    return; // Prevent adding duplicate characters by name
            }

            // Clone the character to make a copy owned by the team
            Character* newMember = character->clone();
            m_members.push_back(newMember);
        }

        // Remove Member
        void removeMember(const std::string& name)
        {
            for (auto it = m_members.begin(); it != m_members.end(); ++it)
            {
                if ((*it)->getName() == name)
                {
                    delete *it;  // Properly delete the character
                    m_members.erase(it);
                    break;
                }
            }
        }

        // Access Operator
        Character* operator[](size_t index) const
        {
            if (index < m_members.size())
                return m_members[index];
            return nullptr;
        }

        // Show Members
        void showMembers() const
        {
            std::cout << "[Team] " << m_name << "\n";
            for (const auto& member : m_members)
            {
                std::cout << "    " << member->getName() << "\tHealth: " << member->getHealth() << "\tAttack: " << member->getAttackAmnt() << "\tDefense: " << member->getDefenseAmnt() << "\n";
            }
        }
    };
}

#endif
