/***************************************************************
 * Name:      CalendarMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Valentin Vladimirov ()
 * Created:   2018-06-28
 * Copyright: Valentin Vladimirov ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "CalendarMain.h"
#include <wx/msgdlg.h>
#include <wx/colour.h>
#include <wx/gdicmn.h>

#include "months.cpp"

int DayOfWeek(int y, int m, int d);

void DateToStr(wxString& date);
void DrawDays(wxClientDC& dc, int m);
void DrawCalendarFrame(wxPaintDC& p);
void DrawDaysOfWeek(wxClientDC& dc);

bool IsLastWeekOfMonth(int& c);

//(*InternalHeaders(CalendarFrame)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(CalendarFrame)
const long CalendarFrame::ID_BUTTON1 = wxNewId();
const long CalendarFrame::ID_BUTTON2 = wxNewId();
const long CalendarFrame::ID_TEXTCTRL1 = wxNewId();
const long CalendarFrame::ID_COMBOBOX1 = wxNewId();
const long CalendarFrame::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CalendarFrame,wxFrame)
    //(*EventTable(CalendarFrame)
    //*)
END_EVENT_TABLE()

CalendarFrame::CalendarFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(CalendarFrame)
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(310,280));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    FlexGridSizer2 = new wxFlexGridSizer(0, 4, 0, 0);
    Btn_Back = new wxButton(Panel1, ID_BUTTON1, _("<"), wxDefaultPosition, wxSize(29,29), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer2->Add(Btn_Back, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Btn_Next = new wxButton(Panel1, ID_BUTTON2, _(">"), wxDefaultPosition, wxSize(29,29), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    FlexGridSizer2->Add(Btn_Next, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl1 = new wxTextCtrl(Panel1, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxSize(95,29), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    FlexGridSizer2->Add(TextCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ComboBox1 = new wxComboBox(Panel1, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxSize(102,29), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    ComboBox1->Append(_("--January--"));
    ComboBox1->SetSelection( ComboBox1->Append(_("01/01/2018")) );
    ComboBox1->Append(_("02/01/2018"));
    ComboBox1->Append(_("03/01/2018"));
    ComboBox1->Append(_("04/01/2018"));
    ComboBox1->Append(_("05/01/2018"));
    ComboBox1->Append(_("06/01/2018"));
    ComboBox1->Append(_("07/01/2018"));
    ComboBox1->Append(_("08/01/2018"));
    ComboBox1->Append(_("09/01/2018"));
    ComboBox1->Append(_("10/01/2018"));
    ComboBox1->Append(_("11/01/2018"));
    ComboBox1->Append(_("12/01/2018"));
    ComboBox1->Append(_("13/01/2018"));
    ComboBox1->Append(_("14/01/2018"));
    ComboBox1->Append(_("15/01/2018"));
    ComboBox1->Append(_("16/01/2018"));
    ComboBox1->Append(_("17/01/2018"));
    ComboBox1->Append(_("18/01/2018"));
    ComboBox1->Append(_("19/01/2018"));
    ComboBox1->Append(_("20/01/2018"));
    ComboBox1->Append(_("21/01/2018"));
    ComboBox1->Append(_("22/01/2018"));
    ComboBox1->Append(_("23/01/2018"));
    ComboBox1->Append(_("24/01/2018"));
    ComboBox1->Append(_("25/01/2018"));
    ComboBox1->Append(_("26/01/2018"));
    ComboBox1->Append(_("27/01/2018"));
    ComboBox1->Append(_("28/01/2018"));
    ComboBox1->Append(_("29/01/2018"));
    ComboBox1->Append(_("30/01/2018"));
    ComboBox1->Append(_("31/01/2018"));
    ComboBox1->Append(_("--February--"));
    ComboBox1->Append(_("01/02/2018"));
    ComboBox1->Append(_("02/02/2018"));
    ComboBox1->Append(_("03/02/2018"));
    ComboBox1->Append(_("04/02/2018"));
    ComboBox1->Append(_("05/02/2018"));
    ComboBox1->Append(_("06/02/2018"));
    ComboBox1->Append(_("07/02/2018"));
    ComboBox1->Append(_("08/02/2018"));
    ComboBox1->Append(_("09/02/2018"));
    ComboBox1->Append(_("10/02/2018"));
    ComboBox1->Append(_("11/02/2018"));
    ComboBox1->Append(_("12/02/2018"));
    ComboBox1->Append(_("13/02/2018"));
    ComboBox1->Append(_("14/02/2018"));
    ComboBox1->Append(_("15/02/2018"));
    ComboBox1->Append(_("16/02/2018"));
    ComboBox1->Append(_("17/02/2018"));
    ComboBox1->Append(_("18/02/2018"));
    ComboBox1->Append(_("19/02/2018"));
    ComboBox1->Append(_("20/02/2018"));
    ComboBox1->Append(_("21/02/2018"));
    ComboBox1->Append(_("22/02/2018"));
    ComboBox1->Append(_("23/02/2018"));
    ComboBox1->Append(_("24/02/2018"));
    ComboBox1->Append(_("25/02/2018"));
    ComboBox1->Append(_("26/02/2018"));
    ComboBox1->Append(_("27/02/2018"));
    ComboBox1->Append(_("28/02/2018"));
    ComboBox1->Append(_("----March----"));
    ComboBox1->Append(_("01/03/2018"));
    ComboBox1->Append(_("02/03/2018"));
    ComboBox1->Append(_("03/03/2018"));
    ComboBox1->Append(_("04/03/2018"));
    ComboBox1->Append(_("05/03/2018"));
    ComboBox1->Append(_("06/03/2018"));
    ComboBox1->Append(_("07/03/2018"));
    ComboBox1->Append(_("08/03/2018"));
    ComboBox1->Append(_("09/03/2018"));
    ComboBox1->Append(_("10/03/2018"));
    ComboBox1->Append(_("11/03/2018"));
    ComboBox1->Append(_("12/03/2018"));
    ComboBox1->Append(_("13/03/2018"));
    ComboBox1->Append(_("14/03/2018"));
    ComboBox1->Append(_("15/03/2018"));
    ComboBox1->Append(_("16/03/2018"));
    ComboBox1->Append(_("17/03/2018"));
    ComboBox1->Append(_("18/03/2018"));
    ComboBox1->Append(_("19/03/2018"));
    ComboBox1->Append(_("20/03/2018"));
    ComboBox1->Append(_("21/03/2018"));
    ComboBox1->Append(_("22/03/2018"));
    ComboBox1->Append(_("23/03/2018"));
    ComboBox1->Append(_("24/03/2018"));
    ComboBox1->Append(_("25/03/2018"));
    ComboBox1->Append(_("26/03/2018"));
    ComboBox1->Append(_("27/03/2018"));
    ComboBox1->Append(_("28/03/2018"));
    ComboBox1->Append(_("29/03/2018"));
    ComboBox1->Append(_("30/03/2018"));
    ComboBox1->Append(_("31/03/2018"));
    ComboBox1->Append(_("-----April-----"));
    ComboBox1->Append(_("01/04/2018"));
    ComboBox1->Append(_("02/04/2018"));
    ComboBox1->Append(_("03/04/2018"));
    ComboBox1->Append(_("04/04/2018"));
    ComboBox1->Append(_("05/04/2018"));
    ComboBox1->Append(_("06/04/2018"));
    ComboBox1->Append(_("07/04/2018"));
    ComboBox1->Append(_("08/04/2018"));
    ComboBox1->Append(_("09/04/2018"));
    ComboBox1->Append(_("10/04/2018"));
    ComboBox1->Append(_("11/04/2018"));
    ComboBox1->Append(_("12/04/2018"));
    ComboBox1->Append(_("13/04/2018"));
    ComboBox1->Append(_("14/04/2018"));
    ComboBox1->Append(_("15/04/2018"));
    ComboBox1->Append(_("16/04/2018"));
    ComboBox1->Append(_("17/04/2018"));
    ComboBox1->Append(_("18/04/2018"));
    ComboBox1->Append(_("19/04/2018"));
    ComboBox1->Append(_("20/04/2018"));
    ComboBox1->Append(_("21/04/2018"));
    ComboBox1->Append(_("22/04/2018"));
    ComboBox1->Append(_("23/04/2018"));
    ComboBox1->Append(_("24/04/2018"));
    ComboBox1->Append(_("25/04/2018"));
    ComboBox1->Append(_("26/04/2018"));
    ComboBox1->Append(_("27/04/2018"));
    ComboBox1->Append(_("28/04/2018"));
    ComboBox1->Append(_("29/04/2018"));
    ComboBox1->Append(_("30/04/2018"));
    ComboBox1->Append(_("------May------"));
    ComboBox1->Append(_("01/05/2018"));
    ComboBox1->Append(_("02/05/2018"));
    ComboBox1->Append(_("03/05/2018"));
    ComboBox1->Append(_("04/05/2018"));
    ComboBox1->Append(_("05/05/2018"));
    ComboBox1->Append(_("06/05/2018"));
    ComboBox1->Append(_("07/05/2018"));
    ComboBox1->Append(_("08/05/2018"));
    ComboBox1->Append(_("09/05/2018"));
    ComboBox1->Append(_("10/05/2018"));
    ComboBox1->Append(_("11/05/2018"));
    ComboBox1->Append(_("12/05/2018"));
    ComboBox1->Append(_("13/05/2018"));
    ComboBox1->Append(_("14/05/2018"));
    ComboBox1->Append(_("15/05/2018"));
    ComboBox1->Append(_("16/05/2018"));
    ComboBox1->Append(_("17/05/2018"));
    ComboBox1->Append(_("18/05/2018"));
    ComboBox1->Append(_("19/05/2018"));
    ComboBox1->Append(_("20/05/2018"));
    ComboBox1->Append(_("21/05/2018"));
    ComboBox1->Append(_("22/05/2018"));
    ComboBox1->Append(_("23/05/2018"));
    ComboBox1->Append(_("24/05/2018"));
    ComboBox1->Append(_("25/05/2018"));
    ComboBox1->Append(_("26/05/2018"));
    ComboBox1->Append(_("27/05/2018"));
    ComboBox1->Append(_("28/05/2018"));
    ComboBox1->Append(_("29/05/2018"));
    ComboBox1->Append(_("30/05/2018"));
    ComboBox1->Append(_("31/05/2018"));
    ComboBox1->Append(_("-----June-----"));
    ComboBox1->Append(_("01/06/2018"));
    ComboBox1->Append(_("02/06/2018"));
    ComboBox1->Append(_("03/06/2018"));
    ComboBox1->Append(_("04/06/2018"));
    ComboBox1->Append(_("05/06/2018"));
    ComboBox1->Append(_("06/06/2018"));
    ComboBox1->Append(_("07/06/2018"));
    ComboBox1->Append(_("08/06/2018"));
    ComboBox1->Append(_("09/06/2018"));
    ComboBox1->Append(_("10/06/2018"));
    ComboBox1->Append(_("11/06/2018"));
    ComboBox1->Append(_("12/06/2018"));
    ComboBox1->Append(_("13/06/2018"));
    ComboBox1->Append(_("14/06/2018"));
    ComboBox1->Append(_("15/06/2018"));
    ComboBox1->Append(_("16/06/2018"));
    ComboBox1->Append(_("17/06/2018"));
    ComboBox1->Append(_("18/06/2018"));
    ComboBox1->Append(_("19/06/2018"));
    ComboBox1->Append(_("20/06/2018"));
    ComboBox1->Append(_("21/06/2018"));
    ComboBox1->Append(_("22/06/2018"));
    ComboBox1->Append(_("23/06/2018"));
    ComboBox1->Append(_("24/06/2018"));
    ComboBox1->Append(_("25/06/2018"));
    ComboBox1->Append(_("26/06/2018"));
    ComboBox1->Append(_("27/06/2018"));
    ComboBox1->Append(_("28/06/2018"));
    ComboBox1->Append(_("29/06/2018"));
    ComboBox1->Append(_("30/06/2018"));
    ComboBox1->Append(_("------July------"));
    ComboBox1->Append(_("01/07/2018"));
    ComboBox1->Append(_("02/07/2018"));
    ComboBox1->Append(_("03/07/2018"));
    ComboBox1->Append(_("04/07/2018"));
    ComboBox1->Append(_("05/07/2018"));
    ComboBox1->Append(_("06/07/2018"));
    ComboBox1->Append(_("07/07/2018"));
    ComboBox1->Append(_("08/07/2018"));
    ComboBox1->Append(_("09/07/2018"));
    ComboBox1->Append(_("10/07/2018"));
    ComboBox1->Append(_("11/07/2018"));
    ComboBox1->Append(_("12/07/2018"));
    ComboBox1->Append(_("13/07/2018"));
    ComboBox1->Append(_("14/07/2018"));
    ComboBox1->Append(_("15/07/2018"));
    ComboBox1->Append(_("16/07/2018"));
    ComboBox1->Append(_("17/07/2018"));
    ComboBox1->Append(_("18/07/2018"));
    ComboBox1->Append(_("19/07/2018"));
    ComboBox1->Append(_("20/07/2018"));
    ComboBox1->Append(_("21/07/2018"));
    ComboBox1->Append(_("22/07/2018"));
    ComboBox1->Append(_("23/07/2018"));
    ComboBox1->Append(_("24/07/2018"));
    ComboBox1->Append(_("25/07/2018"));
    ComboBox1->Append(_("26/07/2018"));
    ComboBox1->Append(_("27/07/2018"));
    ComboBox1->Append(_("28/07/2018"));
    ComboBox1->Append(_("29/07/2018"));
    ComboBox1->Append(_("30/07/2018"));
    ComboBox1->Append(_("31/07/2018"));
    ComboBox1->Append(_("---August----"));
    ComboBox1->Append(_("01/08/2018"));
    ComboBox1->Append(_("02/08/2018"));
    ComboBox1->Append(_("03/08/2018"));
    ComboBox1->Append(_("04/08/2018"));
    ComboBox1->Append(_("05/08/2018"));
    ComboBox1->Append(_("06/08/2018"));
    ComboBox1->Append(_("07/08/2018"));
    ComboBox1->Append(_("08/08/2018"));
    ComboBox1->Append(_("09/08/2018"));
    ComboBox1->Append(_("10/08/2018"));
    ComboBox1->Append(_("11/08/2018"));
    ComboBox1->Append(_("12/08/2018"));
    ComboBox1->Append(_("13/08/2018"));
    ComboBox1->Append(_("14/08/2018"));
    ComboBox1->Append(_("15/08/2018"));
    ComboBox1->Append(_("16/08/2018"));
    ComboBox1->Append(_("17/08/2018"));
    ComboBox1->Append(_("18/08/2018"));
    ComboBox1->Append(_("19/08/2018"));
    ComboBox1->Append(_("20/08/2018"));
    ComboBox1->Append(_("21/08/2018"));
    ComboBox1->Append(_("22/08/2018"));
    ComboBox1->Append(_("23/08/2018"));
    ComboBox1->Append(_("24/08/2018"));
    ComboBox1->Append(_("25/08/2018"));
    ComboBox1->Append(_("26/08/2018"));
    ComboBox1->Append(_("27/08/2018"));
    ComboBox1->Append(_("28/08/2018"));
    ComboBox1->Append(_("29/08/2018"));
    ComboBox1->Append(_("30/08/2018"));
    ComboBox1->Append(_("31/08/2018"));
    ComboBox1->Append(_("-September-"));
    ComboBox1->Append(_("01/09/2018"));
    ComboBox1->Append(_("02/09/2018"));
    ComboBox1->Append(_("03/09/2018"));
    ComboBox1->Append(_("04/09/2018"));
    ComboBox1->Append(_("05/09/2018"));
    ComboBox1->Append(_("06/09/2018"));
    ComboBox1->Append(_("07/09/2018"));
    ComboBox1->Append(_("08/09/2018"));
    ComboBox1->Append(_("09/09/2018"));
    ComboBox1->Append(_("10/09/2018"));
    ComboBox1->Append(_("11/09/2018"));
    ComboBox1->Append(_("12/09/2018"));
    ComboBox1->Append(_("13/09/2018"));
    ComboBox1->Append(_("14/09/2018"));
    ComboBox1->Append(_("15/09/2018"));
    ComboBox1->Append(_("16/09/2018"));
    ComboBox1->Append(_("17/09/2018"));
    ComboBox1->Append(_("18/09/2018"));
    ComboBox1->Append(_("19/09/2018"));
    ComboBox1->Append(_("20/09/2018"));
    ComboBox1->Append(_("21/09/2018"));
    ComboBox1->Append(_("22/09/2018"));
    ComboBox1->Append(_("23/09/2018"));
    ComboBox1->Append(_("24/09/2018"));
    ComboBox1->Append(_("25/09/2018"));
    ComboBox1->Append(_("26/09/2018"));
    ComboBox1->Append(_("27/09/2018"));
    ComboBox1->Append(_("28/09/2018"));
    ComboBox1->Append(_("29/09/2018"));
    ComboBox1->Append(_("30/09/2018"));
    ComboBox1->Append(_("--October--"));
    ComboBox1->Append(_("01/10/2018"));
    ComboBox1->Append(_("02/10/2018"));
    ComboBox1->Append(_("03/10/2018"));
    ComboBox1->Append(_("04/10/2018"));
    ComboBox1->Append(_("05/10/2018"));
    ComboBox1->Append(_("06/10/2018"));
    ComboBox1->Append(_("07/10/2018"));
    ComboBox1->Append(_("08/10/2018"));
    ComboBox1->Append(_("09/10/2018"));
    ComboBox1->Append(_("10/10/2018"));
    ComboBox1->Append(_("11/10/2018"));
    ComboBox1->Append(_("12/10/2018"));
    ComboBox1->Append(_("13/10/2018"));
    ComboBox1->Append(_("14/10/2018"));
    ComboBox1->Append(_("15/10/2018"));
    ComboBox1->Append(_("16/10/2018"));
    ComboBox1->Append(_("17/10/2018"));
    ComboBox1->Append(_("18/10/2018"));
    ComboBox1->Append(_("19/10/2018"));
    ComboBox1->Append(_("20/10/2018"));
    ComboBox1->Append(_("21/10/2018"));
    ComboBox1->Append(_("22/10/2018"));
    ComboBox1->Append(_("23/10/2018"));
    ComboBox1->Append(_("24/10/2018"));
    ComboBox1->Append(_("25/10/2018"));
    ComboBox1->Append(_("26/10/2018"));
    ComboBox1->Append(_("27/10/2018"));
    ComboBox1->Append(_("28/10/2018"));
    ComboBox1->Append(_("29/10/2018"));
    ComboBox1->Append(_("30/10/2018"));
    ComboBox1->Append(_("31/10/2018"));
    ComboBox1->Append(_("-November-"));
    ComboBox1->Append(_("01/11/2018"));
    ComboBox1->Append(_("02/11/2018"));
    ComboBox1->Append(_("03/11/2018"));
    ComboBox1->Append(_("04/11/2018"));
    ComboBox1->Append(_("05/11/2018"));
    ComboBox1->Append(_("06/11/2018"));
    ComboBox1->Append(_("07/11/2018"));
    ComboBox1->Append(_("08/11/2018"));
    ComboBox1->Append(_("09/11/2018"));
    ComboBox1->Append(_("10/11/2018"));
    ComboBox1->Append(_("11/11/2018"));
    ComboBox1->Append(_("12/11/2018"));
    ComboBox1->Append(_("13/11/2018"));
    ComboBox1->Append(_("14/11/2018"));
    ComboBox1->Append(_("15/11/2018"));
    ComboBox1->Append(_("16/11/2018"));
    ComboBox1->Append(_("17/11/2018"));
    ComboBox1->Append(_("18/11/2018"));
    ComboBox1->Append(_("19/11/2018"));
    ComboBox1->Append(_("20/11/2018"));
    ComboBox1->Append(_("21/11/2018"));
    ComboBox1->Append(_("22/11/2018"));
    ComboBox1->Append(_("23/11/2018"));
    ComboBox1->Append(_("24/11/2018"));
    ComboBox1->Append(_("25/11/2018"));
    ComboBox1->Append(_("26/11/2018"));
    ComboBox1->Append(_("27/11/2018"));
    ComboBox1->Append(_("28/11/2018"));
    ComboBox1->Append(_("29/11/2018"));
    ComboBox1->Append(_("30/11/2018"));
    ComboBox1->Append(_("-December-"));
    ComboBox1->Append(_("01/12/2018"));
    ComboBox1->Append(_("02/12/2018"));
    ComboBox1->Append(_("03/12/2018"));
    ComboBox1->Append(_("04/12/2018"));
    ComboBox1->Append(_("05/12/2018"));
    ComboBox1->Append(_("06/12/2018"));
    ComboBox1->Append(_("07/12/2018"));
    ComboBox1->Append(_("08/12/2018"));
    ComboBox1->Append(_("09/12/2018"));
    ComboBox1->Append(_("10/12/2018"));
    ComboBox1->Append(_("11/12/2018"));
    ComboBox1->Append(_("12/12/2018"));
    ComboBox1->Append(_("13/12/2018"));
    ComboBox1->Append(_("14/12/2018"));
    ComboBox1->Append(_("15/12/2018"));
    ComboBox1->Append(_("16/12/2018"));
    ComboBox1->Append(_("17/12/2018"));
    ComboBox1->Append(_("18/12/2018"));
    ComboBox1->Append(_("19/12/2018"));
    ComboBox1->Append(_("20/12/2018"));
    ComboBox1->Append(_("21/12/2018"));
    ComboBox1->Append(_("22/12/2018"));
    ComboBox1->Append(_("23/12/2018"));
    ComboBox1->Append(_("24/12/2018"));
    ComboBox1->Append(_("25/12/2018"));
    ComboBox1->Append(_("26/12/2018"));
    ComboBox1->Append(_("27/12/2018"));
    ComboBox1->Append(_("28/12/2018"));
    ComboBox1->Append(_("29/12/2018"));
    ComboBox1->Append(_("30/12/2018"));
    ComboBox1->Append(_("31/12/2018"));
    FlexGridSizer2->Add(ComboBox1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel1);
    FlexGridSizer2->SetSizeHints(Panel1);
    FlexGridSizer1->Add(Panel1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    SetSizer(FlexGridSizer1);
    Layout();

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalendarFrame::OnBtn_BackClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&CalendarFrame::OnBtn_NextClick);
    Panel1->Connect(wxEVT_PAINT,(wxObjectEventFunction)&CalendarFrame::OnPanel1Paint,0,this);
    //*)
}

CalendarFrame::~CalendarFrame()
{
    //(*Destroy(CalendarFrame)
    //*)
}

void CalendarFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void CalendarFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

wxDateTime my;
wxDateTime leapOrNLeap;

int month = my.GetCurrentMonth() + 1; // Gets the current moth
int year = my.GetCurrentYear(); // Gets the current year
int weekDay = -1; // Gets weekday
int counter = 1; // Counts the weeks

wxString date;
wxString months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                     "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
wxString yearToStr = wxString::Format(wxT("%i"), year);

void CalendarFrame::OnPanel1Paint(wxPaintEvent& event)
{
    wxPaintDC p(this);
    wxClientDC dc(this);

    TextCtrl1->SetValue(months[month - 1] + "/" + yearToStr);

    //Draw calendar
    DrawCalendarFrame(p);

    // Draw day of the week
    DrawDaysOfWeek(dc);

    //Draw days of the month
    DrawDays(dc, month);

}

/* Draws the weekdays in calendar frame */
void DrawDaysOfWeek(wxClientDC& dc)
{
    wxColour txtR(wxT("RED"));
    wxColour txtBl(wxT("BLUE"));

    int posXFDW = 17;
    wxString dayOfWeek[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

    for(int k = 0; k < 7; k++)
    {
        if(k == 5 || k == 6)
        {
            // Set color RED for Saturday and Sunday
            dc.SetTextForeground(txtR);
        }
        else
        {
            // Set color BLACK for the rest of the days
            dc.SetTextForeground(txtBl);
        }

        dc.DrawText(dayOfWeek[k], posXFDW, 52);
        posXFDW += 40;
    }
}

/* Draws the frame for calendar */
void DrawCalendarFrame(wxPaintDC& p)
{
    wxPen pen(*wxBLACK, 2);

    p.SetPen(pen);
    p.DrawRectangle(13, 47, 281, 211);

    // Draw Horizontal Lines
    int y = 77;

    for(int j = 0; j < 6; j++)
    {
        if(j == 0)
        {
            wxPen pen2(*wxBLACK, 2);
            p.SetPen(pen2);
        }
        else
        {
            wxPen pen2(*wxBLACK, 1);
            p.SetPen(pen2);
        }

        p.DrawLine(13, y, 292, y);
        y += 30;
    }

    //Draw Vertical Lines
    int x = 53;

    for(int i  = 0; i < 6; i++)
    {
        p.DrawLine(x, 47, x,257);
        x += 40;
    }
}

/* Returns 0-Sunday, 1-Monday, 2-Tuesday, 3-Wednesday, 4-Thursday, 5-Friday, 6-Saturday.
   Also 1 <= m <= 12,  y > 1752, 1 <= d <= 31  for the algorithm here to work correctly*/
int DayOfWeek(int y, int m, int d)
{
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

/* Checks if counter is equal to 6 and if it is the counter is reset to 1 */
bool IsLastWeekOfMonth(int &c)
{
    if(c == 6) return true;
}

/* Draws days on screen */
void DrawDays(wxClientDC& dc, int m)
{
    wxColour txtBc(wxT("BLACK"));
    wxColour txtR(wxT("RED"));

    // 31 days months
    if(m == 1 || m == 3 || m == 5 || m == 7
                  || m == 8 || m == 10 || m == 12)
    {
        for(int i = 0; i < 31; i++)
        {
            weekDay = DayOfWeek(year, m, month31[i]);

            if(weekDay == 0)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 260, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 260, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 260, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 260, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 260, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 300, 237);
                }
                counter++;
            }
            if(weekDay == 1)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 23, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 23, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 23, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 23, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 23, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 23, 237);
                }

            }
            if(weekDay == 2)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 63, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 63, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 63, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 63, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 63, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 63, 237);
                }
            }
            if(weekDay == 3)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 103, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 103, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 103, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 103, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 103, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 103, 237);
                }
            }
            if(weekDay == 4)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 143, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 143, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 143, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 143, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 143, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 143, 237);
                }
            }
            if(weekDay == 5)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 183, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 183, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 183, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 183, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 183, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 183, 237);
                }
            }
            if(weekDay == 6)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 223, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 223, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 223, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 223, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 223, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month31[i]);

                    dc.DrawText(dayToTxt, 223, 237);
                }
            }
        }
    }

    // 30 days months
    else if(m == 4 || m == 6 || m == 9 || m == 11)
    {
        for(int i = 0; i < 30; i++)
        {
            weekDay = DayOfWeek(year, m, month30[i]);

            if(weekDay == 0)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 260, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 260, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 260, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 260, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 260, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 300, 237);
                }
                counter++;
            }
            if(weekDay == 1)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 23, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 23, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 23, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 23, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 23, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 23, 237);
                }

            }
            if(weekDay == 2)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 63, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 63, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 63, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 63, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 63, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 63, 237);
                }
            }
            if(weekDay == 3)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 103, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 103, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 103, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 103, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 103, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 103, 237);
                }
            }
            if(weekDay == 4)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 143, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 143, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 143, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 143, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 143, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 143, 237);
                }
            }
            if(weekDay == 5)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 183, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 183, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 183, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 183, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 183, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 183, 237);
                }
            }
            if(weekDay == 6)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 223, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 223, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 223, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 223, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 223, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month30[i]);

                    dc.DrawText(dayToTxt, 223, 237);
                }
            }
        }
    }

    // February
    else
    {
        if(leapOrNLeap.IsLeapYear())
        {
            for(int i = 0; i < 29; i++)
            {
                weekDay = DayOfWeek(year, m, month29[i]);

            if(weekDay == 0)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 260, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 260, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 260, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 260, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 260, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 300, 237);
                }
                counter++;
            }
            if(weekDay == 1)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 23, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 23, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 23, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 23, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 23, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 23, 237);
                }

            }
            if(weekDay == 2)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 63, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 63, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 63, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 63, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 63, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 63, 237);
                }
            }
            if(weekDay == 3)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 103, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 103, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 103, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 103, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 103, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 103, 237);
                }
            }
            if(weekDay == 4)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 143, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 143, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 143, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 143, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 143, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 143, 237);
                }
            }
            if(weekDay == 5)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 183, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 183, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 183, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 183, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 183, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 183, 237);
                }
            }
            if(weekDay == 6)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 223, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 223, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 223, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 223, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 223, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month29[i]);

                    dc.DrawText(dayToTxt, 223, 237);
                }
            }
            }
        }
        else
        {
            for(int i = 0; i < 28; i++)
            {
                weekDay = DayOfWeek(year, m, month28[i]);

            if(weekDay == 0)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 260, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 260, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 260, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 260, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 260, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 300, 237);
                }
                counter++;
            }
            if(weekDay == 1)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 23, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 23, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 23, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 23, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 23, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 23, 237);
                }

            }
            if(weekDay == 2)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 63, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 63, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 63, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 63, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 63, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 63, 237);
                }
            }
            if(weekDay == 3)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 103, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 103, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 103, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 103, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 103, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 103, 237);
                }
            }
            if(weekDay == 4)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 143, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 143, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 143, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 143, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 143, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 143, 237);
                }
            }
            if(weekDay == 5)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 183, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 183, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 183, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 183, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 183, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 183, 237);
                }
            }
            if(weekDay == 6)
            {
                if(counter == 1)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 223, 87);
                }
                if(counter == 2)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 223, 117);
                }
                if(counter == 3)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 223, 147);
                }
                if(counter == 4)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 223, 177);
                }
                if(counter == 5)
                {
                    dc.SetTextForeground(txtR);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 223, 207);
                }
                if(counter == 6)
                {
                    dc.SetTextForeground(txtBc);

                    wxString dayToTxt = wxString::Format(wxT("%i"), month28[i]);

                    dc.DrawText(dayToTxt, 223, 237);
                }
            }
            }
        }
    }

    if(IsLastWeekOfMonth(counter)) counter = 1; // If counter == 5 set counter back 1
}

/* Converts the date to string */
void DateToStr(wxString& date)
{
    wxDateTime dt = wxDateTime::Now();
    date = dt.FormatISODate();
}

void CalendarFrame::OnBtn_BackClick(wxCommandEvent& event)
{
    if(month > 1)
    {
        --month;
        TextCtrl1->SetValue(months[month - 1] + "/" + yearToStr);
    }
}

void CalendarFrame::OnBtn_NextClick(wxCommandEvent& event)
{
    if(month < 12)
    {
        ++month;
        TextCtrl1->SetValue(months[month - 1] + "/" + yearToStr);
    }
}
