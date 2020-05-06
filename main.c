/*
 * main.c
 *
 *  Created on: 08-Mar-2019
 *      Author: abhimanyu
 */
#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "queue.h"
#include "node.h"
#include "main.h"
int main()
{
	Queue *q = queue_create();
	int i = 0, num, choice;
	char ch = 0;
	Node* n;
	printf("program to simulate cpu scheduling by ABHIMANYU MAURYA( 1713310003 AKTU ) B.Tech NIET Gr. Noida \n");
	printf("1.it can accept unsorted data\n2.it can calculate cpu idle time\n\n");
	printf("enter number of processes: ");
	scanf("%d",&num);
	if(num <= 0) 
	{
		printf("number is invalid\n");
		exit(1);
	}
	for(i =0; i<num; i++)
	{
		Process* p = process_create();
		process_init(p);
		p->pid = i;
		queue_push(q, p);
	}	
	printf("do you want to enter priority for processes(y/n)\n");
	scanf(" %c",&ch);
	if(ch == 'y')
	for (n = q->start; n != 0; n = n->next)
	    {
		do 
		  {
		    printf ("enter priority of P%d : ", n->data->pid);
		    		scanf ("%f", &n->data->pr);
		    if(n->data->pr < 0.0) printf("priority must be greater or equal to zero\n");
		  }while(n->data->pr < 0.0);
	    }
	else if(ch != 'n') exit(0);
	do
	  {
	    	printf("\n1. first come first serve\n2. sortest job first\n3. sortest remaining time next\n4. round robin\n");
	    	printf("5. decreasing priority (non - preemptive)\n6. increasing priority (non - preemptive)\n7. decreasing priority ( preemptive )\n8. increasing priority ( preemptive )\n9. run 1 - 4\n10. run 5 - 8\n99. exit\n");
	    	printf("enter your choice: ");
	    	scanf("%d",&choice);
	    	switch(choice)
	    	{
	    	  case 1: fcfs(q); break;
	    	  case 2: sjf(q); break;
	    	  case 3: srtn(q); break;
	    	  case 4: rr(q); break;
	    	  case 5: dpriority_np(q); break;
	    	  case 6: ipriority_np(q); break;
	    	  case 7: dpriority(q); break;
	    	  case 8: ipriority(q); break;
	    	  case 9: fcfs(q); sjf(q); srtn(q); rr(q); break;
	    	  case 10: dpriority_np(q); ipriority_np(q); dpriority(q); ipriority(q); break;
	    	  case 99: exit(0);
	    	  default: printf("invalid choice");
	    	  
	    	}
	  }while(1);	
}
