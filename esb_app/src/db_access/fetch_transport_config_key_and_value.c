
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mysql.h>
#include "connection.h"


#define STRING_SIZE 50

#define SELECT_SAMPLE "SELECT config_key,config_value FROM transport_config where route_id = ?"


transport_config *  fetch_transport_config_key_and_value(int route_id){

	MYSQL_STMT    *stmt;
    MYSQL_BIND    input_bind[1];
    unsigned long input_length;
    int           id;
	MYSQL_BIND    bind[2];
	MYSQL_RES     *prepare_meta_result;
	unsigned long length[2];
	int           param_count, column_count, row_count;
	short         small_data;
	int           int_data;
	char          str_data[2][STRING_SIZE];
	bool          is_null[2];
	
	
	MYSQL * mysql;

    mysql = mysql_init(NULL);
         
    if (mysql == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
	    return NULL;
    }  
  
    if (mysql_real_connect(mysql, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
	    fprintf(stderr, "Error [%d]: %s \n",mysql_errno(mysql),mysql_error(mysql));
	    mysql_close(mysql);
	    return NULL;
    }  
        
	/* Prepare a SELECT query to fetch data from test_table */
	stmt = mysql_stmt_init(mysql);
	if (!stmt)
	{
	  fprintf(stderr, " mysql_stmt_init(), out of memory\n");
	    return NULL;
	}
	if (mysql_stmt_prepare(stmt, SELECT_SAMPLE, strlen(SELECT_SAMPLE)))
	{
	  fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}
	fprintf(stdout, " prepare, SELECT successful\n");

	/* Get the parameter count from the statement */
	param_count= mysql_stmt_param_count(stmt);
	fprintf(stdout, " total parameters in SELECT: %d\n", param_count);

	if (param_count != 1) /* validate parameter count */
	{
	  fprintf(stderr, " invalid parameter count returned by MySQL\n");
	    return NULL;
	}

	/* Fetch result set meta information */
	prepare_meta_result = mysql_stmt_result_metadata(stmt);
	if (!prepare_meta_result)
	{
	  fprintf(stderr,
		 " mysql_stmt_result_metadata(), returned no meta information\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}

	/* Get total columns in the query */
	column_count= mysql_num_fields(prepare_meta_result);
	fprintf(stdout, " total columns in SELECT statement: %d\n", column_count);

	if (column_count != 2) /* validate column count */
	{
	  fprintf(stderr, " invalid column count returned by MySQL\n");
	    return NULL;
	}


    memset(input_bind, 0, sizeof(input_bind));

    /* STRING COLUMN */
    input_bind[0].buffer_type= MYSQL_TYPE_LONG;
    input_bind[0].buffer= (char *)&id;
    input_bind[0].is_null= 0;
    input_bind[0].length= &input_length;



    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmt, input_bind))
    {
    fprintf(stderr, " mysql_stmt_bind_param() failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    return NULL;
    }


    id=route_id;


	/* Execute the SELECT query */
	if (mysql_stmt_execute(stmt))
	{
	  fprintf(stderr, " mysql_stmt_execute(), failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}

	/* Bind the result buffers for all 4 columns before fetching them */

	memset(bind, 0, sizeof(bind));

	
	/* config_key  COLUMN */
	bind[0].buffer_type= MYSQL_TYPE_STRING;
	bind[0].buffer= (char *)str_data[0];
	bind[0].buffer_length= STRING_SIZE;
	bind[0].is_null= &is_null[0];
	bind[0].length= &length[0];

	/* config_value COLUMN */
    bind[1].buffer_type= MYSQL_TYPE_STRING;
	bind[1].buffer= (char *)str_data[1];
	bind[1].buffer_length= STRING_SIZE;
	bind[1].is_null= &is_null[1];
	bind[1].length= &length[1];
	
	
	

	/* Bind the result buffers */
	if (mysql_stmt_bind_result(stmt, bind))
	{
	  fprintf(stderr, " mysql_stmt_bind_result() failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}

	/* Now buffer all results to client */
	if (mysql_stmt_store_result(stmt))
	{
	  fprintf(stderr, " mysql_stmt_store_result() failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}

	/* Fetch all rows */
	row_count= 0;
	fprintf(stdout, "Fetching results ...\n");
    transport_config  * tp = (transport_config* ) malloc(sizeof(transport_config));
	if (!mysql_stmt_fetch(stmt))
	{
	  row_count++;
	  fprintf(stdout, "  row %d\n", row_count);

	  /* column 1 */
	  fprintf(stdout, "   column1 (config_key)  : ");
	  if (is_null[0])
	    fprintf(stdout, " NULL\n");
	  else
	    fprintf(stdout, " %s\n", str_data[0]);
	     tp->key=str_data[0];

	  /* column 2 */
	  fprintf(stdout, "   column2 (config_value)   : ");
	  if (is_null[1])
	    fprintf(stdout, " NULL\n");
	  else
	    fprintf(stdout, " %s\n", str_data[1]);
	     tp->value=str_data[1];
	    
	    /* Free the prepared result metadata */
	   mysql_free_result(prepare_meta_result);


	  /* Close the statement */
	  if (mysql_stmt_close(stmt))
	  {
	    fprintf(stderr, " failed while closing the statement\n");
	    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	  }
	  return tp;

	}

	/* Validate rows fetched */
	
	/* Free the prepared result metadata */
	mysql_free_result(prepare_meta_result);


	/* Close the statement */
	if (mysql_stmt_close(stmt))
	{
	  fprintf(stderr, " failed while closing the statement\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	return NULL;
	}
	
	return NULL;
}	

/*
int main()
{
    int id=15;
	transport_config * tp= fetch_transport_config_key_and_value(id);
    if(tp!=NULL)
	    printf("%s \n%s\n", tp->key,tp->value);
    else
    {
        printf("NO such type of route_id like %d\n", id);
    }
        
	return 0;
}	
*/