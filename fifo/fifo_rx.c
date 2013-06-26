/* fifo_reciever.c*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#define FIFO_NODE_DEVICE_INFO "/tmp/fifo_device_info"

int main(void)
{
    int fd;
    int len;
    char buf[PIPE_BUF];

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
      printf("%s", buf);

    }  
    close(fd);
    exit(0);
}
