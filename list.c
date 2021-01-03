#include "hashqueue.h"

//print list
void printList(node_t *head){

	while(head != NULL){
		printf("%s \n", head->url);
		head = head->next;
	}

}
//function to create a node
node_t *create_new_list_node(char *url){

	node_t *node = malloc(sizeof(node_t));
	node->url = url;
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
//fing a node in the list
node_t * find_node(node_t *head, char *url){

	while(head != NULL){
		if(head->url == url){
			printf("Found the node>>> %s\n", head->url);
			return head;
		}
		head = head->next;
	}

	return NULL;
}
/*
//main function
int main(int argc, char *argv[]){

	node_t *head = NULL;
	int i;
	node_t *tmp;

	for(i=0;i<200;i++){
		insert_node_head(&head, i+1);
	}

	//find node
	tmp = find_node(head, 13);
	// Insert after
	insert_node_after(tmp, create_new_node(100));
	//insert node at end of list
	for(; i< 400; i++){
		insert_node_tail(head, i+1);
	}

	//call printList function
	printList(head);
	printf("\n");

	return 0;
}
*/