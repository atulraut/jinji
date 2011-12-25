/*
 * controller.c 
 *
 * Controller code.
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
#include <controller.h>
#include <view.h>
#include <gthread.h>
#include <glib.h>

/* GUI changes */
gboolean
delete_event (GtkWidget * widget, GdkEvent * event, gpointer data)
{
  g_print ("delete event occurred\n");

  return FALSE;
}

void
destroy (GtkWidget * widget, gpointer data)
{
  gthread_cleanup ();
  gtk_main_quit ();
}

int
initialize (gint argc, gchar * argv[])
{
  gtk_init (&argc, &argv);

  return TRUE;
}

int
atul_retail_start (GtkWidget *window)
{
  create_window (window);

  gtk_main ();

  gthread_cleanup ();

  return TRUE;
}
