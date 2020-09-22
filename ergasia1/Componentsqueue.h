#ifndef COMPONENTSQUEUE_H
#define COMPONENTSQUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// this struct is what a queue node should contain (and every other usefull variable inside it)
typedef struct {
	clock_t creation_time;
	clock_t paint_in_time;
	char id[5];
	int type;
}Component;

// this is a queue node declaration
typedef struct qn {				
	Component component;
	struct qn *next;
}QueueNode;

typedef struct {			
	QueueNode *head; // points head queue node
	QueueNode *tail; // points last queue node
	int count;	// keep the number of queue nodes		
}Queue;


// Our queue interface
void initQueue(Queue * queue);  // Queue initialization
void addNode(Queue * queue, Component component); // add a component in queue end
int removeNode(Queue * queue, Component *component);	// remove a component from head
void printQueue(Queue * queue); // print queue content
void copyComponent(Component *source,Component *target); //copy components
int queueIsEmpty(Queue * queue); //tsekarw an einai adeia i oura

#endif






