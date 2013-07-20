/*
 * retail_create.c 
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

#include <retail_config.h>
#include <model.h>
#include "view.h"

/**
* Creates a new GtkTreeView widget and set gtk tree view pointer.
*/
void
retail_create_tree_view ()
{
  GtkWidget *view = NULL;
  view = gtk_tree_view_new ();
  if (view == NULL) {
    printf ("\n[retail_create_tree_view] view is NULL, returing\n");
    return;
  }
  //g_return_val_if_fail (NULL != view, NULL);
  g_object_set_data (G_OBJECT (retail_get_app_window ()), VIEW_POINTER,
		     (gpointer) view);
}

/**
* Creates a new GtkCellRendererText and set gtk cell renderer text pointer.
*/
void
retail_create_gtk_cell_renderer_text ()
{
  GtkCellRenderer *model = NULL;
  model = gtk_cell_renderer_text_new ();
  if (model == NULL) {
    printf ("\n[retail_create_gtk_cell_renderer_text] model is NULL, returing\n");
    return;
  }
  //  g_return_val_if_fail (NULL != model, NULL);
  g_object_set_data (G_OBJECT (retail_get_app_window ()), CELL_TEXT,
		     (gpointer) model);

}

void
retail_create_tree_store ()
{
  GtkListStore *store;
  store = gtk_list_store_new (DB_FIELDS_NUM, G_TYPE_FLOAT,
			      G_TYPE_FLOAT, G_TYPE_STRING,
			      G_TYPE_STRING, G_TYPE_STRING);
  if (store == NULL) {
    printf ("[retail_create_tree_store] store is NULL, returing");
    return;
  }
  //g_return_val_if_fail (NULL != store, NULL);
  g_object_set_data (G_OBJECT (retail_get_app_window ()), TREE_STORE,
		     (gpointer) store);

}

/* create tabular view */
GtkWidget *
create_view_and_model ()
{
  GtkCellRenderer *renderer = NULL;
  GtkTreeModel *model = NULL;
  GtkWidget *view = NULL;

  view =
    (GtkWidget *) g_object_get_data (G_OBJECT (retail_get_app_window ()),
				     VIEW_POINTER);
  gtk_tree_view_set_headers_visible ((GtkTreeView*)view, TRUE);

  /* Latitude */
  renderer =
    g_object_get_data (G_OBJECT (retail_get_app_window ()),
				     CELL_TEXT);

  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1,
					       "LATITUDE", renderer, "text",
					       DB_LATITUDE, NULL);
  /* Longitude */
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1,
					       "LONGITUDE", renderer, "text",
					       DB_LONGITUDE, NULL);

  /* Directory */
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1,
					       "PATH", renderer, "text",
					       DB_PATH, NULL);

  /* File */
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1,
					       "FILENAME", renderer, "text",
					       DB_FILE, NULL);

  /* Timestamp */
  gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), -1,
					       "TIMESTAMP", renderer, "text",
					       DB_TIME, NULL);

  model = create_and_fill_model ();
  gtk_tree_view_set_model (GTK_TREE_VIEW (view), model);
  g_object_unref (model);
  return view;
}

/**
* destroy unused object 
*
*/
void
retail_cleanup ()
{
  GtkWidget *view = NULL;
  GtkTreeModel *renderer = NULL;

  view =
    (GtkWidget *) g_object_get_data (G_OBJECT (retail_get_app_window ()),
				     VIEW_POINTER);
  g_object_unref (view);
  view = NULL;

  renderer =
    (GtkTreeModel *) g_object_get_data (G_OBJECT (retail_get_app_window ()),
					CELL_TEXT);
  g_object_unref (renderer);
  renderer = NULL;
}
