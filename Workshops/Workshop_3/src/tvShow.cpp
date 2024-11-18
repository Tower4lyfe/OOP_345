#include "tvShow.h"
#include "mediaItem.h"
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <algorithm>
#include <string>

namespace seneca 
{
    TvShow::TvShow(const std::string &id, const std::string & title, unsigned short year,
    const std::string& summary):MediaItem(title, summary, year), m_id(id){}

    void TvShow::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
          out << "S | ";
          out << std::left << std::setfill('.');
          out << std::setw(50) << this->getTitle() << " | ";
          out << std::right << std::setfill(' ');
          out << std::setw(2) << this->m_episodes.size() << " | ";
          out << std::setw(4) << this->getYear() << " | ";
          out << std::left;
          if (g_settings.m_maxSummaryWidth > -1)
          {
            if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
              out << this->getSummary();
            else
              out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
          }
          else
            out << this->getSummary();
          out << std::endl;
        }
        else
        {
          size_t pos = 0;
          out << this->getTitle() << " [" << this->getYear() << "]\n";
          out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
          while (pos < this->getSummary().size())
          {
            out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
            pos += g_settings.m_maxSummaryWidth;
          }
          for (auto& item : m_episodes)
          {
            out << std::setfill('0') << std::right;
            out << "    " << 'S' << std::setw(2) << item.m_season
              << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
            if (item.m_title != "")
              out << item.m_title << '\n';
            else
              out << "Episode " << item.m_numberOverall << '\n';

            pos = 0;
            while (pos < item.m_summary.size())
            {
              out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
              pos += g_settings.m_maxSummaryWidth - 8;
            }
          }
          out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
            << std::setfill(' ') << '\n';
        }
    }

    TvShow* TvShow::createItem(const std::string &strShow)
    {
        if(strShow.empty() || strShow[0] == '#')
        {
            throw "Not a valid show.";
        }

        std::istringstream stream(strShow);
        std::string id, title, yearStr, summary;

        std::cout << "Before GETLINE REACHED.\n";

        std::getline(stream, id, ',');
        std::getline(stream, title, ',');
        std::getline(stream, yearStr, ',');
        std::getline(stream, summary);

        std::cout << "After Getline Reached. \n";

        trim(id);
        trim(title);
        trim(yearStr);
        trim(summary);

        std::cout << "Trimmed!\n";

        unsigned short year = static_cast<unsigned short>(std::stoi(yearStr));

        std::cout << "Right before return!\n";
        
        return new TvShow(id, title, year, summary);
    }


    double TvShow::getEpisodeAverageLength()const
    {
        if(m_episodes.empty())
        {
            return 0;
        }
        
        double result = std::accumulate // accumulate used!!!
        (m_episodes.begin(), m_episodes.end(), 0.0,
        [](double sum, const TvEpisode& episode)
        {
            return sum + episode.m_length;
        }
        ); 

        return result/m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes()const
    {
      std::list<std::string> result; 
      std::list<TvEpisode> buffer; 

      std::copy_if
      (m_episodes.begin(), m_episodes.end(), std::back_inserter(buffer),
      [](const TvEpisode& episode)
      {
        return episode.m_length > 3600;
      });

      std::transform
      (
        buffer.begin(), buffer.end(), std::back_inserter(result),
        [](const TvEpisode& epi)
        {
          return epi.m_title;
        }
      );

      return result;
    }
}