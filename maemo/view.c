/*
 * view.c 
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
#include <controller.h>
#include <model.h>
#include "retail_config.h"

/**
* static GtkWidgets window pointer which use by whole application.
*
*/
static GtkWidget *s_window = NULL;

/**
* retail_get_app_window used to return window pointer.
*/
GtkWidget *
retail_get_app_window (void)
{
  if (NULL != s_window)
    return s_window;
  else
    return NULL;
}

void
create_menu (GtkWidget * main_window)
{
/*
    GtkWidget * main_menu;
    GtkWidget *menu_item;
   
    main_menu = gtk_menu_new ();

    menu_item = gtk_menu_item_new_with_label ("Settings");
    g_signal_connect (menu_item, "activate", G_CALLBACK (retail_settings), NULL);
    gtk_menu_shell_append (GTK_MENU_SHELL (main_menu), menu_item);

    menu_item = gtk_menu_item_new_with_label ("Upload Data");
    g_signal_connect (menu_item, "activate", G_CALLBACK (upload_data), (gpointer) main_window);
    gtk_menu_shell_append (GTK_MENU_SHELL (main_menu), menu_item);
  
    menu_item = gtk_menu_item_new_with_label ("About");
    g_signal_connect (menu_item, "activate", G_CALLBACK (ui_callback_about_clicked), (gpointer)  main_window);
    gtk_menu_shell_append (GTK_MENU_SHELL (main_menu), menu_item);  

    menu_item = gtk_menu_item_new_with_label ("Exit Kiira");
    g_signal_connect (menu_item, "activate", G_CALLBACK (destroy), NULL);
    gtk_menu_shell_append (GTK_MENU_SHELL (main_menu), menu_item);
*/
   GtkWidget *vbox;

  GtkWidget *menuBar;
  GtkWidget *fileMenu, *settMenu, *abotMenu;
  GtkWidget *file, *settings, *about;
  GtkWidget *quit, *upload, *abt;
  
  vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(main_window), vbox);

  menuBar  = gtk_menu_bar_new();
  fileMenu = gtk_menu_new();
  settMenu = gtk_menu_new();
  abotMenu = gtk_menu_new();

  file     = gtk_menu_item_new_with_label("File");
  quit     = gtk_menu_item_new_with_label("Quit");

  settings = gtk_menu_item_new_with_label("Settings"); 
  upload   = gtk_menu_item_new_with_label("Upload");

  about    = gtk_menu_item_new_with_label("About");
  abt      = gtk_menu_item_new_with_label("About");

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), fileMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quit);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), file);

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(settings), settMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(settMenu), upload);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), settings);

  gtk_menu_item_set_submenu(GTK_MENU_ITEM(about), abotMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(abotMenu), about);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), abt);

  gtk_box_pack_start(GTK_BOX(vbox), menuBar, FALSE, FALSE, 10);

  g_signal_connect_swapped(G_OBJECT(main_window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

  g_signal_connect(G_OBJECT(quit), "activate",
        G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(main_window);
    
}

/* Populate store with data from model */
GtkTreeModel *
create_and_fill_model (void)
{
  gint total = 0;
  gint i = 0;
  gchar **database_result = NULL;
  GtkTreeIter iter;


  GtkListStore *store;
  store =
    (GtkListStore *) g_object_get_data (G_OBJECT (retail_get_app_window ()),
					TREE_STORE);
  database_result = get_data_from_model (database_result);
  total = return_database_entries ();
  g_print ("total %d\n", total);
  if (total)
    {
      /* get data from database */
      for (i = DB_FIELDS_NUM; i < total; i += DB_FIELDS_NUM)
	{
	  gtk_list_store_append (store, &iter);
	  gtk_list_store_set (store, &iter,
			      DB_LATITUDE,
			      g_ascii_strtod (database_result[i], NULL),
			      DB_LONGITUDE,
			      g_ascii_strtod (database_result[i + 1], NULL),
			      DB_PATH, database_result[i + 2],
			      DB_FILE, database_result[i + 3],
			      DB_TIME, database_result[i + 4], -1);
	}

      /* free memory allocated when retrieveing data from database */
      //database_free_obtained_data (database_result);
    }

  return GTK_TREE_MODEL (store);
}

/* create the window */
void
create_window (GtkWidget *window)
{
  GtkWidget *view = NULL;
  GtkWidget *scrolled_window = NULL;
  GtkWidget *noteboook = NULL;
  GtkWidget *label = NULL, *label1 = NULL, *label2 = NULL;

  /* create the hildon program and set title */
  //program = HILDON_PROGRAM (hildon_program_get_instance ());
  g_set_application_name ("Atul Retailing");

  /* create the HildonWindow and set it to HildonProgram */
  s_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(s_window), 1100, 1100);
  g_return_val_if_fail (NULL != s_window, NULL);

  /* connect signal to X on top right corner */
  g_signal_connect (G_OBJECT (s_window), "delete_event",
		    G_CALLBACK (gtk_main_quit), NULL);

  //hildon_program_add_window (program, s_window);

  /* create_menu (window); */
  create_menu (s_window);
  
  ///retail_widgets_creation ();

  ///view = create_view_and_model ();
  /*
  scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW
					 (scrolled_window), view);
  label = gtk_label_new ("Dummy widget: Integrate map code here.");
  label1 = gtk_label_new ("Maps");
  label2 = gtk_label_new ("Info");
  noteboook = gtk_notebook_new ();

  gtk_notebook_append_page (GTK_NOTEBOOK (noteboook), label, label1);
  gtk_notebook_append_page (GTK_NOTEBOOK (noteboook), scrolled_window,
			    label2);

  gtk_container_add (GTK_CONTAINER (s_window), noteboook);
  */
  /* begin the main application */
  gtk_widget_show_all (GTK_WIDGET (s_window));
}

/**
* Initialize the widgets pointer. 
*
*/
void
retail_widgets_creation ()
{
  /* set gtk tree view pointer. */
  //retail_create_tree_view ();

  /* set gtk cell renderer text pointer. */
  ///retail_create_gtk_cell_renderer_text ();

  //retail_create_tree_store ();
}

void
update_view ()
{
/*
  gint total = 0;
  gint i = 0;
  gchar **database_result = NULL;
  GtkListStore *store;
  GtkTreeIter iter;
  GtkWidget *view;
  GtkTreeModel *model;

  g_print ("\tIn Update View \n");
  view =
    (GtkWidget *) g_object_get_data (G_OBJECT (retail_get_app_window ()),
				     VIEW_POINTER);


  store = GTK_LIST_STORE (gtk_tree_view_get_model (GTK_TREE_VIEW (view)));
  model = gtk_tree_view_get_model (GTK_TREE_VIEW (view));

  if (gtk_tree_model_get_iter_first (model, &iter) == FALSE)
    ;
  else
    {
      gtk_list_store_clear (store);
      // g_object_unref (store);
    }

  g_print ("\t clear store\n");
  database_result = get_data_from_model (database_result);
  total = return_database_entries ();
  g_print ("total %d\n", total);
  if (total)
    {
      // get data from database 
      for (i = DB_FIELDS_NUM; i < total; i += DB_FIELDS_NUM)
	{

	  gtk_list_store_append (store, &iter);
	  gtk_list_store_set (store, &iter,
			      DB_LATITUDE,
			      g_ascii_strtod (database_result[i], NULL),
			      DB_LONGITUDE,
			      g_ascii_strtod (database_result[i + 1], NULL),
			      DB_PATH, database_result[i + 2],
			      DB_FILE, database_result[i + 3],
			      DB_TIME, database_result[i + 4], -1);
	}
      // free memory allocated when retrieveing data from database 
      //database_free_obtained_data (database_result);
    }
*/
}

/* Show "About" information */
void 
ui_callback_about_clicked (GtkMenuItem *menuitem, GtkWindow *parent)
{
  GtkWidget *dialog = NULL;
  GtkWidget *label  = NULL; 
  GtkWidget *image  = NULL; 
  GtkWidget *hbox   = NULL;
  /* Create a new dialog with one OK button. */
  dialog = gtk_dialog_new_with_buttons (ABOUT_INFO, parent,
                                      GTK_DIALOG_MODAL,
                                      GTK_STOCK_OK, GTK_RESPONSE_OK,
                                      NULL);
  g_return_if_fail (NULL != dialog);

  //gtk_dialog_set_has_separator (GTK_DIALOG (dialog), FALSE);
  label = gtk_label_new (GS_ABOUT_STRING);
  g_return_if_fail (NULL != label);  
 
  image = gtk_image_new_from_stock (GTK_STOCK_DIALOG_INFO,
                                  GTK_ICON_SIZE_DIALOG);
  g_return_if_fail (NULL != image); 

  hbox = gtk_hbox_new (FALSE, ABOUT_HBOX_SPACING);
  g_return_if_fail (NULL != hbox);  

  gtk_container_set_border_width (GTK_CONTAINER (hbox), ABOUT_CONTAINER_BORDER_WIDTH);
  //gtk_box_pack_start_defaults (GTK_BOX (hbox), image);
  //gtk_box_pack_start_defaults (GTK_BOX (hbox), label);
  /* Pack the dialog content into the dialog's GtkVBox. */
//  gtk_box_pack_start_defaults (GTK_BOX (GTK_DIALOG (dialog)->vbox), hbox);
  gtk_widget_show_all (dialog);
  /* Create the dialog as modal and destroy it when a button is clicked. */
  gtk_dialog_run (GTK_DIALOG (dialog));
  gtk_widget_destroy (dialog);	
}
