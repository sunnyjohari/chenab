#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "connection.h"

#define SELECT_SAMPLE "SELECT id,route_id,config_key,config_value FROM transform_config WHERE route_id= ?" 

void finish_with_error(MYSQL *con) {

  fprintf(stderr, "Error [%d]: %s \n",mysql_errno(con),mysql_error(con));
  mysql_close(con);

  exit(1);        
}





bool check_id_in_transform_config(int route_id){

 MYSQL_STMT    *stmt;
 MYSQL_BIND    input_bind[1];
 unsigned long input_length[2];
 MYSQL_BIND    bind[4];
 MYSQL_RES     *prepare_meta_result;
 MYSQL_TIME    ts;
 unsigned long length[4];
 int           param_count, column_count, row_count;
 int           small_data;
 int big_data;
 int           int_data;
 char          str_data[2][STRING_SIZE];




server = "localhost";
user = "root";
password = "Pavan1999@"; /*password is not set in this example*/
database = "esb_db";

port = 3306; /*port number*/
unix_socket = NULL; /*unix socket*/
int flag = 0; /*last parameter to mysql_real_connect*/


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

   char query[STRING_SIZE]; /*to store query*/

  /*Fill in the query with parameters*/
  sprintf(query,
  "SELECT * FROM transport_config WHERE route_id = %d ",
  route_id);
  //printf("For query :%s\n",query);
  /*checks execution of SQL statement*/
  if (mysql_query(mysql, query)) {
      finish_with_error(mysql);
  }

  MYSQL_RES *result;/*structure that holds result set*/

  /* Gets the result set and stores in result */
  result = mysql_store_result(mysql); 
  
  /* if there is no result error will be returned*/
  if (result == NULL) {
      finish_with_error(mysql);
  }

  /* stores number of fields in the result*/ 
  int num_fields = mysql_num_fields(result);
  /*mysql structure that holds a row*/
  MYSQL_ROW row;
  /*mysql structure that holds field values*/
  MYSQL_FIELD *field;
   int rows = mysql_num_rows(result);
  /*prints all the rows from the result*/
 /* while ((row = mysql_fetch_row(result))) { 
      for(int i = 0; i < num_fields; i++) { 
          if(i==0) {
              while(field = mysql_fetch_field(result)) {
                  printf(" %s |", field->name);
              } 
              printf("\n");
            }

          printf(" %s |", row[i] ? (char *)row[i] : "NULL"); 
      } 
          printf("\n"); 
  }
  */
  /*frees the result*/
  mysql_free_result(result);
  /*closes the database connection*/
  mysql_close(mysql);
  if(rows== 1)
      return true;
  return false;
}


/*
int main(int argc, char **argv) {
   int route_id=15;
   select_transform_config(route_id);
   return 0;
}   
*/



  
