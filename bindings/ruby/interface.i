/* 
   Feel free to use this file as a template for creating swig interfaces
   for other languages. If you have any questions, feel free to contact me
   at <leon@ugcs.caltech.edu>. If you want to read something first, try
   reading the swig1.3 docs at swig.org and their mailing list archive.
   In particular, look for %typemap(out) Node * = SWIGTYPE *DYNAMIC
   in the mail archive.
 */

%module ParaGUI
%{
/* Includes the header in the wrapper code */
#include "pgmessageobject.h"
#include "pgapplication.h"
%}
     
/* Parse the header file to generate wrappers */
%include "pgmessageobject.h"
%include "pgapplication.h"

class PG_Widget;

// downcast anything that returns a (PG_Widget *) to appropriate subclass
%typemap(out) PG_Widget * = SWIGTYPE *DYNAMIC;

// include everything here so the above typemap affects everything

// this function is associated with the downcasting typemap defined above
%{
    // given some PG_Widget object (subclass), figure out what SWIGTYPE it is
    static swig_type_info *
    PG_Widget_dynamic_cast(void **ptr) 
    {
        PG_Widget **pgwptr = (PG_Widget **) ptr;

        // these should be ordered by frequency of widget messaging
        PG_Button *b1 = dynamic_cast<PG_Button *>(*pgwptr);
        if (b1) {
            *ptr = (void *) b1;
            return SWIGTYPE_p_PG_Button;
        }
        PG_Slider *b2 = dynamic_cast<PG_Slider *>(*pgwptr);
        if (b2) {
            *ptr = (void *) b2;
            return SWIGTYPE_p_PG_Slider;
        }
        PG_ScrollBar *b3 = dynamic_cast<PG_ScrollBar *>(*pgwptr);
        if (b3) {
            *ptr = (void *) b3;
            return SWIGTYPE_p_PG_ScrollBar;
        }
        PG_Label *b5 = dynamic_cast<PG_Label *>(*pgwptr);
        if (b5) {
            *ptr = (void *) b5;
            return SWIGTYPE_p_PG_Label;
        }
        PG_ColumnItem *b7 = dynamic_cast<PG_ColumnItem *>(*pgwptr);
        if (b7) {
            *ptr = (void *) b7;
            return SWIGTYPE_p_PG_ColumnItem;
        }
        PG_PopupMenu *b9 = dynamic_cast<PG_PopupMenu *>(*pgwptr);
        if (b9) {
            *ptr = (void *) b9;
            return SWIGTYPE_p_PG_PopupMenu;
        }
        PG_ProgressBar *a1 = dynamic_cast<PG_ProgressBar *>(*pgwptr);
        if (a1) {
            *ptr = (void *) a1;
            return SWIGTYPE_p_PG_ProgressBar;
        }
        PG_RadioButton *a2 = dynamic_cast<PG_RadioButton *>(*pgwptr);
        if (a2) {
            *ptr = (void *) a2;
            return SWIGTYPE_p_PG_RadioButton;
        }
        PG_CheckButton *a3 = dynamic_cast<PG_CheckButton *>(*pgwptr);
        if (a3) {
            *ptr = (void *) a3;
            return SWIGTYPE_p_PG_CheckButton;
        }
        PG_ListBox *a4 = dynamic_cast<PG_ListBox *>(*pgwptr);
        if (a4) {
            *ptr = (void *) a4;
            return SWIGTYPE_p_PG_ListBox;
        }
        PG_SpinnerBox *a5 = dynamic_cast<PG_SpinnerBox *>(*pgwptr);
        if (a5) {
            *ptr = (void *) a5;
            return SWIGTYPE_p_PG_SpinnerBox;
        }
        PG_Window *a6 = dynamic_cast<PG_Window *>(*pgwptr);
        if (a6) {
            *ptr = (void *) a6;
            return SWIGTYPE_p_PG_Window;
        }
        PG_MessageBox *a7 = dynamic_cast<PG_MessageBox *>(*pgwptr);
        if (a7) {
            *ptr = (void *) a7;
            return SWIGTYPE_p_PG_MessageBox;
        }
        PG_Image *a8 = dynamic_cast<PG_Image *>(*pgwptr);
        if (a8) {
            *ptr = (void *) a8;
            return SWIGTYPE_p_PG_Image;
        }
        PG_LineEdit *a9 = dynamic_cast<PG_LineEdit *>(*pgwptr);
        if (a9) {
            *ptr = (void *) a9;
            return SWIGTYPE_p_PG_LineEdit;
        }
        PG_MaskEdit *b10 = dynamic_cast<PG_MaskEdit *>(*pgwptr);
        if (b10) {
            *ptr = (void *) b10;
            return SWIGTYPE_p_PG_MaskEdit;
        }
        PG_WidgetDnD *b12 = dynamic_cast<PG_WidgetDnD *>(*pgwptr);
        if (b12) {
            *ptr = (void *) b12;
            return SWIGTYPE_p_PG_WidgetDnD;
        }
        PG_ListBoxItem *b6 = dynamic_cast<PG_ListBoxItem *>(*pgwptr);
        if (b6) {
            *ptr = (void *) b6;
            return SWIGTYPE_p_PG_ListBoxItem;
        }
        PG_ListBoxBaseItem *b61 = dynamic_cast<PG_ListBoxBaseItem *>(*pgwptr);
        if (b61) {
            *ptr = (void *) b61;
            return SWIGTYPE_p_PG_ListBoxBaseItem;
        }
        PG_DropDown *b4 = dynamic_cast<PG_DropDown *>(*pgwptr);
        if (b4) {
            *ptr = (void *) b4;
            return SWIGTYPE_p_PG_DropDown;
        }
        PG_MenuBar *b8 = dynamic_cast<PG_MenuBar *>(*pgwptr);
        if (b8) {
            *ptr = (void *) b8;
            return SWIGTYPE_p_PG_MenuBar;
        }
        // missing widgetlist, themewidget, widgetlistex, richedit

        return SWIGTYPE_p_PG_Widget;
    }
%}

// this registers the above function with the appropriate SWIGTYPE
DYNAMIC_CAST(SWIGTYPE_p_PG_Widget, PG_Widget_dynamic_cast);


/*
   Paragui's message system is signal based. That means when a widget sends 
   a signal, the message handling code will invoke any client callbacks bound 
   to that message. Because it's impossible to generically map scripting 
   language functions to C++ callbacks (python function objects, ruby procs, 
   lisp lambdas, etc), we need to use an indirect method.

   As it turns out, Paragui wraps message callbacks in an object that can 
   carry extra info as a void pointer (clientdata). We will use that to our 
   advantage. The strategy here is:

   1) Create a generic proxy callback to be invoked by Paragui's message system.
   2) Use the void pointer to store the address of the relevant function 
   object (Proc or Method). The function should be on the heap for persistency.
   3) Create a bridge function to bind the above two thingies to a message
   via PG_MessageObject->SetEventCallback.
   4) When our proxy callback is invoked, it pulls the function object from 
   the heap and calls it according to the scripting language C API.
 */

%extend PG_MessageObject 
{
    // determines type of data passed by message, if it is an object
    static swig_type_info *
    MessageDataObjectType(int id, const swig_type_info *wtype)
    {
        if (wtype == SWIGTYPE_p_PG_DropDown)
            return SWIGTYPE_p_PG_ListBoxItem;
        if (wtype == SWIGTYPE_p_PG_ListBox)
            return SWIGTYPE_p_PG_ListBoxBaseItem;
        return 0;
    }

    // proxy callback. The ruby proc or method is stored in *clientdata
    static bool 
    RubyCallBack(int id, PG_Widget *widget, unsigned long data, void *clientdata) 
    {
        VALUE result, rwidget;
        VALUE *rbfunc;
        VALUE rdata = Qnil;
        bool res = 0;

        rbfunc = reinterpret_cast<VALUE *>(clientdata);
        {
            swig_type_info *ty1, *ty2;

            ty1 = SWIG_TypeDynamicCast(SWIGTYPE_p_PG_Widget, (void **) &widget);
            rwidget = SWIG_NewPointerObj((void *) widget, ty1, 0);
            ty2 = PG_MessageObject_MessageDataObjectType(id, ty1);
            if (ty2) rdata = SWIG_NewPointerObj((void *) data, ty2, 0);
        }

        if (rdata == Qnil)
            result = rb_funcall(*rbfunc, rb_intern("call"), 3, 
                    INT2FIX(id), rwidget, INT2FIX(data));
        else
            result = rb_funcall(*rbfunc, rb_intern("call"), 3, 
                    INT2FIX(id), rwidget, rdata);

        switch(TYPE(result)) {
            case T_FLOAT:
            case T_FIXNUM:
            case T_BIGNUM:
                // I don''t know why this is a double
                res = NUM2DBL(result); // nil -> 0
                break;
        }
        return res;
    }

    // connects a proc or method to a message using proxy callback (use in ruby)
    void 
    set_rbcallback(PG_MSG_TYPE type, VALUE rbfunc) 
    {
        VALUE *funcptr = new VALUE;

        // put rbfunc in heap for persistence, let old reference die
        *funcptr = rbfunc;
        // bind the proxy and this rbfunc to message
        self->SetEventCallback(type, PG_MessageObject_RubyCallBack, 
                reinterpret_cast<void *>(funcptr));
    }
}
