/* 
   fifo_rx2.c
   parsing the string recieving from pipe
 
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define FIFO_NODE_DEVICE_INFO "/tmp/fifo_device_info"

#define END_OF_PARSE "end"
#define REQ_ID       "request_id"
#define IN
#define OUT

const char delims[] = ":\n";

int parse_the_content(IN char* sOriginalString, OUT char* sFieldName, OUT char* sFieldContent);
 
int main(void)
{
    int fd;
    int len;
    char buf[PIPE_BUF];
    char sFiledName[PIPE_BUF];
    char sFiledContent[PIPE_BUF];

    /* read string from  FIFO_NODE_DEVICE_INFO*/

    fd = open(FIFO_NODE_DEVICE_INFO, O_RDONLY);

    if (fd < 0) {
      mode_t mode=0666;
      fprintf(stderr, "creating the fifo node\n");

      if ((mkfifo(FIFO_NODE_DEVICE_INFO, mode)) < 0) {
        fprintf(stderr, "mkfifo error\n");
        exit(1);
      }
      //try again
      fd = open(FIFO_NODE_DEVICE_INFO, O_RDONLY);
      if(fd < 0){
        fprintf(stderr, " failed to open fifo node\n");
        exit(1);
      }
    }

    while((len = read(fd, buf, PIPE_BUF-1)) > 0) {
      buf[len] = 0;
      printf("%s\n", buf);
      if( parse_the_content(buf, sFiledName, sFiledContent) == 1 ){
        fprintf(stderr, "parsed successfully.\n");
      }
      else{
        fprintf(stderr, "finished the parsing!");
      }

    }  
    close(fd);
    exit(0);
}

/*
 * parse_the_content
 * @return 1 on success
 *         0 on reaching the end of parsing or error
 *  
*/
int parse_the_content(IN char* sOriginalString, OUT char* sFieldName, OUT char* sFieldContent)
{
   char *sName = NULL;
   char *sContent = NULL;
   
   /* get the first token */
   sName = strtok(sOriginalString, delims);
   //IMPORTANT: after strtok, the content of str has been changed. clone it beforehand on necessary
   
   /* walk through other tokens */
   if( sName!= NULL ) 
   {
      printf( "filedname is - %s\n", sName);
      //check if it is the end of parsing
      if(strcmp(END_OF_PARSE, sName) == 0 ) {
        //end of parsing 
        printf("parsing finished!\n");
        return 0;

      }

      //check if filed name match
      if(strcmp(REQ_ID, sName) == 0) {
        sContent = strtok(NULL, delims);
        printf("content is   - %s\n", sContent);
        strcpy(sFieldName, sName);
        strcpy(sFieldContent, sContent);
        return 1;
      }

      printf("no matched filed name\n");
   }
   
   return 0;
  
}
