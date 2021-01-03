#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
/* --------------- queue.c declarations --------------- */

#define QUEUE_EMPTY "e"
#define URL_LEN 2024
// node 
struct node{
	char url[URL_LEN];//changed
	struct node *next;
};
typedef struct node node_t;

//queue
struct queue{
	node_t *head;
	node_t *tail;
};
typedef struct queue queue_t;

//declare a queue
queue_t q;
//function to create a node
node_t *create_new_node(char *url);
//Enqueue
bool enqueue(queue_t *q, char *url);
//Dequeue
char *dequeue(queue_t *q);

/*------------- Hash.c declarations --------------------*/

#define MAX_NAME 256
#define MAX_HASH 100
//hash table
node_t *hash_table[MAX_HASH];
//hash function
unsigned int hashFunction(char *url);
//Add element to the hash
bool insert_hash(node_t *p, queue_t *q);
//print hash
void write_hash_to_file();

/*--------------list.c declarations--------------*/
node_t * create_new_list_node(char *url);
void insert_node_head(node_t **head, char* url);