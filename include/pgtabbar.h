#ifndef PG_TABBAR_H
#define PG_TABBAR_H

#include "pgthemewidget.h"
#include "pgwidgetlistex.h"
#include "pgbutton.h"

class PG_TabBar : public PG_Widget {
public:
	
	PG_TabBar(PG_Widget* parent, const PG_Rect r, const char* style = "TabBar");
	~PG_TabBar();
	
	PG_Button* AddTab(const char* text);

	PG_Button* AddTab(const char* text, PG_TabSelectSlot slot);
	
	PG_SignalTabSelect sigTabSelect;
	
protected:
	
	void eventSizeWidget(Uint16 w, Uint16 h);
	
	bool handleTabClick(PG_Button* button);
	
	bool handleTabNav(PG_Button* button);
	
	PG_Button* my_selectedTab;
	
	PG_WidgetListEx* my_tabList;
	PG_Button* my_btnPrev;
	PG_Button* my_btnNext;
	
};

#endif // PG_TABBAR_H
