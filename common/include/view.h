/*
 * view.h 
 *
 * view header file.
 * 
 * Copyright (C) 2008 Re-Ram Solutions Ltd.
 * Authored by Atul Raut <atulraut17@gmail.com>
 * Date : Sunday, September 11 2011, 02:35 PM
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
 *
 */

#include <gtk/gtk.h>
//#include <gtk/gtkmain.h>

/* In ui_callback_about_clicked */
#define ABOUT_INFO 			"Information"
#define ABOUT_HBOX_SPACING 		5
#define ABOUT_CONTAINER_BORDER_WIDTH 	10
#define GS_ABOUT_STRING 		"Project by Re-Ram India!"

GtkWidget *retail_get_app_window (void);
void create_menu (GtkWidget *main_window);
GtkTreeModel *create_and_fill_model (void);
void create_window (GtkWidget *window);
void retail_widgets_creation ();
void update_view ();
/* Show "About" information */
void ui_callback_about_clicked (GtkMenuItem * menuitem, GtkWindow * parent);

GdkPixbuf *create_pixbuf(const gchar * filename);
