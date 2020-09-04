#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "xml.h"
#include <string.h>
#include "connection.h"

/* @ brief : validating bmd request
*  input : filepath output yes/no
*  validating bmd request under 4 conditions
* 1.The mandatory values (Sender, Destination, Message Type, etc.) must be present in the
*    received BMD.
* 2. For the received {Sender, Destination, Message Type}, there should be an active route
*    record present in the routes table (​ see here​ ).
* 3. For the selected route record, there should be corresponding records present in
*    transport_config and transform_config tables.
* 4. We will also check for some upper limit on the payload size. For example, the payload
*    larger than 5MB may not be allowed, or are allowed only for certain senders and message
*    types, etc. 
*/
bool validate_bmd_request(char * filepath)
{
    bmd  * bd = (bmd*) malloc (sizeof(bmd));
    bd->envelope=  extract_envelope(filepath);
    bd->Payload= extract_payload(filepath);

    if(validate_xml_file(bd)){
        int id =active_routes_from_source(bd->envelope->Sender,
                                           bd->envelope->Destination,bd->envelope->MessageType);
        if(id > 0 ){
          if(check_id_in_transform_config(id) &&  check_id_in_transport_config(id)){
               return true;
            // TODO : check payload data <= 5MB
          }
        }     
    }
    return false;                                         
}



int main()
{

    char  * filepath= "/home/bpavan/bmd_extract/dum.xml";
    if(validate_bmd_request(filepath)){
      printf("request validated\n");
    }
                              
    return 0;
}
