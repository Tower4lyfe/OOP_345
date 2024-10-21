#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"
#include <string>

namespace seneca
{

    //basically just copy pasting team module with some minor tweaks
    class Guild
    {
    private:
        std::string m_name;
        Character** m_members;

        //like I said, copy pasting..
        size_t m_memberCount;
        size_t m_capacity;

        void resize(size_t newCapacity)
        {
            Character** newMembers = new Character*[newCapacity];
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                newMembers[i] = m_members[i];
            }
            delete[] m_members;
            m_members = newMembers;
            m_capacity = newCapacity;
        }

    public:
        Guild(const std::string& name):m_name(name), m_members(nullptr), m_memberCount(0), m_capacity(0) {m_members = new Character*[1];};
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