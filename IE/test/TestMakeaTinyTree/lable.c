/*************************************************************************
    > File Name: lable.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Wed Sep 23 15:52:43 2015
 ************************************************************************/

#include<stdio.h>
#include"lable.h"

int addElem(Lable* l, LableElem* le)
{
   if(l->le == NULL)
   {
	  l->le = le;
	  l->leTail = le;
   }
   else
   {
	  l->leTail->next = le;
	  l->leTail = l->leTail->next;
   }
}



int readElem(Lable* l)
{
   if(l->le == NULL)
   {
	  return 0;
   }
   LableElem* p = l->le;
   while(p != NULL)
   {
	  printf("key:%s, value:%s\n", p->key, p->value);
	  p = p->next;
   }
}

int fill_lable(Lable* l, char* file)
{
   FILE* fp;
   char* line = NULL;	
   size_t len = 0;
   ssize_t read_n;

   fp = fopen(file, "r");
   if(fp == NULL)
   {
	  perror("read file error!");
	  return 0;
   }

   while((read_n = getline(&line, &len, fp)) != -1)
   {
	  int i = 0;

	  if(line[i] != '\0')
	  {
		 //
		 if(line[i] == '<')
		 {
			LableElem* le = (LableElem*)malloc(sizeof(LableElem));
			
		 }
	  }
   }

   	  
}


