/* ----- Header File ------*/
#include "crawler.h"
#include <time.h>

/*---------------MAIN FUNCTION-----------------*/ 
int main(int argc, char **argv)
{
    
  if(argc == 2) {
  
    first_spider(argv[1]);//first spider call
    //spider(NULL);

    pthread_t tid[NO_OF_THREADS];
   
    int i;
    for( i=0;i<NO_OF_THREADS;i++)
    {

      pthread_create(&tid[i],NULL, spider,NULL);
    }
    for( i=0;i<NO_OF_THREADS;i++)
    {
      pthread_join(tid[i],NULL);
    }
    write_hash_to_file();

  }

  else{
    printf("usage: %s <url>\n", argv[0]);
  }

  return 0;
}
/*---------------MAIN ENDS-----------------*/
