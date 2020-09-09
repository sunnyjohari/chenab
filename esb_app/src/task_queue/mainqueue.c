
#include <stdio.h>
#include <string.h>
#include "task_queue.h"


int main() 
{ 
    q = createQueue(); 
    enQueue(q,1,1,"available");
    enQueue(q,2,1,"available");
    task_node * qn;
    printf("Queue Front : %d  %d %s \n", q->front->id,q->front->processing_attempts,q->front->status); 
    printf("Queue Rear : %d  %d %s \n", q->rear->id,q->rear->processing_attempts,q->rear->status); 
    qn = task_queue_process(q);
    printf("Queue processing node  : %d  %d %s \n", qn->id,qn->processing_attempts,qn->status); 
    qn = task_queue_process(q);
    printf("Queue processing node  : %d  %d %s \n", qn->id,qn->processing_attempts,qn->status); 
    printf("Queue Front : %d  %d %s \n", q->front->id,q->front->processing_attempts,q->front->status); 
    printf("Queue Rear : %d  %d %s \n ", q->rear->id,q->rear->processing_attempts,q->rear->status); 

    return 0; 
}