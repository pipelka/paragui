#include <pgapplication.h>
#include <pgwindow.h>
#include <pglineedit.h>
#include <pgbutton.h>
#include <pgeventobject.h>

class MyDialog : public PG_Window, public PG_EventObject
{
    public:
        MyDialog();

        PARAGUI_CALLBACK(ok_clicked);

        PG_LineEdit* e;
        PG_Button* ok;
};

MyDialog::MyDialog()
    : PG_Window(0, PG_Rect(0, 0, 200, 200), "test", true)
{
            e = new PG_LineEdit(this, PG_Rect(0, 0, 200, 20));
            ok = new PG_Button(this, 0, PG_Rect(10, 100, 180, 20));

            ok->SetEventObject(MSG_BUTTONCLICK, this, (MSG_CALLBACK_OBJ)&MyDialog::ok_clicked);
}

PARAGUI_CALLBACK(MyDialog::ok_clicked)
{
    SendMessage(this, MSG_MODALQUIT, 0, 0);
}

int main(int argc, char** argv)
{
	PG_Application app;
	app.SetEmergencyQuit(true);
	
	if (!app.LoadTheme("default", true, "../dat"))
	{
        cerr << "Unable to load theme!" << endl;
        exit(-1);
	}
	
    app.SetFontSize(14);

	if (!app.InitScreen(300, 300, 16, 0))
	{
		cerr << "Couldn't initialize X Windowing System\n";
		exit(1);
	}

    if (1)
    {
        MyDialog md;
        md.Show();
        md.RunModal();
        md.Hide();
    }

    app.Run();

    return 0;
}
