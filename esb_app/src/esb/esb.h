int process_esb_request(char* bmd_file_path);




typedef struct 
{
    char  *Sender;
    char * Destination;
    char  *MessageID;
    char  *MessageType;
    char *CreationDateTime;
    char  *Signature;
    char  *ReferenceID;
}bmd_envelope;


typedef struct 
{
  bmd_envelope be;
  char * Payload;
} bmd;

static bmd bm;


extern bmd_envelope  extract_envelope(char * filepath);
extern char * extract_payload(char * filepath);

const char * attributes[] =  {
    "MessageID",
    "MessageType",
    "Sender",
    "Destination",
    "CreationDateTime",
    "Signature",
    "ReferenceID"
};
 
