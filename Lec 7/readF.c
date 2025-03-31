// Program to open a file and read with different buffer sizes
#include <stdlib.h>
#include <stdio.h>
#define BUFSIZE   24
#define O_RDONLY  00
#include <fcntl.h> // for open
#include <unistd.h> // for close

int main ()
{
  char buffer [BUFSIZE];
  int length;
  int fd;
  if ( ( fd = open ("alice.txt", O_RDONLY) ) < 0 ) {
     perror("Unable to open data");
    exit (1);
  }
  while ( (length = read (fd, buffer, BUFSIZE)) > 0 ) {
    write (1, buffer, length);
    write (1," *** ",5);
  }
  close (fd);
  exit (0);
}