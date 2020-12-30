#include "hashqueue.h"
/*-------- init hash -------- */
void init_hash(){
	int i;
	for(i=0;i<MAX_HASH;i++){
		hash_table[i] = NULL;
	}
}

/*-------- print hash -------- */
void print_hash(){
	printf("START __\n");
	int i;
	for(i=0;i<MAX_HASH;i++){
		if(hash_table[i] == NULL){
			printf("\t%d\t----\n", i);
		}else{
			printf("\t%d\t", i);
			node_t *tmp = hash_table[i];
			while(tmp != NULL){
				printf("%s----", tmp->url);
				tmp = tmp->next;
			}
			printf("\n");
		}
	}
	printf("___END\n");
}

/*-------- hash function -------- */
unsigned int hashFunction(char *url){
	int len = strlen(url);
	unsigned int asc = 0, i;
	int g=31;
	for(i=0;i<len;i++){
		asc += url[i];
	}
	asc = asc%MAX_HASH;
	return asc;
}

/*-------- insert into hash -------- */
bool insert_hash(node_t *p, queue_t *queue){
	if(p == NULL) return false;
	int index = hashFunction(p->url);
	node_t *tmp = hash_table[index];

	while(tmp != NULL && strcmp(tmp->url, p->url) != 0){
		tmp = tmp->next;
	}
	if(tmp == NULL){
		//enqueue
		enqueue(queue, p->url);
		p->next = hash_table[index];
		hash_table[index] = p;

	}

	return true;
}

/*-------- lookup from hash -------- */
node_t *lookup_hash(char *url){
	int index = hashFunction(url);
	node_t *tmp = hash_table[index];

	while(tmp != NULL && strcmp(tmp->url, url) != 0){
		tmp = tmp->next;
	}

	return tmp;
}
