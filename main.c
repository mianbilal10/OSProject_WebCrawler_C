/* ----- Header File ------*/
#include "crawler.h"

/*---------------MAIN FUNCTION-----------------*/ 
int main(int argc, char **argv)
{
    signal(SIGINT, file_writer); 
    signal(SIGSEGV, file_writer);
    signal(SIGABRT, file_writer);
    signal(SIGSTOP, stop_handler);
    bootup();

    file_writer_default();

    return 0;
}
/*---------------MAIN ENDS-----------------*/
