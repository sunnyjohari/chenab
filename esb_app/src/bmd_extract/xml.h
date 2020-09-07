// header file

//scdsfcsd

#ifndef XML_H
#define XML_H

#define MAX_SIZE 5242880 // 5MB

typedef struct 
{
    char  *MessageID;
    char  *MessageType;
    char  *Sender;
    char * Destination;
    char *CreationDateTime;
    char  *Signature;
    char  *ReferenceID;
}bmd_envelope;


typedef struct 
{
  bmd_envelope * envelope;
  char * payload;
} bmd;



bmd_envelope *  extract_envelope(char * filepath);
char * extract_payload(char * filepath);
int validate_xml_file (bmd * bmd_file);
bmd * parse_bmd_xml(char * filepath);
char * xml_to_json ( bmd * bd);
long int find_size(char * file_name);
int is_bmd_valid(bmd* bd); 
void  insert (bmd * bd);


/*char * attributes[7] =  {
    "MessageID",
    "MessageType",
    "Sender",
    "Destination",
    "CreationDateTime",
    "Signature",
    "ReferenceID"
};*/
 

 #endif
