#include "App.h"
#include "MainFrame.h"
#include "View.h"

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, APP_TITLE)
{
    // メニュー作成
    m_menubar = new wxMenuBar();
    m_control = new wxMenu();

    // メニュー：ファイルの項目にアイテムを追加
    m_control->AppendCheckItem(ID_CAMERA_CONNECT, wxT("&Connect"));
    m_control->Append(wxID_EXIT, wxT("&Exit"));

    //// 作成したメニューをウィンドウの貼り付け
    m_menubar->Append(m_control, wxT("&Control"));
    SetMenuBar(m_menubar);

    // メニュークリック時の呼び出される関数の関連付け
    Connect(ID_CAMERA_CONNECT, wxEVT_MENU, wxCommandEventHandler(MainFrame::OnConnect));
    Connect(wxID_EXIT, wxEVT_MENU, wxCommandEventHandler(MainFrame::OnExit));
    // 終了時、ウィンドウ閉じるとき
    Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MainFrame::OnClose));

    //// 映像表示部の作成
    m_view = new View(this);
    // wxPanelを継承したコンストラクタではなぜか色設定できないのでここで設定
    m_view->SetBackgroundColour(wxColour(wxT("#000000")));

    Centre();
}

void MainFrame::OnConnect(wxCommandEvent &event)
{
    if (m_view->m_is_display)
    {
        // チェックが入っているときは接続→切断にする
        m_view->Stop();
    }
    else
    {
        // チェックが入っていないときは切断→接続する
        m_view->Start();
    }
}

void MainFrame::OnExit(wxCommandEvent &event)
{
    // CloseによりwxEVT_CLOSEのイベントハンドラでonCloseがコールされる
    Close(true);
}

void MainFrame::OnClose(wxCloseEvent &event)
{
    // Stopで
    // ビデオキャプチャオブジェクトの解放と
    // キャプチャした画像領域の解放をする。
    // さらにDestroyでMainFrameは削除されるが、
    // その前に、子のViewが削除される
    m_view->Stop();
    Destroy();
}