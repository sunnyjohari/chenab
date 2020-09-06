#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "connection.h"
#include<time.h>

#define SELECT_SAMPLE "SELECT * FROM esb_request WHERE status= ?" 

int select_status(char * status){
 
 MYSQL_STMT    *stmt;
 MYSQL_RES     *prepare_meta_result;
 MYSQL_TIME    ts;
 MYSQL_BIND    input_bind[1];
 unsigned long input_length;
 char          input_data[STRING_SIZE];
 MYSQL_BIND    bind[10];
 int           param_count, column_count, row_count;
 int           id; 
 char          int_data[8][STRING_SIZE];
 unsigned long str_length[10];
 bool          is_null[2];
 


 MYSQL *mysql = mysql_init(NULL);

  /* Print an error message incase
   * initialisation of con fails.
   */
  if (mysql == NULL) {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  /* Check if connection is 
   * properly established.
   */
  if (mysql_real_connect(mysql, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
       fprintf(stderr, "Error [%d]: %s \n",mysql_errno(con),mysql_error(con));
       mysql_close(con);
       return -1;
  }    


 stmt = mysql_stmt_init(mysql);
 if (!stmt)
 {
  fprintf(stderr, " mysql_stmt_init(), out of memory\n");
  return -1;
 }
  /* Prepare a SELECT query to fetch data from routes_table */
 if (mysql_stmt_prepare(stmt, SELECT_SAMPLE, strlen(SELECT_SAMPLE)))
 {
  fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  return -1;
 }
 fprintf(stdout, " prepare, SELECT successful\n");

 /* Get the parameter count from the statement */
 param_count= mysql_stmt_param_count(stmt);
 //fprintf(stdout, " total parameters in SELECT: %d\n", param_count);

 if (param_count != 1) /* validate parameter count */
 {
  fprintf(stderr, " invalid parameter count returned by MySQL\n");
  return -1;
 }


/* Fetch result set meta information */
 prepare_meta_result = mysql_stmt_result_metadata(stmt);
 if (!prepare_meta_result)
 {
  fprintf(stderr," mysql_stmt_result_metadata(), returned no meta information\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }

 /* Get total columns in the query */
 column_count= mysql_num_fields(prepare_meta_result);
// fprintf(stdout, " total columns in SELECT statement: %d\n", column_count);
 if (column_count != 10) /* validate column count */
 {
  fprintf(stderr, " invalid column count returned by MySQL\n");
  return -1;
 }

 memset(input_bind, 0, sizeof(input_bind));

 /* STRING COLUMN */
 input_bind[0].buffer_type= MYSQL_TYPE_STRING;
 input_bind[0].buffer= (char *)input_data;
 input_bind[0].buffer_length= STRING_SIZE;
 input_bind[0].is_null= 0;
 input_bind[0].length= &input_length;


 /* Bind the buffers */
 if (mysql_stmt_bind_param(stmt, input_bind))
 {
  fprintf(stderr, " mysql_stmt_bind_param() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  return -1;
 }

 strncpy(input_data, status, STRING_SIZE);
 input_length= strlen(input_data);


 if (mysql_stmt_execute(stmt))
 {
  fprintf(stderr, " mysql_stmt_execute,  failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  return -1;
 }

 /* Bind the result buffers for all 3 columns before fetching them */
 memset(bind, 0, sizeof(bind));

 /* This is a number type, so there is no need to specify buffer_length */
 /* INTEGER PARAM  for id*/
 bind[0].buffer_type= MYSQL_TYPE_LONG;
 bind[0].buffer= (char *)&id;
 bind[0].is_null= 0;
 bind[0].length= &str_length[0];


 /* STRING PARAM */
 bind[1].buffer_type= MYSQL_TYPE_STRING;
 bind[1].buffer= (char *)&int_data[0];
 bind[1].is_null= 0;
 bind[1].length= &str_length[1];
 bind[1].buffer_length= STRING_SIZE;


 /* STRING PARAM */
 bind[2].buffer_type= MYSQL_TYPE_STRING;
 bind[2].buffer= (char *)&int_data[1];
 bind[2].is_null= 0;
 bind[2].length= &str_length[2];
 bind[2].buffer_length= STRING_SIZE;


 /* STRING PARAM */
 bind[3].buffer_type= MYSQL_TYPE_STRING;
 bind[3].buffer= (char *)&int_data[2];
 bind[3].is_null= 0;
 bind[3].length= &str_length[3];
 bind[3].buffer_length= STRING_SIZE;


 /* STRING PARAM */
 bind[4].buffer_type= MYSQL_TYPE_STRING;
 bind[4].buffer= (char *)&int_data[3];
 bind[4].is_null= 0;
 bind[4].length= &str_length[4];
 bind[4].buffer_length= STRING_SIZE;


 /* STRING PARAM */
 bind[5].buffer_type= MYSQL_TYPE_STRING;
 bind[5].buffer= (char *)&int_data[4];
 bind[5].is_null= 0;
 bind[5].length= &str_length[5];
 bind[5].buffer_length= STRING_SIZE;


 /* DATETIME PARAM */
 bind[6].buffer_type= MYSQL_TYPE_DATETIME;
 bind[6].buffer= (char *)&ts;
 bind[6].is_null= 0;
 bind[6].length= &str_length[6];



 /* STRING PARAM */
 bind[7].buffer_type= MYSQL_TYPE_STRING;
 bind[7].buffer= (char *)&int_data[5];
 bind[7].is_null= &is_null[0];
 bind[7].length= &str_length[7];
 bind[7].buffer_length= STRING_SIZE;


 /* STRING PARAM */
 bind[8].buffer_type= MYSQL_TYPE_STRING;
 bind[8].buffer= (char *)&int_data[6];
 bind[8].is_null= 0;
 bind[8].length= &str_length[8];
 bind[8].buffer_length= STRING_SIZE;

 /* STRING PARAM */
 bind[9].buffer_type= MYSQL_TYPE_STRING;
 bind[9].buffer= (char *)&int_data[7];
 bind[9].is_null= &is_null[1];
 bind[9].length= &str_length[9];
 bind[9].buffer_length= STRING_SIZE;



 /* Bind the result buffers */
 if (mysql_stmt_bind_result(stmt, bind))
 {
  fprintf(stderr, " mysql_stmt_bind_result() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }

 /* Now buffer all results to client */
 if (mysql_stmt_store_result(stmt))
 {
  fprintf(stderr, " mysql_stmt_store_result() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }

 /* Fetch all rows */
 row_count= 0;
// fprintf(stdout, "Fetching results ...\n\n");
 //printf("HEADER--> id  sender_id  dest_id  message_type  reference_id  message_id received_on\t  data_location  status   status_details\n");
 int route_id;
 while (!mysql_stmt_fetch(stmt))
 {

  row_count++;
  route_id=id;
  #if 0
  fprintf(stdout, "row %d :-->", row_count);
  /* column 1 */
      fprintf(stdout, " %d  ", id);
        /* column 2 */
    fprintf(stdout, " %s  ", int_data[0]);

  	/* column 3 */
    fprintf(stdout, "     %s", int_data[1]);
 	/* column 4 */
    fprintf(stdout, "     %s", int_data[2]);
	/* column 5 */
    fprintf(stdout, "     %s", int_data[3]);
	/* column 6 */
    fprintf(stdout, "     %s", int_data[4]);
	/* column 7 */    
    fprintf(stdout, " %04d-%02d-%02d %02d:%02d:%02d \t",ts.year, ts.month, ts.day,
							   ts.hour, ts.minute, ts.second);

    /* column 8 */
    if (is_null[0])
    fprintf(stdout, " NULL\t");
    else
    fprintf(stdout, "     %s\t", int_data[5]);
    /* column 9 */
    fprintf(stdout, "     %s\t", int_data[6]);
    /* column 10 */
    if (is_null[1])
    fprintf(stdout, " NULL\t");
    else
    fprintf(stdout, "     %s\t", int_data[7]);
    


    printf("\n");
    #endif
}

 /* Validate rows fetched */
 fprintf(stdout, " total rows fetched: %d\n", row_count);

 /* Free the prepared result metadata */
 mysql_free_result(prepare_meta_result);

 /* Close the statement */
 if (mysql_stmt_close(stmt))
 {
  fprintf(stderr, " failed while closing the statement\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  return -1;
 }
 
 mysql_close(mysql); 
 return route_id;   
}


/*
int main(int argc, char **argv) {
   char * status="wewww";
   select_status(status);
   return 0;
}   

*/


  
