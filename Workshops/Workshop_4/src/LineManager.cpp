#include "LineManager.h"
#include "Workstation.h"
#include <algorithm>
#include <ostream>



namespace seneca 
{
    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {
        if (file.empty() == true) 
        {
		    throw std::string("ERROR: No filename provided.");
	    }

	    std::ifstream fileObj(file);

	    if (!fileObj)
		    throw std::string("Unable to open [") + file + "] file.";



        Utilities util;
        util.setDelimiter('|');
        std::vector<std::string> nextStationNames;

        std::string line;
	    while (!fileObj.eof())
	    {
            
            size_t next_pos = 0;
            bool more = false;
		    std::getline(fileObj, line);

            std::string currentStationName = util.extractToken(line, next_pos, more);
            std::string nextStationName = more? util.extractToken(line, next_pos, more) : "";

            //find if to find station that fits the name
            auto currentStation = std::find_if(stations.begin(), stations.end(), 
            [&currentStationName](Workstation* station)
            {
                return station->getItemName() == currentStationName;
            });

            if(currentStation == stations.end()){throw std::string{"No Station Found.\n"};}

            //there is a next station
            if(!nextStationName.empty())
            {
                auto nextStation = std::find_if(stations.begin(), stations.end(), 
                [&nextStationName](Workstation* station)
                {
                    return station->getItemName() == nextStationName;
                });

                if(nextStation == stations.end())
                    throw std::string{"No next Station with that name.\n"};

                (*currentStation)->setNextStation(*nextStation);
                nextStationNames.push_back(nextStationName);
            }else
            {
                //just be safe.
                (*currentStation)->setNextStation(nullptr);
            }
	    }

        m_activeLine = stations;

	    fileObj.close();

            // Find the first station
        m_firstStation = *std::find_if(m_activeLine.begin(), m_activeLine.end(),
                [&nextStationNames](Workstation *station) 
                {
                    //If its name does not exist in the nextStaionNames
                    return std::none_of(nextStationNames.begin(),nextStationNames.end(),
                            [&station](const std::string &nextName) 
                            {
                                return station->getItemName() == nextName;
                            });
                });

        if (m_firstStation == nullptr) 
        {
            throw std::string("Could not identify the first station.");
        }

        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations() 
    {
        std::vector<Workstation*> orderedLine;

        Workstation* currentStation = m_firstStation;
        while (currentStation != nullptr) 
        {
            orderedLine.push_back(currentStation);
            currentStation = currentStation->getNextStation();
        }

        m_activeLine = std::move(orderedLine);
    }

    bool LineManager::run(std::ostream& os)
    {
        static size_t currentIteration = 1;

        os << "Line Manager Iteration: " << currentIteration << std::endl;
            
        (*m_firstStation)+= std::move(g_pending.front());
        g_pending.pop_front();

        std::for_each(m_activeLine.begin(), m_activeLine.end(), 
        [&os](Workstation* station)
        {
            station->fill(os);
        });

        std::for_each(m_activeLine.begin(), m_activeLine.end(), 
        [](Workstation* station)
        {
            station->attemptToMoveOrder();
        });

        currentIteration++;

        if(g_completed.size() + g_incomplete.size() == m_cntCustomerOrder)
            return true;  

        return false;
    }
    
    void LineManager::display(std::ostream& os) const
    {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), 
        [&os](Workstation* station)
        {
            station->display(os);
        });
    }

}