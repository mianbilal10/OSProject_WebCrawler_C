#include "hashqueue.h"
//function to create a node
node_t *create_new_list_node(char *url){

	node_t *node = malloc(sizeof(node_t));
	strcpy(node->url, url);
	node->next = NULL;

	return node;
}
//function to insert nod at head
void insert_node_head(node_t **head, char* url){

	node_t *tmp;
	tmp = create_new_list_node(url); 
	tmp->next = *head;
	*head = tmp;
}
