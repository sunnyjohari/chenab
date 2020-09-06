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
                   
int select_status(char * status);
int update_esb_request(int index, char * status);                   

#define SERVER "localhost"
#define USER "root" 
#define PASSWORD "Pavan1999@" /*password is not set in this example*/
#define  DATABASE "esb_db" 
#define PORT 3306  /*port number*/
#define UNIX_SOCKET NULL /*unix socket*/
#define FLAG 0  /*last parameter to mysql_real_connect*/







/**
 * @brief Whenever there is an error opening a database
 * or executing a query finish_with_error prints error
 * specifying error number and error message
 * 
 * @param con database connection handle
 */

#endif
