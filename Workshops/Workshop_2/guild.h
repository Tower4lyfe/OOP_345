#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <iostream>
#include <string>

namespace seneca
{
    class Guild
    {
    private:
        std::string m_name;
        Character** m_members;  // Dynamically allocated array for storing members
        size_t m_memberCount;
        size_t m_capacity;  // Keeps track of the number of members

        void resize(size_t newCapacity)
        {
            //new vessel for our INJECTION
            Character** newMembers = new Character*[newCapacity];

            for (size_t i = 0; i < m_memberCount; ++i)
            {
                newMembers[i] = m_members[i];
            }
            //Kill the old body
            delete[] m_members;
            //MOVE IT 
            m_members = newMembers;
            m_capacity = newCapacity;
        }

    public:
        Guild(const std::string& name);
        ~Guild();
        Guild(const Guild& other);
        Guild& operator=(const Guild& other);
        Guild(Guild&& other) noexcept;
        Guild& operator=(Guild&& other) noexcept;

        void addMember(Character* character);
        void removeMember(const std::string& name);
        Character* operator[](size_t index) const;
        void showMembers() const;
    };
}

#endif