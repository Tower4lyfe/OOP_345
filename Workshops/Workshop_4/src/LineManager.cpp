#include "lineManager.h"
#include "Workstation.h"
#include <algorithm>



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
            m_activeLine.push_back(*currentStation);
	    }

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
}