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

    spider(argv[1]);//calling spider

  }

  else{
    printf("usage: %s <url>\n", argv[0]);
  }

  return 0;
}
/*---------------MAIN ENDS-----------------*/
