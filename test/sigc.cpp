
#include "paragui.h"
#include "pgapplication.h"
#include "pgsignals.h"
#include "pglabel.h"

#include <string>

// create a custom class derived from SigC::Object
class MySigC : public virtual SigC::Object {
public:
    SigC::Signal1<bool, const std::string&> msg;
};

// MyLabel uses PG_Label (which has the bas class SigC::Object)
// and MySigC (also derived from SigC::Object)
class MyLabel : public PG_Label, public MySigC {
public:
    MyLabel(PG_Widget* parent, const PG_Rect& r) : PG_Label(parent, r, "") {
	msg.connect(slot(*this, &MyLabel::MySlot));
    };
    
    bool MySlot(const std::string& text) {
	SetText(text.c_str());
	return true;
    };
};

int main(int argc, char* argv[]) {
    PG_Application app;
    app.LoadTheme("default");
    
    app.InitScreen(640, 480, 0);
    app.SetEmergencyQuit(true);
    
    MyLabel l(NULL, PG_Rect(50, 50, 300, 25));
    l.msg("test");
    l.Show();

    app.Run();
}
