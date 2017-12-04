#pragma once

#include "App.h"
#include "View.h"

class MainFrame : public wxFrame
{
public:
    MainFrame();
    wxMenuBar *m_menubar;
    wxMenu *m_control;
    View *m_view;

    void OnConnect(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnClose(wxCloseEvent &event);
};
