# TODO find out why this crashes on exit

require 'paragui'

include Paragui

$counter = 1

def populate(list)
  10.times do
    list.AddItem PG_ListBoxItem.new(25, "Item#{$counter}")
    $counter += 1
  end
end

app = PG_Application.new
app.LoadTheme "default"
app.InitScreen(640, 480, 0, 0)
app.SetEmergencyQuit(true)

lb = PG_ListBox.new nil, PG_Rect.new(10,10,300,100)
# this is how we set a callback
lb.set_rbcallback MSG_SELECTITEM, proc {|id, widget, item| 
  # inspect the data
  puts "#{id}, #{item} #{widget.type}"
  widget.DeleteAll
  populate widget
  widget.Update
  true
}
populate lb
lb.Show

app.Run
