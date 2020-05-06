/*
 * queue.h
 *
 *  Created on: 09-Mar-2019
 *      Author: abhimanyu
 */
#include "node.h"
#ifndef QUEUE_H_
#define QUEUE_H_
typedef struct queue
{
	Node *start, *end;
} Queue;
Queue* queue_create();
void queue_delete(Queue*);
void queue_push(Queue* q, Process* p);
Process * queue_pop(Queue* q);
void queue_display(const Queue* q);
Queue* queue_clone(Queue* q);
void queue_sort(Queue* q,char s[5]);
void calc_tat(Queue* q);
void calc_wt(Queue* q);
void gantt_chart(Queue* q);
void cal_avg_tat_wt(Queue* q);
#endif /* QUEUE_H_ */
