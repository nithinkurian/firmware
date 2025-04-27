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

#endif /* QUEUE_H_ */