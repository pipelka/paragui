#ifndef PG_TABBAR_H
#define PG_TABBAR_H

#include "pgthemewidget.h"
#include "pgwidgetlistex.h"
#include "pgbutton.h"

class PG_TabBar;
typedef Signal1<bool, PG_Button*> PG_SignalTabRemove;

class PG_TabBar : public PG_Widget {
public:
	
	PG_TabBar(PG_Widget* parent, const PG_Rect r, const char* style = "TabBar");
	~PG_TabBar();
	
	PG_Button* AddTab(const char* text, int id = -1);

	PG_Button* AddTab(const char* text, PG_TabSelectSlot slot, int id = -1);
	
	bool RemoveTab(PG_Button* tab);
	
	bool SelectNext();
	
	bool SelectPrev();
	
	PG_Button* FindTab(int index);
	
	PG_Button* FindTab(const char* text);
	
	int FindIndex(PG_Button* tab);
	
	inline int GetChildCount() {
		return my_tabList->GetChildCount();
	}
	
	PG_SignalTabSelect sigTabSelect;
	PG_SignalTabRemove sigTabRemove;
	
protected:
	
	void eventSizeWidget(Uint16 w, Uint16 h);
	
	bool handleTabClick(PG_Button* button);
	
	bool handleTabNav(PG_Button* button);
	
	PG_Button* my_selectedTab;
	
	PG_WidgetListEx* my_tabList;
	PG_Button* my_btnPrev;
	PG_Button* my_btnNext;
	
	std::string my_style;
};

#endif // PG_TABBAR_H
