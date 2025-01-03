/*
- ToTsz, Lau,
- 125497248
- ttlau3@myseneca.ca
- Nov 18th, 2024 */
#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include "mediaItem.h"
#include "settings.h"
#include <string>
#include <iostream>

namespace seneca
{
    class Book : public MediaItem
    {
        std::string m_author;
        std::string m_country;
        double m_price;

        Book(const std::string& author, const std::string& title, const std::string& country, 
        double price, unsigned short year, const std::string& summary);

    public:
        void display(std::ostream& out) const override;

        static Book* createItem(const std::string& strBook);
    };
}

#endif
