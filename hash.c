#include "hashqueue.h"

//write hash to the file FoundUrls.txt
void write_hash_to_file(FILE *fp){

	int i;
	for(i=0;i<MAX_HASH;i++){
		if(hash_table[i] == NULL){
		}else{
			node_t *tmp = hash_table[i];
			while(tmp != NULL){
				fprintf(fp, "%s\n", tmp->url);
				tmp = tmp->next;
			}
		}
	}
	printf("\n>>>> URLs has successfully been Written to the FoundUrls.txt\n");
}

//hash function based on ascii
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

//insert into hash
bool insert_hash(node_t *p, queue_t *queue){
	if(p == NULL) return false;
	int index = hashFunction(p->url);
	node_t *tmp = hash_table[index];

	while(tmp != NULL && strcmp(tmp->url, p->url) != 0){
		tmp = tmp->next;
	}
	if(tmp == NULL){
		printf("Found.........%s\n", p->url);
		//enqueue
		enqueue(queue, p->url);
		//insert node to hash
		p->next = hash_table[index];
		hash_table[index] = p;
	}

	return true;
}


// only insert into hash while bootup
bool just_insert_to_hash(node_t *p){
	if(p == NULL) return false;
	int index = hashFunction(p->url);
	node_t *tmp = hash_table[index];

	while(tmp != NULL && strcmp(tmp->url, p->url) != 0){
		tmp = tmp->next;
	}
	if(tmp == NULL){
		//insert node to hash
		p->next = hash_table[index];
		hash_table[index] = p;
	}

	return true;
}