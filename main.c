/* ----- Header File ------*/
#include "crawler.h"
void help();
//main starts 
int main(int argc, char **argv)
{   
	//Signal handler call
    signal(SIGINT, file_writer);//ctrl+C 
    signal(SIGSEGV, file_writer);//seg fault
    signal(SIGABRT, file_writer);//aborted

    bootup();//bootup function call

    return 0;
}//main ends

// signal handler
void file_writer(){

    file_writer_default();

    raise (SIGTERM);
}
//write to file
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
