#include <stdlib.h>
#include <stdio.h>
#ifdef DMALLOC
#include "dmalloc.h"
#endif

int main(int argc, char *argv[])
{
   printf("DEBUG -- line %d\n",__LINE__);
   int imax=10, jmax=10;

   printf("DEBUG -- line %d\n",__LINE__);
   // first allocate a block of memory for the row pointers
   double *x = (double *)malloc(imax*sizeof(double *));
   return(0);
   printf("DEBUG -- line %d\n",__LINE__);

   // Last, assign the memory location to point to in the block of data for each row pointer
   for (int i = 0; i < jmax; i++) {
   printf("DEBUG -- line %d\n",__LINE__);
      x[i] = 0.0;
   printf("DEBUG -- line %d\n",__LINE__);
   }
   printf("DEBUG -- line %d\n",__LINE__);
   return(0);
}
