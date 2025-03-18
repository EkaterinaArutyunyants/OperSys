#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define KIBI 1024
#define MIBI (KIBI * KIBI)
#define PAGE_SIZE (4 * KIBI)

int main (int argc, char** argv)
{
   int n = atoi(argv[1]);
   unsigned long mem = n * MIBI;
   unsigned long pages = mem / PAGE_SIZE;
   if (mem % PAGE_SIZE > 0) ++pages;

   printf("Process %d requesting %d MiB = %lu pages...", getpid(), n, pages);
   fflush(stdout);

   void *m = malloc(mem);
   if (m == NULL) {
      printf(" malloc FAILED.\n");
      exit(1);
   }
   printf(" success.\n");

/*
   printf("Press Enter to continue:");
   fflush(stdout);
   char c;
   scanf("%c", &c);

   printf("Writing to each page...\n");
   int p;
   for (p = 0; p < pages; p++) {
      void *a = m + p * PAGE_SIZE;
      memset(a, 0, 1);
   }
*/

   printf("Process %d sleeping...\n", getpid());
   sleep(6000);
   printf("... finished.\n");
}
