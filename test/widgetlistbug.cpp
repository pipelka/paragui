#include <pgapplication.h>
#include <pgbutton.h>
#include <pgwidgetlist.h>
#include <pglabel.h>

PARAGUI_CALLBACK(exit_handler) {
    PG_Application* app = (PG_Application*) clientdata;
    app->Quit();
    return true;
}

PARAGUI_CALLBACK(show_handler) {
    PG_WidgetList* list = (PG_WidgetList*) clientdata;
    //list->SetVisible(true);
    //list->Update();
    list->Show();
    std::cerr << "Show" << std::endl;
    return true;
}

PARAGUI_CALLBACK(hide_handler) {
    PG_WidgetList* list = (PG_WidgetList*) clientdata;
    //list->SetVisible(false);
    //list->Update();
    list->Hide();
    std::cerr << "Hide" << std::endl;
    return true;
}

PARAGUI_CALLBACK(add_handler) {
    PG_WidgetList* list = (PG_WidgetList*) clientdata;
    PG_Label* label=new PG_Label(NULL, PG_Rect(0,0,200,100), "Blubber Bla Bla");
    //label->Show();
    list->AddWidget(label);
    std::cerr << "Add" << std::endl;
    return true;
}


int main(int argc, char* argv[]) {
    PG_Application app;
    app.LoadTheme("default");
    app.InitScreen(640, 480, 16, SDL_SWSURFACE);

    PG_Button myButton(NULL,1,PG_Rect(260, 100, 120, 50),"Exit!");
    myButton.SetEventCallback(MSG_BUTTONCLICK, exit_handler, &app);
    myButton.Show();

    PG_WidgetList list(NULL,PG_Rect(10,10,150,150));
    list.EnableScrollBar(true, PG_SB_VERTICAL);
    list.SetTransparency(0);
    list.Show();

    PG_Button myButtonHide(NULL,1,PG_Rect(260, 0, 120, 50),"Hide!");
    myButtonHide.SetEventCallback(MSG_BUTTONCLICK, hide_handler, &list);
    myButtonHide.Show();

    PG_Button myButtonShow(NULL,1,PG_Rect(260, 50, 120, 50),"Show!");
    myButtonShow.SetEventCallback(MSG_BUTTONCLICK, show_handler, &list);
    myButtonShow.Show();

    PG_Button myButtonAdd(NULL,1,PG_Rect(260, 150, 120, 50),"Add!");
    myButtonAdd.SetEventCallback(MSG_BUTTONCLICK, add_handler, &list);
    myButtonAdd.Show();

    app.Run();
    return 0;
}
