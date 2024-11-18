#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H

namespace seneca
{
    struct Settings
    {
        bool m_tableView{false}; 
        int m_maxSummaryWidth{80} ;
    };

    extern Settings g_settings;
}



#endif