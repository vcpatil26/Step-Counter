#define QUEUE_SIZE 128
typedef struct queue {
int head;
int tail;
int buffer[QUEUE_SIZE];
} queue_t;
void init_queue(queue_t *);
int enqueue(queue_t *, int);
int dequeue(queue_t *);
int queue_empty(queue_t *);

