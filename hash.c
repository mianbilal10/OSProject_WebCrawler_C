#include "hashqueue.h"
/*-------- print hash -------- */
void write_hash_to_file(){
	int count = 1;
	FILE *fp;
  	fp = fopen("urls.txt","w");
	int i;
	for(i=0;i<MAX_HASH;i++){
		if(hash_table[i] == NULL){
		}else{
			node_t *tmp = hash_table[i];
			while(tmp != NULL){
				fprintf(fp, "%d: %s\n",count++, tmp->url);
				tmp = tmp->next;
			}
		}
	}
	fclose(fp);
	printf("URLs has successfully been Written to the urls.txt\n");
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
		//printf("Inserted:_____------%s\n", p->url);
		//enqueue
		enqueue(queue, p->url);
		p->next = hash_table[index];
		hash_table[index] = p;
	}

	return true;
}
