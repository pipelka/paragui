
#ifndef PG_SCROLLAREA_H
#define PG_SCROLLAREA_H

#include "pgwidget.h"
#include "pgpoint.h"

class PG_ScrollArea : public PG_Widget {
public:

	class SignalAreaChangedHeight : public PG_Signal2<PG_ScrollArea*, Uint16> {};
	class SignalAreaChangedWidth : public PG_Signal2<PG_ScrollArea*, Uint16> {};

	PG_ScrollArea(PG_Widget* parent, const PG_Rect& r = PG_Rect::null);
	~PG_ScrollArea();

	void SetShiftOnRemove(bool shiftx, bool shifty);

	void ScrollTo(Uint16 x, Uint16 y);

	inline void SetAreaWidth(Uint16 w) {
		my_area.w = w;
	}

	inline void SetAreaHeight(Uint16 h) {
		my_area.h = h;
	}

	inline Uint16 GetAreaWidth() {
		return my_area.w;
	};

	inline Uint16 GetAreaHeight() {
		return my_area.h;
	};

	/**
	Remove all widgets from the list (without deletion)
	*/
	void RemoveAll();

	/**
	Delete (destroy) all widgets in the list
	*/
	void DeleteAll();

	/**
	Get the number of widgets in the list
	*/
	Uint16 GetWidgetCount();

	Uint16 GetScrollPosX();

	Uint16 GetScrollPosY();

	SignalAreaChangedHeight sigAreaChangedHeight;
	SignalAreaChangedWidth sigAreaChangedWidth;

	void AddChild(PG_Widget* child);

protected:

	bool RemoveChild(PG_Widget* child);

	PG_Rect my_area;
	bool my_shiftx;
	bool my_shifty;
};

#endif // PG_SCROLLAREA_H
