#include <stdio.h>
#include <mysql/mysql.h>
#include<stdlib.h>
#include<string.h>
#include "connection.h"

#define UPDATE_SAMPLE "UPDATE esb_request SET status=? WHERE id=?"

int  update_esb_request(int index, char * status){

MYSQL_STMT    *stmt;
MYSQL_BIND    bind[2];
my_ulonglong  affected_rows;
int           param_count;
int           id; 
char          int_data[STRING_SIZE];
unsigned long str_length;
bool          is_null;


MYSQL *conn = mysql_init(NULL);
  /* Print an error message incase
   * initialisation of con fails.
   */
  if (conn == NULL) {

      fprintf(stderr, "mysql_init() failed\n");
      return -1;
  }  
  
  /* Check if connection is 
   * properly established.
   */
  if (mysql_real_connect(conn, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
      finish_with_error(conn);
        return -1;
  }    


/* Prepare an UPDATE query with 2 parameters */
  stmt = mysql_stmt_init(mysql);
  if (!stmt)
  {
    finish_with_error(conn);
    return -1;
  }


  if (mysql_stmt_prepare(stmt, UPDATE_SAMPLE, strlen(UPDATE_SAMPLE)))
  {
    finish_with_error(conn);
    return -1;
  }

  fprintf(stdout, " prepare, INSERT successful\n");

  /* Get the parameter count from the statement */
  param_count= mysql_stmt_param_count(stmt);
  fprintf(stdout, " total parameters in INSERT: %d\n", param_count);

  if (param_count != 2) /* validate parameter count */
  {
    fprintf(stderr, " invalid parameter count returned by MySQL\n");
    return -1;
  }

  /* Bind the data for all 3 parameters */

  memset(bind, 0, sizeof(bind));

  /* STRING PARAM */
  bind[0].buffer_type= MYSQL_TYPE_STRING;
  bind[0].buffer= (char *)&int_data;
  bind[0].is_null= 0;
  bind[0].length= &str_length;
  bind[0].buffer_length= STRING_SIZE;

  /* This is a number type, so there is no need to specify buffer_length */
  /* INTEGER PARAM */
  bind[1].buffer_type= MYSQL_TYPE_LONG;
  bind[1].buffer= (char *)&id;
  bind[1].is_null= 0;
  bind[1].length= 0;

  /* Bind the buffers */
  if (mysql_stmt_bind_param(stmt, bind))
  {
    fprintf(stderr, " mysql_stmt_bind_param() failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    return -1;
  }

  id = index;
  strncpy(int_data, status, STRING_SIZE);
  str_length= strlen(int_data);

  /* Execute the UPDATE statement */
  if (mysql_stmt_execute(stmt))
  {
    fprintf(stderr, " mysql_stmt_execute, 2 failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    return -1;
  }

  /* Get the total rows affected */
  affected_rows= mysql_stmt_affected_rows(stmt);
  fprintf(stdout, " total affected rows(insert 2): %lu\n",
                (unsigned long) affected_rows);

  if (affected_rows != 1) /* validate affected rows */
  {
    fprintf(stderr, " invalid affected rows by MySQL\n");
    return -1;
  }

  /* Close the statement */
  if (mysql_stmt_close(stmt))
  {
    finish_with_error(conn);
    return -1;
  }

   printf("connection id: %ld\n", mysql_thread_id(mysql));
  
  /*closes the database connection*/
   mysql_close(conn);  
   
   return 1;
  
}

int main(int argc, char **argv) {
    char * status = "RECEIVED";
    int id=2;
    update_esb_request(id,status);
    return 0;
}  
