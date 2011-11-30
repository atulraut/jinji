/*
 * gthread.c 
 *
 * GLib thread for inotify callbacks.
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

#include <glib.h>
#include <gthread.h>

gint
gthread_initialize ()
{
  GError *g_error = NULL;

  /* threads are supported */
  if (!g_thread_supported ())
    {
      g_thread_init (NULL);
      g_print ("g_thread supported\n");
    }
  else
    {
      g_print ("g_thread NOT supported\n");
      return FALSE;
    }
/*
  struct inotify_event *event; 

  if (!g_thread_create ((GThreadFunc) inotify_callback, event, FALSE, &g_error))
    {
      g_print ("Thread creation failed: %s\n", g_error->message);
      g_error_free (g_error);
      return FALSE;
    }
*/
  return TRUE;
}

void
gthread_cleanup ()
{
  /* Nothing to do here? Buy some Maaza. */
}
