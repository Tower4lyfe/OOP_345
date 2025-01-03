/*
- ToTsz, Lau,
- 125497248
- ttlau3@myseneca.ca
- Nov 18th, 2024 */
#include "movie.h"
#include <iomanip>
#include <sstream>


namespace seneca
{
    Movie::Movie(const std::string& title, unsigned short year, const std::string& summary)
        : MediaItem(title, summary, year) {}

    void Movie::display(std::ostream& out) const
  {
    if (g_settings.m_tableView)
    {
      out << "M | ";
      out << std::left << std::setfill('.');
      out << std::setw(50) << this->getTitle() << " | ";
      out << std::right << std::setfill(' ');
      out << std::setw(9) << this->getYear() << " | ";
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
      out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
        << std::setfill(' ') << '\n';
    }
  }

    Movie* Movie::createItem(const std::string& strMovie)
    {
        if (strMovie.empty() || strMovie[0] == '#')
        {
            throw "Not a valid movie.";
        }

        std::istringstream stream(strMovie);
        std::string title, yearStr, summary;

        std::getline(stream, title, ',');
        std::getline(stream, yearStr, ',');
        std::getline(stream, summary);

        trim(title);
        trim(yearStr);
        trim(summary);

        if (title.empty() || yearStr.empty())
        {
            throw "Not a valid movie.";
        }

        unsigned short year = static_cast<unsigned short>(std::stoi(yearStr));

        return new Movie(title, year, summary);
    }
}
