/*----------This file is to open/create folders
 and read data from those files to the memory
  in queues and hash tables to assist booting up the crawler------------*/

#include "crawler.h"
void print_hash();
void print_queue();
int bootup(){

	int input;// 1 for new project and 2 for existing project
	char proj_name[100];//name of project or directory path
	char url[URL_LEN];//first url for crawling
	printf("********************Web Crawler**********************\n");
	printf("Please Enter:\n");
	printf("1 for new_project\n");
	printf("2 for existing_project\n");
	scanf("%d",&input);
	if(input == 1){//new project
		printf("Enter Project Name: \n");
		scanf("%s",proj_name);
		//input the project name
		set_file_path(proj_name);//set all file paths
		if(create_project(proj_name) == 0){
			
			printf("Project: \"%s\" created successfully!\n", proj_name);
			printf("Please Enter the starting url: \n");
			scanf("%s",url);//get the starting url from user.
			printf("Press a key to start crawling.....");
			getchar();
			  
			first_spider(url);//first spider call
			create_threads();//create threads

		}else{
			printf("Could not create the project.\n");
			return 0;
		}
		

	}else if(input == 2){//existing project
		printf("Enter Project Name: \n");
		scanf("%s",proj_name);
		//get the existing project path

		if(look_up(proj_name) == 0){//exists
			printf("File/directory exist.\n");
			printf("Booting up your project........\n");

			set_file_path(proj_name);//set all file paths
			file_to_queue(waiting_list);//fill queue
			file_to_hash(found_list);//fill hash
			printf("press any key to start the crawl...");
			getchar();

			FILE*fp;
			fp=fopen(crawled_list,"r");
			fscanf(fp,"%s",root);
			fclose(fp);
			create_threads();//create threads
			
			return 0;
		}else{//do not exist
			printf("File/directory do not exist.\n");
			exit(0);//exit the program
		}

	}else{
		printf("Invalid Input.\n");
	}
	
	return 0;
}
/*------------create threads--------------*/
void create_threads(){
			/*----------- start crawling -----------*/
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
		    /*----------- end crawling -----------*/
}
//checks if a directory exists or not
bool look_up(char *path){
	if(stat(path, &stats) == 0) return 0;
	else return -1;
}
//create new folder if not exist
int create_project(char *proj_name){
	if(look_up(proj_name) == 0){
		printf("File/Directory already exist\n");
		return -1;
	}
	if(mkdir(proj_name, 777) == 0){
		chmod(proj_name, S_IRUSR | S_IWUSR | S_IXUSR);
		FILE *fp;

		fp = fopen(waiting_list, "w");
		fclose(fp);
		fp = fopen(crawled_list, "w");
		fclose(fp);
		fp = fopen(found_list, "w");
		fclose(fp);

	}else{
		return -1;
	}
	
	return 0;
}

//Create file paths
void set_file_path(char *proj_name){

	strcpy(waiting_list, proj_name);
	strcat(waiting_list, "/WaitingList.txt");
	strcpy(found_list, proj_name);
	strcat(found_list, "/FoundUrls.txt");
	strcpy(crawled_list, proj_name);
	strcat(crawled_list, "/Crawled.txt");

}
/*---------------Functions to read from files -----------------*/
void file_to_queue(char *path){

	FILE *fp = fopen(path, "r");
    if(fp == NULL) {
      perror("Unable to open file!");
      return;
    }
    printf("QUEUE\n");
    char chunk[URL_LEN], copy[URL_LEN];
 
    while(fgets(chunk, sizeof(chunk), fp) != NULL) {
    	sscanf(chunk, "%[^\n]", copy);
    	enqueue(&q, copy);
        //fputs(chunk, stdout);
    }
 	
    fclose(fp);
	
}
void file_to_hash(char *path){

	FILE *fp = fopen(path, "r");
    if(fp == NULL) {
      perror("Unable to open file!");
      return;
    }
    printf("HASH\n");
    char chunk[URL_LEN], copy[URL_LEN];
 
    while(fgets(chunk, sizeof(chunk), fp) != NULL) {
    	sscanf(chunk, "%[^\n]", copy);
    	just_insert_to_hash(create_new_node(copy));
        //fputs(chunk, stdout);
    }
    fclose(fp);

}

/*-------- print hash -------- */
void print_hash(){

	int i;
	//int count=0;
	for(i=0;i<MAX_HASH;i++){
		if(hash_table[i] == NULL){
		}else{
			node_t *tmp = hash_table[i];
			while(tmp != NULL){
				//fprintf(fp, "%s\n", tmp->url);
				printf("write_hash-------%s\n", tmp->url);
				tmp = tmp->next;
			}
		}
	}

}
/*--------print queue-----------*/
void print_queue(){
	int n=1;
	if(q.head == NULL){
		printf("QUEUE IS EMPTY:\n");
	}else if(q.head != NULL){
		while(q.head != NULL){
			printf("print_queue_to_file---------%s\n", q.head->url);
			q.head = q.head->next;
		}
	}
}