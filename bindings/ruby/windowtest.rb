require 'paragui'

include Paragui

class CMyWindow < PG_Window
  def initialize(parent, rect, text, flags, style="Window")
    super(parent, rect, text, flags, style)
  end
end

class CMyWidget < PG_ThemeWidget
  def initialize(parent, rect)
    super(parent, rect)
    mywindow = CMyWindow.new(self, PG_Rect.new(50,50,150,100), "Fenster", WF_DEFAULT)
    AddChild(mywindow)
  end
end

def init_app(app)
  app.SetEmergencyQuit true
  app.LoadTheme "default"
  app.InitScreen(800,600,0,0)
end

app = PG_Application.new
init_app(app)

def create_widgets
  mywidget = CMyWidget.new(nil, PG_Rect.new(200,200,350,250))
  mywidget.Show

  msgbox = PG_MessageBox.new nil, PG_Rect.new(200,50,240,200),
                            "Model Messagebox", 'Click "Ok" to close me',
                            PG_Rect.new(90,120,50,50), "Ok", 
                            PG_Rect.new(0,0,0,0), "", 
                            PG_TA_CENTER, "MessageBox"

  drop = PG_DropDown.new msgbox, 15, PG_Rect.new(5,60,200,25)
  drop.SetIndent 5
  drop.AddItem "Under Construction"
  3.times {|i| drop.AddItem "Item#{i}"}

  msgbox.Show
  msgbox.WaitForClick
  msgbox
end

(create_widgets).Hide

app.Run
# can't seem to delete app completely
