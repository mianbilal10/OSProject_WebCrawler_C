/* ----- Header File ------*/
#include "crawler.h"

/*  -----------PRINT URLS FUNCTION-------------  */
void url_print(){
  int j;
  for(j=0;j<n;j++){
    printf("%d: \"%s\" \n", j, url[j]);
  }

}

/* curl write callback, to fill tidy's input buffer...  */ 
uint write_cb(char *in, uint size, uint nmemb, TidyBuffer *out)
{
  uint r;
  r = size * nmemb;
  tidyBufAppend(out, in, r);
  return r;
}
 
/* ------------ DUMPNODE: Traverse the document tree---------------------- */ 
void dumpNode(TidyDoc doc, TidyNode tnod)
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
        const char *attrValue = tidyAttrValue(attr);
        if(attrId == 58 && attrValue){
          strcpy(url[n], attrValue);//copy url to global variable
          n++;
          break;
        } 
      }
    }
    dumpNode(doc, child); /* recursive */ 
  }
}

/*--------------  crawl function  ------------------*/

int crawl(char *argv){
  CURL *curl;
    char curl_errbuf[CURL_ERROR_SIZE];
    TidyDoc tdoc;
    TidyBuffer docbuf = {0};
    TidyBuffer tidy_errbuf = {0};
    int err;
    
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, argv);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    
    tdoc = tidyCreate();
    tidyOptSetBool(tdoc, TidyForceOutput, yes); /* try harder */ 
    tidyOptSetInt(tdoc, TidyWrapLen, 4096);
    tidySetErrorBuffer(tdoc, &tidy_errbuf);
    tidyBufInit(&docbuf);
 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &docbuf);
    err = curl_easy_perform(curl);

    if(!err) {
      err = tidyParseBuffer(tdoc, &docbuf); /* parse the input */ 
      if(err >= 0) {
        err = tidyCleanAndRepair(tdoc); /* fix any problems */ 
        if(err >= 0) {
          err = tidyRunDiagnostics(tdoc); /* load tidy error buffer */ 
          if(err >= 0) {

            dumpNode(tdoc, tidyGetRoot(tdoc)); /* walk the tree */
          }
        }
      }

    }else{
      return err;
    }

    /* clean-up */ 
    curl_easy_cleanup(curl);
    tidyBufFree(&docbuf);
    tidyBufFree(&tidy_errbuf);
    tidyRelease(tdoc);
    //url_print();
    //return err;
}
/*-------------------  crawl function ends  ----------------------*/
