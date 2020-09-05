// header file

//scdsfcsd

#ifndef XML_H
#define XML_H

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
int is_bmd_valid(bmd * b);

 

 #endif