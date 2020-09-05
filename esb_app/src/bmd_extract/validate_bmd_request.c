#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "xml.h"
#include <string.h>
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

bool validate_bmd_request(char * filepath)
{
    bmd  * bd = (bmd*) malloc (sizeof(bmd));
    bd->envelope=  extract_envelope(filepath);
    bd->payload= extract_payload(filepath);

    if(validate_xml_file(bd)){
        int id =active_routes_from_source(bd->envelope->Sender,
                                           bd->envelope->Destination,bd->envelope->MessageType);
        if(id > 0 ){
          if(check_id_in_transform_config(id) &&  check_id_in_transport_config(id)){
             if(strlen(bd->payload) <= (5*1024*1024) ) {
               return true;
             }
          }
        }     
    }
    return false;                                         
}


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


/**
 * TODO: This is to be implemented separately.
 */
bmd * parse_bmd_xml(char * filepath)
{
   bmd  * bd = (bmd*) malloc (sizeof(bmd));
   bd->envelope=  extract_envelope(filepath);
   bd->payload= extract_payload(filepath);
   return bd;
}







int main()
{

    char  * filepath= "/home/bpavan/bmd_extract/dum.xml";
    bmd  * bd = (bmd*) malloc (sizeof(bmd));
    bd = parse_bmd_xml(filepath);
    printf("%d\n",insert_to_esb_request ( bd->envelope->Sender, bd->envelope->Destination, bd->envelope->MessageType,      \
                   bd->envelope->ReferenceID, bd->envelope->MessageID,bd->envelope->CreationDateTime,    \
                   "","received",""));
     validate_bmd_request(filepath)? printf("\nyes valid \n"):printf("NOT valid\n");
                              
    return 0;
}
