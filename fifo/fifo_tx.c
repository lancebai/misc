/* fifo_tx.c */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>

#define FIFO_NODE_DEVICE_INFO "/tmp/fifo_device_info"
int main(void)
{
    int fd;
    int len;
    char buf[PIPE_BUF];
    time_t tp;
    mode_t mode=0666;
    struct stat sb;



    if (stat(FIFO_NODE_DEVICE_INFO, &sb) == -1 ||  \
        sb.st_mode & S_IFMT != S_IFIFO ) {
      fprintf(stderr, "fifo not exist, creating..");
      //exit(EXIT_FAILURE);
      unlink(FIFO_NODE_DEVICE_INFO);

      if ((mkfifo(FIFO_NODE_DEVICE_INFO, mode)) < 0) {
        fprintf(stderr,"mkfifo error");
        exit(1);
      }

    }
 
    printf("fifo_tx is running....\n");


    fd = open(FIFO_NODE_DEVICE_INFO, O_WRONLY);

     if (fd < 0) {
       fprintf(stderr,"open error");
       exit(1);
     }


     while(1) {
       time(&tp); // 取得目前時間
 len = sprintf(buf, "fifo03 傳來的目前時間為 %s", ctime(&tp));
     if ((write(fd, buf, len+1)) < 0) {
         fprintf(stderr,"write error");
         close(fd);
         exit(1);
       }
       sleep(3);
     }
     close(fd);
     exit(0);
}

