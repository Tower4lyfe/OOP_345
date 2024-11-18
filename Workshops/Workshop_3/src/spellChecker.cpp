#include "spellChecker.h"
#include <fstream>

namespace seneca
{
    SpellChecker::SpellChecker(const char* filename)
    {
        std::ifstream file(filename);
        if (!file)
        {
            throw "Bad file name!";
        }

        for (size_t i = 0; i < ARR_SIZE; ++i)
        {
            file >> m_badWords[i] >> m_goodWords[i];
        }
    }

    void SpellChecker::operator()(std::string& text)
    {
        for (size_t i = 0; i < ARR_SIZE; ++i)
        {
            size_t pos = 0;
            while ((pos = text.find(m_badWords[i], pos)) != std::string::npos)
            {
                text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
                ++m_replacementsCNT[i];
                pos += m_goodWords[i].length(); 
            }
        }
    }

    void SpellChecker::showStatistics(std::ostream& out) const
    {
        std::cout << "Spellchecker Statistics\n";
        for (size_t i = 0; i < ARR_SIZE; ++i)
        {
            out.width(15);
            out << std::left << m_badWords[i] << ": " << m_replacementsCNT[i] << " replacements\n";
        }
    }
}
