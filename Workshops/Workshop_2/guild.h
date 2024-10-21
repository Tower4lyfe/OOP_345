#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H
#include "character.h"




namespace seneca
{
    class Guild
    {
        std::string m_name; //wasn't sure cstring or string, so I went with string 
        Character** m_members;
        size_t m_memberCount; 

        public:
        Guild(const std::string& name) : m_name(name), m_members(nullptr), m_memberCount(0) {};
        //RULE OF 5
        ~Guild();
        Guild(const Guild&other);
        Guild& operator=(const Guild&other);
        Guild(Guild&&other)noexcept;
        Guild& operator=(Guild&&other)noexcept;

        //Not Rule of 5
        void addMember(Character* c);//NOT CONST
        void removeMember(const std::string&c);
        Character* operator[](size_t idx)const;
        void showMembers()const;

    };
}

#endif