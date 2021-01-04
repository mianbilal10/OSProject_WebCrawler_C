
/* ----------- HEADER FILE  ---------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <tidy/tidy.h>
#include <tidy/buffio.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "hashqueue.h"
#include <pthread.h>
#include <signal.h> 
/*  ----------------crawler.c Declarations--------------  */


#define NO_OF_THREADS 4
static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex2=PTHREAD_MUTEX_INITIALIZER;
char root[400]; //domain name of first url

uint write_cb(char *in, uint size, uint nmemb, TidyBuffer *out);
void dumpNode(TidyDoc doc, TidyNode tnod, node_t **head);
node_t *crawl(char *url, node_t *head);
/*  --------------crawl_frontier.c Declarations------------------  */
void crawl_frontier(node_t *head);
void extract_root(char *root, char *url);//root extractor

/*  ------------------spider.c declarations------------------------  */
void* spider(void *no_argument);
void *first_spider(char *argv);
void file_writer();
void file_writer_default();

/*--------------bootup.c Declarations---------------*/
//struct used for stat function
struct stat stats; 
char waiting_list[100], crawled_list[100], found_list[100];//file paths
//create new project directory with all supporting files.
int bootup();

int create_project(char *proj_name);
bool look_up(char *path);
void file_to_queue(char *path);
void file_to_hash(char *path);
void set_file_path(char *proj_name);
void create_threads();