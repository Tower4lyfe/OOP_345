#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include "mediaItem.h"
#include "settings.h"
#include <string>
#include <vector>
#include <list>


namespace seneca
{
    struct TvEpisode
    {
        const class TvShow* m_show{};
        unsigned short m_numberOverall{};
        unsigned short m_season{};
        unsigned short m_numberInSeason{};
        std::string m_airDate{};
        unsigned int m_length{};
        std::string m_title{};
        std::string m_summary{};
    };

    class TvShow : public MediaItem
    {
        std::string m_id;
        std::vector<TvEpisode> m_episodes;

        TvShow(const std::string& id, const std::string& title, unsigned short year, 
        const std::string& summary);

    public:
        void display(std::ostream& out) const override;
        static TvShow* createItem(const std::string& strShow);
        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode);
        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;
    };
}

#endif