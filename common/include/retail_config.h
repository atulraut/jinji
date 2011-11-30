/*
 * retail_config.h 
 *
 * GUI implementation.
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
#include <view.h>

/* set objet name */
#define VIEW_POINTER "view pointer"
#define CELL_TEXT    "cell text pointer"
#define TREE_STORE    "tree store"

/* set gtk tree view pointer. */
void retail_create_tree_view ();

/* set gtk cell renderer text pointer. */
void retail_create_gtk_cell_renderer_text ();

/* destroy unused object */
void retail_cleanup ();

/* file uplaod */
void upload_data (GtkMenuItem *, GtkWindow *);

/* retail related settings */
void
retail_settings (GtkMenuItem * settingmenuitem, GtkWindow * parent_window);
