/*
 * rr.c
 *
 *  Created on: 12-Mar-2019
 *      Author: abhimanyu
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "node.h"
void rr(Queue *init)
{
    Node* n, *add;
    Queue *rq = queue_create(), *inpq= queue_clone(init);
    Process *p;
    int num = 0, i;	//number of elements in queue
    float cpu_time = 0, idle_time = 0, throughput = 0,temp = 0, quantum = 0;
    printf("\nround robbin process scheduling\n\n");
    printf("enter time quantum: ");
    scanf("%f",&quantum);
    queue_sort(inpq,"at");
    add = inpq->start;
	for(n = inpq->start; n != 0; n = n->next, num++);
	void add_p()
	{
		for (n = add; n != 0 && n->data->at <= cpu_time; n = n->next)
		{
			queue_push(rq, n->data);
			n->data->rq = 1;
			add = add->next;
		}
	}
	for(i = 0; i < num; i++)
	{
		add_p();
		if(rq->start != 0)
		{
			p = rq->start->data;
			if (p->rbt < quantum)
				temp = p->rbt;
			else
				temp = quantum;
			if (p->bt == p->rbt)
				p->rt = cpu_time;
			p->ft = cpu_time + temp;
			p->rbt = p->rbt - temp;
			printf("| P%d (%.1f-%.1f)|", p->pid, cpu_time, p->ft);
			cpu_time = p->ft;
			
			if (p->rbt != 0)
			{
				queue_push(rq, p);
				i--;
			}
			queue_pop(rq);
			add_p();
		}
		
		if (rq->start == 0 && add != 0)
		{
			temp = add->data->at - cpu_time;
			printf("| idle (%.1f-%.1f)|", cpu_time, cpu_time + temp);
			idle_time = idle_time + temp;
			cpu_time = cpu_time + temp;
			add_p();
			i = i - 1;			
		}
	}
    calc_tat(inpq);
    calc_wt(inpq);
    gantt_chart(inpq);
    cal_avg_tat_wt(inpq);
	throughput = num / cpu_time;
	printf("throughput of the system = %.3f\n",throughput);
    printf("cpu idle time = %.3f\n",idle_time);
    queue_delete(inpq);
}
