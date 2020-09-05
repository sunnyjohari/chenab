#include<stdio.h>
#include "../adapter/email.h"
#include "esb.h"
#include "../db_access/connection.h"

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


int is_bmd_valid(bmd * b)
{  
   int valid =1, invalid = -1;
    if(validate_xml_file(b)){
        int id =active_routes_from_source(b->envelope->Sender,
                                           b->envelope->Destination,b->envelope->MessageType);
        if(id > 0 ){
          if(check_id_in_transform_config(id) &&  check_id_in_transport_config(id)){
             if(strlen(b->payload) <= (5*1024*1024) ) {
               return valid;
             }
          }
        }     
    }
    return invalid;                                         
}

int queue_the_request(bmd * bd)
{
    int success = 1; // 1 => OK, -1 => Error cases
    int error = -1;
    /** 
     * TODO: Insert the envelop data into esb_requests table,
     * and implement other logic for enqueueing the request
     * as specified in Theory of Operation.
     */

    if(insert_to_esb_request ( bd->envelope->Sender, bd->envelope->Destination, bd->envelope->MessageType,      \
                   bd->envelope->ReferenceID, bd->envelope->MessageID,bd->envelope->CreationDateTime,    \
                   "","received",""));
             return success;

     
   return error;  
}

/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */
int process_esb_request(char* bmd_file_path) {
    int status = 1; // 1 => OK, -ve => Errors
    printf("Handling the BMD %s\n", bmd_file_path);
    /** TODO: 
     * Perform the steps outlined in the Theory of Operation section of
     * the ESB specs document. Each major step should be implemented in
     * a separate module. Suitable unit tests should be created for all
     * the modules, including this one.
     */
    // Step 1:
    bmd * b = parse_bmd_xml(bmd_file_path);

    // Step 2:
    if (!is_bmd_valid(b))
    {
        //TODO: Process the error case
        printf("BMD is invalid!\n");
        status = -2;
    }
    else
    {
        // Step 3:
        status = queue_the_request(b);
    }
    
    return status;
}
