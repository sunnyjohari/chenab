#include <stdio.h>
#include <libxml/parser.h>
#include<stdlib.h>
#include<string.h>
#include "xml.h"

/*gcc `xml2-config --cflags --libs` sample.c*/

bmdMessage bm ;
    char * Payload;
    char   *MessageID;
    char   *MessageType;
    char   *Sender;
    char  *Destination;
    char *CreationDateTime;
    char   *Signature;
    char  *ReferenceID;


int is_leaf(xmlNode * node)
{
  xmlNode * child = node->children;
  while(child)
  {
    if(child->type == XML_ELEMENT_NODE) return 0;

    child = child->next;
  }

  return 1;
}

void extractEnvelopeUtils(xmlNode * node)
{
    int n;
    while(node)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
            if(is_leaf(node))
            {
                 n= strlen((char*) xmlNodeGetContent(node));
                if((strcmp(((char *) node->name),attributes[0]))==0)
                {
                    MessageID = malloc((n+1)* sizeof(char));
                    strcpy(MessageID,(char *) xmlNodeGetContent(node));
                    bm.MessageID = malloc((strlen(MessageID)+1)* sizeof(char));
                    strcpy(bm.MessageID,MessageID);
                 }
                else  if((strcmp(((char *) node->name),attributes[1]))==0)
			    {
				    MessageType =  (char *)malloc((n+1)* sizeof(char));
                    strcpy(MessageType ,(char *)xmlNodeGetContent(node));
                    bm.MessageType = malloc((strlen(MessageType)+1)* sizeof(char));
                    strcpy(bm.MessageType,MessageType);
                    free(MessageType);
			    }
                else   if(strcmp(((char *) node->name), "Sender")==0)
			    {
				    Sender =  (char *)malloc((n+1)* sizeof(char));
                    strcpy(Sender ,(char *)xmlNodeGetContent(node));
                    bm.Sender= malloc((strlen(Sender)+1)* sizeof(char));
                    strcpy(bm.Sender,Sender);
                    free(Sender);
			    }
                else    if((strcmp(((char *) node->name),attributes[3]))==0)
			    {
				     Destination =  (char *)malloc((n+1)* sizeof(char));
                     strcpy(Destination ,(char *)xmlNodeGetContent(node));
                     bm.Destination= malloc((strlen(Destination)+1)* sizeof(char));
                     strcpy(bm.Destination,Destination);
                     free(Destination);
			    }
                else  if((strcmp(((char *) node->name),attributes[4]))==0)
			    {
				     CreationDateTime =  (char *)malloc((n+1)* sizeof(char));
                     strcpy(CreationDateTime ,(char *)xmlNodeGetContent(node));
                     bm.CreationDateTime= malloc((strlen(CreationDateTime)+1)* sizeof(char));
                     strcpy(bm.CreationDateTime,CreationDateTime);
                     free(CreationDateTime);	

			    }
			    else  if((strcmp(((char *) node->name),attributes[5]))==0)
			    {
				     Signature =  (char *)malloc((n+1)* sizeof(char));
                     strcpy(Signature ,(char *)xmlNodeGetContent(node));
                     bm.Signature= malloc((strlen(Signature)+1)* sizeof(char));
                     strcpy(bm.Signature,Signature);
                     free(Signature);
			    }
                else  if((strcmp(((char *) node->name),attributes[6]))==0)
			    {
				     ReferenceID =  (char *)malloc((n+1)* sizeof(char));
                     strcpy(ReferenceID ,(char *)xmlNodeGetContent(node));
                     bm.ReferenceID= malloc((strlen(ReferenceID)+1)* sizeof(char));
                     strcpy(bm.ReferenceID,ReferenceID);
                     free(ReferenceID);
			    }
                else if ((strcmp(((char *) node->name),"Payload"))==0)
			    {
                     Payload = (char *)malloc((n+1)* sizeof(char));
                     strcpy(Payload , (char *) xmlNodeGetContent(node));
                     return;
                }
         
            }
        }
        extractEnvelopeUtils(node->children);
        node = node->next;
    }
}

bmdMessage  extractEnvelope(char * filepath)
{
  xmlDoc *doc = NULL;
  xmlNode *root_element = NULL;

  doc = xmlReadFile(filepath, NULL, 0);

  if (doc == NULL) {
    printf("Could not parse the XML file");
  }

  root_element = xmlDocGetRootElement(doc);
  extractEnvelopeUtils(root_element);
  xmlFreeDoc(doc);
  xmlCleanupParser();
  return bm;
}

char * extractPayload(char * filepath)
{

  return Payload;
}

int main()
{
    char * filepath="/home/bpavan/bmd_extract/dum.xml";
    bm=extractEnvelope(filepath);
    return 0;
}
