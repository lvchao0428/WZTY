/*************************************************************************
    > File Name: write.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Thu Sep 24 15:22:50 2015
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>

int write_to_file(char* filename, char* s)
{
   FILE* fp;

   fp = fopen(filename, "w");
   if(fp == NULL)
   {
	  printf("openfile wrong");
	  return 0;

   }
   int i;
   printf("strlen: %d\n", strlen(s));
   for(i = 0; i < strlen(s); ++i)
   {
	  fprintf(fp, "%c\n", s[i]);
   }

   fclose(fp);

}

int main(int argc, char* argv[])
{
   if(argc < 2)
   {
	  perror("need more 2 argv\n");
   }
   write_to_file(argv[1], "china");


   return 0;
}
