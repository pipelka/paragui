#include <SDL.h>
#include <paragui.h>
#include <pgapplication.h>
#include <pgthemewidget.h>
#include <pgwindow.h>
#include <iostream>

class CentralWidget : public PG_ThemeWidget {
public:
    CentralWidget(PG_Widget *parent, const PG_Rect &rect);
    virtual ~CentralWidget();
    virtual void eventMouseLeave();
private:
    PG_ThemeWidget *innerWidget;
};

CentralWidget::CentralWidget(PG_Widget *parent, const PG_Rect &rect) : PG_ThemeWidget(parent, rect) {
    innerWidget = new PG_ThemeWidget(this, PG_Rect(rect.w / 2 - 40, rect.h / 2 - 10, 80, 20));
    innerWidget->SetBorderSize(1);
    innerWidget->Show(false);
}

CentralWidget::~CentralWidget() {
    RemoveAllChilds();
}

void CentralWidget::eventMouseLeave() {
    std::cout << "eventMouseLeave triggered" << std::endl;
    innerWidget->Hide(); // this will set off an infinite loop
}

int main(int argc, char* argv[]) {
   putenv("SDL_VIDEO_CENTERED=\"\"");
   
   PG_Application app;

   if (!app.LoadTheme("default") || !app.InitScreen(800, 600, 32, SDL_SWSURFACE | SDL_NOFRAME)) {
       std::cout << "error, aborting" << std::endl;
       return EXIT_FAILURE;
   }

   PG_Window window(NULL, PG_Rect(0, 0, 800, 600), "Infinite Loop Application", PG_Window::DEFAULT);
   CentralWidget centralWidget(&window, PG_Rect(200, 100, 400, 400));
   centralWidget.SetBorderSize(1);
   centralWidget.Show(false);
   window.Show(false);
   SDL_WarpMouse(centralWidget.my_xpos + 20, centralWidget.my_ypos + 20);
   window.RunModal();
   return EXIT_SUCCESS;
}
