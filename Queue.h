/*BUDURAN CATALINA-ANDREEA, 311 CD*/
#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef char T;
typedef struct node {
    T *data;
    struct node *next;
} QueueNode;

typedef struct queue {
    QueueNode *front, *rear;
    int size;
} *TQueue;

TQueue createQueue(){ //functie care creeaza o coada
	TQueue queue = malloc(sizeof(TQueue));
	queue->front = NULL;
	queue->rear = NULL;
    queue->size = 0;
	return queue;
}

QueueNode *createNodeQueue(T *data) { //functie care creeaza un nod pe care sa-l adaug in coada
	QueueNode *node = (QueueNode*)malloc(sizeof(QueueNode));
    if (node == NULL)
        return NULL;
	node->data = data;
    node->next = NULL;
	return node;
}

QueueNode *freeNode (QueueNode *node) { //elibereaza memoria pentru nodul creat 
    if (node)
        free(node);
    return NULL;
}

int isEmpty(TQueue queue) { //verific daca o coada e goala sau nu
    return queue == NULL || queue->front == NULL || queue->size == 0;
}

TQueue initQueue(T *data) { 
    TQueue queue = malloc(sizeof(struct queue));
    queue->front = queue->rear = createNodeQueue(data);
    queue->size = 1;
    return queue;
}

void enqueue(TQueue *queue, T *data){ //functie care adauga un nod intr-o coada
    QueueNode *node = createNodeQueue(data);
	if ((*queue)->front == NULL ) { //daca este goala coada, atunci si primul nod din coada si ultimul sunt egale cu nodul respectiv
		(*queue)->front = (*queue)->rear = node;
	}
    else {
	(*queue)->rear->next = node;
	(*queue)->rear = node;}
	(*queue)->size++;
}

void dequeue (TQueue *queue) { //functie care sterge un nod dintr-o coada
    QueueNode *tmp;
    if (isEmpty(*queue) == 0) { //verific sa nu fie goala coada
        tmp = (*queue)->front;
        (*queue)->front = (*queue)->front->next;
         freeNode(tmp);
        (*queue)->size--;
    }
    return;
}

void destroyQueue(TQueue queue) { //eliberez memoria alocata cozii
    if (queue == NULL) {
        return;
    }
    QueueNode *curent;
    while (queue->front != NULL) {
        curent = queue->front;
        queue->front = queue->front->next;
        free(curent->data);
        free(curent);
    }
    queue->rear = NULL;
    queue->size = 0;
}

#endif