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
    Update Date:      $Date: 2003/11/24 09:17:20 $
    Source File:      $Source: /sources/paragui/paragui/include/pgprogressbar.h,v $
    CVS/RCS Revision: $Revision: 1.3.2.1 $
    Status:           $State: Exp $
*/

#ifndef PG_PROGRESSBAR_H
#define PG_PROGRESSBAR_H

#ifdef SWIG
%include "swigcommon.h"
%module pgprogressbar
%{
#include "pgprogressbar.h"
%}
#endif

#include "pgthemewidget.h"

/**
	@author Alexander Pipelka
 
	@short A progress bar.
 
	Displays progress by taking a percentage and sizing the bar appropriately.
*/
/* Perhaps this could be created with a 'max value' attribute (or what 100%
 * actually is) to ease the load on the application coder so he does not have
 * to worry about converting to percent?
 */
class DECLSPEC PG_ProgressBar : public PG_ThemeWidget {
public:

	/** */
	PG_ProgressBar(PG_Widget* parent, const PG_Rect& r, const char* style="Progressbar");

	/** */
	~PG_ProgressBar();

	//! Set the progress of the widget
	/*! 
	  \note The progress, p,  should be a double between 0.0 and 100.0.
	  \param p new progress
	*/
	void SetProgress(double p);

	void LoadThemeStyle(const char* widgettype);

	//! Toggle drawing of the percentage text
	/*! 
	  \param drawit whether or not to draw the percentage
	*/
	void SetDrawPercentage(bool drawit = true);

protected:

	/** */
	void eventBlit(SDL_Surface* srf, const PG_Rect& src, const PG_Rect& dst);

	/**
	void eventDraw(SDL_Surface* surface, const PG_Rect& rect);
	*/
private:
#ifndef SWIG

	PG_ProgressBar(const PG_ProgressBar&);
	PG_ProgressBar& operator=(const PG_ProgressBar&);
#endif

	PG_Gradient my_pbGradient;
	SDL_Surface* my_pbBackground;
	int my_pbBackmode;
	int my_pbBlend;
	PG_Color my_colorText;
	double my_percentCurrent;
	bool my_drawPercentage;
};

#endif // PG_PROGRESSBAR_H

