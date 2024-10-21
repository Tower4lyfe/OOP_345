#include "team.h"

namespace seneca
{
    //RULE OF 5
        Team::~Team()
        {
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                delete m_members[i];
            }
            delete[] m_members;
            m_memberCount = 0;
            m_capacity = 0;
            //BETTER SAFE THAN SORRY, VALGRIN WILL NOT GET ME
        }

        //going the complicated route instead of *this = other;
        //because internet sayS this is better
        Team::Team(const Team& other) 
        : m_name(other.m_name), m_memberCount(other.m_memberCount), m_capacity(other.m_capacity)
        {
            m_members = new Character*[m_capacity];
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                m_members[i] = other.m_members[i]->clone();
            }
        }

        Team& Team::operator=(const Team&other)
        {
            if (this != &other)
            {
                // Delete existing members
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    delete m_members[i];
                }
                delete[] m_members;

                // Copy from other
                m_name = other.m_name;
                m_memberCount = other.m_memberCount;
                m_capacity = other.m_capacity;

                m_members = new Character*[m_capacity];
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    m_members[i] = other.m_members[i]->clone();
                }
            }
            return *this;
        }

        Team::Team(Team&& other) noexcept
            : m_name(std::move(other.m_name)), m_members(other.m_members), m_memberCount(other.m_memberCount), m_capacity(other.m_capacity)
        {
            other.m_members = nullptr;
            other.m_memberCount = 0;
            other.m_capacity = 0;
        }

        Team& Team::operator=(Team&& other) noexcept
        {
            if (this != &other)
            {
                // Delete existing members
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    delete m_members[i];
                }
                delete[] m_members;

                // Move from other
                m_name = std::move(other.m_name);
                m_members = other.m_members;
                m_memberCount = other.m_memberCount;
                m_capacity = other.m_capacity;

                //SAD FUNERAL
                other.m_members = nullptr;
                other.m_memberCount = 0;
                other.m_capacity = 0;
            }
            return *this;
        }

    //Not Rule of 5

    //IMAGING  USING VECTOR 
        void Team::addMember(const Character* c)
        {
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                if (m_members[i]->getName() == c->getName())
                    return; // Prevent adding duplicate characters by name
            }

            if (m_memberCount == m_capacity)
            {
                size_t newCapacity = (m_capacity == 0) ? 2 : m_capacity * 2;
                resize(newCapacity);
            }

            m_members[m_memberCount++] = c->clone();
        }


        //I wrote it, and it still takes me 5 mins to understand what I wrote.
        void Team::removeMember(const std::string& C)
        {
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                if (m_members[i]->getName() == C)
                {
                    delete m_members[i];

                    //shifting, fill the void, no void, void bad
                    for (size_t j = i; j < m_memberCount - 1; ++j)
                    {
                        m_members[j] = m_members[j + 1];
                    }
                    --m_memberCount;
                    break;
                }
            }
        }


        Character* Team::operator[](size_t idx)const
        {
            if (idx < m_memberCount)
                return m_members[idx];
            return nullptr;
        }


        void Team::showMembers()const
        {
            if(m_memberCount == 0)
                std::cout << "No team.\n";
            else
            {
                std::cout << "[Team] " << m_name << "\n";
                for(size_t i = 0; i < m_memberCount; ++i)
                {
                    std::cout <<"\t" << i+1 << ": " *m_members[i] << std::endl; //I think this works?
                }
            }
        }






}