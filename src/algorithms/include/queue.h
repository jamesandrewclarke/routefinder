//
// Created by James Clarke on 04/04/2021.
//

#pragma once

#define INF FLT_MAX
#define UNDEFINED -1

typedef struct Node Node;
typedef struct PriorityQueue PriorityQueue;

struct Node
{
    int id;
    double priority;
    Node *next;
};

struct PriorityQueue
{
    Node *head;
};

PriorityQueue *createQueue();

/**
 * Deallocates a priority queue
 * @param queue The queue to be deleted
 * @return A status code, 1 if successful
 */
int deleteQueue(PriorityQueue *queue);

/**
 * Returns whether a queue is empty
 * @param queue The queue to check
 * @return Boolean, 1 if empty.
 */
int queueIsEmpty(PriorityQueue *queue);

Node *createNode(unsigned int id, double priority);

void addWithPriority(PriorityQueue *queue, unsigned int id, double priority);

void removeFromQueue(PriorityQueue *queue, unsigned int id);

void changePriority(PriorityQueue *queue, unsigned int id, double priority);

/**
 * Removes the first node from the queue and returns it
 * @param queue The queue to extract the node from
 * @return The minimum node
 */
Node extractMin(PriorityQueue *queue);