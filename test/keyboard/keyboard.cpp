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
#define BTN_ID_BACKSPACE BTN_ID_CANCEL
#define BTN_ID_CONFIRM BTN_ID_YES
#define BTN_ID_ESCAPE BTN_ID_NO

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
			nReturnValue = BTN_ID_YES;
			EditEnd();
			SetText(pDisplay->GetText());
			pKeyboardSpace->Hide();
			break;
		case BTN_ID_ESCAPE:
			nReturnValue = BTN_ID_NO;
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
	nReturnValue = BTN_ID_NO;
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
	Buttons[1] = new PG_Button(pKeyboardSpace,1,PG_Rect(nSizeX*0,nSizeY,nSizeX,nSizeY),"1");
	Buttons[2] = new PG_Button(pKeyboardSpace,2,PG_Rect(nSizeX*1,nSizeY,nSizeX,nSizeY),"2");
	Buttons[3] = new PG_Button(pKeyboardSpace,3,PG_Rect(nSizeX*2,nSizeY,nSizeX,nSizeY),"3");
	Buttons[4] = new PG_Button(pKeyboardSpace,4,PG_Rect(nSizeX*3,nSizeY,nSizeX,nSizeY),"4");
	Buttons[5] = new PG_Button(pKeyboardSpace,5,PG_Rect(nSizeX*4,nSizeY,nSizeX,nSizeY),"5");
	Buttons[6] = new PG_Button(pKeyboardSpace,6,PG_Rect(nSizeX*5,nSizeY,nSizeX,nSizeY),"6");
	Buttons[7] = new PG_Button(pKeyboardSpace,7,PG_Rect(nSizeX*6,nSizeY,nSizeX,nSizeY),"7");
	Buttons[8] = new PG_Button(pKeyboardSpace,8,PG_Rect(nSizeX*7,nSizeY,nSizeX,nSizeY),"8");
	Buttons[9] = new PG_Button(pKeyboardSpace,9,PG_Rect(nSizeX*8,nSizeY,nSizeX,nSizeY),"9");
	Buttons[0] = new PG_Button(pKeyboardSpace,0,PG_Rect(nSizeX*9,nSizeY,nSizeX,nSizeY),"0");
	Buttons[39] = new PG_Button(pKeyboardSpace,BTN_ID_BACKSPACE,PG_Rect(nSizeX*10,nSizeY,nSizeX,nSizeY),"<-");
	// row 2
	Buttons[10] = new PG_Button(pKeyboardSpace,10,PG_Rect(nOffsetX+nSizeX*0,nSizeY*2,nSizeX,nSizeY),"Q");
	Buttons[11] = new PG_Button(pKeyboardSpace,11,PG_Rect(nOffsetX+nSizeX*1,nSizeY*2,nSizeX,nSizeY),"W");
	Buttons[12] = new PG_Button(pKeyboardSpace,12,PG_Rect(nOffsetX+nSizeX*2,nSizeY*2,nSizeX,nSizeY),"E");
	Buttons[13] = new PG_Button(pKeyboardSpace,13,PG_Rect(nOffsetX+nSizeX*3,nSizeY*2,nSizeX,nSizeY),"R");
	Buttons[14] = new PG_Button(pKeyboardSpace,14,PG_Rect(nOffsetX+nSizeX*4,nSizeY*2,nSizeX,nSizeY),"T");
	Buttons[15] = new PG_Button(pKeyboardSpace,15,PG_Rect(nOffsetX+nSizeX*5,nSizeY*2,nSizeX,nSizeY),"Y");
	Buttons[16] = new PG_Button(pKeyboardSpace,16,PG_Rect(nOffsetX+nSizeX*6,nSizeY*2,nSizeX,nSizeY),"U");
	Buttons[17] = new PG_Button(pKeyboardSpace,17,PG_Rect(nOffsetX+nSizeX*7,nSizeY*2,nSizeX,nSizeY),"I");
	Buttons[18] = new PG_Button(pKeyboardSpace,18,PG_Rect(nOffsetX+nSizeX*8,nSizeY*2,nSizeX,nSizeY),"O");
	Buttons[19] = new PG_Button(pKeyboardSpace,19,PG_Rect(nOffsetX+nSizeX*9,nSizeY*2,nSizeX,nSizeY),"P");
	// row 3
	Buttons[20] = new PG_Button(pKeyboardSpace,20,PG_Rect(nSizeX*0,nSizeY*3,nSizeX,nSizeY),"A");
	Buttons[21] = new PG_Button(pKeyboardSpace,21,PG_Rect(nSizeX*1,nSizeY*3,nSizeX,nSizeY),"S");
	Buttons[22] = new PG_Button(pKeyboardSpace,22,PG_Rect(nSizeX*2,nSizeY*3,nSizeX,nSizeY),"D");
	Buttons[23] = new PG_Button(pKeyboardSpace,23,PG_Rect(nSizeX*3,nSizeY*3,nSizeX,nSizeY),"F");
	Buttons[24] = new PG_Button(pKeyboardSpace,24,PG_Rect(nSizeX*4,nSizeY*3,nSizeX,nSizeY),"G");
	Buttons[25] = new PG_Button(pKeyboardSpace,25,PG_Rect(nSizeX*5,nSizeY*3,nSizeX,nSizeY),"H");
	Buttons[26] = new PG_Button(pKeyboardSpace,26,PG_Rect(nSizeX*6,nSizeY*3,nSizeX,nSizeY),"J");
	Buttons[27] = new PG_Button(pKeyboardSpace,27,PG_Rect(nSizeX*7,nSizeY*3,nSizeX,nSizeY),"K");
	Buttons[28] = new PG_Button(pKeyboardSpace,28,PG_Rect(nSizeX*8,nSizeY*3,nSizeX,nSizeY),"L");
	// CANCEL mapped on DEL
	Buttons[40] = new PG_Button(pKeyboardSpace,BTN_ID_CLEAR,PG_Rect(nSizeX*9,nSizeY*3,nSizeX,nSizeY),"clr");
	// row 4
	Buttons[29] = new PG_Button(pKeyboardSpace,29,PG_Rect(nOffsetX+nSizeX*0,nSizeY*4,nSizeX,nSizeY),"Z");
	Buttons[30] = new PG_Button(pKeyboardSpace,30,PG_Rect(nOffsetX+nSizeX*1,nSizeY*4,nSizeX,nSizeY),"X");
	Buttons[31] = new PG_Button(pKeyboardSpace,31,PG_Rect(nOffsetX+nSizeX*2,nSizeY*4,nSizeX,nSizeY),"C");
	Buttons[32] = new PG_Button(pKeyboardSpace,32,PG_Rect(nOffsetX+nSizeX*3,nSizeY*4,nSizeX,nSizeY),"V");
	Buttons[33] = new PG_Button(pKeyboardSpace,33,PG_Rect(nOffsetX+nSizeX*4,nSizeY*4,nSizeX,nSizeY),"B");
	Buttons[34] = new PG_Button(pKeyboardSpace,34,PG_Rect(nOffsetX+nSizeX*5,nSizeY*4,nSizeX,nSizeY),"N");
	Buttons[35] = new PG_Button(pKeyboardSpace,35,PG_Rect(nOffsetX+nSizeX*6,nSizeY*4,nSizeX,nSizeY),"M");
	Buttons[36] = new PG_Button(pKeyboardSpace,36,PG_Rect(nOffsetX+nSizeX*7,nSizeY*4,nSizeX,nSizeY),".");
	Buttons[37] = new PG_Button(pKeyboardSpace,37,PG_Rect(nOffsetX+nSizeX*8,nSizeY*4,nSizeX,nSizeY),"-");
	// SPACE
	Buttons[38] = new PG_Button(pKeyboardSpace,38,PG_Rect(nSizeX*4,nSizeY*5,nSizeX*3,nSizeY)," ");
	Buttons[41] = new PG_Button(pKeyboardSpace,BTN_ID_CONFIRM,PG_Rect(nSizeX*8,nSizeY*5,nSizeX,nSizeY),"ok");
	Buttons[42] = new PG_Button(pKeyboardSpace,BTN_ID_ESCAPE,PG_Rect(nSizeX*9,nSizeY*5,nSizeX,nSizeY),"exit");
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
	Buttons[7] = new PG_Button(pKeyboardSpace,7,PG_Rect(nSizeX*0,nSizeY,nSizeX,nSizeY),"7");
	Buttons[8] = new PG_Button(pKeyboardSpace,8,PG_Rect(nSizeX*1,nSizeY,nSizeX,nSizeY),"8");
	Buttons[9] = new PG_Button(pKeyboardSpace,9,PG_Rect(nSizeX*2,nSizeY,nSizeX,nSizeY),"9");
	Buttons[12] = new PG_Button(pKeyboardSpace,BTN_ID_BACKSPACE,PG_Rect(nSizeX*3,nSizeY,nSizeX,nSizeY),"<-");
	// row 2
	Buttons[4] = new PG_Button(pKeyboardSpace,4,PG_Rect(nSizeX*0,nSizeY*2,nSizeX,nSizeY),"4");
	Buttons[5] = new PG_Button(pKeyboardSpace,5,PG_Rect(nSizeX*1,nSizeY*2,nSizeX,nSizeY),"5");
	Buttons[6] = new PG_Button(pKeyboardSpace,6,PG_Rect(nSizeX*2,nSizeY*2,nSizeX,nSizeY),"6");
	Buttons[13] = new PG_Button(pKeyboardSpace,BTN_ID_CLEAR,PG_Rect(nSizeX*3,nSizeY*2,nSizeX,nSizeY),"clr");
	// row 3
	Buttons[1] = new PG_Button(pKeyboardSpace,1,PG_Rect(nSizeX*0,nSizeY*3,nSizeX,nSizeY),"1");
	Buttons[2] = new PG_Button(pKeyboardSpace,2,PG_Rect(nSizeX*1,nSizeY*3,nSizeX,nSizeY),"2");
	Buttons[3] = new PG_Button(pKeyboardSpace,3,PG_Rect(nSizeX*2,nSizeY*3,nSizeX,nSizeY),"3");
	Buttons[14] = new PG_Button(pKeyboardSpace,BTN_ID_ESCAPE,PG_Rect(nSizeX*3,nSizeY*3,nSizeX,nSizeY),"exit");
	// row 4
	Buttons[0] = new PG_Button(pKeyboardSpace,0,PG_Rect(nSizeX*0,nSizeY*4,nSizeX,nSizeY),"0");
	Buttons[10] = new PG_Button(pKeyboardSpace,10,PG_Rect(nSizeX*1,nSizeY*4,nSizeX,nSizeY),".");
	Buttons[11] = new PG_Button(pKeyboardSpace,11,PG_Rect(nSizeX*2,nSizeY*4,nSizeX,nSizeY),"-");
	Buttons[15] = new PG_Button(pKeyboardSpace,BTN_ID_CONFIRM,PG_Rect(nSizeX*3,nSizeY*4,nSizeX,nSizeY),"ok");
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
