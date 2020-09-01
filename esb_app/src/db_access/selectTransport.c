#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include "connection.h"

void select_transport_config(int roue_id){

MYSQL *conn = mysql_init(NULL);

/* Print an error message incase
* initialisation of con fails.
*/
  if (conn == NULL) {
      finish_with_error(conn);
  }  
  
/* Check if connection is 
* properly established.
*/
if (mysql_real_connect(conn, server, user, password,database,port,unix_socket,flag) == NULL) {
      finish_with_error(conn);
}    

char query[STRING_SIZE];

/*sends formatted output to a string pointed to, by query*/
sprintf(query,
        "SELECT * FROM transport_config WHERE status= %d ", 
        route_id);
  printf("For query :%s\n",query);

  /*checks execution of SQL statement*/
  if (mysql_query(conn, query)) {
      finish_with_error(conn);
  }

  MYSQL_RES *result;/*structure that holds result set*/

  /* Gets the result set and stores in result */
  result = mysql_store_result(conn); 
  
  /* if there is no result error will be returned*/
  if (result == NULL) {
      finish_with_error(conn);
  }

  /* stores number of fields in the result*/ 
  int num_fields = mysql_num_fields(result);

  /*mysql structure that holds a row*/
  MYSQL_ROW row;

  /*mysql structure that holds field values*/
  MYSQL_FIELD *field;
      
printf("\n* -------------------------------------------- ------------*\n");
// for printing colum headers
  while(field = mysql_fetch_field(result)) {
       printf(" %s |", field->name);
    } 
printf("\n* -------------------------------------------- ------------*\n");
int num =mysql_num_rows(result);
if(num==0){
    printf("\t\tNO rows\t\t\n");
}
else{
  while ((row = mysql_fetch_row(result))) { 
      for(int i = 0; i < num_fields; i++) { 
          printf(" \t%s  |", row[i] ?row[i] : "NULL"); 
      } 
      printf("\n");
  }
} 
printf("* -------------------------------------------- ------------*\n");

  /*frees the result*/
  mysql_free_result(result);
  /*closes the database connection*/
  mysql_close(conn);  
}

int main(int argc, char **argv) {
   int route_id=1;
   select_transport_config(route_id);
   return 0;
}   




  