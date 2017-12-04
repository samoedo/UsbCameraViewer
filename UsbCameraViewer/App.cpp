#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Rpcrt4.lib")

#ifdef _DEBUG

#pragma comment(lib, "opencv_core2413d.lib")
#pragma comment(lib, "opencv_highgui2413d.lib")

#pragma comment(lib, "wxbase30ud.lib")
#pragma comment(lib, "wxmsw30ud_core.lib")
#pragma comment(lib, "wxzlibd.lib")
#pragma comment(lib, "wxpngd.lib")

#else

#pragma comment(lib, "opencv_core2413.lib")
#pragma comment(lib, "opencv_highgui2413.lib")

#pragma comment(lib, "wxbase30u.lib")
#pragma comment(lib, "wxmsw30u_core.lib")
#pragma comment(lib, "wxzlib.lib")
#pragma comment(lib, "wxpng.lib")

#endif

#include "App.h"
#include "MainFrame.h"

bool App::OnInit()
{
    MainFrame *main_frame = new MainFrame();
    main_frame->Show(true);
    return true;
}

IMPLEMENT_APP(App);
//IMPLEMENT_APP_CONSOLE(App);
