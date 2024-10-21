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
        size_t m_memberCount = 0;  // Keeps track of the number of members

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