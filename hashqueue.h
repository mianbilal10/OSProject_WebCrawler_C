#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
/* --------------- queue.c declarations --------------- */

#define QUEUE_EMPTY "e"
// node 
struct node{
	char *url;
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
// init queue
void init_queue(queue_t *q);
//function to create a node
node_t *create_new_node(char *url);
//Enqueue
bool enqueue(queue_t *q, char *url);
//Dequeue
char *dequeue(queue_t *q);
//print queue
void print_queue(queue_t q);

/*------------- Hash.c declarations --------------------*/

#define MAX_NAME 256
#define MAX_HASH 10000
//hash table
node_t *hash_table[MAX_HASH];
//init fucntion for hash_table
void init_hash();
//hash function
unsigned int hashFunction(char *url);
//Add element to the hash
bool insert_hash(node_t *p, queue_t *q);
//Look up function 
node_t *lookup_hash(char *url);
//print hash
void write_hash_to_file();

