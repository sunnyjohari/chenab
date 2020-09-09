#include <stdio.h> 
#include <stdlib.h> 
#include "task_queue.h"
#include <string.h>
  
// A utility function to create a new linked list node. 
task_node* newNode(task_node_info * k,int processing_attempts, char * status) 
{ 
    task_node * temp = (task_node *)malloc(sizeof(task_node)); 
    temp->task_info = k; 
    temp->processing_attempts=processing_attempts;
    temp->status=status;
    temp->next = NULL; 
    return temp; 
} 
  
// A utility function to create an empty queue 
task_queue* createQueue() 
{ 
    task_queue * q = (task_queue*)malloc(sizeof(task_queue)); 
    q->front = q->rear = NULL; 
    return q; 
} 
  
// The function to add a key k to q 
void enQueue(task_queue* q, task_node_info * k ,int processing_attempts, char * status) 
{ 
    // Create a new LL node 
   task_node* temp = newNode(k,processing_attempts,status); 
  
    // If queue is empty, then new node is front and rear both 
    if (q->rear == NULL) { 
        q->front = q->rear = temp; 
        return; 
    } 
  
    // Add the new node at the end of queue and change rear 
    q->rear->next = temp; 
    q->rear = temp; 
} 
  
// Function to remove a key from given queue q 
void deQueue(task_queue* q) 
{ 
    // If queue is empty, return NULL. 
    if (q->front == NULL) 
        return; 
  
    // Store previous front and move front one node ahead 
    task_node* temp = q->front; 
  
    q->front = q->front->next; 
  
    // If front becomes NULL, then change rear also as NULL 
    if (q->front == NULL) 
        q->rear = NULL; 
  
    free(temp); 
} 



/**
 *  @ brief processing task_queue
 * 
 * whenver we take the node from the queue we dequeue from the queue
 *
 */
task_node * task_queue_process(task_queue * q)
{
    task_node * qn = q->front;

      if(!(strcmp(qn->status , "available"))){    
         qn->processing_attempts+=1;
         qn->status="processing";
         dequeue(q);
         return qn;
      }
    return NULL;
}
  