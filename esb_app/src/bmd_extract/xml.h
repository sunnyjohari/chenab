/*
typedef struct bmdMessage_
{
    char   * Message;
    char  *Sender;
    char * Destination;
    char  *MessageID;
    char  *MessageType;
    char  *Signature;
    char  *ReferenceID;
}bmdMessage;

bmdMessage bm ;
enum bmd
{
    Message=0,
    Sender=1,
    Destination=2,
    MessageID=3,
    MessageType=4,
    Signature=5,
    ReferenceID=6,
};
*/
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
 