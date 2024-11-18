#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H

#include "mediaItem.h"
#include "settings.h"
#include <string>
#include <vector>
#include <list>
#include <sstream>


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

    template<typename Collection_t>
    void TvShow::addEpisode(Collection_t& col, const std::string& strEpisode)
    {
        if (strEpisode.empty() || strEpisode[0] == '#')
        {
            throw std::invalid_argument("Not a valid episode");
        }

        std::istringstream stream (strEpisode);
        std::string id, episodeNumStr, seasonStr, episodeInSeasonStr, airDate, lengthStr;
        std::string title, summary;

        std::getline(stream, id, ',');
        std::getline(stream, episodeNumStr, ',');
        std::getline(stream, seasonStr, ',');
        std::getline(stream, episodeInSeasonStr, ',');
        std::getline(stream, airDate, ',');
        std::getline(stream, lengthStr, ',');
        std::getline(stream, title, ',');
        std::getline(stream, summary, '\n');

        trim(id);
        trim(episodeNumStr);
        trim(seasonStr);
        trim(episodeInSeasonStr);
        trim(airDate);
        trim(lengthStr);
        trim(title);
        trim(summary);

        unsigned short episodeNum = static_cast<unsigned short>(std::stoi(episodeNumStr));
        unsigned short season = seasonStr.empty() ? 1 : static_cast<unsigned short>(std::stoi(seasonStr));
        unsigned short episodeInSeason = static_cast<unsigned short>(std::stoi(episodeInSeasonStr));
        unsigned int length = static_cast<unsigned int>(std::stoi(lengthStr));

        for(size_t i = 0; i < col.size(); ++i)
        {
            TvShow* show = dynamic_cast<TvShow*>[i];
            if(show && show->m_id == id)
            {
                TvEpisode episode;
                episode.m_show = show;
                episode.m_numberOverall = episodeNum;
                episode.m_season = season;
                episode.m_numberInSeason = episodeInSeason;
                episode.m_airDate = airDate;
                episode.m_length = length;
                episode.m_title = title;
                episode.m_summary = summary;
                show->m_episodes.push_back(episode);
                return;
            }
        }

        throw std::invalid_argument("Show not found"); //Assuming if we can't find any episodes
    }
}

#endif