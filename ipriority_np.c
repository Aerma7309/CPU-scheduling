/*
 * ipriority_np.c
 *
 *  Created on: 02-Apr-2019
 *      Author: abhimanyu
 */
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "queue.h"
#include "process.h"
#include "node.h"
void ipriority_np(Queue* init)
{
	Process *p;
	Node* n, *add;
	Queue *rq = queue_create(), *inpq = queue_clone(init);
	float cpu_time = 0, idle_time = 0, throughput = 0, temp = 0;
	int num = 0, i;
	queue_sort(inpq, "at");
	add = inpq->start;
	cpu_time = idle_time = inpq->start->data->at;
	for (n = inpq->start; n != 0; n = n->next, num++);
	printf("\nincreasing priority  scheduling ( non - preemptive )\n");
	for (i = 0; i < num; i++)
	{
		for (n = add; n != 0 && n->data->at <= cpu_time; n = n->next)
		{
			queue_push(rq, n->data);
			n->data->rq = 1;
			add = add->next;
		}
		queue_sort(rq, "ipr");
		if (rq->start == 0  && add != 0)
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
			if (p->bt == p->rbt)
				p->rt = cpu_time;
			p->ft = cpu_time + p->bt;
			p->rbt = p->rbt - temp;
			printf("| P%d (%.1f-%.1f)|", p->pid, cpu_time, p->ft);
			cpu_time = p->ft;
			queue_pop(rq);
		}
	}
	calc_tat(inpq);
	calc_wt(inpq);
	queue_sort(inpq, "at");
	gantt_chart(inpq);
	cal_avg_tat_wt(inpq);
	throughput = num / cpu_time;
	printf("throughput of the system = %.3f\n", throughput);
	printf("cpu idle time = %.3f\n", idle_time);	
	queue_delete(inpq);
}

