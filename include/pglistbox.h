/*
    ParaGUI - crossplatform widgetset
    Copyright (C) 2000,2001,2002  Alexander Pipelka
 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
 
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
 
    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 
    Alexander Pipelka
    pipelka@teleweb.at
 
    Last Update:      $Author: braindead $
    Update Date:      $Date: 2003/11/21 12:27:52 $
    Source File:      $Source: /sources/paragui/paragui/include/pglistbox.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.2.2.1 $
    Status:           $State: Exp $
*/

#ifndef PG_LISTBOX_H
#define PG_LISTBOX_H

#ifdef SWIG
%include "swigcommon.h"
%module pglistbox
%{
#include "pglistbox.h"
    %}
#endif

#include "pgwidgetlist.h"
#include "pglistboxitem.h"

/**
	@author Alexander Pipelka
	
	@short A scrollable box that can hold any number of text items
*/

class DECLSPEC PG_ListBox : public PG_WidgetList {
public:

	/**
	Signal type declaration
	**/
	template<class datatype = PG_Pointer> class SignalSelectItem : public PG_Signal1<PG_ListBoxBaseItem*, datatype> {};

	/** */
	PG_ListBox(PG_Widget* parent, const PG_Rect& r, const char* style="ListBox");

	/** */
	~PG_ListBox();

	/** */
	void AddItem(PG_ListBoxBaseItem* item);

	/** */
	void SetMultiSelect(bool multi = true);

	/** */
	bool GetMultiSelect();

	/** */
	PG_ListBoxBaseItem* GetSelectedItem();

	/** */
	void SelectItem(PG_ListBoxBaseItem* item, bool select = true);

	/* */
	void SelectFirstItem();

	/* */
	void SelectNextItem();

	/* */
	void SelectPrevItem();

	/**
	Remove all widgets from the list (without deletion)
	*/
	void RemoveAll();

	/**
	Delete (destroy) all widgets in the list
	*/
	void DeleteAll();

	/**
	Set the item indentation
	@param	indent		number of pixels for item indentation (must be set before adding items)
	*/
	void SetIndent(int indent);

	/**
	Returns the index of the last selected item
	*/
	int GetSelectedIndex();

	void GetSelectedItems(std::vector<PG_ListBoxBaseItem*>& items);

	SignalSelectItem<> sigSelectItem;

protected:

	/** */
	virtual bool eventSelectItem(PG_ListBoxBaseItem* item);

	/** */
	bool eventMouseButtonUp(const SDL_MouseButtonEvent* button);

	/** */
	bool eventMouseButtonDown(const SDL_MouseButtonEvent* button);

	/** */
	bool eventMouseMotion(const SDL_MouseMotionEvent* motion);

	friend class PG_ListBoxBaseItem;
	
private:

	void AddWidget(PG_Widget* w);

	bool my_multiselect;
	int my_indent;
	int my_selectindex;

	PG_ListBoxBaseItem* my_selectedItem;

};

#endif	// PG_LISTBOX_H
