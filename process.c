/*
 * process.c
 *
 *  Created on: 08-Mar-2019
 *      Author: abhimanyu
 */
#include"process.h"
#include <stdio.h>
#include <stdlib.h>
#include<assert.h>

Process* process_create()
{
    Process *t = (Process*)calloc(1,sizeof(Process));
    assert(t);
    return t;
}


void process_delete(void *t)
{
	assert(t);
    free(t);
}

void process_init(Process *t)
{
    float temp;
    printf("enter arrival time: ");
    scanf("%f",&t->at);
    printf("enter bus time: ");
    scanf("%f",&temp);
    t->bt = temp;
    t->rbt = temp;
}

void process_display(const Process* p)
{
	printf("P%-6d:   %-6.3f   %-6.3f        \n", p->pid, p->at, p->bt);
}
