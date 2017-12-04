#include "App.h"
#include "MainFrame.h"
#include "View.h"
#include <iostream>



View::View(wxFrame *parent) : wxPanel(parent, ID_VIEW, wxPoint(0, 0), wxSize(640, 480))
{
    m_p_cap = NULL;
    m_p_picture = NULL;
    m_width = 640;
    m_height = 480;
    m_is_display = false;
    m_timer = new wxTimer(this, -1);
    Connect(wxEVT_TIMER, wxTimerEventHandler(View::OnTimer));
    Connect(wxEVT_PAINT, wxPaintEventHandler(View::OnPaint));
    //Connect(wxEVT_ERASE_BACKGROUND, wxEraseEventHandler(View::OnEraseBackground));
}

View::~View()
{
    delete m_timer;
}

void View::OnPaint(wxPaintEvent &event)
{
    // カメラ接続中であるかチェック
    if (!m_is_display)
    {
        return;
    }

    // カメラから1フレームの絵を取得
    cv::Mat capture;
    *m_p_cap >> capture;

    // Mat型の絵からunsinged charで絵を取得
    bool ret = SetPicture(capture);
    if (!ret)
    {
        wxPuts(wxT("Error: can't get picture data."));
        return;
    }

    // 画面に描画できる形式に変換
    // trueで使用画像データをwxImageデストラクタで解放しない
    //wxImage image(m_width, m_height, capture.data, true);
    wxImage image(m_width, m_height, m_p_picture, true);
    wxBitmap current_capture(image);

    // 描画
    wxBufferedPaintDC dc(this);
    dc.DrawBitmap(current_capture, wxPoint(0, 0));
}

void View::OnTimer(wxTimerEvent &event)
{
    // false: wxEVT_ERASE_BACKGROUNDをさせない
    Refresh(false);
}

// カメラを切断する
void View::Stop()
{
    if (m_is_display)
    {
        m_timer->Stop();
        m_is_display = false;
        delete m_p_cap;
        delete[] m_p_picture;
    }
    Refresh();
}

// カメラに接続する
void View::Start()
{
    if (m_is_display)
    {
        // 既に接続済みは、いったん解放
        m_is_display = false;
        delete m_p_cap;
        delete[] m_p_picture;

    }

    m_p_cap = new cv::VideoCapture(0);
    //カメラデバイスが正常にオープンしたか確認
    if (!m_p_cap->isOpened())
    {
        wxPuts(wxT("Camera Open Error!"));
        delete m_p_cap;
        return;
    }

    m_p_picture = new unsigned char[m_width * m_height * 3];

    wxPuts(wxT("Camera Open Success!"));
    m_is_display = true;

    // 親のMainFrame(wxFrame)にサイズ変更するように通知
    ((MainFrame*)GetParent())->SetSize(wxSize(m_width, m_height));

    // 1000/30ms(30fps)でパラパラ漫画開始
    m_timer->Start(1000 / 30);
}

// Mat型の画像データよりunsigned charで画像データを取得する
bool View::SetPicture(cv::Mat &mat)
{
    // 正しく画像取得できているかチェック
    if (mat.rows != m_height) return false;
    if (mat.cols != m_width) return false;

    // 取得先の領域が確保されているかチェック
    if (NULL == m_p_picture) return false;

    // 画像を変換
    // MatはBGRの順に格納されているので、RGBに直す
    for (int i = 0; i < m_width * m_height * 3 - 2; i += 3)
    {
        // MatはBGRの順に格納されているのでRGBの順に並べなおす
        m_p_picture[i] = mat.data[i + 2];
        m_p_picture[i + 1] = mat.data[i + 1];
        m_p_picture[i + 2] = mat.data[i];
    }
    return true;
}

void View::OnEraseBackground(wxEraseEvent &event)
{
    // 何もしない
}