/**
 **	A GTK widget showing a palette's colors.
 **
 **	Written: 12/24/2000 - JSF
 **/


#ifndef INCL_PALEDIT
#define INCL_PALEDIT	1

/*
Copyright (C) 2000 The Exult Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "objbrowse.h"
#include "rect.h"

class Flex;
class U7object;

/*
 *	Show a palette.
 */
class Palette_edit: public Object_browser
	{
	char *file;			// Full filename.
	int count;			// # palettes in file.
	guchar *image;			// Holds data to render.
	int width, height;		// Dimensions of image.
	GtkWidget *draw;		// GTK draw area to display them in.
	GdkGC *drawgc;			// For drawing in 'draw'.
	GdkRgbCmap *palette;		// The palette to display.
	GtkColorSelectionDialog *colorsel;// Open color selector.
	GtkWidget *sbar;		// Status bar.
	GtkAdjustment *palnum_adj;	// Spin btn. for palette #.
	guint sbar_sel;			// Status bar context for selection.
	int selected;			// Index of user-selected entry.
	Rectangle selected_box;		// Location of selected color.
					// Blit onto screen.
	virtual void show(int x, int y, int w, int h);
	virtual void show()
		{ Palette_edit::show(0, 0, 
			draw->allocation.width, draw->allocation.height);}
	void select(int new_sel);	// Show new selection.
	virtual void render();		// Draw list.
					// Handle color-selector buttons.
	static int color_closed(GtkWidget *widget, GdkEvent *event, 
							gpointer data);
	static void color_cancel(GtkWidget *widget, gpointer data);
	static void color_okay(GtkWidget *widget, gpointer data);
	void double_clicked();		// Handle double-click on a color.
	GtkWidget *create_controls();	// Controls at bottom of browser.
	void setup();			// Setup box.
public:
	Palette_edit(const char *fullname);
	~Palette_edit();
	void show_palette(int palnum);	// Show desired palette.
					// Turn off selection.
	void unselect(bool need_render = true);
					// Configure when created/resized.
	static gint configure(GtkWidget *widget, GdkEventConfigure *event,
							gpointer data);
					// Blit to screen.
	static gint expose(GtkWidget *widget, GdkEventExpose *event,
							gpointer data);
					// Handle mouse press.
	static gint mouse_press(GtkWidget *widget, GdkEventButton *event,
							gpointer data);
					// Give dragged palette.
	static void drag_data_get(GtkWidget *widget, GdkDragContext *context,
		GtkSelectionData *data, guint info, guint time, gpointer data);
					// Someone else selected.
	static gint selection_clear(GtkWidget *widget,
				GdkEventSelection *event, gpointer data);
	static gint drag_begin(GtkWidget *widget, GdkDragContext *context,
							gpointer data);
	static void palnum_changed(GtkAdjustment *adj, gpointer data);
	};

#endif
