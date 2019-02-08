/***************************************************************
 * Name:      CalendarApp.h
 * Purpose:   Defines Application Class
 * Author:    Valentin Vladimirov ()
 * Created:   2018-06-28
 * Copyright: Valentin Vladimirov ()
 * License:
 **************************************************************/

#ifndef CALENDARAPP_H
#define CALENDARAPP_H

#include <wx/app.h>

class CalendarApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // CALENDARAPP_H
