
/*Required C standard libraries*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/* Contains necessary C functions of mysql */
#include <mysql/mysql.h>

/* C standard macro and library for handling datetime*/
#include <time.h>
#include "connection.h"


#define INSERT_SAMPLE "INSERT INTO                                  \
esb_request(id,sender_id,dest_id,message_type,reference_id,     \
message_id,data_location,status,status_details,received_on)              \
VALUES(?,?,?,?,?,?,?,?,?,?)"


#define INSERT_SAMPLE1 "INSERT INTO                                  \
esb_request(id,sender_id,dest_id,message_type,reference_id,     \
message_id,data_location,status,status_details)              \
VALUES(?,?,?,?,?,?,?,?,?)"

int  insert_to_esb_request ( char * sender_id, char * dest_id, char * message_type,      \
                   char * reference_id, char * message_id,char * received_on,char * data_location, \
                   char * status,char * status_details){
                   
 MYSQL_STMT    *stmt;
 MYSQL_BIND    bind[10];
 MYSQL_TIME    ts;
 my_ulonglong  affected_rows;
 int           param_count;
 int           id; 
 char          int_data[8][STRING_SIZE];
 unsigned long str_length[8];
 bool          is_null[2];
 int col=9;

 char *server = "localhost";
 char *user = "root";
 char *password = "Pavan1999@"; /*password is not set in this example*/
 char *database = "esb_db";
 unsigned int port = 3306; /*port number*/
 char * unix_socket = NULL; /*unix socket*/
 unsigned int flag = 0; /*last parameter to mysql_real_connect*/



  /**
   * @brief Allocates and initialises a MYSQL object 
   * suitable for mysql_real_connect() function
   * 
   */

  MYSQL *conn = mysql_init(NULL); /*database connection handle*/
  
  /**
   * @brief Prints error message incase
   * initialisation of con fails.
   */
  

  if (conn == NULL) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      return 0;
  }  
  
  /**
   * @brief Checks if connection is 
   * properly established.
   * 
   */
  if (mysql_real_connect(conn, server, user, password,database,port,unix_socket,flag) == NULL) {
      fprintf(stderr, "%s\n", mysql_error(conn));
      mysql_close(conn);
      return 0;
  }    



/* Prepare an INSERT parameters */
stmt = mysql_stmt_init(conn);
if (!stmt)
{
  fprintf(stderr, " mysql_stmt_init(), out of memory\n");
      return 0;
}
int pp=9;
if(received_on != NULL && received_on !="")
{
   pp=10;
   col=10;
  if (mysql_stmt_prepare(stmt, INSERT_SAMPLE, strlen(INSERT_SAMPLE)))
  {
    fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
      return 0;
  }
}
else
   if (mysql_stmt_prepare(stmt, INSERT_SAMPLE1, strlen(INSERT_SAMPLE1)))
  {

    fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    return 0;
  }



fprintf(stdout, " prepare, INSERT successful\n");

/* Get the parameter count from the statement */
param_count= mysql_stmt_param_count(stmt);
fprintf(stdout, " total parameters in INSERT: %d\n", param_count);

if (param_count != pp) /* validate parameter count */
{
  fprintf(stderr, " invalid parameter count returned by MySQL\n");
  return 0;
}



/* Bind the data for all 9 including id parameters */

memset(bind, 0, sizeof(bind));

/* This is a number type, so there is no need to specify buffer_length */
/* INTEGER PARAM  for id*/
bind[0].buffer_type= MYSQL_TYPE_LONG;
bind[0].buffer= (char *)&id;
bind[0].is_null= 0;
bind[0].length= 0;


/* Sender id */
bind[1].buffer_type= MYSQL_TYPE_STRING;
bind[1].buffer= (char *)&int_data[0];
bind[1].is_null= 0;
bind[1].length= &str_length[0];
bind[1].buffer_length= STRING_SIZE;


/* dest_id */
bind[2].buffer_type= MYSQL_TYPE_STRING;
bind[2].buffer= (char *)&int_data[1];
bind[2].is_null= 0;
bind[2].length= &str_length[1];
bind[2].buffer_length= STRING_SIZE;


/* message_type */
bind[3].buffer_type= MYSQL_TYPE_STRING;
bind[3].buffer= (char *)&int_data[2];
bind[3].is_null= 0;
bind[3].length= &str_length[2];
bind[3].buffer_length= STRING_SIZE;


/* reference_id */
bind[4].buffer_type= MYSQL_TYPE_STRING;
bind[4].buffer= (char *)&int_data[3];
bind[4].is_null= 0;
bind[4].length= &str_length[3];
bind[4].buffer_length= STRING_SIZE;


/* STRING PARAM */
bind[5].buffer_type= MYSQL_TYPE_STRING;
bind[5].buffer= (char *)&int_data[4];
bind[5].is_null= 0;
bind[5].length= &str_length[4];
bind[5].buffer_length= STRING_SIZE;



/* data_location */
 bind[6].buffer_type= MYSQL_TYPE_STRING;
 bind[6].buffer= (char *)&int_data[5];
 bind[6].is_null= &is_null[0];
 bind[6].length= &str_length[5];
 bind[6].buffer_length= STRING_SIZE;


/* status */
 bind[7].buffer_type= MYSQL_TYPE_STRING;
 bind[7].buffer= (char *)&int_data[6];
 bind[7].is_null= 0;
 bind[7].length= &str_length[6];
 bind[7].buffer_length= STRING_SIZE;

 /* status details */
 bind[8].buffer= (char *)&int_data[7];
 bind[8].is_null= &is_null[1];
 bind[8].length= &str_length[7];
 bind[8].buffer_length= STRING_SIZE;

 if(received_on != "" && received_on !=NULL){
 /* Received on */  
 bind[9].buffer_type= MYSQL_TYPE_DATETIME;
 bind[9].buffer= (char *)&ts;
 bind[9].is_null= 0;
 bind[9].length= 0;
 /* C structure to store DATETIME format */
  struct tm res;// storing time  
  /* Convert string to DATETIME format. Store the result*/   
 if (strptime(received_on, "%Y-%m-%dT%H:%M:%S+%Z",&res) ==0)
      printf("\nstrptime failed\n");
  /* Epoch is 1900 in C standard */
  ts.year= res.tm_year+1900;
  /* Month count is from 0(JAN) */
  ts.month= res.tm_mon+1;
  ts.day= res.tm_mday;
  ts.hour= res.tm_hour;
  ts.minute= res.tm_min;
  ts.second= res.tm_sec;
 } 

  /* Bind the buffers */
if (mysql_stmt_bind_param(stmt, bind))
{
    fprintf(stderr, " mysql_stmt_bind_param() failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    exit(0);
}


if (mysql_query(conn, "SELECT * FROM esb_request")) 
  {
      finish_with_error(conn);
  }
  
  MYSQL_RES *result = mysql_store_result(conn);
  
  if (result == NULL) 
  {
      finish_with_error(conn);
  }
  
  int nu;
    MYSQL_ROW row;
  while ((row = mysql_fetch_row(result))) {               
         nu = atoi(row[0]);
         }
  printf("%d\n",nu);
  mysql_free_result(result);

 nu+=1;
 id=nu;
 strncpy(int_data[0], sender_id, STRING_SIZE);
 strncpy(int_data[1], dest_id, STRING_SIZE);
 strncpy(int_data[2], message_type, STRING_SIZE);
 strncpy(int_data[3], reference_id, STRING_SIZE);
 strncpy(int_data[4], message_id, STRING_SIZE);
 if( data_location == "" || data_location == NULL){
     is_null[0]=1;
 }
 else {
    strncpy(int_data[5], data_location, STRING_SIZE);
    is_null[0] = 0;
 }
 
 strncpy(int_data[6], status, STRING_SIZE);

 if(status_details == "" || status_details == NULL){
     is_null[1] =1;
 }
 else {
   strncpy(int_data[7], status_details, STRING_SIZE);
   is_null[1]=0;
 } 



   for(int i=0;i<8;i++)
       str_length[i]= strlen(int_data[i]);


 /* Execute the INSERT statement */
 if (mysql_stmt_execute(stmt))
 {
  fprintf(stderr, " mysql_stmt_execute, 1 failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }

 /* Get the total rows affected */
 affected_rows= mysql_stmt_affected_rows(stmt);
 fprintf(stdout, " total affected rows(insert 2): %lu\n",
                (unsigned long) affected_rows);

 if (affected_rows != 1) /* validate affected rows */
 {
  fprintf(stderr, " invalid affected rows by MySQL\n");
  exit(0);
  return 0;
 }

 /* Close the statement */
 if (mysql_stmt_close(stmt))
 {
  fprintf(stderr, " failed while closing the statement\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  return 0;
 }

 printf("connection id: %ld\n", mysql_thread_id(conn));
  
 /*closes the database connection*/
  mysql_close(conn);  
  return 1;
}

/* sample test case through main
int main(int argc, char **argv) {
      char * attr [] = {"A","aaa","ass888a","asasa88","asas--asas","","","wewww",""};
     esb_request(attr[0],attr[1],attr[2],attr[3],attr[4],attr[5],attr[6],attr[7],attr[8]);
      return 0;
}    */
