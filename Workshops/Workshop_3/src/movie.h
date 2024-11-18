#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include "mediaItem.h"
#include "settings.h"
#include <string>
#include <iostream>

namespace seneca
{
    class Movie : public MediaItem
    {
        Movie(const std::string& title, unsigned short year, const std::string& summary);

    public:
        void display(std::ostream& out) const override;

        static Movie* createItem(const std::string& strMovie);
    };
}

#endif

