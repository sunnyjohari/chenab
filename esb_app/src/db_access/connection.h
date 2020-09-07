/**
 * @brief Parameters required for 
 * mysql_real_connect() function are declared as
 * global variables.
 * 
 */
#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdio.h>
#include <mysql.h>

#define SERVER "localhost"   /*hostname*/
#define USER  "root"       /*username*/
#define PASSWORD    "Pavan1999@"         /*blank password this user*/
#define DATABASE "esb_db"   /*name of the database*/
#define PORT  3306         /*port number*/
#define UNIX_SOCKET NULL   /*unix socket*/
#define FLAG 0             /*last parameter to mysql_real_connect*/

int insert_to_esb_request(char *sender_id,char *dest_id,
char *message_type,char *reference_id,char *message_id, 
char *data_location, char *status,char *status_details,char *received_on);
int active_routes_from_source(char *sender,char* destination,char *message_type);
int check_id_in_transform_config(int route_id);
int check_id_in_transport_config(int route_id);

#endif

