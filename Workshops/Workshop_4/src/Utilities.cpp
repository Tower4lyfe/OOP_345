#include "Utilities.h"

namespace seneca
{

    char Utilities::m_delimiter = '\0';

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
    {
        std::string token;
        if(str[next_pos] == m_delimiter)
        {
            //really? what if there are more later?
            more = false;
            throw "ERROR. No Token.";
        }


        while(next_pos < str.length() && isspace(str[next_pos]))
        {
            next_pos++;
        }

        size_t nextDelimiter = str.find(m_delimiter, next_pos);
        if(nextDelimiter != std::string::npos)
        {
            token = str.substr(next_pos, nextDelimiter - next_pos);
        }   
        else
        {
            token = str.substr(next_pos);
        }

        size_t end = token.find_last_not_of(" \t");
        if (end != std::string::npos)
            token.erase(end + 1);

        if(token.length() > m_widthField)
            m_widthField = token.length();
        
        if(nextDelimiter == std::string::npos||nextDelimiter + 1 >= str.length())
        {
            more = false;
        }else
        {
            more = true;
            next_pos = nextDelimiter + 1;
        }
        
        return token;
    }


    void Utilities::setDelimiter(char newdelimiter)
    {
        m_delimiter = newdelimiter;
    }

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
}