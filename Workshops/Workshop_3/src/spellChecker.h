#ifndef SENECA_SPELLCHECKER_H
#define SENECA_SPELLCHECKER_H
#include <iostream>
#include <fstream>
#define ARR_SIZE 6

namespace seneca
{
    class SpellChecker
    {
        std::string m_badWords[ARR_SIZE];
        std::string m_goodWords[ARR_SIZE];
        size_t m_replacementsCNT[ARR_SIZE]{0};
        
        public:
        SpellChecker(const char* filename);
        void operator()(std::string& text);
        void showStatistics(std::ostream& out)const;
    };
}


#endif 