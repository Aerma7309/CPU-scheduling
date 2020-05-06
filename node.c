/*
 * node.c
 *
 *  Created on: 08-Mar-2019
 *      Author: abhimanyu
 */
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
Node* node_create()
{
	Node *t = calloc(1,sizeof(Node));
	assert(t);
	return t;
}

void node_delete(Node* t)
{
	assert(t);
	free(t);
}

void node_init(Node* n)
{
	n->data = process_create();
	process_init(n->data);
}
