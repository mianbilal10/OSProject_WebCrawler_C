/* ----- Header File ------*/
#include "crawler.h"
/* curl write callback, to fill tidy's input buffer...  */ 
uint write_cb(char *in, uint size, uint nmemb, TidyBuffer *out)
{
  uint r;
  r = size * nmemb; 
  tidyBufAppend(out, in, r);
  return r;
}
 
/* ------------ DUMPNODE: Traverse the document tree---------------------- */ 
void dumpNode(TidyDoc doc, TidyNode tnod, node_t **head)
{
  TidyNode child;
  for(child = tidyGetChild(tnod); child; child = tidyGetNext(child) ) {
    const int tagId = tidyNodeGetId(child);
    if(tagId == 1) { // a-tag ID = 1
      /* if it has a name, then it's an HTML tag ... */ 
      TidyAttr attr;
      /* walk the attribute list */ 
      for(attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr) ) {
        const int attrId = tidyAttrGetId(attr); //href attribute ID = 58
        char *attrValue = (char *)tidyAttrValue(attr);
        if(attrId == 58 && attrValue){
          insert_node_head(head, attrValue);
          break;
        } 
      }
    }
    dumpNode(doc, child, head); /* recursive */ 
  }
}

/*--------------  crawl function  ------------------*/

node_t *crawl(char* url, node_t *head){

    CURL *curl;
    TidyDoc tdoc;
    TidyBuffer docbuf = {0};
    TidyBuffer tidy_errbuf = {0};
    int err;
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);

    tdoc = tidyCreate();
    tidySetErrorBuffer(tdoc, &tidy_errbuf);
    tidyBufInit(&docbuf);
 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &docbuf);
    err = curl_easy_perform(curl);

    if(!err) {
      err = tidyParseBuffer(tdoc, &docbuf); /* parse the input */ 
      if(err >= 0) {
        dumpNode(tdoc, tidyGetRoot(tdoc), &head); /* walk the tree */
        tidyBufFree(&docbuf);//clear buffer
        tidyBufFree(&tidy_errbuf);//clear buffer
        curl_easy_cleanup(curl);//clear buffer
        return head;
      }
    }else{
      return NULL;
    }
}
/*-------------------  crawl function ends  ----------------------*/

