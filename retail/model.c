/*
 * model.c 
 *
 * Backend model/database implementation.
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

#include <sqlite3.h>
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>

#include <curl/curl.h>
#include <curl/typecheck-gcc.h>
#include <curl/easy.h>

#include <model.h>
#include <retail_config.h>
#include <view.h>
#include "gthread.h"

sqlite3 *db = NULL;

gint database_entries = 0;
//extern GtkTreeIter iter;

G_LOCK_DEFINE_STATIC (db);
G_LOCK_DEFINE_STATIC (database_entries);

/* execute a sqlite3 SQL query */
void
sqlite3_execute (void *database, const gchar * sql,
		 int (*callback) (void *, int, gchar **, gchar **),
		 void *arg, gchar * err_msg)
{
  sqlite3 *db = (sqlite3 *) database;
  if (sqlite3_exec (db, sql, callback, arg, &err_msg) != SQLITE_OK)
    {
      g_print ("Can't execute: %s\n", err_msg);
      sqlite3_free (err_msg);
    }

//  create_and_fill_model();
}

/* get data from table */
gint
get_data_from_model (gchar ** database_result)
{
  gint nrow, get_result;
  gint ncolumn;
  gchar *err_msg = 0;

  G_LOCK (db);
  get_result = sqlite3_get_table (db, SQLITE3_GET_TABLE, &database_result,
				  &nrow, &ncolumn, &err_msg);
  G_LOCK (database_entries);
  database_entries = (nrow + 1) * ncolumn;
  G_UNLOCK (database_entries);
  G_UNLOCK (db);

  if (!get_result)
    {
      //    for (get_result = 0; get_result < (nrow + 1) * ncolumn; get_result++)
//      g_print ("%s\n", database_result[get_result]);

      //return database_result;
    }

  return FALSE;
}

int
return_database_entries (void)
{
  gint value = 0;

  G_LOCK (database_entries);
  value = database_entries;
  G_UNLOCK (database_entries);

  return value;
}


/* free memory allocated when retrieveing data from database */ /*
void
database_free_obtained_data (gchar ** database_result)
{
  sqlite3_free_table (database_result);
}
*/
/* insert an entry into the table */ /*
void
insert_into_table (inotify_details * entry, gps_coordinates * position)
{
  gchar *err_msg = 0;
  gchar *sql = NULL;
  gchar *parse_filename = NULL;
  gchar *parse_filepath = NULL;

  // Sql query file name check 
  parse_filename = inotify_file_name_check (entry);
  // Sql query file path check 
  parse_filepath = inotify_file_path_check (entry);

  // Create string for INSERT_TABLE 
  sql = g_strconcat (INSERT_INTO_TABLE,
		     g_strdup_printf ("%.2f", position->latitude), ",",
		     g_strdup_printf ("%.2f", position->longitude), ",",
		     "'", parse_filepath, "',",
		     "'", parse_filename, "',"
		     "'", entry->timestamp, "'" ")", NULL);

  // g_print ("insert = %s\n", sql);

  G_LOCK (db);
  sqlite3_execute (db, sql, 0, 0, err_msg);
  G_UNLOCK (db);


  g_free (sql);
}
*/
/* update an entry into the table */ /*
void
update_table (inotify_details * entry, struct gps_coordinates *position)
{
  gchar *err_msg = 0;
  gchar *sql = NULL;
  gchar *parse_filename = NULL;

  // Sql query file name check 
  parse_filename = inotify_file_name_check (entry);
  parse_filename = g_strdup (parse_filename);

  // Create string for UPDATE_TABLE 
  sql = g_strconcat (UPDATE_TABLE,
		     G_STRINGIFY (TIMESTAMP), "=\"", entry->timestamp, "\"",
		     " where ",
		     G_STRINGIFY (FILENAME), "=", "\"", parse_filename, "\"",
		     NULL);

// g_print ("update = %s\n", sql);

  G_LOCK (db);
  sqlite3_execute (db, sql, 0, 0, err_msg);
  G_UNLOCK (db);


  g_free (sql);
}
*/
/* Update only path, filename for a moved/renamed file */ /*
void
update_moved_file_in_table (inotify_details * entry,
			    struct gps_coordinates *position,
			    gchar * previous_filename)
{
  gchar *err_msg = 0;
  gchar *sql = NULL;
  gchar *parse_filename = NULL;
  gchar *parse_filepath = NULL;

  // Sql query file name check 
  parse_filename = inotify_file_name_check (entry);
  // Sql query file path check 
  parse_filepath = inotify_file_path_check (entry);

  // Create string for UPDATE_TABLE 
  sql = g_strconcat (UPDATE_TABLE,
		     G_STRINGIFY (PATH), "=\"", parse_filepath, "\",",
		     G_STRINGIFY (FILENAME), "=\"", parse_filename, "\"",
		     " where ",
		     G_STRINGIFY (FILENAME), "=", "\"", previous_filename,
		     "\"", NULL);

//  g_print ("update = %s\n", sql);

  G_LOCK (db);
  sqlite3_execute (db, sql, 0, 0, err_msg);
  G_UNLOCK (db);


  g_free (sql);
}
*/
/* delete an entry from a file */ /*
void
delete_from_table (inotify_details * entry, struct gps_coordinates *position)
{
  gchar *err_msg = 0;
  gchar *sql = NULL;
  gchar *parse_filename;

  // Sql query file name check 
  parse_filename = inotify_file_name_check (entry);

  // Create string for DELETE_FROM_TABLE 
  sql = g_strconcat (DELETE_FROM_TABLE,
		     G_STRINGIFY (FILENAME), "=",
		     "'", parse_filename, "'", NULL);

  //g_print ("delete = %s\n", sql);

  G_LOCK (db);
  sqlite3_execute (db, sql, 0, 0, err_msg);
  G_UNLOCK (db);


  g_free (sql);
}
*/
/* open the database */
void *
database_open (void *database)
{
  sqlite3 *db = (sqlite3 *) database;

  if (sqlite3_open (DB, &db))
    {
      g_print ("Can't open database: %s\n", sqlite3_errmsg (db));
      sqlite3_close (db);
      return NULL;
    }

  return db;
}

/* callback from inotify to do database operations */ /*
void
database_execute (inotify_details * entry, struct gps_coordinates *position)
{
  static gchar *previous_filename = NULL;

  if (0 == g_strcasecmp (CREATE, entry->occured_event))
    {
      // insert into table 
  //    insert_into_table (entry, position);
    }
  else if (0 == g_strcasecmp (MODIFY, entry->occured_event))
    {
      // if file already exists, just update 
      //   timestamp, latitude, longitude 
    //  update_table (entry, position);
    }
  else if (0 == g_strcasecmp (DELETE, entry->occured_event))
    {
     // delete_from_table (entry, position);
    }
  else if (0 == g_strcasecmp (MOVED_FROM, entry->occured_event))
    {
      ///previous_filename = g_strdup (entry->filename);
      //g_print ("previous 1 = %s\n", previous_filename);
    }
  else if (0 == g_strcasecmp (MOVED_TO, entry->occured_event))
    {
     // update_moved_file_in_table (entry, position, previous_filename);
     // g_free (previous_filename);
    }
}
*/
/* initialize/open the database */
gint
database_initialize ()
{
  gchar *err_msg = 0;
  gchar *sql = NULL;

  /* open or create database */
  db = database_open (db);
  if (!db)
    {
      g_print ("Cannot open database\n");
      return FALSE;
    }

  /* Create string for CREATE_TABLE */
  sql = g_strconcat (CREATE_TABLE,
		     G_STRINGIFY (LATITUDE), " real,",
		     G_STRINGIFY (LONGITUDE), " real,",
		     G_STRINGIFY (PATH), " varchar(",
		     G_STRINGIFY (PATH_LENGTH), ")", ",",
		     G_STRINGIFY (FILENAME), " varchar(",
		     G_STRINGIFY (FILENAME_LENGTH), "),",
		     G_STRINGIFY (TIMESTAMP), " varchar(",
		     G_STRINGIFY (TIMESTAMP_LENGTH), ")", ")", NULL);

  G_LOCK (db);
  sqlite3_execute (db, sql, 0, 0, err_msg);
  G_UNLOCK (db);

  g_free (sql);

  return TRUE;
}

/* close the database */
void
database_cleanup (void *database)
{
  gchar *err_msg = 0;

  sqlite3 *db = (sqlite3 *) database;

  sqlite3_execute (db, HEY_VACUUM, 0, 0, err_msg);

  sqlite3_close (db);
}

/*new_bill: Make new bill payment */
void
new_bill(GtkMenuItem * runfilemenuitem, GtkWindow * parent_window)
{
  printf ("\n new_bill fun got called ....\n");

  CURL *curl;
  CURLcode res;
  struct curl_httppost *formpost = NULL;
  struct curl_httppost *lastptr = NULL;
  struct curl_slist *headerlist = NULL;
  static const char buf[] = "Expect:";

  GtkWidget *dialog = NULL;
  FILE *fp = NULL;

  res = curl_global_init (CURL_GLOBAL_ALL);

  if (res)
    {
      g_print ("\nAT :curl_global_init failed \n");
      gthread_cleanup ();
    }
  else
    {
      g_print ("\nAT : curl_global_init ()\n");
    }

  dialog = gtk_file_chooser_dialog_new ("Open File",
					parent_window,
					GTK_FILE_CHOOSER_ACTION_OPEN,
					GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
					NULL);
  g_return_if_fail (NULL != dialog);

  if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
    {
      gchar *filename = NULL;
      filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));

      fp = fopen (filename, "r");
      if (fp == NULL)
	{
	  g_printf ("\nAT : Unable to open file\n");
	}
      else
	{
	  /* Fill in the file upload field */
	  curl_formadd (&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "file",
			CURLFORM_FILE, filename, CURLFORM_END);
	  /* Fill in the filename field */
	  curl_formadd (&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "file",
			CURLFORM_COPYCONTENTS, filename, CURLFORM_END);


	  /* Fill in the submit field too, even if this is rarely needed */
	  curl_formadd (&formpost,
			&lastptr,
			CURLFORM_COPYNAME, "submit",
			CURLFORM_COPYCONTENTS, "Submit", CURLFORM_END);

	  curl = curl_easy_init ();
	  /* initalize custom header list (stating that Expect: 100-continue is not
	     wanted */
	  headerlist = curl_slist_append (headerlist, buf);
	  if (curl)
	    {
	      /* what URL that receives this POST */
	      curl_easy_setopt (curl, CURLOPT_URL,
				"http://192.168.1.211/retail/upload_file.php");
	      //                     if ( (argc == 2) && (!strcmp(argv[1], "noexpectheader")) )
	      /* only disable 100-continue header if explicitly requested */
	      curl_easy_setopt (curl, CURLOPT_HTTPHEADER, headerlist);
	      curl_easy_setopt (curl, CURLOPT_HTTPPOST, formpost);
	      res = curl_easy_perform (curl);

	      /* always cleanup */
	      curl_easy_cleanup (curl);

	      /* then cleanup the formpost chain */
	      curl_formfree (formpost);
	      /* free slist */
	      curl_slist_free_all (headerlist);
	    }
	}
    }
  gtk_widget_destroy (dialog);
}

/* retail related settings */
void
retail_settings (GtkMenuItem * settingmenuitem, GtkWindow * parent_window)
{

}

