/***************************************************************
 * Name:      CalendarApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Valentin Vladimirov ()
 * Created:   2018-06-28
 * Copyright: Valentin Vladimirov ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "CalendarApp.h"

//(*AppHeaders
#include "CalendarMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(CalendarApp);

bool CalendarApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	CalendarFrame* Frame = new CalendarFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
