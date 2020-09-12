 

#define THRESHOLD 5

// A linked list (LL) node to store a task information
typedef struct Qinfo { 
    int id;
    char * sender;
    char * destination;
    char * message_type;
}task_node_info;



// A linked list (LL) node to store a queue entry 
typedef struct QNode { 
    task_node_info * task_info;
    int processing_attempts;
    char * status;
    struct QNode* next; 
}task_node; 
  
// The queue, front stores the front node of LL and rear stores the 
// last node of LL 
typedef struct Queue { 
    task_node *front, *rear; 
}task_queue; 

static task_queue* q;

void enQueue(task_queue* q, int k,int processing_attempts, char * status); 

void deQueue(task_queue * q,int k);

task_queue * createQueue ();

task_node * task_queue_process(task_queue * q);

void print(task_queue * q);

