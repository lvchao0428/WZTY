/*************************************************************************
    > File Name: test_readline.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Sep 22 14:43:55 2015
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
   FILE* fp;
   char* line = NULL;
   size_t len = 0;
   ssize_t read;

   fp = fopen(argv[1], "r");

   if(fp == NULL)
   {
	  exit(EXIT_FAILURE);
   }

   while((read = getline(&line, &len, fp)) != -1)
   {
	  printf("%Retrieved line of length %zu: \b", read);
	  printf("%s", line);
   }

   free(line);

   exit(EXIT_FAILURE);

   return 0;
}
