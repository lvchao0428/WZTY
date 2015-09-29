/*
  Open Read full file into dynamic memory.
  Need to free dest after calling.
*/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<malloc.h>
#define BUFSIZ 1024

int file_read_full(char **dest, const char *filename)
{
   FILE *f;
   struct stat file_stats;
   int nItems, nBytesRead;

   *dest = NULL;
   if((f = fopen(filename,"r")) == NULL)
   {
      fprintf(stderr,"Failed to open %s - %s\n", filename, strerror(errno));
      return(-1);
   }
   fstat(fileno(f),&file_stats);

   if((*dest = (char *)malloc(file_stats.st_size+1))==NULL)
   {
     fclose(f);
     fprintf(stderr,"Failed to allocate memory for reading file %s\n", filename);
     return(-2);
   }
   nBytesRead=0;
   while((nItems=fread(*dest+nBytesRead,1,BUFSIZ,f))>0)
     nBytesRead+=nItems;
   fclose(f);
   *(*dest + nBytesRead) = '\0';
   return(nBytesRead);
}


int main(int argc, char* argv[])
{
   char* buf = NULL;
   file_read_full(&buf, argv[1]);

   printf("%s\n", buf);

   free(buf);

   return 0;
}
