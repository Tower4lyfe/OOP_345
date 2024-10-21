#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H
#include "character.h"




namespace seneca
{
    class Team
    {
        std::string m_name; //wasn't sure cstring or string, so I went with string 
        Character** m_members;

        //We need these three things to mimic vector 
        size_t m_memberCount; //how many members are in the team right now
        size_t m_capacity; //actual array size 

        //secret function 
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

        public: //BOOOOOORING
        Team(const std::string& name) : m_name(name), m_members(nullptr), m_memberCount(0),m_capacity(0) {m_members = new Character*[1];};
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