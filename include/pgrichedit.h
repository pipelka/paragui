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
   Update Date:      $Date: 2003/06/29 17:09:49 $
   Source File:      $Source: /sources/paragui/paragui/include/pgrichedit.h,v $
   CVS/RCS Revision: $Revision: 1.3.6.4 $
   Status:           $State: Exp $
*/

#ifndef PG_RICHEDIT_H
#define PG_RICHEDIT_H

#include "paragui.h"
#include "pgwidgetlistex.h"
#include <map>

/**
	@author Jaroslav Vozab
	@short A optionay editable rich text flowing around child widgets.
	Generally used to make a large 'pane' of widgets and rich text that can be scrolled
	through in a smaller 'portal' with scrollbars.
*/

class DECLSPEC PG_RichEdit : public PG_WidgetListEx {
public:

	/**
	Constructor of the PG_WidgetListEx class
	*/
	PG_RichEdit(PG_Widget* parent, const PG_Rect& r, bool autoVerticalResize = false, Uint32 linewidth = 0, Uint32 tabSize = 30, Uint32 childsborderwidth = 8, const char* style="WidgetList");

	/**
	Sets rich text
	@param	text			rich text to set
	*/
	void SetText(const char *text);
	/**
	Sets rich text
	@param	text			rich text to set
	*/
	void SetText(const string &text);

	/**
	Add a widget to the list
	@param	w			pointer to a widget
	*/
	void AddWidget(PG_Widget* w);

	/**
	Remove a widget from the list
	@param	w			pointer to a widget
	*/

	bool RemoveWidget(PG_Widget* w, bool shiftx = false, bool shifty = false);

	//! Load the content of the widget from a text file
	/*!
	This function loads the text of the widget from a file. As ever this file operation is done transparently
	through PhysFS so you can place any text files into your theme and or file archives.
	\param textfile relative path to the text file
	*/
	bool LoadText(const char* textfile);
	
	void SetAutoVerticalResize(bool bResize);
	
	void SetAlignment(Uint8 align);

	void SetTabSize(Uint32 tabSize);

protected:

	/**
	*/
	void eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst);

	void UpdateScrollBarsPos();

	bool my_AutoVerticalResize;

	struct RichWordDescription {
		string my_Word;
		Uint32 my_Width;
		Uint32 my_EndSpaceWidth;
		Uint32 my_WidthAfterFormating;
		Uint32 my_Height;
		Uint32 my_BaseLine;
		Uint32 my_LineSkip;
		Uint32 my_EndMark;
	};

	typedef vector<RichWordDescription> RichWordDescriptionArray;

	RichWordDescriptionArray my_ParsedWords;

	typedef vector<size_t> Size_tArray;

	struct RichLinePart {
		Uint32 my_Left;
		Size_tArray my_WordIndexes;
		Sint32 my_WidthMax;

		RichLinePart(Uint32 left, Sint32 widthMax) {
			my_Left = left;
			my_WidthMax = widthMax;
		}

		Uint32 Width(RichWordDescriptionArray &parsedWords) {
			Size_tArray::iterator word;
			Uint32 width= 0;

			for (word = my_WordIndexes.begin(); word < my_WordIndexes.end(); word++) {
				width += parsedWords[*word].my_WidthAfterFormating;
			}

			return width;
		}
	};

	typedef vector<RichLinePart> RichLinePartArray;

	struct RichLine {
		Uint32 my_BaseLine;
		Uint32 my_LineSpace;
		RichLinePartArray my_LineParts;

		RichLine(Uint32 baseLine) {
			my_BaseLine = baseLine;
		}
	};

	typedef vector<RichLine> RichLineArray;

	RichLineArray my_RichText;

	Uint32 my_ChildsBorderWidth;

	Uint32 my_TabSize;

private:

	enum { MARK_SPACE, MARK_NONBREAKABLE_SPACE, MARK_ENTER, MARK_TAB,
	       MARK_TEXT_LEFT, MARK_TEXT_CENTER, MARK_TEXT_RIGHT, MARK_TEXT_BLOCK,
	       MARK_ALL_LEFT, MARK_ALL_CENTER, MARK_ALL_RIGHT,
	       MARKS_COUNT };

	static const Uint32 my_Marks[MARKS_COUNT];

	static const Uint32 my_FontBeginMark;

	Uint32 my_Align;

	string my_ActualFontName;

	typedef map<Sint32, PG_Widget*> WidgetMap;

	Sint32 CompleteLines();
	size_t CompleteLine(RichLineArray::iterator actualLine, Sint32 &lineTop, size_t searchFrom, Uint32 &lineSpace, Uint32 &lineAscent, bool changeAlign);
	Sint32 CompleteLinePart(size_t searchFrom, Sint32 lineTop, Uint32 &lineSpace, RichLineArray::iterator actualLine, RichLinePartArray::iterator actualLinePart, bool &breakLine, Uint32 &lineAscent, bool changeAlign);
	void GetWidgetsOnLine(Sint32 lineTop, Uint32 lineHeight, WidgetMap &widgetsOnLine, bool clear);
	bool ProcessLongLine(string &word, size_t &searchFrom, Uint32 oldFind, Sint32 lineTop, Uint32 &lineSpace, bool normalLine, RichLineArray::iterator actualLine, RichLinePartArray::iterator actualLinePart, Uint32 &lineAscent);
	size_t GetWord(size_t searchFrom, string *word, Uint32 *endMark);
	void AlignLinePart(RichLinePartArray::iterator actualLinePart, Uint32 align, bool breakLine);
	void AlignLine(RichLineArray::iterator actualLine, WidgetMap &widgetsOnLine, Uint32 align);
	void ParseWords();

public:

	enum {
	    PG_TEXT_LEFT   = MARK_TEXT_LEFT,
	    PG_TEXT_CENTER = MARK_TEXT_CENTER,
	    PG_TEXT_RIGHT  = MARK_TEXT_RIGHT,
	    PG_TEXT_BLOCK  = MARK_TEXT_BLOCK,
	    PG_ALL_LEFT    = MARK_ALL_LEFT,
	    PG_ALL_CENTER  = MARK_ALL_CENTER,
	    PG_ALL_RIGHT   = MARK_ALL_RIGHT
	};

private:
	void* my_internaldata;
};



#endif

