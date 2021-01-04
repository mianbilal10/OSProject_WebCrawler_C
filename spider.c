#include "crawler.h"
/*--------------spider function------------------*/

//thread function
void *spider(void *no_argument){
    
    node_t *head = NULL;//linked list head
    char*url;

    CURL *curl;
    char curl_errbuf[CURL_ERROR_SIZE];
    TidyDoc tdoc;
    TidyBuffer docbuf = {0};
    TidyBuffer tidy_errbuf = {0};
    int err;

    curl = curl_easy_init();
    
    while(1)
    {
        
        pthread_mutex_lock(&mutex);//lock
        url=dequeue(&q);
        pthread_mutex_unlock(&mutex);//unlock

        if(strcmp(url,QUEUE_EMPTY) == 0)//break condition
          break;
      
        printf("Crawling......%s\n", url);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);

        tdoc = tidyCreate();
        tidyOptSetBool(tdoc, TidyForceOutput, yes); /* try harder */ 
        tidyOptSetInt(tdoc, TidyWrapLen, 4096);
        tidySetErrorBuffer(tdoc, &tidy_errbuf);
        tidyBufInit(&docbuf);
 
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &docbuf);
        err = curl_easy_perform(curl);

        if(!err) {
            err = tidyParseBuffer(tdoc, &docbuf); /* parse the input */ 
            if(err >= 0) {
                err = tidyCleanAndRepair(tdoc); /* fix any problems */ 
                if(err >= 0) {
                    err = tidyRunDiagnostics(tdoc); /* load tidy error buffer */ 
                    if(err >= 0) {
                        dumpNode(tdoc, tidyGetRoot(tdoc), &head); /* walk the tree */
                    }
                }
            }
        }
      
        pthread_mutex_lock(&mutex2);//lock
        crawl_frontier(head);
        pthread_mutex_unlock(&mutex2);//unlock

        head = NULL;
    }
}//spider ends

//crawl first url
void *first_spider(char *argv){

    node_t *head = NULL;//linked list head
    char*url;

    extract_root(root, argv);//extract domain name
    //write the domain name into Domain.txt file
    FILE* fp;
    fp=fopen(root_list,"w");
    fprintf(fp,"%s",root);
    fclose(fp);//file close

    insert_hash(create_new_node(argv), &q);//insert first url to hash/queue

    url=dequeue(&q);//dequeue url
    if(strcmp(url,QUEUE_EMPTY) == 0)//break condition
        return;
    printf("Crawling......%s\n", url);
    head = crawl(url,head);//crawl first url
    crawl_frontier(head);//insert retrieved urls to hash/ queue
}

