#include "crawler.h"

/*  -----------CRAWL FRONTIER-------------  */
/*--------- It validate the urls
      Populate the hash table
      Populate the queue
      Empty the url array-----------*/

void crawl_frontier(node_t *head){

    size_t dLength = strlen(root);
    char *temp;
    node_t *tmp_node;
    
    //start loop
    while(head != NULL){
      if (strncmp("http://", head->url, 7) == 0){
        if(strncmp(root,(head->url)+7,dLength) == 0){
          insert_hash(create_new_node(head->url), &q);//insert into hash
        }

      }else if (strncmp("https://", head->url, 8) ==0){
        if(strncmp(root,(head->url)+8,dLength) ==0) {
          insert_hash(create_new_node(head->url), &q);//insert into hash
        } 

      }else if(strncmp("//", head->url, 2) ==0){//start from double slash 
        if(strncmp(root,(head->url)+2,dLength) ==0) 
        {//refined from root domain
          temp=strdup(head->url);
          strcpy(head->url,"https:");
          strcat(head->url, temp);
          insert_hash(create_new_node((head->url)), &q);//insert into hash
        }

      }else{  
          //concatenate root in front of incomplete urls
        if(head->url[0] == '/'){
          temp=strdup(head->url);
          strcpy(head->url,"https://");
          strcat(head->url,root);
          strcat(head->url, temp);   
          insert_hash(create_new_node(head->url), &q);//insert new node into hash
        }else{
          temp=strdup(head->url);
          strcpy(head->url,"https://");
          strcat(head->url,root);
          strcat(head->url, "/");
          strcat(head->url, temp);   
          insert_hash(create_new_node(head->url), &q);//insert new node into hash
        }
          
      }
      tmp_node = head;
      head = head->next;
      free(tmp_node);
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
