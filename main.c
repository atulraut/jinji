/*
 * main.c 
 *
 * The main function.
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

#include <view.h>
#include "controller.h"

gint main (gint argc, gchar *argv[]) {

  GtkWidget *window = NULL;

  if (!initialize (argc, argv))
    {
      g_print ("initialize failed :(\n");
      return FALSE;
    }
      
   if (!atul_retail_start (window))
    {
      g_print ("atul_retail_start() failed\n");
      return FALSE;
    }

  return FALSE;
}
