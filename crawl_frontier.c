#include "crawler.h"

/*  -----------CRAWL FRONTIER-------------  */
/*--------- It validate the urls
      Populate the hash table
      Populate the queue
      Empty the url array-----------*/

void crawl_frontier(){

    size_t dLength = strlen(root);
    char complete_url[URL_LEN];
    char *temp;
    //start loop
    for(; current<n; current++){

      if (strncmp("http://", url[current], 7) == 0){
        if(strncmp(root,(url[current])+7,dLength) == 0){
          insert_hash(create_new_node((url[current])+7), &q);//insert into hash
        }

      }else if (strncmp("https://", url[current], 8) ==0){
        if(strncmp(root,(url[current])+8,dLength) ==0) {
          insert_hash(create_new_node((url[current])+8), &q);//insert into hash
        } 

      }else if(strncmp("//", url[current], 2) ==0){//start from double slash 
        if(strncmp(root,(url[current])+2,dLength) ==0) {//refined from root domain
          insert_hash(create_new_node((url[current])+2), &q);//insert into hash
        }

      }else{  
          //concatenate root in front of incomplete urls
        if(url[current][0] == '/'){
          temp=strdup(url[current]);
          strcpy(url[current],root);
          strcat(url[current], temp);   
          insert_hash(create_new_node(url[current]), &q);//insert new node into hash
        }else{
          temp=strdup(url[current]);
          strcpy(url[current],root);
          strcat(url[current], "/");
          strcat(url[current], temp);   
          insert_hash(create_new_node(url[current]), &q);//insert new node into hash
        }
          
      }
    
    }
    //end loop
}

/*--------------Extract domain name-----------------*/
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

}
void print_root(char *root){
  printf("ROOT___: %s\n", root);
}
