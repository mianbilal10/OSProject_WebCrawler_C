#include "crawler.h"

/*--------------spider function------------------*/
void spider(char *argv){

	strcpy(url[n], argv);//copy url to global variable
    n++;
    extract_root(root, argv);
   
    insert_hash(create_new_node(argv), &q);
    current++;
    
    char *url_string= dequeue(&q);
    crawl(url_string);
    crawl_frontier(); 

    int status = 1;//Comment

	int loop;
    //for(loop=0;loop<2;loop++){
      	while(strcmp(url_string=dequeue(&q), QUEUE_EMPTY) !=0){
      		crawl(url_string);
      		crawl_frontier();//insert queue and hash
      		printf("URL#%d___Crawled...%s\n", status++, url_string);
      		print_hash();//write to file
      	}
      	//print_queue(q);
    	//crawl_frontier();
   //}
   
    //print_hash();//write to file

}