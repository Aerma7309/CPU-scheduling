/*
 * node.h
 *
 *  Created on: 08-Mar-2019
 *      Author: abhimanyu
 */
#include"process.h"
#ifndef NODE_H_
#define NODE_H_
typedef struct node
{
	Process *data;
	struct node *next;
} Node;
Node* node_create();
void node_delete(Node*);
#endif /* NODE_H_ */
