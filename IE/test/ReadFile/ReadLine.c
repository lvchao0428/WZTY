/*************************************************************************
    > File Name: ReadLine.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Thu Sep 24 10:39:39 2015
 ************************************************************************/

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<errno.h>
int readline(char* filename)
{
   FILE* fp;
   char* line = NULL;
   size_t len = 0;
   ssize_t read_n;

   fp = fopen(filename, "r");
   if(fp == NULL)
   {
	  fprintf(stderr, "file to open %s - %s\n", filename, strerror(errno));
	  return (-1);
   }

   while((read_n = getline(&line, &len, fp)) != -1)
   {
	  printf("len:%d, %s\n", strlen(line), line);
   }
   free(line);
}

int main(int argc, char* argv[])
{
   readline(argv[1]);

   return 0;
}
