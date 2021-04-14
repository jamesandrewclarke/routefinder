//
// Created by James Clarke on 04/04/2021.
//

#include "include/queue.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"

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
int queueIsEmpty(const PriorityQueue *queue)
{
    return queue->head == NULL;
}

Node *createNode(const unsigned int id, const double priority)
{
    Node *node = malloc(sizeof(Node));
    node->id = id;
    node->priority = priority;
    node->next = NULL;

    return node;
}

int addWithPriority(PriorityQueue *queue, const unsigned int id, const double priority)
{
    if (queue == NULL) return 0;

    Node *new = createNode(id, priority);
    new->next = NULL;

    // If the queue is empty, set the node to the new head and return
    if (queue->head == NULL)
    {
        queue->head = new;
        return 1;
    }

    if (priority < queue->head->priority)
    {
        new->next = queue->head;
        queue->head = new;
        return 1;
    }

    Node *find = queue->head;
    while (find->next != NULL && find->next->priority < priority)
    {
        find = find->next;
    }

    new->next = find->next;
    find->next = new;
    return 1;
}

int removeFromQueue(PriorityQueue *queue, const unsigned int id)
{
    if (queue == NULL) return 0;

    Node *ref = queue->head;
    if (ref == NULL) return 0;
    if (ref->id == id)
    {
        queue->head = ref->next;
        free(ref);
        return 1;
    }

    while (ref->next != NULL)
    {
        if (ref->next->id == id)
        {
            Node *next = ref->next->next;
            free(ref->next);
            ref->next = next;
            return 1;
        }
        ref = ref->next;
    }

    return 0;
}

int changePriority(PriorityQueue *queue, const unsigned int id, const double priority)
{
    return removeFromQueue(queue, id) & addWithPriority(queue, id, priority);
}

/**
 * Removes the first node from the queue and returns it
 * @param queue The queue to extract the node from
 * @return The minimum node
 */
Node extractMin(PriorityQueue *queue)
{
    if (queue == NULL || queue->head == NULL)
    {
        const Node result = {.id = -1}; // This indicates a failure
        return result;
    }

    const Node min = *(queue->head);
    Node *next = queue->head->next;
    free(queue->head);
    queue->head = next;

    return min;
}