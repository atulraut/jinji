/*
 * model.h 
 *
 * model/database connectivity header file.
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

#define DB "/tmp/foobar"
#define SQL_FILENAME_DELIMITERS "_-|><,$!@--#%^&()[]*\/*%_; "
#define SQL_FILEPATH_DELIMITERS "_-|><,$!@--#%^&()[]*\*%_; "

#define DB_FIELDS_NUM 5

enum DB_FIELDS
{
  DB_LATITUDE,
  DB_LONGITUDE,
  DB_PATH,
  DB_FILE,
  DB_TIME,
};

typedef struct _database_contents database_contents;

#define CREATE_TABLE "create table if not exists korpi("
#define INSERT_INTO_TABLE "insert into korpi values("
#define DELETE_FROM_TABLE "delete from korpi where "
#define UPDATE_TABLE "update korpi set "
#define HEY_VACUUM "vacuum"
#define SQLITE3_GET_TABLE "select * from korpi"

void *database_open (void *database);
gint database_initialize ();
void database_cleanup (void *database);
gint get_data_from_model (gchar ** database_result);
void database_free_obtained_data (gchar ** database_result);
int return_database_entries (void);

