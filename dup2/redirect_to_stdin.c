#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main(int argc, char** argv)
{
  int fdRead;
  char *filename = NULL;
  printf("argc:%d\n", argc);
  if(2 != argc) {
    fprintf(stderr, "redirect_to_stdin filename\n");
    return;
  }

  filename = argv[1];
  fdRead = open(filename,  O_SYNC | O_WRONLY); 
  if(-1 == fdRead){
    fprintf(stderr, "Cannot open %s. Try again later.\n", filename);
    exit(-1);
  }

  dup2(fdRead, STDIN_FILENO);
  close(fdRead);
}
