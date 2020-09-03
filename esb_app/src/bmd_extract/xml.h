typedef struct bmdMessage_
{
    char   * Message;
    char  *Sender;
    char * Destination;
    char  *MessageID;
    char  *MessageType;
    char *CreationDateTime;
    char  *Signature;
    char  *ReferenceID;
}bmdMessage;
const char * attributes[] =  {
    "MessageID",
    "MessageType",
    "Sender",
    "Destination",
    "CreationDateTime",
    "Signature",
    "ReferenceID"
};
 
