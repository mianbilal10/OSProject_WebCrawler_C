#include "hashqueue.h"
/*-------- init queue  -------- */
void init_queue(queue_t *q){
	q->head = NULL;
	q->tail = NULL;
}

/*-------- create node  -------- */
node_t *create_new_node(char *url){

	node_t *node = malloc(sizeof(node_t));
	node->url = url;
	node->next = NULL;

	return node;
}

/*-------- enqueue  -------- */
bool enqueue(queue_t *q, char *url){

	node_t *tmp = create_new_node(url);
	
	if(q->head == NULL){
		q->head = tmp;
		q->tail = tmp;
		return 1;
	}else if(q->tail != NULL){
		q->tail->next = tmp;
		q->tail = tmp;
		return 1;
	}

	return 0;
}

/*-------- dequeue  -------- */
char *dequeue(queue_t *q){

	char *url;

	if(q->head != NULL){
		url = q->head->url;
		q->head = q->head->next;
		return url;
	}else if(q->head == NULL){
		return QUEUE_EMPTY;
	}

}
/*-------- print queue  -------- */
void print_queue(queue_t q){
	int n=1;
	if(q.head == NULL){
		printf("QUEUE IS EMPTY:\n");
	}else if(q.head != NULL){
		while(q.head != NULL){
			printf("%d___%s\n",n++, q.head->url);
			q.head = q.head->next;
		}
	}
}
