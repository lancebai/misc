/**
   a simple example of using strtok as parser 
 */
#include <string.h>
#include <stdio.h>

/* the format to be parsed is
filed_name:content
end
 */
#define END_OF_PARSE "end"
#define REQ_ID       "request_id"
char str[] = "request_id:the_fudge_id\nend";
const char delims[] = ":\n";

int main()
{

   char *token = NULL;
   char *sFieldName = NULL;
   char *sContent = NULL;
   
   /* get the first token */
   sFieldName = strtok(str, delims);
   //IMPORTANT: after strtok, the content of str has been changed. clone it beforehand on necessary
   
   /* walk through other tokens */
   while( sFieldName!= NULL ) 
   {
      printf( "filedname is - %s\n", sFieldName);
      //check if it is the end of parsing
      if(strcmp(END_OF_PARSE, sFieldName) == 0 ) {
        //end of parsing 
        printf("parsing finished!\n");
        break;

      }

      //check if filed name match
      if(strcmp(REQ_ID, sFieldName) == 0) {
        sContent = strtok(NULL, delims);
        printf("content is   - %s\n", sContent);
      }
      sFieldName = strtok(NULL, delims);

   }
   
   return(0);
}

