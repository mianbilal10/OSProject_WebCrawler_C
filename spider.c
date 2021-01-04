#include "crawler.h"
/*--------------spider function------------------*/

void *spider(void *no_argument){
    
    node_t *head = NULL;
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

        if(strcmp(url,QUEUE_EMPTY) == 0)
          break;

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

        /*---crawl Ends---*/       
        pthread_mutex_lock(&mutex2);//lock
        crawl_frontier(head);
        pthread_mutex_unlock(&mutex2);//unlock

        head = NULL;
    }
}

void *first_spider(char *argv){

    node_t *head = NULL;
    char*url;

    extract_root(root, argv);//extract root/domain name
    FILE* fp;
    fp=fopen(crawled_list,"w");
    fprintf(fp,"%s",root);
    fclose(fp);
    insert_hash(create_new_node(argv), &q);

    url=dequeue(&q);//dequeue url
    if(strcmp(url,QUEUE_EMPTY) == 0)
        return;
    head = crawl(url,head);//crawl first url
    crawl_frontier(head);//insert retrieved urls to hash/ queue

}

void file_writer(){

    file_writer_default();

    raise (SIGTERM);
}
void file_writer_default(){

    FILE *fp_queue;
    fp_queue = fopen(waiting_list, "w");
    FILE *fp_hash;    
    fp_hash = fopen(found_list, "w");

    write_hash_to_file(fp_hash);
    print_queue_to_file(q,fp_queue);

    
    fclose(fp_queue);
    fclose(fp_hash);

}
