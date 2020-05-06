/*
 * sjf.c
 *
 *  Created on: 09-Mar-2019
 *      Author: abhimanyu
 */
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "queue.h"
#include "process.h"
#include "node.h"
void sjf(Queue* init)
{
	Process *p;
    Node* n, *add;
    Queue *rq = queue_create(), *inpq= queue_clone(init);
    float cpu_time = 0, idle_time = 0, throughput = 0, temp = 0;
    int num = 0, i;
    queue_sort(inpq,"at");
    add = inpq->start;
    cpu_time = idle_time = inpq->start->data->at;
    for(n = inpq->start; n != 0; n = n->next,num++);
    printf("\nsortest job first scheduling\n\n");
    for(i = 0; i < num; i++)
    {
    	for( n = add; n != 0 && n->data->at <= cpu_time; n = n->next)
    	{
    		queue_push(rq,n->data);
    		n->data->rq = 1;
    		add = add->next;
    	}   	
    	queue_sort(rq,"bt");
    	if(rq->start == 0)
    	{
    		temp = add->data->at - cpu_time;
    		printf("| idle (%.1f-%.1f)|", cpu_time, cpu_time + temp);
    		idle_time = idle_time + temp;
    		cpu_time = cpu_time + temp;
    		i = i - 1;
    	}
    	else
    	{
    		p = rq->start->data;
    		p->ft = cpu_time + p->bt;
    		printf("| P%d (%.1f-%.1f)|", p->pid, cpu_time, p->ft);
    		p->rt = cpu_time;
    		cpu_time = p->ft;
    		p->ps = 1;
    		queue_pop(rq);
    	} 
    }
    calc_tat(inpq);
    calc_wt(inpq);
    queue_sort(inpq,"at");
    gantt_chart(inpq);
    cal_avg_tat_wt(inpq);
	throughput = num / cpu_time;
	printf("throughput of the system = %.3f\n",throughput);
    printf("cpu idle time = %.3f\n",idle_time);
    queue_delete(inpq);
}