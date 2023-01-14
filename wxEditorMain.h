/***************************************************************
 * Name:      wxEditorMain.h
 * Purpose:   Defines Application Frame
 * Author:    Lisette Hawkins (lhawk012@fiu.edu)
 * Created:   2022-09-12
 * Copyright: Lisette Hawkins ()
 * License:
 **************************************************************/

#ifndef WXEDITORMAIN_H
#define WXEDITORMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wxEditorApp.h"

class wxEditorFrame: public wxFrame
{
    public:
        wxEditorFrame(wxFrame *frame, const wxString& title);
        ~wxEditorFrame();
    private:
        enum
        {
            idMenuQuit = 1000,
            idMenuAbout,
            idMenuOpen,
            idMenuSave,
            ID_TextBox
        };
        wxTextCtrl* textControl;
        wxFileDialog* saveDialog;
        wxFileDialog* openDialog;

        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOpen (wxCommandEvent& event);
        void OnSave (wxCommandEvent& event);
        DECLARE_EVENT_TABLE()
};


#endif // WXEDITORMAIN_H
