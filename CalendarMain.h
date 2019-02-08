/***************************************************************
 * Name:      CalendarMain.h
 * Purpose:   Defines Application Frame
 * Author:    Valentin Vladimirov ()
 * Created:   2018-06-28
 * Copyright: Valentin Vladimirov ()
 * License:
 **************************************************************/

#ifndef CALENDARMAIN_H
#define CALENDARMAIN_H

//(*Headers(CalendarFrame)
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
//*)

class CalendarFrame: public wxFrame
{
    public:

        CalendarFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~CalendarFrame();

    private:

        //(*Handlers(CalendarFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPanel2Paint(wxPaintEvent& event);
        void OnPanel2Paint1(wxPaintEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnBtn_BackClick(wxCommandEvent& event);
        void OnBtn_NextClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(CalendarFrame)
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_TEXTCTRL1;
        static const long ID_COMBOBOX1;
        static const long ID_PANEL1;
        //*)

        //(*Declarations(CalendarFrame)
        wxPanel* Panel1;
        wxButton* Btn_Next;
        wxComboBox* ComboBox1;
        wxButton* Btn_Back;
        wxTextCtrl* TextCtrl1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // CALENDARMAIN_H
