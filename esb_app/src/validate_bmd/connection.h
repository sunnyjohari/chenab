// header file


#ifndef CONNECTION_H
#define CONNECTION_H
#include <stdbool.h>
#include <stddef.h>
#define STRING_SIZE 500

/**
 * @brief Parameters requiered for 
 * mysql_real_connect() function are declared as
 * global variables.
 * 
 */


bool check_id_in_transform_config(int route_id);
bool check_id_in_transport_config(int route_id);
int active_routes_from_source(char * message, char * destination, char * message_type);


static char *server ;
static  char *user ;
static char *password ; /*password is not set in this example*/
static char *database ;

static  unsigned int port ; /*port number*/
static char * unix_socket ; /*unix socket*/
static  unsigned int flag ; /*last parameter to mysql_real_connect*/







/**
 * @brief Whenever there is an error opening a database
 * or executing a query finish_with_error prints error
 * specifying error number and error message
 * 
 * @param con database connection handle
 */

#endif