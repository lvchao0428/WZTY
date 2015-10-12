/*************************************************************************
    > File Name: myfiledeal.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Sat Oct 10 17:59:07 2015
 ************************************************************************/

#include<stdio.h>
#include"myfiledeal.h"


int fill_buf(char* filename, LineBuf* lb)
{
   FILE* fp;
   char* line = NULL;
   size_t len = 0;
   ssize_t read_n;

   fp = fopen(filename, "r");
   if(fp == NULL)
   {
	  perror("read file error.");
	  return -1;
   }
   LineBuf* p = lb->next;
   int no =0;
   //getline len的参数为当前line的最大长度
   while((read_n = getline(&line, &len, fp)) != -1)
   {
	  no++;

	  // printf("lineno:%d, len:%d, %s\n",no, len, line);
	  if(line[0] == '\n')
		 continue;
	  LineBuf* q = (LineBuf*)malloc(sizeof(LineBuf));
	  //	  printf("len:%d, %s\n", strlen(line), line);
	  q->str = (char*)malloc(sizeof(char)*(strlen(line)+1));

	  q->next = NULL;
	  strcpy(q->str, line);

	  if(lb->next == NULL)
	  {
		 lb->next = q;
		 p = q;
	  }
	  else
	  {
		 p->next = q;
		 p = p->next;
	  }

   }

   free(line);
}


int file_read_full(char** dest, const char* filename)
{//把整个文件读成一个字符串
   FILE* fp;
   struct stat file_stats;
   int nItems, nBytesRead;

   *dest = NULL;
   if((fp = fopen(filename, "r")) == NULL)
   {
	  fprintf(stderr, "failed to open %s - %s\n", filename, strerror(errno));
	  return(-1);
   }
   fstat(fileno(fp), &file_stats);

   if((*dest = (char*)malloc(file_stats.st_size+1)) == NULL)
   {
	  fclose(fp);
	  fprintf(stderr, "failed to allocate memory for reading file%s\n", filename);
	  return(-2);
   }
   nBytesRead = 0;
   while((nItems = fread(*dest + nBytesRead, 1, BUFSIZ,fp)) > 0)
   {
	  nBytesRead += nItems;
   }
   fclose(fp);
   *(*dest + nBytesRead) = '\0';

   return (nBytesRead);
}



