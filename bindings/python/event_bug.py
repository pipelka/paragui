import sys
from paragui import *

class MyDialog(PG_Window, PG_EventObject):
    def __init__(self):
        PG_Window.__init__(self, None, PG_Rect(0, 0, 200, 200), "Test", 1)
        self.e = PG_LineEdit(self, PG_Rect(10, 40, 150, 20))
        self.ok = PG_Button(self, 0, PG_Rect(10, 100, 180, 20))
        self.ok.set_pymethod(MSG_BUTTONCLICK, self.okClicked)

    def okClicked(self, *args):
        print "okClicked:", self
        self.QuitModal()

app = PG_Application()
app.SetEmergencyQuit(1)

if not app.LoadTheme("default", 1, "../dat"):
    print "Unable to load theme!"
    sys.exit(-1)

app.SetFontSize(14)

if not app.InitScreen(300, 300, 16, 0):
    print "Couldn't initialize X Windowing System"
    sys.exit(1)

md = MyDialog()
md.Show()
md.RunModal()
md.Hide()

app.Run()
