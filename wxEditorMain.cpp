/***************************************************************
 * Name:      wxEditorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Lisette Hawkins (lhawk012@fiu.edu)
 * Created:   2022-09-12
 * Copyright: Lisette Hawkins ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "wxEditorMain.h"

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
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
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

BEGIN_EVENT_TABLE(wxEditorFrame, wxFrame)
    EVT_CLOSE(wxEditorFrame::OnClose)
    EVT_MENU(idMenuQuit, wxEditorFrame::OnQuit)
    EVT_MENU(idMenuAbout, wxEditorFrame::OnAbout)
    EVT_MENU(idMenuOpen, wxEditorFrame::OnOpen)
    EVT_MENU(idMenuSave, wxEditorFrame::OnSave)
END_EVENT_TABLE()

wxEditorFrame::wxEditorFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
#if wxUSE_MENUS
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuOpen, _("&Open\tAlt-F5"),_("Open a file"));
    fileMenu->Append(idMenuSave, _("&Save\tAlt-F3"),_("Save a file"));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
    mbar->Append(fileMenu, _("&File"));

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
    mbar->Append(helpMenu, _("&Help"));

    SetMenuBar(mbar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(1);
    // SetStatusText(_("Hello Code::Blocks user!"),0);
    // SetStatusText(wxbuildinfo(short_f), 1);
    SetStatusText("Hello its " + wxDateTime::Now().Format("%c using" + wxbuildinfo(short_f)),0);
#endif // wxUSE_STATUSBAR


 textControl = new wxTextCtrl(this, ID_TextBox,
 wxT(""), wxDefaultPosition, wxDefaultSize,
 wxTE_MULTILINE | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);
}


wxEditorFrame::~wxEditorFrame()
{
}

void wxEditorFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void wxEditorFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void wxEditorFrame::OnAbout(wxCommandEvent &event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void wxEditorFrame::OnSave(wxCommandEvent &event)
{
    wxFileDialog *saveDialog = new wxFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""),
        wxT("Text Files (*.txt)|*.txt|C++ Files (*.cpp)|*.cpp|Header Files (*.h)|*.h"),
        wxFD_SAVE );
    int response = saveDialog->ShowModal(); //get response from the dialog
    if(response == wxID_OK)
    { //if response ok, then load contents into textControl
        this->textControl->SaveFile(saveDialog->GetPath());
    }
}

void wxEditorFrame::OnOpen(wxCommandEvent &event)
{
    wxFileDialog *openDialog = new wxFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""),
        wxT("Text Files (*.txt)|*.txt|C++ Files (*.cpp)|*.cpp|Header Files (*.h)|*.h"),
        wxFD_OPEN );
    int response = openDialog->ShowModal(); //get response from the dialog
    if(response == wxID_OK)
    { //if response ok, then load contents into textControl
        this->textControl->LoadFile(openDialog->GetPath());
    }


}
