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
int insert_to_esb_request ( char * sender_id, char * dest_id, char * message_type,      \
                   char * reference_id, char * message_id,char * received_on,char * data_location, \
                   char * status,char * status_details);
void select_status_of_route_id(char * status); 
void select_transport_config(int roue_id);


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