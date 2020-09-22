#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Componentsqueue.h"

int queueIsEmpty(Queue * queue){

	return queue->count==0;

}


void initQueue(Queue * queue){
	queue->head=NULL;
	queue->tail=NULL;
	queue->count=0;
}

void addNode(Queue * queue, Component component){
	QueueNode *temp = (QueueNode*)malloc(sizeof(QueueNode));
	temp->component.type=component.type;
	temp->component.creation_time=component.creation_time;
	temp->component.paint_in_time=component.paint_in_time;
	strcpy(temp->component.id,component.id);

	temp->next=NULL;
	// If queue is empty, then new node is front and rear both 
	if(queue->head==NULL && queue->tail==NULL){
		queue->head=queue->tail=temp;
		queue->count++;
		return;
	}
	// Add the new node at the end of queue and change rear
	queue->tail->next=temp;
	queue->tail=temp;
	queue->count++;	
}

int removeNode(Queue * queue,Component *component){
	//If queue is empty, return NULL.
	if (queue->count == 0){
		return 0;
	}
	QueueNode *temp=queue->head;
	queue->head=queue->head->next;
	queue->count=queue->count-1;
	// after removing we check if there are no more nodes make the queue empty,we could do it with count too
	if (queue->count == 0) 
       queue->tail = NULL; 
	copyComponent(&(temp->component),component);
	free(temp);
    return 1;
}

void copyComponent(Component *source,Component *target){
	strcpy(target->id,source->id);
	target->creation_time=source->creation_time;
	target->paint_in_time=source->paint_in_time;
	target->type=source->type;
}

void printQueue(Queue * queue){
	QueueNode* temp=queue->head;
	while (temp!=NULL){
		printf("%s-> ",temp->component.id);
		temp=temp->next;
	}
	printf("\n");
}


/*int main(){
	Component c1,c2,c3,c4;
	c1.id=1;
	c2.id=2;
	c3.id=3;
	Queue q;
	initQueue(&q);
	addNode(&q,c1);
	addNode(&q,c2);
	addNode(&q,c3);
	printQueue(&q);
	removeNode(&q,&c4);
	printf("%d\n",c4.id);
	printQueue(&q);

} */


