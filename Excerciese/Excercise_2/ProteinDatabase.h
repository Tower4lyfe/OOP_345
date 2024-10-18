#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H
#include <iostream>
#include <string>

namespace seneca
{
    class ProteinDatabase
    {
        std::string* unique_id;
        std::string* amino_acid;
        size_t count;

        public:
        ProteinDatabase(){amino_acid = nullptr; count = 0;};
        ProteinDatabase(const std::string&);
        ~ProteinDatabase();
        ProteinDatabase(const ProteinDatabase&);
        ProteinDatabase &operator=(const ProteinDatabase&);
        ProteinDatabase(ProteinDatabase&&)noexcept;
        ProteinDatabase &operator=(ProteinDatabase&&)noexcept;
        size_t size() const;
        std::string operator[](size_t) const;
        std::string getUID(size_t) const;

    };
}


#endif