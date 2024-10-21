#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <string>

namespace seneca
{
    class Guild
    {
    private:
        std::string m_name;
        Character** m_members;
        size_t m_memberCount;

    public:
        Guild(const std::string& name);
        //rule of 5
        ~Guild();
        Guild(const Guild& other);
        Guild& operator=(const Guild& other);
        Guild(Guild&& other) noexcept;
        Guild& operator=(Guild&& other) noexcept;
        //not rule of 5
        void addMember(Character* character);
        void removeMember(const std::string& name);
        Character* operator[](size_t index) const;
        void showMembers() const;
    };
}

#endif