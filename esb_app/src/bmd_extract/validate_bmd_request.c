#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "xml.h"
#include <string.h>
#include <libxml/parser.h>
#include "../db_access/connection.h"

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








int  is_bmd_valid(bmd  * bd)
{
   

   char * sender=bd->envelope->Sender;
   char * destination=bd->envelope->Destination;
   char * message_type= bd->envelope->MessageType;
   


    if(validate_xml_file(bd)){
        int id =active_routes_from_source(sender,destination,message_type);                                 
        if(id > 0 ){
             if(check_id_in_transform_config(id) >=0  &&  check_id_in_transport_config(id) >=0 ){
              char * file = xml_to_json(bd);
              if(find_size(file) <= MAX_SIZE)
               return 1;
            } 
          }
        }     
   
    return 0;                                         
}



/* @ brief: validating bmd.
 * checking whether xml file consists of appropriate elements.
 * if it contains returns 1
 * else return 0
*/



int validate_xml_file( bmd * bmd_file)
{
  /* MessageID */
  if(bmd_file->envelope->MessageID  == NULL) {
    fprintf(stderr,"Message ID doesnot exist in bmd");
    return 0;
  }

  /* MessageType */
  if(bmd_file->envelope->MessageType == NULL) {
    fprintf(stderr,"Message Type doesnot exist in bmd");
    return 0;
  }

  /* Sender */
  if(bmd_file->envelope->Sender == NULL) {
    fprintf(stderr,"Sender doesnot exist in bmd");
    return 0;
  }


  /* Destination */
  if(bmd_file->envelope->Destination == NULL) {
    fprintf(stderr,"Destination doesnot exist in bmd");
    return 0;
  }


  /* CreationDateTime */
  if(bmd_file->envelope->CreationDateTime == NULL) {
    fprintf(stderr,"CreationDateTime doesnot exist in bmd");
    return 0;
  }


  /* Signature */
  if(bmd_file->envelope->Signature == NULL) {
    fprintf(stderr,"Signature doesnot exist in bmd");
    return 0;
  }

  /* ReferenceID */
  if(bmd_file->envelope->ReferenceID == NULL) {
      fprintf(stderr,"ReferenceID doesnot exist in bmd");
      return 0;
  }

  /* payload */
  if(bmd_file->payload == NULL) {
    fprintf(stderr,"Payload doesnot exist in bmd");
    return 0;
  }

  return 1;
}







