/*
 * process.h
 *
 *  Created on: 08-Mar-2019
 *      Author: abhimanyu
 */
#ifndef PROCESS_H_
#define PROCESS_H_
typedef struct process
{
    int pid, ps, rq;
    float at, bt, ft, tat, wt, rt, pr,rbt;
} Process;
Process *process_create();
void process_delete(void *);
void process_init(Process *);
void process_display(const Process*);
#endif /* PROCESS_H_ */
