#include <stdlib.h>
#ifdef DMALLOC
#include "dmalloc.h"
#endif

int main(int argc, char *argv[])
{
   int imax=10, jmax=12;

   // first allocate a block of memory for the row pointers
   double *x = (double *)malloc(imax*sizeof(double *));

   // now initialize the x array to zero
   for (int i = 0; i < jmax; i++) {
      x[i] = 0.0;
   }
   free(x);
   return(0);
}
