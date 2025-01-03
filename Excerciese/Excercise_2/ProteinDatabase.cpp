#include "ProteinDatabase.h"
#include <fstream>
#include <utility>

namespace seneca
{
    ProteinDatabase::ProteinDatabase(const std::string& fileName)
    {
        // set them to zero first
        count = 0;
        amino_acid = nullptr;
        unique_id = nullptr;

        std::ifstream file(fileName.c_str()); // open the input file stream

        if (!file)
            return; // if we fail to open the file

        // since we are here, file opened without problem

        // create buffers?
        std::string line;

        // As long as getline is fine, no eofbit, failbit, badbit
        // counting!!
        while (std::getline(file, line).good()) // hmmm? why not just std::getline(file,line)
        {
            // if the the first character of the line is > we encounter a new protein
            if (line[0] == '>')
                count++;
        }

        amino_acid = new std::string[count];
        unique_id = new std::string[count];

        file.clear();              // clear out the flags, if there were any such as eofbit
        file.seekg(std::ios::beg); // moving the file pointer to the beggining of the file
        line.clear();              // clear out the string, makes it empty

        int i = -1;
        while(std::getline(file, line).good())
        {
            if(line[0] == '>')
            {
                ++i;

                unique_id[i] = line.substr(4u, line.find_first_of('|', 4u) - 4u);
            }
            else
            {
                amino_acid[i] += line;
            }
        }




        // I just want to know if this work or not
        // for (struct {int count{-1}; std::string buffer{}; } temp;
        //      std::getline(file, temp.buffer);)
        // {
        //     // if you see > you know this is a new thing, and you do the storing id thing
        //     // then you move on to the next line, assuming you could
        //     // it doesn't start with >, you store that line to amino_acid
        //     if (temp.buffer[0] == '>')
        //     {
        //         ++temp.count;
        //         unique_id[temp.count] = temp.buffer.substr(4, temp.buffer.find('|', 4) - 4);
        //     }
        //     else
        //     {
        //         amino_acid[count] += temp.buffer;
        //     }
        // }
    }

    ProteinDatabase::~ProteinDatabase()
    {
        delete[] unique_id;
        delete[] amino_acid;
    }

    ProteinDatabase::ProteinDatabase(const ProteinDatabase &copy)
    {
        *this = copy;
    }

    ProteinDatabase &ProteinDatabase::operator=(const ProteinDatabase &copy)
    {
        if (this != &copy)
        {
            delete[] amino_acid;
            amino_acid = nullptr;
            delete[] unique_id;
            unique_id = nullptr;

            count = copy.count;

            if (count != 0) // if count is 0, it means the the copy obj has nothing inside
            {
                amino_acid = new std::string[count];
                unique_id = new std::string[count];

                for (auto i = 0u; i < count; ++i)
                {
                    amino_acid[i] = copy.amino_acid[i];
                    unique_id[i] = copy.unique_id[i];
                }
            }
        }

        return *this;
    }

    ProteinDatabase::ProteinDatabase(ProteinDatabase &&move) noexcept
    {
        *this = std::move(move);
    }

    ProteinDatabase &ProteinDatabase::operator=(ProteinDatabase &&move) noexcept
    {
        if (this != &move) // why is this important? Especially when we already have copy constructor
        {
            delete[] unique_id;
            delete[] amino_acid;

            unique_id = move.unique_id;
            amino_acid = move.amino_acid;
            count = move.count;

            // sad preparation for funeral :(
            move.count = 0;
            move.unique_id = nullptr;
            move.amino_acid = nullptr;
        }

        return *this;
    }

    size_t ProteinDatabase::size() const
    {
        return count;
    }

    std::string ProteinDatabase::operator[](size_t i) const
    {
        if(i < count)
        {
            return amino_acid[i];
        }
            return "";

    }

    std::string ProteinDatabase::getUID(size_t i) const
    {
        if(i < count)
        {
            return unique_id[i];
        }
            return "None";
    }
}