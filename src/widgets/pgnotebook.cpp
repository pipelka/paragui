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
  Update Date:      $Date: 2003/11/24 09:17:22 $
  Source File:      $Source: /sources/paragui/paragui/src/widgets/pgnotebook.cpp,v $
  CVS/RCS Revision: $Revision: 1.3.6.1.2.1 $
  Status:           $State: Exp $
*/
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#define USE_COLOR_CONSTANTS

#include "pgnotebook.h"
#include "pglog.h"
#include "pgcolors.h"

#include <cstring>
#include <cassert>

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
#define AMASK 0x000000FF
#else
#define AMASK 0xFF000000
#endif

PG_NotebookPage::PG_NotebookPage(PG_Notebook *parent, const PG_Rect &r, const char *title,
                                 Uint32 id, const char *style)
                : PG_Widget(parent, r), ok_callbacks(), cancel_callbacks(),
                  apply_callbacks(), help_callbacks(),
                  my_title(title ? title : "-untitled-"), my_page_id(id),
                  srf_icon(0), srf_inactiveIcon(0), srf_back(0), bmp_back(false),
                  alpha_back(SDL_ALPHA_OPAQUE), my_enabled(true)
{
        if (strcmp(style, "NotebookPage"))
                LoadThemeStyle("NotebookPage");
        LoadThemeStyle(style);
}

void PG_NotebookPage::LoadThemeStyle(const char *widgettype)
{
        PG_Widget::LoadThemeStyle(widgettype);

        PG_Theme  *t = PG_Application::GetTheme();
        PG_Color *c;
        
        // 1. Background (color or bitmap, gray64)
        col_back = gray64;
        srf_back = t->FindSurface(widgettype, "NotebookPage", "Background");
        if (srf_back) {
                bmp_back = true;
        } else {
                c = t->FindColor(widgettype, "NotebookPage", "BackgroundColor");
                if (c)
                        col_back = *c;
        }
        
        // 2. #1 transparency
        long alpha = t->FindProperty(widgettype, "NotebookPage", "BackgroundAlpha");
        if (alpha >= 0 && alpha <= 255)
                alpha_back = static_cast<Uint32>(alpha);
}

bool PG_NotebookPage::NotebookEvent(PG_NotebookButtons btn)
{
        cblist *clist = 0;
        
        switch(btn) {
            case TNB_BUTTON_OK:
                    clist = &ok_callbacks;
                    break;

            case TNB_BUTTON_CANCEL:
                    clist = &cancel_callbacks;
                    break;

            case TNB_BUTTON_APPLY:
                    clist = &apply_callbacks;
                    break;

            case TNB_BUTTON_HELP:
                    clist = &help_callbacks;
                    break;

            default:
                    return false;
        };

        cblist::iterator it = clist->begin();
        cblist::iterator end = clist->end();

        Uint32 cbok = 0;
        
        while(it != end) {
                PG_NotebookPageCallback  &cb = *it;

                switch(cb.cbType) {
                    case TNCT_APPLICATION:
                            cbok += (cb.oApp->*(cb.fApp))(btn, this);
                            break;

                    case TNCT_DRAWOBJECT:
                            cbok += (cb.oDraw->*(cb.fDraw))(btn, this);
                            break;

                    case TNCT_STANDALONE:
                            cbok += cb.fAlone(btn, this);
                            break;

                    default:
                            PG_LogERR("Incorrect callback type in Notebook (%d)",
                                      cb.cbType);
                            return false;
                }
                it++;
        }

        return (cbok ? false : true);
}

inline cblist* PG_NotebookPage::InitCallback(PG_NotebookButtons btn)
{
        cblist *ret = 0;
        
        switch(btn) {
            case TNB_BUTTON_OK:
                    ret = &ok_callbacks;
                    break;

            case TNB_BUTTON_CANCEL:
                    ret = &cancel_callbacks;
                    break;

            case TNB_BUTTON_APPLY:
                    ret = &apply_callbacks;
                    break;

            case TNB_BUTTON_HELP:
                    ret = &help_callbacks;
                    break;

            default:
                    return 0;
        };

        ret->push_back(PG_NotebookPageCallback());
        return ret;
}

bool PG_NotebookPage::SetButtonHandler(PG_NotebookButtons btn, PG_Application *app, cbAppMethod cfun)
{
		// hehe,...
		// MS VC++ bailed out with an internal compiler error, so i splitted it
        if (!app)
                return false;

		if (cfun == NULL)
                return false;

        cblist *clist = InitCallback(btn);
        if (!clist)
                return false;

        PG_NotebookPageCallback   &cb = clist->back();

        cb.cbType = TNCT_APPLICATION;
        cb.oApp = app;
        cb.fApp = cfun;

        return true;
}

bool PG_NotebookPage::SetButtonHandler(PG_NotebookButtons btn, PG_DrawObject *drw, cbDrawableMethod cfun)
{
		// hehe,...
		// MS VC++ bailed out with an internal compiler error, so i splitted it
        if (!drw)
                return false;

		if (cfun == NULL)
				return false;

        cblist *clist = InitCallback(btn);

        if (!clist)
                return false;

        PG_NotebookPageCallback   &cb = clist->back();

        cb.cbType = TNCT_DRAWOBJECT;
        cb.oDraw = drw;
        cb.fDraw = cfun;

        return true;
}

bool PG_NotebookPage::SetButtonHandler(PG_NotebookButtons btn, cbStandaloneFunc cfun)
{
        if (!cfun)
                return false;

        cblist *clist = InitCallback(btn);
        if (!clist)
                return false;

        PG_NotebookPageCallback   &cb = clist->back();
        
        cb.cbType = TNCT_STANDALONE;
        cb.fAlone = cfun;

        return true;
}


PG_NotebookButton::PG_NotebookButton(PG_NotebookTabs *parent, int btnid,
                                     const PG_Rect &rect, PG_NotebookPage *page,
                                     const char *style)
                : PG_Button(parent, btnid, rect,
                            page ? (char*)(page->GetTitle().c_str()) : 0),
                  my_page(page)
{}

PG_NotebookButton::~PG_NotebookButton()
{}



PG_NotebookTabs::PG_NotebookTabs(PG_Notebook *parent, const PG_Rect &rect, const char *style)
                : PG_WidgetList(parent, rect, style),
                  my_tab_pages(0)
{
        EnableScrollBar(false, PG_SB_VERTICAL);
        EnableScrollBar(false, PG_SB_HORIZONTAL);
        
        if (strcmp(style, "NotebookTabs"))
                LoadThemeStyle("NotebookTabs");
        LoadThemeStyle(style);
}

PG_NotebookTabs::~PG_NotebookTabs()
{}

void PG_NotebookTabs::LoadThemeStyle(const char *widgettype)
{
        PG_Widget::LoadThemeStyle(widgettype);
}

void PG_NotebookTabs::AddTab(PG_NotebookPage *page)
{
        if (!page)
                return;
        
        my_tab_pages.push_back(page);

        PG_NotebookButton  *btn;

        btn = new PG_NotebookButton(this, page->GetId(),
                                    PG_Rect(0, 0, 0, 0),
                                    page);
        btn->SetSizeByText(3);
        AddWidget(btn);
        btn->Show();
}

void PG_NotebookTabs::RemoveTab(PG_NotebookPage *page)
{
        if (!page)
                return;

        vector<PG_NotebookPage*>::iterator pit = my_tab_pages.begin();
        vector<PG_NotebookPage*>::iterator pend = my_tab_pages.end();

        while(pit != pend) {
                if (*pit == page) {
                        my_tab_pages.erase(pit);
                        break;
                } else {
                        pit++;
                }
        }

        vector<PG_Widget*>::iterator lit = my_widgetList.begin();
        vector<PG_Widget*>::iterator lend = my_widgetList.end();

        while (lit != lend) {
#ifdef RTTI_ENABLED
                PG_NotebookButton *btn = dynamic_cast<PG_NotebookButton*>(*lit);
#else
                PG_NotebookButton *btn = static_cast<PG_NotebookButton*>(*lit);
#endif
                if (btn->GetPage() == page) {
                        btn->Hide();
                        DeleteWidget(btn);
                }
        }
}

void PG_NotebookTabs::RefreshState()
{}



PG_Notebook::PG_Notebook(PG_Widget *parent, const PG_Rect &r,
                         PG_NotebookButtons btns, const char *style)
                : PG_Widget(parent, r, false),
                  my_okButton(0), my_cancelButton(0),
                  my_applyButton(0), my_helpButton(0), my_tabsRow(0), my_curPage(0),
                  my_activeButtons(btns), widgetValid(false), my_pages(), my_page_ids()
{
        if (strcmp(style, "Notebook"))
                LoadThemeStyle("Notebook");
        LoadThemeStyle(style);
        my_tabsRow = new PG_NotebookTabs(this, PG_Rect(0, 0, 0, 0));
        my_tabsRow->SetEventObject(MSG_NOTEBOOK_TAB_CLICK, this,
                                   (MSG_CALLBACK_OBJ)&PG_Notebook::handle_tab_click);
}

PG_Notebook::~PG_Notebook()
{}

void PG_Notebook::LoadThemeStyle(const char *widgettype)
{
        PG_Widget::LoadThemeStyle(widgettype);
        
        PG_Theme   *t = PG_Application::GetTheme();
        PG_Color  *c;
        
        //  7. Frame left/top outer (color, LightGrey)
        my_colorBorder[0][0] = LightGrey;
        c = t->FindColor(widgettype, "Notebook", "FrameLeftTopOuter");
        if (c)
                my_colorBorder[0][0] = *c;
        
        //  8. Frame left/top inner (color, gray64)
        my_colorBorder[0][1] = gray64;
        c = t->FindColor(widgettype, "Notebook", "FrameLeftTopInner");
        if (c)
                my_colorBorder[0][1] = *c;
        
        //  9. Frame right/bottom outer (color, black)
        my_colorBorder[1][0] = black;
        c = t->FindColor(widgettype, "Notebook", "FrameRightBottomOuter");
        if (c)
                my_colorBorder[1][0] = *c;
        
        // 10. Frame right/bottom inner (color, gray44)
        my_colorBorder[1][1] = gray44;
        c = t->FindColor(widgettype, "Notebook", "FrameRightBottomInner");
        if (c)
                my_colorBorder[1][1] = *c;
}

bool PG_Notebook::SetButtons(PG_Button *ok, PG_Button *cancel, PG_Button *apply,
                             PG_Button *help)
{
        bool ret = true;

        if ((my_activeButtons & TNB_BUTTON_OK) && ok) {
                my_okButton = ok;
                my_okButton->SetEventObject(MSG_BUTTONCLICK, this,
                                            (MSG_CALLBACK_OBJ)&PG_Notebook::handle_ok);
        } else if (my_activeButtons & TNB_BUTTON_OK) {
                PG_LogERR("Button 'OK' present in options, but not attached!");
                ret = false;
        }
        
        if ((my_activeButtons & TNB_BUTTON_CANCEL) && cancel) {
                my_cancelButton = cancel;
                my_cancelButton->SetEventObject(MSG_BUTTONCLICK, this,
                                                (MSG_CALLBACK_OBJ)&PG_Notebook::handle_cancel);
        } else if (my_activeButtons & TNB_BUTTON_CANCEL) {
                PG_LogERR("Button 'CANCEL' present in options, but not attached!");
                ret = false;
        }

        if ((my_activeButtons & TNB_BUTTON_APPLY) && apply) {
                my_applyButton = apply;
                my_applyButton->SetEventObject(MSG_BUTTONCLICK, this,
                                               (MSG_CALLBACK_OBJ)&PG_Notebook::handle_apply);
        } else if (my_activeButtons & TNB_BUTTON_APPLY) {
                PG_LogERR("Button 'APPLY' present in options, but not attached!");
                ret = false;
        }
        
        if ((my_activeButtons & TNB_BUTTON_HELP) && cancel) {
                my_helpButton = help;
                my_helpButton->SetEventObject(MSG_BUTTONCLICK, this,
                                              (MSG_CALLBACK_OBJ)&PG_Notebook::handle_help);
        } else if (my_activeButtons & TNB_BUTTON_HELP) {
                PG_LogERR("Button 'HELP' present in options, but not attached!");
                ret = false;
        }
        
        return ret;
}

void PG_Notebook::SetButtonOptions(PG_NotebookButtons btns)
{}

void PG_Notebook::eventDraw(SDL_Surface *srf, const PG_Rect &r)
{
        DrawWidget(0, r);
}

void PG_Notebook::eventSizeWidget(Uint16 w, Uint16 h)
{        
        PG_Widget::eventSizeWidget(w, h);
        MeasureWidget(true);
}

void PG_Notebook::DrawWidget(SDL_Surface *srf, const PG_Rect &r)
{
        DrawBorder(my_clientRect, 2);
}

void PG_Notebook::MeasureWidget(bool recalc_pages)
{
        Uint16 fh;

        if (!PG_FontEngine::GetTextSize("My", &my_font, 0, 0, 0, 0, &fh)) {
                PG_LogWRN("GetTextSize failed for Notebook. Assuming default height.");
                fh = 25;
        }
        
        if (fh > 256) { // hmm, that should be enough to catch all the
                        // problems with the font measuring...
                PG_LogERR("PG_FontEngine::GetTextSize returned suspicious value in Notebook");
                return;
        }
        
        fh += 6; // 3px on each side extra
        if (recalc_pages) {
                // Calculate the width of all the pages' titles
                vector<PG_NotebookPage*>::iterator it = my_pages.begin();
                vector<PG_NotebookPage*>::iterator end = my_pages.end();

                Uint16 w, tw = 0;
                
                while (it != end) {
                        PG_NotebookPage  *pg = *it;

                        if (!pg->IsVisible()) {
                                it++;
                                continue;
                        }
                        
                        if (!PG_FontEngine::GetTextSize(pg->my_title.c_str(), &my_font, &w) || w > 256) {
                                PG_LogWRN("GetTextSize failed for Notebook page. Assuming default width.");
                                w = 30; // arbitrary, of course :P
                        }
                        tw += w + 6; // 3px margin on each side
                        it++;
                }

                if (tw > my_width)
                        tw = my_width;

                my_tabsRow->SizeWidget(tw, fh + 2);
                my_tabsRow->RefreshState();
        }
        
        my_clientRect.SetRect(0, fh, my_width, my_height - fh);
        // page rect is -2 on each side - for the border
        my_pageRect.SetRect(2, fh + 2, my_width - 4, my_height - fh - 4);
        widgetValid = true;
}

void PG_Notebook::HandleButtonClick(PG_NotebookButtons btn)
{
        vector<PG_NotebookPage*>::iterator it = my_pages.begin();
        vector<PG_NotebookPage*>::iterator end = my_pages.end();

        Uint32 not_ok = 0;

        while(it != end) {
                PG_NotebookPage *p = *it;
                
                if (!p->NotebookEvent(btn))
                        not_ok++;
                it++;
        }

        if (!not_ok) {
                switch (btn) {
                    case TNB_BUTTON_OK:
                    case TNB_BUTTON_CANCEL:
                            Hide();
                            break;

                    default: // to shut the compiler warning up :P
                            break;
                }
        }
}

PARAGUI_CALLBACK(PG_Notebook::handle_ok) {
        HandleButtonClick(TNB_BUTTON_OK);
        return true;
}
        
PARAGUI_CALLBACK(PG_Notebook::handle_cancel) {
        HandleButtonClick(TNB_BUTTON_CANCEL);
        return true;
}
        
PARAGUI_CALLBACK(PG_Notebook::handle_apply) {
        HandleButtonClick(TNB_BUTTON_APPLY);
        return true;
}
        
PARAGUI_CALLBACK(PG_Notebook::handle_help) {
        HandleButtonClick(TNB_BUTTON_HELP);
        return true;
}

PARAGUI_CALLBACK(PG_Notebook::handle_tab_click) {
        if (!clientdata) {
                PG_LogDBG("Empty data passed to the tab callback");
                return false;
        }

        PG_NotebookPage  *pg = static_cast<PG_NotebookPage*>(clientdata);

        if (!pg)
                return false;

        if (my_curPage)
                my_curPage->Hide();

        my_curPage = pg;
        my_curPage->Show();
        
        return true;
}

/*
 * Local Variables:
 * c-basic-offset: 8
 * End:
 */
