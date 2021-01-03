#include "crawler.h"
/*--------------spider function------------------*/

void *spider(void *no_argument){
    
    node_t *head = NULL;
    char*url;

    /*--- crawl variables ---*/
    CURL *curl;
    char curl_errbuf[CURL_ERROR_SIZE];
    TidyDoc tdoc;
    TidyBuffer docbuf = {0};
    TidyBuffer tidy_errbuf = {0};
    int err;
    /*--- crawl variables ---*/
    curl = curl_easy_init();
    while(1)
    {
        
        pthread_mutex_lock(&mutex);
        url=dequeue(&q);
        pthread_mutex_unlock(&mutex);
        if(strcmp(url,QUEUE_EMPTY) == 0)
          break;

        /*---crawl starts--*/
        //head = crawl(url,head);

    
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
        pthread_mutex_lock(&mutex2);
        crawl_frontier(head);
        pthread_mutex_unlock(&mutex2);
        write_hash_to_file();
        head = NULL;

        /* clean-up */ 
        //curl_easy_cleanup(curl);
        //tidyBufFree(&docbuf);
        //tidyBufFree(&tidy_errbuf);
        //tidyRelease(tdoc);
    


    }
    

}
void *first_spider(char *argv){

    node_t *head = NULL;
    char*url;

    extract_root(root, argv);//extract root/domain name
    insert_hash(create_new_node(argv), &q);

    url=dequeue(&q);//dequeue url
    if(strcmp(url,QUEUE_EMPTY) == 0)
        return;

    head = crawl(url,head);//crawl first url
    crawl_frontier(head);//insert retrieved urls to hash/ queue
    write_hash_to_file();
}