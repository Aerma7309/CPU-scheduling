/*
 * fcfs.c
 *
 *  Created on: 09-Mar-2019
 *      Author: abhimanyu
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "process.h"
#include "node.h"
void fcfs(Queue *init)
{
    Node* n;
    Queue *rq = queue_clone(init);
    int num = 0;	//number of elements in queue
    float cpu_time = 0, idle_time = 0, throughput = 0,temp = 0;
    printf("\nfirst come first serve process scheduling\n\n");
    queue_sort(rq,"at");
    for(n = rq->start; n != 0; n = n->next,num++);
    for(n = rq->start; n != 0; n = n->next)
    {
    	Process* p = n->data;
        if(p->at > cpu_time)
        {
            temp = p->at - cpu_time;
            printf("| idle (%.1f-%.1f)|", cpu_time, cpu_time + temp);
            cpu_time = cpu_time + temp;
            idle_time = idle_time + temp;
        }
        p->ft = cpu_time + p->bt;
        printf("| P%d (%.1f-%.1f)|", p->pid, cpu_time, p->ft);
        p->rt = cpu_time;
        cpu_time = p->ft;
    }
    calc_tat(rq);
    calc_wt(rq);
    gantt_chart(rq);
    cal_avg_tat_wt(rq);
	throughput = num / cpu_time;
	printf("throughput of the system = %.3f\n",throughput);
    printf("cpu idle time = %.3f\n",idle_time);
    queue_delete(rq);
}

