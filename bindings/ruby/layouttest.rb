# test XML layout

require 'paragui'

include Paragui

app = PG_Application.new
app.EnableBackground true
app.LoadTheme "default"

if not app.InitScreen(800, 600, 0, 0)
  puts "Reesolution not supported!"
  exit
end

wnd = PG_Window.new nil, PG_Rect.new(0,0,400,300), "Test"
wnd.LoadLayout "pokus.xml"

sleep 2
wnd.Show

app.Run
