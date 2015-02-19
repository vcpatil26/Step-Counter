#include <queue.h>
void init_queue(queue_t *buf) {
buf->head=0;
buf->tail=0;
}
int enqueue (queue_t *buf, int data) {
int return_val=0;
if ((((buf->head)+1)%QUEUE_SIZE)!=buf->tail) {
buf->buffer[buf->head]=data;
buf->head=((buf->head)+1)%QUEUE_SIZE;
return_val=1;
}
else {
return_val=0;
}
return (return_val);
}
int dequeue (queue_t *buf) {
int return_val=0;
if (buf->tail!=buf->head) {
return_val=buf->buffer[buf->tail];
buf->tail=((buf->tail)+1)%QUEUE_SIZE;
}
return(return_val);
}
int queue_empty(queue_t *buf) {
int retval = 0;
if (buf->head==buf->tail) {
retval=1;
}
return (retval);
}

