// Program to allocate memory for a number of ints
#include <stdlib.h>
#include <stdio.h>

int main() {
  int n, *ptr;
  // read a number of ints
  printf("How many ints do you want to allocate memory for?: ");
  scanf("%d", &n);

  ptr = (int*) malloc(n * sizeof(int));

  printf("\n total memory requested : %d \n",n * sizeof(int));
  // if memory cannot be allocated
  if(ptr == NULL) {
    printf("\n Error! There is not enough memory.\n");
    exit(0);
  }

  // free  the memory before leaving the process
  free(ptr);

  return 0;
}
