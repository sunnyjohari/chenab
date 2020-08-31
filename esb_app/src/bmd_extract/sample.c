#include <stdio.h>
#include <libxml/parser.h>
#include<stdlib.h>
#include<string.h>
#include "xml.h"

/*gcc -Wall -I/usr/include/libxml2 -o sa sample.c -lxml2*/

 bmdMessage bm ;
 
 
 char * Payload;
 

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
                    bm.MessageID = malloc((n+1)* sizeof(char));
                    strcpy(bm.MessageID,(char *) xmlNodeGetContent(node));
                 }
                else  if((strcmp(((char *) node->name),attributes[1]))==0)
	              {
				          bm.MessageType =  (char *)malloc((n+1)* sizeof(char));
                    strcpy(bm.MessageType ,(char *)xmlNodeGetContent(node));
	          	}
                else   if(strcmp(((char *) node->name), "Sender")==0)
	        {
		             bm.Sender =  (char *)malloc((n+1)* sizeof(char));
                    strcpy(bm.Sender ,(char *)xmlNodeGetContent(node));
		 }
                else    if((strcmp(((char *) node->name),attributes[3]))==0)
		 {
		     bm.Destination =  (char *)malloc((n+1)* sizeof(char));
                     strcpy(bm.Destination ,(char *)xmlNodeGetContent(node));
	         }
                else  if((strcmp(((char *) node->name),attributes[4]))==0)
	        {
		      bm.CreationDateTime =  (char *)malloc((n+1)* sizeof(char));
                     strcpy(bm.CreationDateTime ,(char *)xmlNodeGetContent(node));

	        }
		else  if((strcmp(((char *) node->name),attributes[5]))==0)
		{
		      bm.Signature =  (char *)malloc((n+1)* sizeof(char));
                     strcpy(bm.Signature ,(char *)xmlNodeGetContent(node));
		}
                else  if((strcmp(((char *) node->name),attributes[6]))==0)
		 {
		      bm.ReferenceID =  (char *)malloc((n+1)* sizeof(char));
                     strcpy(bm.ReferenceID ,(char *)xmlNodeGetContent(node));
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
  
  //extractEnvelope(filepath);
  return Payload;
}
int main()
{
    char * filepath="/home/bpavan/bmd_extract/dum.xml";
    bm=extractEnvelope(filepath);
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s",bm.MessageID,bm.MessageType,bm.Sender,bm.Destination,bm.CreationDateTime,bm.Signature,bm.ReferenceID);
    return 0;
}


