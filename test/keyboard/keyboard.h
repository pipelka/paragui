/***************************************************************************
                          keyboard.h  -  description
                             -------------------
    begin                : Wed Jul 3 2002
    copyright            : (C) 2002 by Dr. H.C.T.
    email                : hct@tin.it
 ***************************************************************************/

#ifndef _KEYBOARD
#define _KEYBOARD

#include "pglabel.h"
#include "pgbutton.h"
#include "pglineedit.h"
#include <string>

class TKey_LineEdit : public PG_LineEdit
{
 private:
	unsigned int nReturnValue;
	bool bFirst;
	std::string InitialText;
 protected:
 	virtual bool SendKey(PG_Button* pWidget);
 	virtual void eventInputFocusLost(PG_MessageObject*);
	PG_Label* pKeyboardSpace;
	PG_LineEdit* pDisplay;
 	
 	virtual void eventEditBegin(int,PG_Widget*,unsigned long,void*);
 	virtual void eventEditEnd(int,PG_Widget*,unsigned long,void*);
 public:
 	// note: field limit set to 100 by default
	TKey_LineEdit(PG_Widget* pParent,const PG_Rect& r,const char* style="LineEdit",int maximumLength=100);
	// creates the keyboard. This function must be separated because if we
	// create buttons in constructor we cannot use "this" as the parent
	void Init(void);
	// this assigns the initial text
	void SetText(const char* Text) { InitialText = Text; PG_LineEdit::SetText(Text); pDisplay->SetText(Text); }
	// retrieves a value BTN_ID_YES or BTN_ID_NO depending on the button
	// pressed to close the keyboard
	unsigned int getReturnValue(void) { return nReturnValue; };
};

/*
	A PG_LineEdit that can be changed through a resizable QWERTY virtual keyboard. Implements
	a numeric keyboard with	dot, minus sign, backspace, clear, cancel and confirmation.
	
	This class could be useful if one needs to insert a text on a keyboardless
	machine with a touch-screen (e.g. an ATM or an industrial machine).
*/
class TKeyAlpha_LineEdit : public TKey_LineEdit
{
 private:
	PG_Button* Buttons[43];
	unsigned int nReturnValue;
	std::string InitialText;
 public:
	TKeyAlpha_LineEdit(PG_Widget* pParent,const PG_Rect& r,const char* style="LineEdit",int maximumLength=1000000);
	// creates the keyboard. This function must be separated because if we
	// create buttons in constructor we cannot use "this" as the parent
	void Init(void);
};

/*
	A PG_LineEdit that can be changed through a resizable virtual keyboard. Implements
	a numeric keyboard with	dot, minus sign, backspace, clear, cancel and confirmation.
	
	This class could be useful if one needs to insert a text on a keyboardless
	machine with a touch-screen (e.g. an ATM or an industrial machine).
*/
class TKeyNum_LineEdit : public TKey_LineEdit
{
 private:
	PG_Button* Buttons[16];
 protected:
	// adjusts field: an incoming "0" field is converted into empty
 	virtual void eventEditBegin(int,PG_Widget*,unsigned long,void*);
	// adjusts field: an outgoing empty field is converted into a "0"
 	virtual void eventEditEnd(int,PG_Widget*,unsigned long,void*);
 public:
	TKeyNum_LineEdit(PG_Widget* pParent,const PG_Rect& r,const char* style="LineEdit",int maximumLength=1000000);
	// creates the keyboard. This function must be separated because if we
	// create buttons in constructor we cannot use "this" as the parent
	void Init(void);
};

#endif
