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
        }

        //going the complicated route instead of *this = other;
        Team::Team(const Team&other)
        : m_name(other.m_name), m_memberCount(other.m_memberCount)
        {
            m_members = new Character*[m_memberCount];
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                m_members[i] = other.m_members[i]->clone();
            }
        }

        Team& Team::operator=(const Team&other)
        {
            if (this != &other)
            {
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    delete m_members[i];
                }
                delete[] m_members;

                m_name = other.m_name;
                m_memberCount = other.m_memberCount;
                m_members = new Character*[m_memberCount];
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    m_members[i] = other.m_members[i]->clone();
                }
            }
            return *this;
        }

        Team::Team(Team&&other)noexcept
        : m_name(std::move(other.m_name)), m_members(other.m_members), m_memberCount(other.m_memberCount)
        {
            other.m_members = nullptr;
            other.m_memberCount = 0;
        }

        Team& Team::operator=(Team&&other)noexcept
        {
            if (this != &other)
            {
                for (size_t i = 0; i < m_memberCount; ++i)
                {
                    delete m_members[i];
                }
                delete[] m_members;

                m_name = std::move(other.m_name);
                m_members = other.m_members;
                m_memberCount = other.m_memberCount;

                other.m_members = nullptr;
                other.m_memberCount = 0;
            }
            return *this;
        }

    //Not Rule of 5

    //Very complicated, we need Vector :(
        void Team::addMember(const Character* c)
        {
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                //ID CHECK!!NO DUPLICATE ALLOWED!
                if (m_members[i]->getName() == c->getName())
                    return; 
            }

            //RESIZING, UPSCALING, YOU NAME IT
            Character** newMembers = new Character*[m_memberCount + 1];
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                newMembers[i] = m_members[i];
            }
            delete[] m_members;
            m_members = newMembers;

            //Is it legal to clone people? hmmm
            m_members[m_memberCount++] = c->clone();
        }


        //EVEN MORE COMPLICATED, PLS JUST LET ME USE VECTOR
        void Team::removeMember(const std::string&c)
        {
            for (size_t i = 0; i < m_memberCount; ++i)
            {
                if (m_members[i]->getName() == c)
                {
                    delete m_members[i]; 

                    // SHIFTING 
                    for (size_t j = i; j < m_memberCount - 1; ++j)
                    {
                        m_members[j] = m_members[j + 1];
                    }
                    --m_memberCount;

                    // DOWNSIZING....
                    if (m_memberCount > 0)
                    {
                        Character** newMembers = new Character*[m_memberCount];
                        for (size_t k = 0; k < m_memberCount; ++k)
                        {
                            newMembers[k] = m_members[k];
                        }
                        delete[] m_members;
                        m_members = newMembers;
                    }
                    else
                    {
                        delete[] m_members;
                        m_members = nullptr;
                    }

                    //we found the guy, get me out of the loop
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
                    std::cout << *m_members[i] << std::endl; //I think this works?
                }
            }
        }






}