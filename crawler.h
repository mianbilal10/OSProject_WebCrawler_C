
/* ----------- HEADER FILE  ---------------- */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <tidy/tidy.h>
#include <tidy/buffio.h>
#include <curl/curl.h>
#include "hashqueue.h"
#include <pthread.h>
/*  ----------------crawler.c Declarations--------------  */

#define MAX_URL 1000000
#define URL_LEN 2024
#define NO_OF_THREADS 100

struct url{
	char *url;
};
typedef struct url url_t;

int n , current;//number of urls retrieved and current
char url[MAX_URL][URL_LEN];//to store obtained urls
char root[400]; //domain name of first url
int initial_queue;
void url_print(void);//print links
void  extract_root(char *root, char *url);//root extractor

uint write_cb(char *in, uint size, uint nmemb, TidyBuffer *out);
void dumpNode(TidyDoc doc, TidyNode tnod);
void *crawl(void *arg);

/*  --------------crawl_frontier.c Declarations------------------  */
void crawl_frontier();
char *url_formatted_string(char *url);
char *domain_name(char *domain);

/*  ------------------spider.c declarations------------------------  */
void spider(char *argv);