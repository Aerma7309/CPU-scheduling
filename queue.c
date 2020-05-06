/*
 * queue.c
 *
 *  Created on: 09-Mar-2019
 *      Author: abhimanyu
 */
#include "queue.h"
#include "node.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
Queue* queue_create()
{
	Queue* q = calloc(1,sizeof(Node));
	assert(q);
	return q;
}

void queue_delete(Queue* q)
{
	Node* n = 0, *t = 0;
	assert(q);
	for(n = q->start; n != 0; )
	{
		assert(n->data);
		process_delete(n->data);
		assert(n);
		t = n;
		n = n->next;
		node_delete(t);
	}
	assert(q);
	free(q);
}

void queue_push(Queue* q, Process* p)
{
	Node* n = node_create();
	n->data = p;
    if (q->start == 0) q->start = q->end = n;
    else
    {
        (q->end)->next = n;
        q->end = n;
    }
}


Process * queue_pop(Queue* q)
{
    Node *n = q->start;
    Process *t = n->data;
    if(q->start->next == 0) q->start = q->end = 0 ; 
    else q->start = q->start->next; 
    node_delete(n);
    return t;
}

void queue_display(const Queue* q)
{
    Node* n = q->start;
    printf("\nprocess        AT      BT\n");
    for( ; n != 0; n = n ->next)
    process_display(n->data);
}

Queue* queue_clone(Queue* q)
{
	Queue *tq = queue_create();
	Node* tn;
	for(tn = q->start; tn != 0; tn = tn->next)
	{
		Process* p = process_create();
		*p = *(tn->data) ;
		queue_push(tq, p);
	}
	return tq;
}

void queue_sort(Queue* q,char s[5])
{
    Node* temp = q->start, *curr;
    int num = 1,swapped=1,i,j;
    if(temp == 0) return;
    else
    {
        for(;temp->next != 0; temp = temp -> next)
        num = num + 1;
    }
    
    void swap()
    {
    	Process *t = curr->data;
    	curr->data = curr->next->data;
    	curr->next->data = t;
    	swapped = 1;
    }
    
    for( i = 0; i < num && swapped == 1; i++)
    {
        swapped = 0;
        curr = q->start;
        for( j =0 ; j < num - i -1 && curr != 0; j++)
        {
        	if(strcmp(s,"at") ==0 && curr->data->at > curr->next->data->at) swap();
        	else if(strcmp(s,"bt") ==0 && curr->data->bt > curr->next->data->bt) swap();
        	else if(strcmp(s,"rbt") ==0 && curr->data->rbt > curr->next->data->rbt) swap();
        	else if(strcmp(s,"dpr") ==0 && curr->data->pr > curr->next->data->pr) swap();
        	else if(strcmp(s,"ipr") ==0 && curr->data->pr < curr->next->data->pr) swap();
            curr = curr->next;
        }
    }
}

void calc_tat(Queue* q)
{
	Node* n = q->start;
    for(; n != 0; n = n->next)
    	n->data->tat = n->data->ft - n->data->at;
}

void calc_wt(Queue* q)
{
	Node* n = q->start;
	for(; n != 0; n = n->next)
	    n->data->wt = n->data->tat - n->data->bt;
}

void gantt_chart(Queue* q)
{
    queue_sort(q,"at");
    Node* n = q->start;
	printf("\n\ndata after gantt chart:\n");
    printf("process        AT      BT   	   FT      TAT     WT       RT\n");
    for(; n != 0; n = n->next)
    {
    	Process* t = n->data;
        printf("P%-6d:   %-6.3f   %-6.3f	%-6.3f	%-7.3f	%-6.3f  %-6.3f\n", t->pid, t->at, t->bt, t->ft, t->tat, t->wt, t->rt);
    }
}

void cal_avg_tat_wt(Queue* q)
{
    Node* n = q->start;
    int num = 0;
    float total_tat = 0, total_wt = 0, avg_tat = 0, avg_wt = 0;
	for(; n != 0; n = n->next, num++)
	{
		total_tat = total_tat + n->data->tat;
		total_wt = total_wt + n->data->wt;
	}
    avg_tat = total_tat / num;
	avg_wt = total_wt / num;
    printf("\naverage turn arround time = %.3f\n",avg_tat);
	printf("average waiting time = %.3f\n",avg_wt);
}

