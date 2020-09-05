int process_esb_request(char* bmd_file_path);


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



extern bmd_envelope *  extract_envelope(char * filepath);
extern char * extract_payload(char * filepath);
extern int validate_bmd_request (bmd * bmd_file);

