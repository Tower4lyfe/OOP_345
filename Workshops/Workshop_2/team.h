#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include "character.h"




namespace seneca
{
    class Team
    {
        std::string m_name; //wasn't sure cstring or string, so I went with string 
        Character** m_members;
        //added to mimic vector with just array
        size_t m_memberCount;
        size_t m_capacity;

        void resize(size_t newCapacity);

        

        public:
        Team(const std::string& name) : m_name(name), m_members(nullptr), m_memberCount(0), m_capacity(0) {};
        //RULE OF 5
        ~Team();
        Team(const Team&other);
        Team& operator=(const Team&other);
        Team(Team&&other)noexcept;
        Team& operator=(Team&&other)noexcept;

        //Not Rule of 5
        void addMember(const Character* c);
        void removeMember(const std::string&c);
        Character* operator[](size_t idx)const;
        void showMembers()const;

    };
}

#endif