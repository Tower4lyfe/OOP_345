#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <vector>
#include "character.h"

namespace seneca
{
    class Guild
    {
    private:
        std::string m_name;
        std::vector<Character*> m_members;

    public:
        // Constructor
        Guild(const std::string& name) : m_name(name) {}

        // Destructor
        ~Guild()
        {
            m_members.clear(); // No need to delete members as they are shared with the team
        }

        // Copy Constructor
        Guild(const Guild& other)
            : m_name(other.m_name), m_members(other.m_members) {}

        // Copy Assignment Operator
        Guild& operator=(const Guild& other)
        {
            if (this != &other)
            {
                m_name = other.m_name;
                m_members = other.m_members;
            }
            return *this;
        }

        // Move Constructor
        Guild(Guild&& other) noexcept
            : m_name(std::move(other.m_name)), m_members(std::move(other.m_members)) {}

        // Move Assignment Operator
        Guild& operator=(Guild&& other) noexcept
        {
            if (this != &other)
            {
                m_name = std::move(other.m_name);
                m_members = std::move(other.m_members);
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

            // Increase maximum health by 300
            int newHealthMax = character->getHealthMax() + 300;
            character->setHealthMax(newHealthMax);

            m_members.push_back(character);
        }

        // Remove Member
        void removeMember(const std::string& name)
        {
            for (auto it = m_members.begin(); it != m_members.end(); ++it)
            {
                if ((*it)->getName() == name)
                {
                    // Decrease maximum health by 300
                    int reducedHealthMax = std::max(0, (*it)->getHealthMax() - 300);
                    (*it)->setHealthMax(reducedHealthMax);

                    // Remove the character from the guild without deleting it
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
            std::cout << "[Guild] " << m_name << "\n";
            for (const auto& member : m_members)
            {
                std::cout << "    " << member->getName() << "\tHealth: " << member->getHealth() << "\tAttack: " << member->getAttackAmnt() << "\tDefense: " << member->getDefenseAmnt() << "\n";
            }
        }
    };
}

#endif
