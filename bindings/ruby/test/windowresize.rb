# resize internally before showing

require 'paragui'

include Paragui

app = PG_Application.new
app.LoadTheme "default"
app.InitScreen(640, 480, 0, 0)

a = PG_Window.new(nil, PG_Rect.new(10, 10, 100, 100), "Window 98, the most reliable window yet.")
b = PG_Window.new(nil, PG_Rect.new(60, 110, 100, 100), "Window XP, .")

a.SizeWidget(400, 200)
b.SizeWidget(400, 200)

a.Show
b.Show

app.Run
