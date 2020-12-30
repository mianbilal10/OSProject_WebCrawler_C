/* ----- Header File ------*/
#include "crawler.h"
#include <time.h>

/*---------------MAIN FUNCTION-----------------*/ 
int main(int argc, char **argv)
{
  clock_t start, end;
  double cpu_time_used;
  
  n = 0, current = 0;
  if(argc == 2) {

    strcpy(url[n], argv[1]);//copy url to global variable
    n++;
    extract_root(root, argv[1]);
    insert_hash(create_new_node(argv[1]), &q);
    current++;
    char *url_string;
    while((url_string = dequeue(&q)) != QUEUE_EMPTY){
      crawl(url_string);
    }
    crawl_frontier();

    printf("TOTAL URLS:_______%d\n", n);
    //print_root(root);
  }else{
    printf("usage: %s <url>\n", argv[0]);
  }

  return 0;
}
/*---------------MAIN ENDS-----------------*/

