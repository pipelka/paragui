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
    Update Date:      $Date: 2002/11/01 15:00:59 $
    Source File:      $Source: /sources/paragui/paragui/include/pgnotebook.h,v $
    CVS/RCS Revision: $Revision: 1.3.6.1 $
    Status:           $State: Exp $
*/


#ifndef PG_NOTEBOOK_H
#define PG_NOTEBOOK_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifdef SWIG
%include "swigcommon.h"
%module pgnotebook
%{
#include "pgnotebook.h"
%}
#endif
#include "pgwidget.h"
#include "pgbutton.h"
#include "pgwidgetlist.h"
#include "pgapplication.h"
#include "pgeventobject.h"

#include <vector>
#include MAP_INC
#include <list>

enum PG_NotebookButtons {
        TNB_BUTTON_OK = 0x0001,
        TNB_BUTTON_CANCEL = 0x0002,
        TNB_BUTTON_APPLY = 0x0004,
        TNB_BUTTON_HELP = 0x0008,
        TNB_BUTTON_OCA = TNB_BUTTON_OK | TNB_BUTTON_CANCEL | TNB_BUTTON_APPLY,
        TNB_BUTTON_OCAH = TNB_BUTTON_OCA | TNB_BUTTON_HELP
};

// Forward declarations
class PG_Notebook;
class PG_NotebookTabs;

/** @name PG_NotebookPage callback types
 *
 * PG_NotebookPage can handle the button events through three types of
 * callbacks. The typedefs below define the callback prototypes.
 *@{
 */

/** Callback defined as a PG_Application-derived object method */
typedef Uint32 (PG_Application::*cbAppMethod)(PG_NotebookButtons btn, PG_Widget *page);

/** Callback defined as a PG_DrawObject-derived object method */
typedef Uint32 (PG_DrawObject::*cbDrawableMethod)(PG_NotebookButtons btn, PG_Widget *page);

/** Callback defined as a standalone function */
typedef Uint32 (*cbStandaloneFunc)(PG_NotebookButtons btn, PG_Widget *page);
/**@}*/

/** Notebook callback type */
enum PG_NotebookCallbackType {
        TNCT_NONE,
        TNCT_APPLICATION,
        TNCT_DRAWOBJECT,
        TNCT_STANDALONE
};

struct PG_NotebookPageCallback {
        PG_NotebookPageCallback() 
                        : cbType(TNCT_NONE) {}
        
        PG_NotebookCallbackType   cbType;

        union {
                PG_Application         *oApp;
                PG_DrawObject          *oDraw;
        };

        union {
                cbAppMethod            fApp;
                cbDrawableMethod       fDraw;
                cbStandaloneFunc       fAlone;
        };
};

typedef std::list<PG_NotebookPageCallback> cblist;

class DECLSPEC PG_NotebookPage : public PG_Widget
{
      public:
        PG_NotebookPage(PG_Notebook *parent, const PG_Rect &r, const char *title,
                        Uint32 id, const char *style = "NotebookPage");
        ~PG_NotebookPage() {};

        void LoadThemeStyle(const char *widgettype);
        
        /**
         * Called whenever any of the parent control's standard buttons
         * is clicked by the user. The tab is expected to take
         * appropriate actions that correspond to the type of the
         * event. The following actions are expected in response to the
         * click on a given button:
         *
         *   - TNB_BUTTON_OK\n
         *     The Notebook widget will be closed and all changes must be
         *     accepted and applied. The Notebook widget may ask the user
         *     questions in order to confirm actions.
         *   - TNB_BUTTON_CANCEL\n
         *     The Notebook widget will be closed and all changes must be
         *     ignored. The Notebook widget may as the user questions in order
         *     to confirm actions.
         *   - TNB_BUTTON_APPLY\n
         *     The Notebook widget will not be closed but all the changes
         *     made so far must be accepted and applied. The Notebook widget may
         *     ask the user questions in order to confirm actions.
         *   - TNB_BUTTON_HELP\n
         *     The Notebook widget may display help on its selected widget. If
         *     this function returns @code true, the parent Notebook widget
         *     will not take any further actions, otherwise it will take
         *     whatever actions defined for the help request.
         *
         * @param btn   button that has been clicked
         *
         * @return @code true if the event was handled correctly, @code
         * false otherwise.
         */
        virtual bool NotebookEvent(PG_NotebookButtons btn);

        /** @name Set the button even handlers
         * Those functions are used to attach external event handlers to
         * this page's events. This mechanism can be used to take special
         * actions in response to those events without the need of
         * deriving a new class from PG_NotebookPage. The callback function can
         * retrieve data from the page's widgets by finding the page's
         * wigets either by ID or by name. All callbacks take two
         * parameters - the event and the pointer to the PG_NotebookPage widget
         * that generated the event.
         * @{
         */

        /**
         * The callback is defined in an object derived from
         * PG_Application.
         *
         * @param btn the event to attach the callback to
         * @param app the object derived from PG_Application
         * @param cfun the object's member method to be used for callback
         */
        virtual bool SetButtonHandler(PG_NotebookButtons btn, PG_Application *app, cbAppMethod cfun);

        /**
         * The callback is defined in an object derived from
         * PG_DrawObject.
         *
         * @param btn the event to attach the callback to
         * @param app the object derived from PG_DrawObject
         * @param cfun the object's member method to be used for callback
         */
        virtual bool SetButtonHandler(PG_NotebookButtons btn, PG_DrawObject *drw, cbDrawableMethod cfun);

        /**
         * The callback is defined as a standalone function
         *
         * @param btn the event to attach the callback to
         * @param cfun the callback function
         */
        virtual bool SetButtonHandler(PG_NotebookButtons btn, cbStandaloneFunc cfun);
        /**
         *@}
         */

        void SetIcon(SDL_Surface *icon) {
                srf_icon = icon;
        }
        
        void SetInactiveIcon(SDL_Surface *icon) {
                srf_inactiveIcon = icon;
        }

        void Enable() {
                my_enabled = true;
        }

        void Disable() {
                my_enabled = false;
        }
        
        bool isEnabled() {
                return my_enabled;
        }

        operator bool() {
                return my_enabled;
        }

        const std::string& GetTitle() {
                return my_title;
        }

        Uint32 GetId() {
                return my_page_id;
        }
        
      private:
        cblist* InitCallback(PG_NotebookButtons btn);
        
      protected:
        cblist        ok_callbacks;
        cblist        cancel_callbacks;
        cblist        apply_callbacks;
        cblist        help_callbacks;

        std::string   my_title;
        Uint32        my_page_id;
        
        SDL_Surface  *srf_icon;
        SDL_Surface  *srf_inactiveIcon;
        SDL_Surface  *srf_back;
        SDL_Color     col_back;
        bool          bmp_back;
        Uint32        alpha_back;
        
        bool          my_enabled;
        
        friend class PG_Notebook;
};

class DECLSPEC PG_NotebookButton : public PG_Button
{
      public:
        PG_NotebookButton(PG_NotebookTabs *parent, int btnid,
                          const PG_Rect &rect, PG_NotebookPage *page,
                          const char *style="NotebookButton");
        ~PG_NotebookButton();

        PG_NotebookPage *GetPage() {
                return my_page;
        }

      protected:
        PG_NotebookPage     *my_page;
};

class DECLSPEC PG_NotebookTabs : public PG_WidgetList, public PG_EventObject
{
      public:
        PG_NotebookTabs(PG_Notebook *parent, const PG_Rect &rect,
                        const char *style="NotebookTabs");
        ~PG_NotebookTabs();

        void LoadThemeStyle(const char *widgettype);

        void AddTab(PG_NotebookPage *page);
        void RemoveTab(PG_NotebookPage *page);
        void RefreshState();
        
      protected:
        std::vector<PG_NotebookPage*>   my_tab_pages;

      private:
        STL_MAP<PG_NotebookPage*, PG_NotebookButton*> page2button;
};

class DECLSPEC PG_Notebook : public PG_Widget, public PG_EventObject
{
      public:
        PG_Notebook(PG_Widget *parent, const PG_Rect &r,
                    PG_NotebookButtons btns = TNB_BUTTON_OCA,
                    const char *style="Notebook");
        ~PG_Notebook();

        void LoadThemeStyle(const char *widgettype);

        virtual PG_Rect& GetPageRect() {
                return my_pageRect;
        }

        /**
         * Connect the buttons defined in the parent widget to the Notebook
         * widget's internal event handling system. The IDs of the buttons
         * don't matter, this widget will not use them.
         *
         * @param ok       the OK button
         * @param cancel   the Cancel button
         * @param apply    the Apply button
         * @param help     the Help button
         *
         * @return @code true if buttons were linked to correctly, @false
         * otherwise.
         *
         * @note The passed buttons must correspond to the button options
         * passed to the widget during its construction time. Buttons that
         * are not found in the set will be ignored. Not passing a valid
         * button pointer while it is present in the button options set is
         * considered a serious error [having exception support here would
         * be nice].
         */
        virtual bool SetButtons(PG_Button *ok, PG_Button *cancel, PG_Button *apply,
                                PG_Button *help = 0);

        virtual void SetButtonOptions(PG_NotebookButtons btns);


        /** @anchor addpage_page
         * Adds a pre-created page to the list of pages.
         *
         * @param page   page to be added
         *
         * @par See also:
         * @ref op_plus_page operator @b +
         */
        virtual PG_Notebook& AddPage(PG_NotebookPage *page) {
                my_pages.push_back(page);

                my_page_ids[page->my_page_id] = page;
                my_tabsRow->AddTab(page);
                MeasureWidget(true);
                
                return *this;
        }

        /** @anchor addpage_title
         * Constructs a page with title @code title and then adds it to the
         * list of pages.
         *
         * @param title  title of the new page.
         *
         * @par See also:
         * @ref op_plus_title operator @b +
         */
        virtual PG_Notebook& AddPage(const char *title, Uint32 id) {
                PG_NotebookPage *tmp = new PG_NotebookPage(this, my_pageRect, title, id);
                return AddPage(tmp);
        }
        /**
         * @return A reference to this Notebook.
         *@}
         */


        /** @name Remove a page from the tabset.
         *
         * Removes the given page from the set of pages handled by this
         * widget. The page object is not destructed.
         *@{
         */

        /** @anchor removepage_page
         * Remove a page pointed to by @code page from the set.
         *
         * @param page   pointer to the page to be removed.
         *
         * @par See also:
         * @ref op_minus_page operator @b -
         */
        virtual PG_Notebook& RemovePage(PG_NotebookPage *page) {
                if (!page)
                        return *this;
                
                std::vector<PG_NotebookPage*>::iterator it = my_pages.begin();
                std::vector<PG_NotebookPage*>::iterator end = my_pages.end();
                
                while(it != end) {
                        if (*it == page) {
                                if (page == my_curPage) {
                                        my_curPage->Hide();
                                        if (my_pages.size())
                                                my_curPage = *(my_pages.begin());
                                        else
                                                my_curPage = 0;

                                        if (my_curPage)
                                                my_curPage->Show();
                                }
                                
                                my_tabsRow->RemoveTab(page);
                                my_pages.erase(it);
                                my_page_ids[(*it)->my_page_id] = 0;
                                MeasureWidget(true);
                                return *this;
                        }
                        it++;
                }
                
                return *this;
        }

        /** @anchor removepage_title
         * Remove a page whose with @code title caption from the set.
         *
         * @param id   ID of the page to be removed.
         *
         * @par See also:
         * @ref op_minus_title operator @b -
         */
        virtual PG_Notebook& RemovePage(Uint32 id) {
                PG_NotebookPage *tmp = my_page_ids[id];

                if (tmp)
                        return RemovePage(tmp);

                return *this;
        }
        /**
         * @return A reference to this Notebook.
         *@}
         */

        /** @name Hide the indicated page.
         *
         * Hides the indicated page and repaints the widget.
         *@{
         */

        /**
         * Hide the page pointed to by @code page.
         *
         * @param page   the page to be hidden
         */
        PG_Notebook& HidePage(PG_NotebookPage *page) {                
                if (page && page->IsVisible()) {
                        if (page == my_curPage)
                                my_curPage = 0;
                        page->Hide();
                        my_tabsRow->RefreshState();
                }

                return *this;
        }

        /**
         * Hide the page with caption @code title.
         *
         * @param id   ID of the page to be hidden
         */
        PG_Notebook& HidePage(Uint32 id) {
                return HidePage(my_page_ids[id]);
        }
        /**
         * @return a reference to this Notebook
         *@}
         */

        PG_Notebook& ShowPage(PG_NotebookPage *page) {
                if (page && !page->IsVisible()) {
                        if (page != my_curPage && my_curPage)
                                my_curPage->Hide();
                        page->Show();
                        my_curPage = page;
                        my_tabsRow->RefreshState();
                }

                return *this;
        }
        
        PG_Notebook& ShowPage(Uint32 id) {
                return ShowPage(my_page_ids[id]);
        }
        
        virtual PG_NotebookPage* GetPage(Uint32 id) {
                if (my_page_ids[id])
                        return my_page_ids[id];
                else
                        return 0;
        }

        virtual PG_NotebookPage* GetCurPage() {
                return my_curPage;
        }
        
        Uint8 NumOfPages() {
                return static_cast<Uint8>(my_pages.size());
        }

        PG_NotebookPage* operator[](Uint32 id) {
                return GetPage(id);
        }

        /** @name Add an existing or new page to the set
         *
         * Adds a page to the set.
         *@{
         */

        /** @anchor op_plus_page
         *
         * Add a pre-created page to this tabset.
         *
         * @param page   page to be added
         *
         * @par See also:
         * @ref addpage_page AddPage
         */
        PG_Notebook& operator+(PG_NotebookPage *page) {
                return AddPage(page);
        }
        
        /**
         * @return a reference to this Notebook
         *@}
         */

        /** @name Remove a page from the set
         *
         * Removes a page from the set.
         *@{
         */

        /** @anchor op_minus_page
         *
         * Remove the given page from the Notebook.
         *
         * @param page   page to be removed
         *
         * @par See also:
         * @ref removepage_page RemovePage
         */
        PG_Notebook& operator-(PG_NotebookPage *page) {
                return RemovePage(page);
        }

        /**
         * @return a reference to this Notebook
         *@}
         */
        
      protected:
        void eventSizeWidget(Uint16 w, Uint16 h);
        void eventDraw(SDL_Surface *srf, const PG_Rect &rect);
        virtual void DrawWidget(SDL_Surface *srf, const PG_Rect &r);

        PARAGUI_CALLBACK(handle_ok);
        PARAGUI_CALLBACK(handle_cancel);
        PARAGUI_CALLBACK(handle_apply);
        PARAGUI_CALLBACK(handle_help);
        PARAGUI_CALLBACK(handle_tab_click);

        void HandleButtonClick(PG_NotebookButtons btn);
        void MeasureWidget(bool recalc_pages = false);
        
      protected:
        PG_Rect                            my_clientRect;
        PG_Rect                            my_pageRect;
        PG_Button                         *my_okButton;
        PG_Button                         *my_cancelButton;
        PG_Button                         *my_applyButton;
        PG_Button                         *my_helpButton;
        PG_NotebookTabs                   *my_tabsRow;
        PG_NotebookPage                   *my_curPage;
        
        PG_NotebookButtons                 my_activeButtons;
        bool                               widgetValid;

        std::vector<PG_NotebookPage*>      my_pages;
        STL_MAP<Uint32, PG_NotebookPage*>  my_page_ids;
};

#endif // !PG_TABSET_H

/*
 * Local Variables:
 * mode: c++ 
 * c-basic-offset: 8
 * End:
 */
