require 'paragui'

include Paragui

app = PG_Application.new
app.LoadTheme "default"
app.InitScreen(640, 480, 0, 0)

dd1 = PG_DropDown.new(nil, 1, PG_Rect.new(10,10,100,20))
dd2 = PG_DropDown.new(nil, 2, PG_Rect.new(120,10,100,20))

10.times {|i| dd1.AddItem "poop"; dd2.AddItem "yeah"}

dd1.Show
dd2.Show

app.Run
