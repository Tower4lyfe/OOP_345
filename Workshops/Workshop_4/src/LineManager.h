/* - To Tsz, Lau,
- 125487248,
- ttlau3@myseneca.ca
- Nov 29th 2024 */
#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H
#include "Workstation.h"
#include <vector>
#include <fstream>
#include <string>

namespace seneca
{
    class LineManager
    {
        std::vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder;
        Workstation* m_firstStation;

        public:
        LineManager() = default;
        ~LineManager() = default;
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif