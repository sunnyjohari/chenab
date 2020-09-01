// header file

#define STRING_SIZE 500

/**
 * @brief Parameters requiered for 
 * mysql_real_connect() function are declared as
 * global variables.
 * 
 */


const char *server = "localhost";
const char *user = "root";
const char *password = "Pavan1999@"; /*password is not set in this example*/
const char *database = "esb_db";

const unsigned int port = 3306; /*port number*/
const char * unix_socket = NULL; /*unix socket*/
const unsigned int flag = 0; /*last parameter to mysql_real_connect*/



/**
 * @brief Whenever there is an error opening a database
 * or executing a query finish_with_error prints error
 * specifying error number and error message
 * 
 * @param con database connection handle
 */
void finish_with_error(MYSQL *con) {

  fprintf(stderr, "Error [%d]: %s \n",mysql_errno(con),mysql_error(con));
  mysql_close(con);

  exit(1);        
}

