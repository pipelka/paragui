#ifndef PG_NOTEBOOK_H
#define PG_NOTEBOOK_H

#include "pgwidget.h"
#include "pgtabbar.h"
#include <map>

class PG_NoteBook;

typedef PG_Signal2<PG_NoteBook*, PG_Widget*> PG_PageSelect;
typedef Slot1<bool, PG_Widget*> PG_PageSelectSlot;

class PG_NoteBook : public PG_Widget {
public:
	
	typedef enum {
		top,
		bottom
	} TabBarPos;
	
	PG_NoteBook(PG_Widget* parent, const PG_Rect& r, TabBarPos pos = top, int BarHeight = 33, const char* style="TabBar");
	
	~PG_NoteBook();
		
	void AddPage(const char* text, PG_Widget* page);

	void AddPage(const char* text, PG_Widget* page, PG_PageSelectSlot slot);
	
	PG_Widget* CreatePage(const char* text);

	PG_Widget* CreatePage(const char* text, PG_PageSelectSlot slot);
	
	inline int GetChildCount() {
		return my_tabBar->GetChildCount();
	}
	
	PG_PageSelect sigPageSelect;
	
protected:
	
	void eventSizeWidget(Uint16 w, Uint16 h);
	
	bool handleTabSelect(PG_Button* button);
	
	PG_TabBar* my_tabBar;
	
	TabBarPos my_barPos;
	
	PG_Rect my_clientRect;
	
	std::map<PG_Button*, PG_Widget*> my_pageMap;
	std::map<PG_Widget*, PG_PageSelectSlot> my_slotMap;
	
	PG_Widget* my_activePage;
};

#endif // PG_NOTEBOOK_H
