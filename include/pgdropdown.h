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
    Update Date:      $Date: 2002/04/15 13:22:31 $
    Source File:      $Source: /sources/paragui/paragui/include/pgdropdown.h,v $
    CVS/RCS Revision: $Revision: 1.1 $
    Status:           $State: Exp $
*/

/** \file pgdropdown.h
	Header file of the PG_DropDown class.
*/

#ifndef PG_DROPDOWN_H
#define PG_DROPDOWN_H

#ifdef SWIG
%include "swigcommon.h"
%module pgdropdown
%{
#include "pgdropdown.h"
%}
#endif

#include "pgbutton.h"
#include "pglineedit.h"
#include "pglistbox.h"
#include "pglistboxitem.h"
#include "pgeventobject.h"

/**
	@author Alexander Pipelka
	
	@short A edit / dropdown combo item
 
	Basically a PG_LineEdit widget but with a button to show a dropdown list with
	predefined entries.
*/

class DECLSPEC PG_DropDown : public PG_Widget, public PG_EventObject {
public:

	/**
	Construct a PG_DropDown object.
	@param parent pointer to the parent of the widget of NULL
	@param id id of the widget
	@param r position of the widget
	@param style style of the widget (loaded from the theme)
	*/
	PG_DropDown(PG_Widget* parent, int id, const PG_Rect& r, const char* style="DropDown");

	/**  */
	~PG_DropDown();

	/** */
	void LoadThemeStyle(const char* style);

	/**
	Add a new item to the dropdown box
	@param text text of the new item
	@param userdata pointer to userdefined data linked to the item.
	*/
	void AddItem(const char* text, void* userdata = NULL);

	/**
	Remove all widgets from the drop down(without deletion)
	*/
	void RemoveAll();

	/**
	Delete (destroy) all widgets from the drop down
	*/
	void DeleteAll();

	/**	Set the item indentation
	@param	indent		number of pixels for item indentation (must be set before adding items)
	*/
	void SetIndent(int indent);

	/**
	Set if the widget is editable by the user
	@param	edit		true - widget is editable / false - widget is read only
	*/
	void SetEditable(bool edit);

	/**
	Check if the widget is editable by the user
	@return			true - widget is editable / false - widget is read only
	*/
	bool GetEditable();

	/**
	Get the current text string
	@return			pointer to text string
	*/
	const char* GetText();

	/**
	Set the current text string
	@param	new_text	pointer to text string
	*/
	void SetText(const char* new_text);

	/** */
	bool ProcessEvent(const SDL_Event * event, bool bModal);

protected:

	/** */
	void eventShow();

	/** */
	void eventHide();

	/** */
	bool eventButtonClick (int id, PG_Widget* widget);

	/** */
	void eventSizeWidget(Uint16 w, Uint16 h);

	/** */
	void eventMoveWidget(int x, int y);

	/** */
	virtual bool eventSelectItem(PG_ListBoxBaseItem* item);

	PG_LineEdit* my_EditBox;
	PG_Button* my_DropButton;
	PG_ListBox* my_DropList;

	PARAGUI_CALLBACK(select_handler);
};

#endif	// PG_DROPDOWN_H
