#include <pgapplication.h>
#include <pgwidget.h>
#include <pgdropdown.h>


int main()
{
    PG_Application app;
    app.LoadTheme("default");
    if (!app.InitScreen(500, 300, 16, 0))
        return -1;

    PG_Widget widget(0, PG_Rect(0, 0, 500, 300));

    PG_DropDown d(&widget, PG_Rect(20, 40, 200, 30));
    d.AddItem("test");
    d.AddItem("test2");

//    d.DeleteAll();
d.RemoveAll();

    d.AddItem("test");
    d.AddItem("test2");
    d.AddItem("test3");

    widget.Show();

    app.Run();
    
    return 0;
}
