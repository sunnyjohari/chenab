
/**
 * section: BMD XML document parsing 
 * synopsis: Navigates through XML document and store the content in a struct present in xml.h
 * purpose: Parse a XML to a tree, use xmlDocGetRootElement() to
 *          get the root element, then walk the document and store
 *          all the element name in a bmdMessage struct.
 */

#include <stdio.h>
#include <libxml/parser.h>
#include <stdlib.h>
#include<string.h>
#include "xml.h"
#include<errno.h>



char * attributes[7] =  {
    "MessageID",
    "MessageType",
    "Sender",
    "Destination",
    "CreationDateTime",
    "Signature",
    "ReferenceID"
};
 
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
* we store if node type is element and it is a leaf
*/


void extract_envelope_utils(xmlNode * node, bmd_envelope * bm)
{
    int n;
    while(node)
    {
        if(node->type == XML_ELEMENT_NODE)
        {
            if(is_leaf(node))
            {
                 n= strlen((char*) xmlNodeGetContent(node));
                 /* MessageID*/
                if((strcmp(((char *) node->name),attributes[0]))==0)
                {
                    bm->MessageID = malloc((n+1)* sizeof(char));
                    strcpy(bm->MessageID,(char *) xmlNodeGetContent(node));
                    if(strcmp(bm->MessageID, "") ==0){
                       bm->MessageType=NULL;  
                    } 
                }
                /* MesageType*/
                else if((strcmp(((char *) node->name),attributes[1]))==0)
	              {
	                  bm->MessageType =  (char *)malloc((n+1)* sizeof(char));
                    strcpy(bm->MessageType ,(char *)xmlNodeGetContent(node));
                    if(strcmp(bm->MessageType, "") ==0){
                       bm->MessageType=NULL;  
                    }    
	              }
                /* Sender*/
                else if(strcmp(((char *) node->name), "Sender")==0)
	              {
		              bm->Sender =  (char *)malloc((n+1)* sizeof(char));
                   strcpy(bm->Sender ,(char *)xmlNodeGetContent(node));
                   if(strcmp(bm->Sender, "") ==0){
                       bm->Sender=NULL;  
                    } 
	            	 }
                 /* Destination*/
                else if((strcmp(((char *) node->name),attributes[3]))==0)
                {
		               bm->Destination =  (char *)malloc((n+1)* sizeof(char));
                   strcpy(bm->Destination ,(char *)xmlNodeGetContent(node));
                   if(strcmp(bm->Destination, "") ==0){
                       bm->Destination=NULL;  
                    } 
	              }
                /* CreationDateTime*/
                else if((strcmp(((char *) node->name),attributes[4]))==0)
	              {
                  printf("yes\n");
		               bm->CreationDateTime =  (char *)malloc((n+1)* sizeof(char));
                   strcpy(bm->CreationDateTime ,(char *)xmlNodeGetContent(node));
                   if(strcmp(bm->CreationDateTime, "") ==0){
                       bm->CreationDateTime=NULL;  
                    } 
	               }
                 /* Signature*/
	              else  if((strcmp(((char *) node->name),attributes[5]))==0)
            	  {
         	         bm->Signature =  (char *)malloc((n+1)* sizeof(char));
                   strcpy(bm->Signature ,(char *)xmlNodeGetContent(node));
                   if(strcmp(bm->Signature, "") ==0){
                       bm->Signature=NULL;  
                    } 
                }
                /* ReferenceID*/
                else if((strcmp(((char *) node->name),attributes[6]))==0)
	              {
		                bm->ReferenceID =  (char *)malloc((n+1)* sizeof(char));
                    strcpy(bm->ReferenceID ,(char *)xmlNodeGetContent(node));\
                    if(strcmp(bm->ReferenceID, "") ==0){
                       bm->ReferenceID=NULL;  
                    } 
                }
            }
        }
       extract_envelope_utils(node->children,bm);
        node = node->next;
    }
}

/* @ brief : extracting bmd_envelope
*/

bmd_envelope * extract_envelope(char * filepath)
{
  xmlDoc *doc = NULL;
  xmlNode *root_element = NULL;

  /*parse the file and get the DOM */
  doc = xmlReadFile(filepath, NULL, 0);

  if (doc == NULL) {
    printf("Could not parse the XML file");
  }
  /*Get the root element node */
  bmd_envelope * bm =(bmd_envelope *) malloc(sizeof(bmd_envelope));
  root_element = xmlDocGetRootElement(doc);

  extract_envelope_utils(root_element,bm);

   /*free the document */
    xmlFreeDoc(doc);

  /*
  *Free the global variables that may
  *have been allocated by the parser.
  */
    xmlCleanupParser();
    return bm;
}


/* @ breif : extracting payload from xml file
* input aruguments : filepath ( ehere xml file is stored)
* returns payload as char *
* returning the payload 
*/


bmd * parse_bmd_xml(char * filepath)
{
   bmd  * bd = (bmd*) malloc (sizeof(bmd));
   bd->envelope=  extract_envelope(filepath);
   bd->payload= extract_payload(filepath);
   return bd;
}


char * extract_payload(char * filepath)
{
  xmlDoc *doc = NULL;
  xmlNode *root_element = NULL;
  char * Payload;
  /*parse the file and get the DOM */
  doc = xmlReadFile(filepath, NULL, 0);

  if (doc == NULL) {
    printf("Could not parse the XML file");
  }
  /*Get the root element node */
  root_element = xmlDocGetRootElement(doc);
  int n;
  xmlNode * node = root_element -> children;
  while(node)
  {
    if(node->type == XML_ELEMENT_NODE)
    {
      if(is_leaf(node))
      {
        n= strlen((char*) xmlNodeGetContent(node));
        if ((strcmp(((char *) node->name),"Payload"))==0)
	      {
            Payload = (char *)malloc((n+1)* sizeof(char));
            strcpy(Payload , (char *) xmlNodeGetContent(node));
            if(strcmp(Payload, "") ==0){
                Payload=NULL;  
            } 
            return Payload;
        }
      } 
    }
    node= node->next;
  } 

  /*free the document */
  xmlFreeDoc(doc);

  /*
  *Free the global variables that may
  *have been allocated by the parser.
  */
  xmlCleanupParser();

  return NULL;     
}

/* @ brief: validating bmd.
 * checking whether xml file consists of appropriate elements.
 * if it contains returns 1
 * else return 0
*/

# if 0

int validate_xml_file( bmd * bmd_file)
{
  /* MessageID */
  if(bmd_file->envelope->MessageID  == NULL) {
    fprintf(stderr,"Message ID doesnot exist in bmd");
    return 0;
  }

  /* MessageType */
  if(bmd_file->envelope->MessageType == NULL) {
    fprintf(stderr,"Message Type doesnot exist in bmd");
    return 0;
  }

  /* Sender */
  if(bmd_file->envelope->Sender == NULL) {
    fprintf(stderr,"Sender doesnot exist in bmd");
    return 0;
  }


  /* Destination */
  if(bmd_file->envelope->Destination == NULL) {
    fprintf(stderr,"Destination doesnot exist in bmd");
    return 0;
  }


  /* CreationDateTime */
  if(bmd_file->envelope->CreationDateTime == NULL) {
    fprintf(stderr,"CreationDateTime doesnot exist in bmd");
    return 0;
  }


  /* Signature */
  if(bmd_file->envelope->Signature == NULL) {
    fprintf(stderr,"Signature doesnot exist in bmd");
    return 0;
  }

  /* ReferenceID */
  if(bmd_file->envelope->ReferenceID == NULL) {
      fprintf(stderr,"ReferenceID doesnot exist in bmd");
      return 0;
  }

  /* payload */
  if(bmd_file->payload == NULL) {
    fprintf(stderr,"Payload doesnot exist in bmd");
    return 0;
  }

  return 1;
}
 #endif

/* @ brief creating JSON file 
 * @ param  file path
 * @ return json file name
 */


  char* xml_to_json ( bmd* bd){

/* excluding the path of the directory and assigning filepath as name of the xml file*/
 

  /* extracting payload information*/
  char * payload = bd->payload;

  /* assigning memoryfor JSON file*/
  char * file_name = malloc((strlen("payload_") + strlen(bd->envelope->MessageID)+ strlen(".json")+1)* sizeof(char));

  /* creating .json file*/
  sprintf(file_name,"payload_%s.json","test");

  FILE *fp = fopen(file_name,"w");
    if(fp == NULL) {
        printf("fopen failed, errno = %d\n", errno);
    }
    fprintf(fp,"{\n \"Payload\":\"%s\"\n}",payload);
        fclose(fp);
    return strdup(file_name);
 
 }   




/*

int main()
{

    char  filepath[50] = "/home/bpavan/bmd_extract/dum.xml";
    bmd  * bd = (bmd*) malloc (sizeof(bmd));
    bd= parse_bmd_xml(filepath);
  //  validate_xml_file(bd)? printf("1"): printf("2");
    printf("\n");
    printf("%s",xml_to_json1(bd));
    return 0;
}

*/

