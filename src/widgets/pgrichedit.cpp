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
   Update Date:      $Date: 2002/05/28 12:37:31 $
   Source File:      $Source: /sources/paragui/paragui/src/widgets/pgrichedit.cpp,v $
   CVS/RCS Revision: $Revision: 1.3.6.1 $
   Status:           $State: Exp $
*/


#include "pgapplication.h"
#include "pgrichedit.h"
#include "pglog.h"

const Uint32 PG_RichEdit::my_Marks[PG_RichEdit::MARKS_COUNT] = { ' ', 0x01, '\n', '\t', 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0xF
                                                               };
const Uint32 PG_RichEdit::my_FontBeginMark = 010;


PG_RichEdit::PG_RichEdit(PG_Widget* parent, const PG_Rect& r, bool autoVerticalResize, Uint32 linewidth, Uint32 tabSize, Uint32 childsborderwidth, const char* style) :
PG_WidgetListEx(parent, r, style) {

	EnableScrollBar(true, PG_SB_HORIZONTAL);

	my_listwidth = (linewidth != 0) ? linewidth : r.my_width;
	my_ChildsBorderWidth = childsborderwidth;

	//TO-DO : Value 5 is font size, witch is currently unknown ...
	my_objHorizontalScrollbar->SetLineSize(5);
	my_TabSize = tabSize;
	my_Align = my_Marks[PG_RichEdit::PG_TEXT_LEFT];
	my_AutoVerticalResize = autoVerticalResize;
}

void PG_RichEdit::UpdateScrollBarsPos() {
	PG_WidgetList::UpdateScrollBarsPos();

	//TO-DO : Value 5 is font size, witch is currently unknown ...
	my_objVerticalScrollbar->SetLineSize(5);
	my_objHorizontalScrollbar->SetLineSize(5);
}

void PG_RichEdit::eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst) {

	PG_WidgetListEx::eventBlit(srf, src, dst);

	RichLineArray::iterator line;

	for (line = my_RichText.begin(); line != my_RichText.end(); line++) {
		{
			RichLinePartArray::iterator linePart;

			for (linePart = line->my_LineParts.begin(); linePart != line->my_LineParts.end(); linePart++) {
				Size_tArray::iterator word;
				Uint32 width = 0;

				for (word = linePart->my_WordIndexes.begin(); word != linePart->my_WordIndexes.end(); word++) {
					int deltax = (my_objHorizontalScrollbar->IsVisible()) ? my_objHorizontalScrollbar->GetPosition() : 0;
					int deltay = (my_objVerticalScrollbar->IsVisible()) ? my_objVerticalScrollbar->GetPosition() : 0;

					PG_FontEngine::RenderText(my_srfScreen, dst, my_xpos - deltax + width + linePart->my_Left,  my_ypos + line->my_BaseLine - deltay, my_ParsedWords[*word].my_Word.c_str(), GetFont());
					width += my_ParsedWords[*word].my_WidthAfterFormating;
				}
			}
		}
		if ((Sint32)(line->my_BaseLine - my_objVerticalScrollbar->GetPosition() - line->my_LineSpace) >= Height())
			break;
	}
}

void PG_RichEdit::AddWidget(PG_Widget* w) {
	PG_WidgetListEx::AddWidget(w);
	CompleteLines();
}

bool PG_RichEdit::RemoveWidget(PG_Widget* w, bool shiftx, bool shifty) {
	bool result = PG_WidgetListEx::RemoveWidget(w, shiftx, shifty);
	CompleteLines();

	return result;
}

void PG_RichEdit::SetText(const std::string &text) {
	my_text = text;
	ParseWords();
	CompleteLines();
}

void PG_RichEdit::SetText(const char *text) {
	PG_Widget::SetText(text);
	ParseWords();
	CompleteLines();
}

void PG_RichEdit::ParseWords() {
	size_t searchFrom = 0;
	std::string word;

	my_ParsedWords.clear();

	do {
		RichWordDescription wordDescr;
		Uint16 w, h, sw = 0;
		int bl, ls;
		bool space = false;

		searchFrom = GetWord(searchFrom, &word, &wordDescr.my_EndMark);

		int length = word.length();
		if (length > 0) {
			if (word[length - 1] == ' ') {
				space = true;
				word.erase(length-1, 1);
			}
		}
		PG_FontEngine::GetTextSize(word.c_str(), GetFont(), &w, &h, &bl, &ls, NULL, NULL, NULL);
		wordDescr.my_Width = w;
		if (space) {
			word += ' ';
			PG_FontEngine::GetTextSize(" ", GetFont(), &sw);
		}
		wordDescr.my_Word = word;
		wordDescr.my_EndSpaceWidth = sw;
		wordDescr.my_WidthAfterFormating = w + sw;
		wordDescr.my_Height = h;
		wordDescr.my_BaseLine = bl;
		wordDescr.my_LineSkip = ls;

		my_ParsedWords.push_back(wordDescr);

		if ((searchFrom != std::string::npos) && (searchFrom < my_text.length()))
			searchFrom++;
		else
			break;
	} while (true);
}

size_t PG_RichEdit::GetWord(size_t searchFrom, std::string *word, Uint32 *endMark) {
	size_t ik, length = my_text.length(), result = std::string::npos;

	*endMark = my_Marks[MARK_SPACE];

	if (searchFrom >= my_text.length()) {
		return std::string::npos;
	}

	for (ik = searchFrom; ik < length; ik++) {
		for (Uint32 jk = 0; jk < MARKS_COUNT; jk++) {
			if ((Uint32)my_text[ik] == my_Marks[jk]) {
				*endMark = my_Marks[jk];
				result = ik;
				jk = MARKS_COUNT;
				ik = length;
			}
		}
	}

	if (result != std::string::npos) {
		size_t increment = 1;

		if ((Uint32)my_text[result] != my_Marks[MARK_SPACE])
			increment = 0;
		*word = my_text.substr(searchFrom, result - searchFrom + increment);
		
		if ((Uint32)my_text[result] == my_Marks[MARK_NONBREAKABLE_SPACE]) {
			std::string newword;

			*word += " ";
			result = GetWord(result + 1, &newword, endMark);
			*word += newword;
		}
	} else {
		*word = my_text.substr(searchFrom);
	}

	return result;
}

Sint32 PG_RichEdit::CompleteLines() {
	my_RichText.clear();

	if (my_text.length() == 0)
		return 0;

	Uint32 lineSpace = 0;
	Sint32 top = 0;
	size_t searchFrom = 0;
	bool changeAlign = false;

	do {
		Uint32 lineAscent = 0;
		Uint32 lineSpaceOld = lineSpace;
		size_t searchFromOld = searchFrom;

		RichLineArray::iterator actualLine = my_RichText.insert(my_RichText.end(), RichLine(top));

		searchFrom = CompleteLine(actualLine, top, searchFrom, lineSpace, lineAscent, changeAlign);

		if (lineSpace != lineSpaceOld) {
			my_RichText.erase(actualLine);
			searchFrom = searchFromOld;
			changeAlign = true;
		} else {
			actualLine->my_BaseLine += lineAscent;

			actualLine->my_LineSpace = lineSpace;
			top += lineSpace;
			lineSpace = 0;
			changeAlign = false;
		}

	} while(searchFrom < my_ParsedWords.size());

	if (top > (Sint32)my_listheight) {
		my_listheight = top;
	}

	if (my_AutoVerticalResize) {
		SizeWidget(my_width, my_listheight);
	}

	CheckScrollBars();
	UpdateScrollBarsPos();
	Update();

	return top;
}

size_t PG_RichEdit::CompleteLine(RichLineArray::iterator actualLine, Sint32 &lineTop, size_t searchFrom, Uint32 &lineSpace, Uint32 &lineAscent, bool changeAlign) {
	bool breakLine = false;

	Sint32 linePartLeft = 0, linePartWidthMax = my_listwidth;
	WidgetMap widgetsOnLine;

	Uint32 align = my_Align;

	GetWidgetsOnLine(lineTop, lineSpace, widgetsOnLine, true);

	WidgetMap::iterator childOnLine = widgetsOnLine.begin();

	if ((align == my_Marks[MARK_ALL_LEFT]) || (align == my_Marks[MARK_ALL_CENTER]) || (align == my_Marks[MARK_ALL_RIGHT])) {
		size_t size;
		Uint32 maxHeight = lineSpace;

		do {
			WidgetMap::iterator widget;

			for (widget = widgetsOnLine.begin(); widget != widgetsOnLine.end(); widget++) {
				PG_Point coord = ScreenToClient(widget->second->my_xpos, widget->second->my_ypos);
				if (widget->second->my_height > maxHeight)
					maxHeight = widget->second->my_height;
				//align widgets to line top
				widget->second->MoveWidget(coord.x, lineTop);
			}
			for (widget = widgetsOnLine.begin(); widget != widgetsOnLine.end(); widget++) {
				//align widgets to line bottom
				PG_Point coord = ScreenToClient(widget->second->my_xpos, widget->second->my_ypos);
				widget->second->MoveWidget(coord.x, coord.y + maxHeight - widget->second->my_height);
				coord = ScreenToClient(widget->second->my_xpos, widget->second->my_ypos);
				lineTop = (coord.y + widget->second->my_height) - lineSpace;
			}
			size = widgetsOnLine.size();
			GetWidgetsOnLine(lineTop, maxHeight, widgetsOnLine, false);
		} while (size != widgetsOnLine.size());

		actualLine->my_BaseLine = lineTop;

		childOnLine = widgetsOnLine.begin();
	}

	do {
		linePartWidthMax = my_listwidth - linePartLeft;
		if (childOnLine != widgetsOnLine.end())
			linePartWidthMax = childOnLine->first - linePartLeft;
		RichLinePartArray::iterator actualLinePart = actualLine->my_LineParts.insert(actualLine->my_LineParts.end(), RichLinePart(linePartLeft, linePartWidthMax));

		searchFrom = CompleteLinePart(searchFrom, lineTop, lineSpace, actualLine, actualLinePart, breakLine, lineAscent, changeAlign);
		if (childOnLine == widgetsOnLine.end())
			break;

		if ((align == my_Marks[MARK_TEXT_LEFT]) || (align == my_Marks[MARK_TEXT_CENTER]) || (align == my_Marks[MARK_TEXT_RIGHT]) || (align == my_Marks[MARK_TEXT_BLOCK])) {
			PG_Point coord = ScreenToClient(childOnLine->second->my_xpos, childOnLine->second->my_ypos);

			if (coord.y >= lineTop) {
				childOnLine->second->MoveWidget(coord.x, lineTop);
			}
		}

		linePartLeft = childOnLine->first + childOnLine->second->my_width + (2 * my_ChildsBorderWidth);
		childOnLine++;
	} while ((searchFrom < my_ParsedWords.size()) && (breakLine == false));

	AlignLine(actualLine, widgetsOnLine, align);


	return searchFrom;
}

void PG_RichEdit::AlignLine(RichLineArray::iterator actualLine, WidgetMap &widgetsOnLine, Uint32 align) {
	if ((align == my_Marks[MARK_ALL_LEFT]) || (align == my_Marks[MARK_ALL_CENTER]) || (align == my_Marks[MARK_ALL_RIGHT])) {
		WidgetMap::iterator widget;
		RichLinePartArray::iterator linePart;
		Sint32 lineWidth = 0, delta = 0;

		for (linePart = actualLine->my_LineParts.begin(); linePart < actualLine->my_LineParts.end(); linePart++) {
			Sint32 width = linePart->Width(my_ParsedWords);

			if (((Sint32)linePart->my_Left + width) > lineWidth)
				lineWidth = linePart->my_Left + width;
		}
		for (widget = widgetsOnLine.begin(); widget != widgetsOnLine.end(); widget++) {
			PG_Point coord = ScreenToClient(widget->second->my_xpos, widget->second->my_ypos);

			if ((coord.x + widget->second->my_width) > lineWidth)
				lineWidth = coord.x + widget->second->my_width;
		}

		if (align == my_Marks[MARK_ALL_CENTER])
			delta = (my_listwidth / 2) - (lineWidth / 2);
		else if (align == my_Marks[MARK_ALL_RIGHT])
			delta = my_listwidth - lineWidth;

		if (align != my_Marks[MARK_ALL_LEFT]) {
			for (linePart = actualLine->my_LineParts.begin(); linePart < actualLine->my_LineParts.end(); linePart++) {
				linePart->my_Left += delta;
			}
			for (widget = widgetsOnLine.begin(); widget != widgetsOnLine.end(); widget++) {
				PG_Point coord = ScreenToClient(widget->second->my_xpos, widget->second->my_ypos);

				widget->second->MoveWidget(coord.x + delta, coord.y);
			}
		}
	}
}

Sint32 PG_RichEdit::CompleteLinePart(size_t searchFrom, Sint32 lineTop, Uint32 &lineSpace, RichLineArray::iterator actualLine, RichLinePartArray::iterator actualLinePart, bool &breakLine, Uint32 &lineAscent, bool changeAlign) {
	breakLine = false;

	Sint32 w = 0, h = 0, ls = 0, lb = 0;
	Sint32 lineWidth = 0;

	int align = my_Align;

	bool linePartEnd = false;

	while ((!linePartEnd) && (!breakLine)) {
		Uint32          oldFind = searchFrom, tabSize = 0;

		w = my_ParsedWords[searchFrom].my_Width + my_ParsedWords[searchFrom].my_EndSpaceWidth;
		h = my_ParsedWords[searchFrom].my_Height;
		lb = my_ParsedWords[searchFrom].my_BaseLine;
		ls = my_ParsedWords[searchFrom].my_LineSkip;

		if (my_ParsedWords[searchFrom].my_EndMark == my_Marks[MARK_ENTER]) {
			breakLine = true;
		} else if (my_ParsedWords[searchFrom].my_EndMark == my_Marks[MARK_TAB]) {
			if (my_TabSize > 0) {
				tabSize = my_TabSize - ((actualLinePart->my_Left + lineWidth + w) % my_TabSize);
				w += tabSize;
			}
		} else if ((my_ParsedWords[searchFrom].my_EndMark == my_Marks[MARK_TEXT_LEFT]   ||
		            my_ParsedWords[searchFrom].my_EndMark == my_Marks[MARK_TEXT_CENTER] ||
		            my_ParsedWords[searchFrom].my_EndMark == my_Marks[MARK_TEXT_RIGHT]  ||
		            my_ParsedWords[searchFrom].my_EndMark == my_Marks[MARK_TEXT_BLOCK]) &&
		           (my_ParsedWords[searchFrom].my_EndMark != my_Align)) {
			if (changeAlign) {
				my_Align = my_ParsedWords[searchFrom].my_EndMark;
				if ((lineWidth + w) > 0)    //if align change mark is not first character on the line part
				{
					linePartEnd = true;
				} else {
					align = my_Align;
				}
			}
		} else if ((my_ParsedWords[searchFrom].my_EndMark == my_Marks[MARK_ALL_LEFT]   ||
		            my_ParsedWords[searchFrom].my_EndMark == my_Marks[MARK_ALL_CENTER] ||
		            my_ParsedWords[searchFrom].my_EndMark == my_Marks[MARK_ALL_RIGHT]) &&
		           (my_ParsedWords[searchFrom].my_EndMark != my_Align)) {
			if (changeAlign) {
				my_Align = my_ParsedWords[searchFrom].my_EndMark;
				breakLine = true;
			}
		}

		if ((lineWidth + w) > actualLinePart->my_WidthMax) {
			if (my_ParsedWords[searchFrom].my_EndSpaceWidth > 0) {
				w = my_ParsedWords[searchFrom].my_Width;
			} else if (my_ParsedWords[searchFrom].my_EndMark == my_Marks[MARK_TAB]) {
				w -= tabSize;
			}
			linePartEnd = true;
		}

		lineWidth += w;

		if (lineWidth > actualLinePart->my_WidthMax) {
			my_Align = align;
			breakLine = false;
			searchFrom = oldFind - 1;

			if (actualLinePart->my_WordIndexes.size() == 0) {
				//searchFrom++;
				lineSpace = my_ParsedWords[searchFrom + 1].my_LineSkip;
			}
			linePartEnd = true;
		} else {
			if ((my_ParsedWords[searchFrom].my_Word.length() > 0) || (tabSize > 0)) {
				if ((Uint32)ls > lineSpace)
					lineSpace = ls;
				if ((Uint32)lb > lineAscent)
					lineAscent = lb;

				actualLinePart->my_WordIndexes.push_back(searchFrom);
				my_ParsedWords[searchFrom].my_WidthAfterFormating = w;
			}
		}
		if (++searchFrom >= my_ParsedWords.size())
			linePartEnd = true;
	}

	//remove last space character in last word
	Sint32 nwords = actualLinePart->my_WordIndexes.size();

	if (nwords > 0)
		my_ParsedWords[actualLinePart->my_WordIndexes[nwords - 1]].my_WidthAfterFormating = my_ParsedWords[actualLinePart->my_WordIndexes[nwords - 1]].my_Width;

	AlignLinePart(actualLinePart, align, breakLine);
	return searchFrom;
}

void PG_RichEdit::AlignLinePart(RichLinePartArray::iterator actualLinePart, Uint32 align, bool breakLine) {
	Uint32 width = 0;

	if ((align == my_Marks[PG_TEXT_CENTER]) || (align == my_Marks[PG_TEXT_RIGHT]) || (align == my_Marks[PG_TEXT_BLOCK])) {
		width = actualLinePart->Width(my_ParsedWords);

		if (align == my_Marks[PG_TEXT_CENTER])
			actualLinePart->my_Left += (actualLinePart->my_WidthMax / 2) - (width / 2);
		else if (align == my_Marks[PG_TEXT_RIGHT])
			actualLinePart->my_Left += actualLinePart->my_WidthMax - width;
		else if (align == my_Marks[PG_TEXT_BLOCK]) {
			if (!breakLine) {
				Sint32 nwords = actualLinePart->my_WordIndexes.size();

				if (nwords > 1) {
					Uint32 addToSpace = (actualLinePart->my_WidthMax - width) / (nwords - 1);
					Sint32 rest = (actualLinePart->my_WidthMax - width) % (nwords - 1);

					for (Sint32 ik = 0, jk = 0; ik < (nwords - 1); ik++) {
						my_ParsedWords[actualLinePart->my_WordIndexes[ik]].my_WidthAfterFormating += (addToSpace + (jk++ < rest));
					}
				}
			}
		}
	}
}

void PG_RichEdit::GetWidgetsOnLine(Sint32 lineTop, Uint32 lineHeight, WidgetMap &widgetsOnLine, bool clear) {
	std::vector<PG_Widget*>::iterator child;

	if (clear)
		widgetsOnLine.clear();

	for (child = my_widgetList.begin(); child < my_widgetList.end(); child++) {
		PG_Point coord = ScreenToClient((*child)->my_xpos, (*child)->my_ypos);

		if ((lineTop < (coord.y + (*child)->my_height)) && ((lineTop + (Sint32)lineHeight) >= coord.y)) {
			bool insert = true;

			if (!clear) {
				WidgetMap::iterator header;

				for (header = widgetsOnLine.begin(); header != widgetsOnLine.end(); header++) {
					if (*child == header->second) {
						insert = false;
						break;
					}
				}
			}
			if (insert) {
				widgetsOnLine.insert(WidgetMap::value_type(coord.x - my_ChildsBorderWidth, *child));
			}
		}
	}
}

bool PG_RichEdit::ProcessLongLine(std::string &word, size_t &searchFrom, Uint32 oldFind, Sint32 lineTop, Uint32 &lineSpace, bool normalLine, RichLineArray::iterator actualLine, RichLinePartArray::iterator actualLinePart, Uint32 &lineAscent) {
	/*Sint32          w = 0, h = 0, ls = 0, la = 0;
	PG_FontParam    newFont; 
	PG_FontParam    CurFont = my_font;

	WidgetMap widgetsOnLine;
	   
	for (size_t ik = 0; ik < word.length(); ik++) 
{                            
	    if (word[ik] == my_FontBeginMark)        
	    {
	    ik += CurFont.FormatTagProc(&word[ik], 0);
	    }
	    
	    std::string newword = word.substr(0, ((ik == std::string::npos) ? ik : ik + 1));           
	    PG_FontEngine::GetTextSize(newword.c_str(), GetFont(), &w, &h, &la, &ls, NULL, NULL, NULL);

	    if (w > (Sint32)my_listwidth)
	    {                                                                                                         
	        if (normalLine) 
	        {                                        
	            GetWidgetsOnLine(lineTop + lineSpace, lineSpace, widgetsOnLine, true);
	            
	            if (widgetsOnLine.size() > 0)
	            {
	                searchFrom = oldFind - 1;                                                                 
	                return false;
	            }
	        }
	        else my_RichText.erase(actualLine);
	        newword = word.substr(0, ik);                        
	        PG_FontEngine::GetTextSize(newword.c_str(), GetFont(), &w, &h, &la, &ls, NULL, NULL, NULL);
	        actualLine = my_RichText.insert(my_RichText.end(), RichLine(lineTop));            
	        actualLinePart = actualLine->my_LineParts.insert(actualLine->my_LineParts.end(), RichLinePart(0, my_listwidth));
	        actualLinePart->my_Left = 0;                    
	        actualLinePart->my_Words.push_back(RichWordDescription(newword, (Uint32)w));               
	        *defaultFont = newFont;            
	                    
	        if ((Uint32)ls > lineSpace) lineSpace = ls;
	        if ((Uint32)la > lineAscent) lineAscent = la;

	        if (searchFrom == my_text.npos) searchFrom = my_text.length() - 1;                                                        
	        searchFrom -= (word.length() - ik);  
	        break;            
	    }  
}    */
	return true;
}

bool PG_RichEdit::LoadText(const char* textfile) {
	PG_DataContainer* text = PG_FileArchive::ReadFile(textfile);
	
	if(text == NULL) {
		return false;
	}
	
	text->data()[text->size()] = 0;
	SetText(text->data());
	
	delete text;
	return true;
}
