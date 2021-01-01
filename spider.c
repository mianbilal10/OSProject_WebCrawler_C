#include "crawler.h"
/*--------------spider function------------------*/
void spider(char *argv){

	strcpy(url[n], argv);//copy url to global variable
    n++;
    extract_root(root, argv);//extract root
   
    insert_hash(create_new_node(argv), &q);
    current++;
    
    char *url_string= dequeue(&q);
    crawl(url_string);
    crawl_frontier();
    /*----ends first crawl----*/


    int threads = 0, id = 0, control = 0;
    char *array[NO_OF_THREADS];
    pthread_t tid[NO_OF_THREADS];

    while(control<2){

        for(threads = 0; threads < NO_OF_THREADS; threads++){

            if(strcmp(array[threads] = dequeue(&q), QUEUE_EMPTY) == 0){
                control++;
                break;
            }
            pthread_create(&tid[threads], NULL, crawl, array[threads]);//create threads
        }

        for(id = 0; id < threads; id++){
            pthread_join(tid[id], NULL);//join threads
        }

        if(strcmp(array[threads-1], QUEUE_EMPTY) == 0){
            crawl_frontier();
        }
    }
    write_hash_to_file();//write to file
}