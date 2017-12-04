#pragma once

#include "App.h"

class View : public wxPanel
{
public:
    View(wxFrame *parent);
    ~View(); // Viewはベースクラスとして使うことはないのでvirtualはつけない
    void OnPaint(wxPaintEvent &event);
    void OnEraseBackground(wxEraseEvent &event);
    void OnTimer(wxTimerEvent &event);
    void Stop();
    void Start();
    bool SetPicture(cv::Mat &mat);

    cv::VideoCapture *m_p_cap;
    unsigned char *m_p_picture;
    int m_width;
    int m_height;
    bool m_is_display;
    wxTimer *m_timer;
};

