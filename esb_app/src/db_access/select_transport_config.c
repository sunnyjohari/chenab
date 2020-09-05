#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "connection.h"

#define SELECT_SAMPLE "SELECT * FROM transport_config WHERE id= ?" 

void finish_with_error(MYSQL *con) {

  fprintf(stderr, "Error [%d]: %s \n",mysql_errno(con),mysql_error(con));
  mysql_close(con);

  exit(1);
}

void select_transport_config(int route_id){

 MYSQL_STMT    *stmt;
 MYSQL_BIND    input_bind[1];
 unsigned long input_length[2];
 MYSQL_BIND    bind[4];
 MYSQL_RES     *prepare_meta_result;
 MYSQL_TIME    ts;
 unsigned long length[4];
 int           param_count, column_count, row_count;
 int           small_data;
 int           big_data;
 int           int_data;
 char          str_data[2][STRING_SIZE];
 bool       is_null[3];
 server = "localhost";
 user = "root";
 password = "Pavan1999@"; /*password is not set in this example*/
 database = "esb_db";

 port = 3306; /*port number*/
 unix_socket = NULL; /*unix socket*/
 flag = 0; /*last parameter to mysql_real_connect*/

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
  if (mysql_real_connect(mysql, server, user, password,database,0,NULL,0) == NULL) {
      finish_with_error(mysql);
  }    


 stmt = mysql_stmt_init(mysql);
 if (!stmt)
 {
  fprintf(stderr, " mysql_stmt_init(), out of memory\n");
  exit(0);
 }
  /* Prepare a SELECT query to fetch data from routes_table */
 if (mysql_stmt_prepare(stmt, SELECT_SAMPLE, strlen(SELECT_SAMPLE)))
 {
  fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }
 fprintf(stdout, " prepare, SELECT successful\n");

 /* Get the parameter count from the statement */
 param_count= mysql_stmt_param_count(stmt);
 fprintf(stdout, " total parameters in SELECT: %d\n", param_count);

 if (param_count != 1) /* validate parameter count */
 {
  fprintf(stderr, " invalid parameter count returned by MySQL\n");
  exit(0);
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
 fprintf(stdout, " total columns in SELECT statement: %d\n", column_count);
 if (column_count != 4) /* validate column count */
 {
  fprintf(stderr, " invalid column count returned by MySQL\n");
  exit(0);
 }
int id;
 memset(input_bind, 0, sizeof(input_bind));

 /* This is a number type, so there is no need to specify buffer_length */
/* INTEGER PARAM  for id*/
 input_bind[0].buffer_type= MYSQL_TYPE_LONG;
 input_bind[0].buffer= (char *)&id;
 input_bind[0].is_null= 0;
 input_bind[0].length= 0;

 



 /* Bind the buffers */
 if (mysql_stmt_bind_param(stmt, input_bind))
 {
  fprintf(stderr, " mysql_stmt_bind_param() failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }
 
 id =route_id;
 

 if (mysql_stmt_execute(stmt))
 {
  fprintf(stderr, " mysql_stmt_execute,  failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
 }

 /* Bind the result buffers for all 3 columns before fetching them */
 memset(bind, 0, sizeof(bind));

 /* SENDER COLUMN */
 bind[0].buffer_type= MYSQL_TYPE_LONG;
 bind[0].buffer= (char *)&small_data;
 bind[0].is_null= 0;
 bind[0].length= &length[0];


 

 
 /* DESTINATION COLUMN */
 bind[1].buffer_type= MYSQL_TYPE_LONG;
 bind[1].buffer= (char *)&big_data;
 bind[1].is_null= &is_null[1];
 bind[1].length= &length[1];
 
 /* SMALLINT COLUMN */
 bind[2].buffer_type= MYSQL_TYPE_STRING;
 bind[2].buffer= (char *)str_data[0];       
 bind[2].is_null=&is_null[1];
 bind[2].length= &length[2];
 bind[2].buffer_length= STRING_SIZE;
 
 
 bind[2].buffer_type= MYSQL_TYPE_STRING;
 bind[2].buffer= (char *)str_data[1];       
 bind[2].is_null=&is_null[1];
 bind[2].length= &length[3];
 bind[2].buffer_length= STRING_SIZE;

 //* Bind the result buffers */
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
 fprintf(stdout, "Fetching results ...\n\n");
 printf("Header--> id   route_id    config_key     config_value\n");
 while (!mysql_stmt_fetch(stmt))
 {
  printf("yess\n");
  row_count++;
  fprintf(stdout, "  row %d\t", row_count);
  /* column 1 */

    fprintf(stdout, " %d\t", small_data);

  /* column 2 */
    fprintf(stdout, "     %d\t", big_data);

  /* column 3 */
    printf("   %s\t", str_data[0]);
 
  /* column 4 */
    printf("   %s\n", str_data[1]);
       
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
  exit(0);
 }
 
 mysql_close(mysql);   
}

int main(int argc, char **argv) {
   int route_id=15;
   select_transport_config(1);
   return 0;
}   




  
