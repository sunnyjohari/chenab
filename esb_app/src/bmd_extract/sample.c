
/**
 * section: BMD XML document parsing 
 * synopsis: Navigates through XML document and store the content in a struct present in xml.h
 * purpose: Parse a XML to a tree, use xmlDocGetRootElement() to
 *          get the root element, then walk the document and store
 *          all the element name in a bmdMessage struct.
 */

#include <stdio.h>
#include <libxml/parser.h>
#include<stdlib.h>
#include<string.h>
#include "xml.h"


bmdMessage bm ;// To store envelope data in bmdMessagestructure
char * Payload;// To store payload
 
/*
* @ breif : checking whether is a leaf node generated in DOM  
    if yes return 1 else 0    
*/
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


/*
* breif @ extracting contents from a XML document and store it in bm
* we store if node type is element and it ia a leaf
*/


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
                    if(strcmp(bm.MessageID, "") ==0){
                       bm.MessageType=NULL;  
                    } 
                }
                else if((strcmp(((char *) node->name),attributes[1]))==0)
	        {
	            bm.MessageType =  (char *)malloc((n+1)* sizeof(char));
                    strcpy(bm.MessageType ,(char *)xmlNodeGetContent(node));
                    if(strcmp(bm.MessageType, "") ==0){
                       bm.MessageType=NULL;  
                    }    
	        }
                else if(strcmp(((char *) node->name), "Sender")==0)
	        {
		    bm.Sender =  (char *)malloc((n+1)* sizeof(char));
                   strcpy(bm.Sender ,(char *)xmlNodeGetContent(node));
                   if(strcmp(bm.Sender, "") ==0){
                       bm.Sender=NULL;  
                    } 
		 }
                else if((strcmp(((char *) node->name),attributes[3]))==0)
                {
		    bm.Destination =  (char *)malloc((n+1)* sizeof(char));
                   strcpy(bm.Destination ,(char *)xmlNodeGetContent(node));
                   if(strcmp(bm.Destination, "") ==0){
                       bm.Destination=NULL;  
                    } 
	        }
                else if((strcmp(((char *) node->name),attributes[4]))==0)
	        {
		    bm.CreationDateTime =  (char *)malloc((n+1)* sizeof(char));
                   strcpy(bm.CreationDateTime ,(char *)xmlNodeGetContent(node));
                   if(strcmp(bm.CreationDateTime, "") ==0){
                       bm.CreationDateTime=NULL;  
                    } 
	        }
	      	else  if((strcmp(((char *) node->name),attributes[5]))==0)
         	{
         	    bm.Signature =  (char *)malloc((n+1)* sizeof(char));
                   strcpy(bm.Signature ,(char *)xmlNodeGetContent(node));
                   if(strcmp(bm.Signature, "") ==0){
                       bm.Signature=NULL;  
                    } 
               }
               else if((strcmp(((char *) node->name),attributes[6]))==0)
	        {
		     bm.ReferenceID =  (char *)malloc((n+1)* sizeof(char));
                    strcpy(bm.ReferenceID ,(char *)xmlNodeGetContent(node));\
                    if(strcmp(bm.ReferenceID, "") ==0){
                       bm.ReferenceID=NULL;  
                    } 
                }
                else if ((strcmp(((char *) node->name),"Payload"))==0)
	        {
                     Payload = (char *)malloc((n+1)* sizeof(char));
                     strcpy(Payload , (char *) xmlNodeGetContent(node));
                     if(strcmp(Payload, "") ==0){
                       Payload=NULL;  
                     } 
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

  /*parse the file and get the DOM */
  doc = xmlReadFile(filepath, NULL, 0);

  if (doc == NULL) {
    printf("Could not parse the XML file");
  }
  /*Get the root element node */
  root_element = xmlDocGetRootElement(doc);

  extractEnvelopeUtils(root_element);

   /*free the document */
    xmlFreeDoc(doc);

  /*
  *Free the global variables that may
  *have been allocated by the parser.
  */
    xmlCleanupParser();
  return bm;
}

char * extractPayload(char * filepath)
{
  
  if(Payload==NULL){
      extractEnvelope(filepath);
  }   
  printf("Payload  is %s\n",Payload);
  return Payload;
}

/*
int main()
{

    char  filepath[50];
    scanf("%s",filepath);
    extractPayload(filepath);
    extractEnvelope(filepath);
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s",bm.MessageID,bm.MessageType,bm.Sender,bm.Destination,bm.CreationDateTime,bm.Signature,bm.ReferenceID);
    return 0;
}
*/


