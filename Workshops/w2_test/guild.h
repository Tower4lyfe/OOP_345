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
        Guild(const std::string& name) : m_name(name) {}

        void addMember(Character* character)
        {
            for (const auto& member : m_members)
            {
                if (member == character)
                    return;
            }
            m_members.push_back(character);
            character->setHealth(character->getHealth() + 200); // Increase health when joining a guild
        }

        void removeMember(const std::string& name)
        {
            for (auto it = m_members.begin(); it != m_members.end(); ++it)
            {
                if ((*it)->getName() == name)
                {
                    (*it)->setHealth((*it)->getHealth() - 200); // Reduce health when leaving a guild
                    m_members.erase(it);
                    break;
                }
            }
        }

        Character* operator[](size_t index) const
        {
            if (index < m_members.size())
                return m_members[index];
            return nullptr;
        }

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