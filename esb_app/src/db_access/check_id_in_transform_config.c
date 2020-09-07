#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include "connection.h"

#define SELECT_SAMPLE "SELECT id,route_id,config_key,config_value FROM transform_config WHERE route_id= ?" 


#define STRING_SIZE 200

int  check_id_in_transform_config(int route_id){

	 MYSQL_STMT    *stmt;
	 MYSQL_BIND    input_bind[1];
	 unsigned long input_length[3];
	 MYSQL_BIND    bind[4];
	 MYSQL_RES     *prepare_meta_result;
	 int id;
	 unsigned long length[4];
	 int           param_count, column_count, row_count;
	 int          small_data[2];
	 char str_data[2][STRING_SIZE];
	 bool is_null[4];

	 MYSQL *mysql = mysql_init(NULL);

	  /* Print an error message incase
	   * initialisation of con fails.
	   */
	 if (mysql == NULL) {
	    fprintf(stderr, "mysql_init() failed\n");
	    return -1;
	  }  
	  
	  /* Check if connection is 
	   * properly established.
	   */
	 if (mysql_real_connect(mysql, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
	     fprintf(stderr, "Error [%d]: %s \n",mysql_errno(mysql),mysql_error(mysql));
	     mysql_close(mysql);
	     return -1;
	 }   


	 stmt = mysql_stmt_init(mysql);
	 if (!stmt){
	  fprintf(stderr, " mysql_stmt_init(), out of memory\n");
	  exit(0);
	 }
	  /* Prepare a SELECT query to fetch data from routes_table */
	 if (mysql_stmt_prepare(stmt, SELECT_SAMPLE, strlen(SELECT_SAMPLE))) {
	  fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
          return -1;
	 }
	 //fprintf(stdout, " prepare, SELECT successful\n");

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
          return -1;
	 }

	 /* Get total columns in the query */
	 column_count= mysql_num_fields(prepare_meta_result);
	// fprintf(stdout, " total columns in SELECT statement: %d\n", column_count);
	 if (column_count != 4) /* validate column count */
	 {
	  fprintf(stderr, " invalid column count returned by MySQL\n");
          return -1;
	 }

	 memset(input_bind, 0, sizeof(input_bind));

	 /* STRING COLUMN */
	 input_bind[0].buffer_type= MYSQL_TYPE_LONG;
	 input_bind[0].buffer= (char *)&id;
	 input_bind[0].is_null= 0;
	 input_bind[0].length= &input_length[0];



	 /* Bind the buffers */
	 if (mysql_stmt_bind_param(stmt, input_bind))
	 {
	  fprintf(stderr, " mysql_stmt_bind_param() failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
          return -1;
	 }


	 id=route_id;
	 
	 if (mysql_stmt_execute(stmt))
	 {
	  fprintf(stderr, " mysql_stmt_execute,  failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
          return -1;
	 }

	 /* Bind the result buffers for all 3 columns before fetching them */
	 memset(bind, 0, sizeof(bind));
	 
	 

	 /* SENDER COLUMN */
	 bind[0].buffer_type= MYSQL_TYPE_LONG;
	 bind[0].buffer= (char *)&small_data[0];
	 bind[0].is_null= &is_null[0];
	 bind[0].length= &length[0];
	 
	 bind[1].buffer_type= MYSQL_TYPE_LONG;
	 bind[1].buffer= (char *)&small_data[1];
	 bind[1].is_null= &is_null[1];
	 bind[1].length= &length[1];
	 
	 bind[2].buffer_type= MYSQL_TYPE_STRING;
	 bind[2].buffer= (char *)str_data[0];
	 bind[2].buffer_length= STRING_SIZE;
	 bind[2].is_null= &is_null[2];
	 bind[2].length= &length[2];
	 
	  bind[3].buffer_type= MYSQL_TYPE_STRING;
	 bind[3].buffer= (char *)str_data[1];
	 bind[3].buffer_length= STRING_SIZE;
	 bind[3].is_null= &is_null[3];
	 bind[3].length= &length[3];
	 
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
          return -1;
	 }

	 /* Fetch all rows */
	 row_count= 0;
	 //fprintf(stdout, "Fetching results ...\n\n");
	 //printf("    route_id     Sender    Destination     Messsage_type\n");
	 while (!mysql_stmt_fetch(stmt))
	 {

	  row_count++;

	 // fprintf(stdout, "  row %d\t", row_count);

	 // fprintf(stdout, " %d\t",id );

	  //fprintf(stdout, " %s\t", str_data[0]);

	  //fprintf(stdout, "     %s\t\t", str_data[1]);

	   printf("   %d\n", small_data[0]);
	   
	      printf("   %d\n", small_data[1]);
	  fprintf(stdout, " %s\t", str_data[0]);
	    fprintf(stdout, " %s\t", str_data[1]);
	   mysql_free_result(prepare_meta_result);

	 /* Close the statement */
	 if (mysql_stmt_close(stmt))
	 {
	  fprintf(stderr, " failed while closing the statement\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
          return -1;
	 }
	   return 1;
	}

	 /* Validate rows fetched */
	// fprintf(stdout, " total rows fetched: %d\n", row_count);

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
	 
	 return -1; 
	}


	/*
	int main(int argc, char **argv) {
	   int route_id=15;
	   check_id_in_transport_config(route_id)?printf("yes\n"):printf("NO\n");
	   return 0;
	}   */



	  
