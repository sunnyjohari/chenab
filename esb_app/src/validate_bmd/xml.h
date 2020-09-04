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
  char * Payload;
} bmd;



bmd_envelope *  extract_envelope(char * filepath);
char * extract_payload(char * filepath);
int validate_xml_file (bmd * bmd_file);
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