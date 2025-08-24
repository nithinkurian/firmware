#ifndef QUEUE_H_
#define QUEUE_H_

// Defining the Queue structure
typedef struct {
    void *queue_buffer;
    uint16_t queue_length;
    uint16_t item_size;
    int front;
    int back;
} QCB_t;

#define MAX_QUEUES           2

#define NOT_WAITING_ON_QUEUE        0
#define WAITING_ON_EMPTY_QUEUE      1
#define WAITING_ON_FULL_QUEUE       2

bool is_queue_empty(queuehandle_t handle);
bool is_queue_full(queuehandle_t handle);

#endif /* QUEUE_H_ */