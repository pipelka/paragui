/***************************************************************************
                          keyboard.cpp  -  description
                             -------------------
    begin                : Wed Jul 3 2002
    copyright            : (C) 2002 by Dr. H.C.T.
    email                : hct@tin.it
 ***************************************************************************/

#include "keyboard.h"
#include "pgapplication.h"

#define BTN_ID_CLEAR 0x8000000A
#define BTN_ID_BACKSPACE PG_Button::CANCEL
#define BTN_ID_CONFIRM PG_Button::YES
#define BTN_ID_ESCAPE PG_Button::NO

TKey_LineEdit::TKey_LineEdit(PG_Widget* pParent,const PG_Rect& r,const char* style,int maximumLength)
 : PG_LineEdit(pParent,r,style,maximumLength),nReturnValue(0),bFirst(true),InitialText("")
{
}
	
bool TKey_LineEdit::SendKey(PG_Button* pWidget)
{
	// this check is needed because, if the keyboard is superimposed to the
	// edited field, the keyboard captures a ButtonDown event that was not
	// intended for it.
	if (bFirst)
	{
		bFirst = false;
		if (PG_Rect::OverlapRect(*pWidget,*this))
			return false;
	}
	switch (pWidget->GetID())
	{
		case BTN_ID_CONFIRM:
			nReturnValue = PG_Button::YES;
			EditEnd();
			SetText(pDisplay->GetText());
			pKeyboardSpace->Hide();
			break;
		case BTN_ID_ESCAPE:
			nReturnValue = PG_Button::NO;
			SetText(InitialText.c_str());
			EditEnd();
			pKeyboardSpace->Hide();
			break;
		case BTN_ID_BACKSPACE:
			SendBackspace();
			pDisplay->SendBackspace();
			break;
		case BTN_ID_CLEAR:
			pDisplay->SetText("");
			PG_LineEdit::SetText("");
			break;
		default:
			pDisplay->SendChar(pWidget->GetText()[0]);
			PG_LineEdit::SendChar(pWidget->GetText()[0]);
			break;
	}
	return true;
}

void TKey_LineEdit::eventInputFocusLost(PG_MessageObject* p)
{
	nReturnValue = PG_Button::NO;
	PG_LineEdit::SetText(InitialText.c_str());
	EditEnd();
	PG_LineEdit::eventInputFocusLost(p);
}

void TKey_LineEdit::eventEditBegin(int id,PG_Widget* p,unsigned long l,void* data)
{
	pKeyboardSpace->Show();
	pDisplay->SetCursorPos(strlen(GetText()));
	SetCursorPos(strlen(GetText()));
	PG_LineEdit::eventEditBegin(id,p,l,data);
}
	
void TKey_LineEdit::eventEditEnd(int id,PG_Widget* w,unsigned long l,void* data)
{
	pKeyboardSpace->Hide();
	PG_LineEdit::eventEditEnd(id,w,l,data);
	bFirst = true;
}
	
	/////////////////////////
 // TKeyAlpha_LineEdit
/////////////////////////
TKeyAlpha_LineEdit::TKeyAlpha_LineEdit(PG_Widget* pParent,const PG_Rect& r,const char* style,int maximumLength)
 : TKey_LineEdit(pParent,r,style,maximumLength)
{
}

void TKeyAlpha_LineEdit::Init(void)
{
	int nSizeX = PG_Application::GetScreenWidth()/14;
	int nSizeY = nSizeX;
	int nOffsetX = nSizeX/2;

PG_TRY {
	pKeyboardSpace = new PG_Label(NULL,PG_Rect(30,30,nSizeX*12,nSizeY*6),"");
	/*
		Keyboard layout:
		
		  1 2 3 4 5 6 7 8 9 0 <-
		   Q W E R T Y U I O P
		  A S D F G H J K L del
  		 Z X C V B N M . -
		       SPACE     ok esc
		
		Also note:
			btn 39 = bck
			btn 40 = CANCEL = del
			btn 41 = OK
			btn 42 = NO = escape/close
	*/
	pDisplay = new PG_LineEdit(pKeyboardSpace,PG_Rect(0,0,nSizeX*11,nSizeY));
	// row 1
	Buttons[1] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*0,nSizeY,nSizeX,nSizeY),"1",1);
	Buttons[2] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*1,nSizeY,nSizeX,nSizeY),"2",2);
	Buttons[3] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*2,nSizeY,nSizeX,nSizeY),"3",3);
	Buttons[4] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*3,nSizeY,nSizeX,nSizeY),"4",4);
	Buttons[5] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*4,nSizeY,nSizeX,nSizeY),"5",5);
	Buttons[6] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*5,nSizeY,nSizeX,nSizeY),"6",6);
	Buttons[7] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*6,nSizeY,nSizeX,nSizeY),"7",7);
	Buttons[8] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*7,nSizeY,nSizeX,nSizeY),"8",8);
	Buttons[9] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*8,nSizeY,nSizeX,nSizeY),"9",9);
	Buttons[0] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*9,nSizeY,nSizeX,nSizeY),"0",0);
	Buttons[39] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*10,nSizeY,nSizeX,nSizeY),"<-",BTN_ID_BACKSPACE);
	// row 2
	Buttons[10] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*0,nSizeY*2,nSizeX,nSizeY),"Q",10);
	Buttons[11] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*1,nSizeY*2,nSizeX,nSizeY),"W",11);
	Buttons[12] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*2,nSizeY*2,nSizeX,nSizeY),"E",12);
	Buttons[13] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*3,nSizeY*2,nSizeX,nSizeY),"R",13);
	Buttons[14] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*4,nSizeY*2,nSizeX,nSizeY),"T",14);
	Buttons[15] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*5,nSizeY*2,nSizeX,nSizeY),"Y",15);
	Buttons[16] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*6,nSizeY*2,nSizeX,nSizeY),"U",16);
	Buttons[17] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*7,nSizeY*2,nSizeX,nSizeY),"I",17);
	Buttons[18] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*8,nSizeY*2,nSizeX,nSizeY),"O",18);
	Buttons[19] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*9,nSizeY*2,nSizeX,nSizeY),"P",19);
	// row 3
	Buttons[20] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*0,nSizeY*3,nSizeX,nSizeY),"A",20);
	Buttons[21] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*1,nSizeY*3,nSizeX,nSizeY),"S",21);
	Buttons[22] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*2,nSizeY*3,nSizeX,nSizeY),"D",22);
	Buttons[23] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*3,nSizeY*3,nSizeX,nSizeY),"F",23);
	Buttons[24] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*4,nSizeY*3,nSizeX,nSizeY),"G",24);
	Buttons[25] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*5,nSizeY*3,nSizeX,nSizeY),"H",25);
	Buttons[26] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*6,nSizeY*3,nSizeX,nSizeY),"J",26);
	Buttons[27] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*7,nSizeY*3,nSizeX,nSizeY),"K",27);
	Buttons[28] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*8,nSizeY*3,nSizeX,nSizeY),"L",28);
	// CANCEL mapped on DEL
	Buttons[40] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*9,nSizeY*3,nSizeX,nSizeY),"clr",BTN_ID_CLEAR);
	// row 4
	Buttons[29] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*0,nSizeY*4,nSizeX,nSizeY),"Z",29);
	Buttons[30] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*1,nSizeY*4,nSizeX,nSizeY),"X",30);
	Buttons[31] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*2,nSizeY*4,nSizeX,nSizeY),"C",31);
	Buttons[32] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*3,nSizeY*4,nSizeX,nSizeY),"V",32);
	Buttons[33] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*4,nSizeY*4,nSizeX,nSizeY),"B",33);
	Buttons[34] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*5,nSizeY*4,nSizeX,nSizeY),"N",34);
	Buttons[35] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*6,nSizeY*4,nSizeX,nSizeY),"M",35);
	Buttons[36] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*7,nSizeY*4,nSizeX,nSizeY),".",36);
	Buttons[37] = new PG_Button(pKeyboardSpace,PG_Rect(nOffsetX+nSizeX*8,nSizeY*4,nSizeX,nSizeY),"-",37);
	// SPACE
	Buttons[38] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*4,nSizeY*5,nSizeX*3,nSizeY)," ",38);
	Buttons[41] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*8,nSizeY*5,nSizeX,nSizeY),"ok",BTN_ID_CONFIRM);
	Buttons[42] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*9,nSizeY*5,nSizeX,nSizeY),"exit",BTN_ID_ESCAPE);
}

PG_CATCH_ALL {
}

	// registers callback
	for (int i = 0; i <= 42; i++)
		Buttons[i]->sigClick.connect(slot(*this, &TKeyAlpha_LineEdit::SendKey));
}

/////////////////////////
// TKeyNum_LineEdit
/////////////////////////
TKeyNum_LineEdit::TKeyNum_LineEdit(PG_Widget* pParent,const PG_Rect& r,const char* style,int maximumLength)
 : TKey_LineEdit(pParent,r,style,maximumLength)
{
}
	
void TKeyNum_LineEdit::Init(void)
{
	int nSizeY = PG_Application::GetScreenHeight()/9;
	int nSizeX = nSizeY;

PG_TRY {	
	pKeyboardSpace = new PG_Label(NULL,PG_Rect(30,30,nSizeX*5,nSizeY*5),"");
	/*
		Keyboard layout:
		
			7 8 9 <-
			4 5 6 clr
			1 2 3 esc
			0 . - ok
	*/
	pDisplay = new PG_LineEdit(pKeyboardSpace,PG_Rect(0,0,nSizeX*4,nSizeY));
	// row 1
	Buttons[7] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*0,nSizeY,nSizeX,nSizeY),"7",7);
	Buttons[8] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*1,nSizeY,nSizeX,nSizeY),"8",8);
	Buttons[9] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*2,nSizeY,nSizeX,nSizeY),"9",9);
	Buttons[12] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*3,nSizeY,nSizeX,nSizeY),"<-",BTN_ID_BACKSPACE);
	// row 2
	Buttons[4] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*0,nSizeY*2,nSizeX,nSizeY),"4",4);
	Buttons[5] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*1,nSizeY*2,nSizeX,nSizeY),"5",5);
	Buttons[6] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*2,nSizeY*2,nSizeX,nSizeY),"6",6);
	Buttons[13] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*3,nSizeY*2,nSizeX,nSizeY),"clr",BTN_ID_CLEAR);
	// row 3
	Buttons[1] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*0,nSizeY*3,nSizeX,nSizeY),"1",1);
	Buttons[2] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*1,nSizeY*3,nSizeX,nSizeY),"2",2);
	Buttons[3] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*2,nSizeY*3,nSizeX,nSizeY),"3",3);
	Buttons[14] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*3,nSizeY*3,nSizeX,nSizeY),"exit",BTN_ID_ESCAPE);
	// row 4
	Buttons[0] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*0,nSizeY*4,nSizeX,nSizeY),"0",0);
	Buttons[10] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*1,nSizeY*4,nSizeX,nSizeY),".",10);
	Buttons[11] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*2,nSizeY*4,nSizeX,nSizeY),"-",11);
	Buttons[15] = new PG_Button(pKeyboardSpace,PG_Rect(nSizeX*3,nSizeY*4,nSizeX,nSizeY),"ok",BTN_ID_CONFIRM);
}

PG_CATCH_ALL {
}	
	// registers callback
	for (int i = 0; i <= 15; i++)
		Buttons[i]->sigClick.connect(slot(*this, &TKeyNum_LineEdit::SendKey));
}

// adjusts field: an incoming "0" field is converted into empty
void TKeyNum_LineEdit::eventEditBegin(int id,PG_Widget* p,unsigned long l,void* data)
{
	if (atof(GetText()) == 0)
		pDisplay->SetText("");
	TKey_LineEdit::eventEditBegin(id,p,l,data);
}

// adjusts field: an outgoing empty field is converted into a "0"
void TKeyNum_LineEdit::eventEditEnd(int id,PG_Widget* p,unsigned long l,void* data)
{
	if (strlen(pDisplay->GetText()) == 0)
		SetText("0");
	TKey_LineEdit::eventEditEnd(id,p,l,data);
}
