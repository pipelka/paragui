#include <pgapplication.h>
#include <pgwindow.h>
#include <pglineedit.h>
#include <pgbutton.h>
#include <iostream>


class MyDialog : public PG_Window {
    public:
        MyDialog();

        bool ok_clicked();

        PG_LineEdit* e;
        PG_Button* ok;
};

MyDialog::MyDialog() : PG_Window(0, PG_Rect(0, 0, 200, 200), "test", MODAL) {
        e = new PG_LineEdit(this, PG_Rect(0, 25, 200, 20));
        ok = new PG_Button(this, PG_Rect(10, 100, 180, 20));

        ok->sigClick.connect(slot(*this, &MyDialog::ok_clicked));
}

bool MyDialog::ok_clicked() {
	QuitModal();
	return true;
}

int main(int argc, char** argv) {
	PG_Application app;
	app.SetEmergencyQuit(true);
	
	if (!app.LoadTheme("default", true, "../dat")) {
		std::cerr << "Unable to load theme!" << std::endl;
		exit(-1);
	}
	
	app.SetFontSize(14);

	if (!app.InitScreen(300, 300, 16, 0)) {
		std::cerr << "Couldn't initialize X Windowing System\n";
		exit(1);
	}

	MyDialog md;
	md.Show();
	md.RunModal();
	md.Hide();

	app.Run();

	return 0;
}
