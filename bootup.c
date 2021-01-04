/*----------This file is to open/create folders
 and read data from those files to the memory
  in queues and hash tables to assist booting up the crawler------------*/

#include "crawler.h"
//bootup starts
int bootup(){

	int input;// 1 for new project and 2 for existing project
	char proj_name[100];//name of project or directory path
	char url[URL_LEN];//first url for crawling

	system("clear");

	printf("|||  ******************** Web Crawler **********************  |||\n\n");

	printf("Press 1 for new_project\n");
	printf("Press 2 for existing_project\n");
	printf(">>>>");
	scanf("%d",&input);
	if(input == 1){//new project
		printf("\nEnter Project Name: \n");
		printf(">>>>");
		scanf("%s",proj_name);
		//input the project name
		set_file_path(proj_name);//set all file paths
		if(create_project(proj_name) == 0){
			
			printf("\nProject: \"%s\" created successfully!\n\n", proj_name);
			printf("Enter the starting url: \n");
			printf(">>>>");
			scanf("%s",url);//get the starting url from user.
			printf("\nPress any key to start crawling.....");
			
			while(getchar() !='\n'){}
			getchar();
			  
			first_spider(url);//first spider call
			create_threads();//create threads

		}else{
			printf("\nERROR: Could not create the project.\n");
			printf("Usage: ./crawler --help\n");
			return 0;
		}
		

	}else if(input == 2){//existing project
		printf("\nEnter Project Name: \n");
		printf(">>>>");
		scanf("%s",proj_name);
		//get the existing project path

		if(look_up(proj_name) == 0){//exists
			printf("\nPlease wait.....\n");
			printf("Booting up your project........\n");

			set_file_path(proj_name);//set all file paths
			file_to_queue(waiting_list);//fill queue
			file_to_hash(found_list);//fill hash
			printf("Press any key to start crawling...");
			
			while(getchar() !='\n'){}
			getchar();

			//read domain name from Domain.txt
			FILE*fp;
			fp=fopen(root_list,"r");
			fscanf(fp,"%s",root);
			fclose(fp);//file close

			//create threads
			create_threads();
			
			return 0;
		}else{//do not exist
			printf("\nFile/Directory do not exist.\n\n");
			exit(0);//exit the program
		}

	}else{
		printf("\nInvalid Input.\n");
	}
	
	return 0;
}//bootup ends

//create threads starts
void create_threads(){
			
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
		    
}//create threads ends

//checks if a directory exists or not
bool look_up(char *path){
	if(stat(path, &stats) == 0) return 0;
	else return -1;
}

//create new folder if not exist
int create_project(char *proj_name){
	//lookup dir
	if(look_up(proj_name) == 0){
		printf("File/Directory already exist\n");
		return -1;
	}
	//create dir
	if(mkdir(proj_name, 777) == 0){
		//change dir mode
		chmod(proj_name, S_IRUSR | S_IWUSR | S_IXUSR);
		//create files in dir
		FILE *fp;
		fp = fopen(waiting_list, "w");
		fclose(fp);
		fp = fopen(root_list, "w");
		fclose(fp);
		fp = fopen(found_list, "w");
		fclose(fp);

	}else{
		return -1;
	}
	
	return 0;
}

//extract domain name
void  extract_root(char *root, char *url){

  char tmp[7];

  strncpy(tmp, url, 6);
  tmp[7] = '\0';

  //extracting the domain name.
  if(strchr(tmp, '/') != NULL){
    sscanf(url, "http://%[^/]", root);
  }else if(strchr(tmp, ':') != NULL){
    sscanf(url, "https://%[^/]", root);
  }else{
    sscanf(url, "%[^/]", root);   
  }

}//ends

//Create file paths
void set_file_path(char *proj_name){

	strcpy(waiting_list, proj_name);
	strcat(waiting_list, "/WaitingList.txt");
	strcpy(found_list, proj_name);
	strcat(found_list, "/FoundUrls.txt");
	strcpy(root_list, proj_name);
	strcat(root_list, "/Domain.txt");

}

//Function to read from Waiting list and fill the queue
void file_to_queue(char *path){

	FILE *fp = fopen(path, "r");
    if(fp == NULL) {
      perror("Unable to open file!");
      return;
    }
    
    char chunk[URL_LEN], copy[URL_LEN];
 	//read line by line
    while(fgets(chunk, sizeof(chunk), fp) != NULL) {
    	sscanf(chunk, "%[^\n]", copy);
    	enqueue(&q, copy);
    }
    fclose(fp);
	
}

//Function to read from found urls and fill the hash
void file_to_hash(char *path){

	FILE *fp = fopen(path, "r");
    if(fp == NULL) {
      perror("Unable to open file!");
      return;
    }
   
    char chunk[URL_LEN], copy[URL_LEN];
 	//read line by line
    while(fgets(chunk, sizeof(chunk), fp) != NULL) {
    	sscanf(chunk, "%[^\n]", copy);
    	just_insert_to_hash(create_new_node(copy));
    }
    fclose(fp);

}
