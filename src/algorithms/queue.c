//
// Created by James Clarke on 04/04/2021.
//

#include "include/queue.h"
#include "stdlib.h"

#define INF FLT_MAX
#define UNDEFINED -1

PriorityQueue *createQueue()
{
    PriorityQueue *queue = malloc(sizeof(struct PriorityQueue));
    queue->head = NULL;

    return queue;
}

/**
 * Deallocates a priority queue
 * @param queue The queue to be deleted
 * @return A status code, 1 if successful
 */
int deleteQueue(PriorityQueue *queue)
{
    while (queue->head != NULL)
    {
        Node *next = queue->head->next;
        free(queue->head);
        queue->head = next;
    }

    free(queue);

    return 1;
}

/**
 * Returns whether a queue is empty
 * @param queue The queue to check
 * @return Boolean, 1 if empty.
 */
int queueIsEmpty(PriorityQueue *queue)
{
    return queue->head == NULL;
}

Node *createNode(unsigned int id, double priority)
{
    Node *node = malloc(sizeof(Node));
    node->id = id;
    node->priority = priority;
    node->next = NULL;

    return node;
}

void addWithPriority(PriorityQueue *queue, unsigned int id, double priority)
{
    Node *new = createNode(id, priority);
    new->next = NULL;

    // Double indirection lets us modify the pointer itself
    if (queue->head == NULL) {
        queue->head = new;
        return;
    }

    Node *find = queue->head;

    while (find->next != NULL)
    {
        if (find->next->priority > priority) break;
        find = find->next;
    }

    find->next = new;
}

void removeFromQueue(PriorityQueue *queue, unsigned int id)
{
    Node *ref = queue->head;
    while (ref->next != NULL)
    {
        if (ref->next->id == id)
        {
            Node *next = ref->next->next;
            free(ref->next);
            ref->next = next;
        }
        ref = ref->next;
    }
}

void changePriority(PriorityQueue *queue, unsigned int id, double priority)
{
    removeFromQueue(queue, id);
    addWithPriority(queue, id, priority);
}

/**
 * Removes the first node from the queue and returns it
 * @param queue The queue to extract the node from
 * @return The minimum node
 */
Node extractMin(PriorityQueue *queue)
{
    Node min = *(queue->head);
    Node *next = queue->head->next;
    free(queue->head);
    queue->head = next;

    return min;
}