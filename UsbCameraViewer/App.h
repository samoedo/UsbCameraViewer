#pragma once

#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <wx/event.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

#define APP_TITLE "USB Camera Viewer"

#define ID_CAMERA_CONNECT 101
#define ID_VIEW 102


class App : public wxApp
{
public:
    bool OnInit();
};

