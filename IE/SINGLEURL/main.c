/*************************************************************************
    > File Name: main.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Sep 22 11:31:43 2015
 ************************************************************************/

#include<stdio.h>
#include"page.h"

#define TITLE_LEN 50

int main(int argc, char* argv[])
{
   //test read file
   
   
   if(argc != 2)
   {
	  perror("two argv needed !\n");
	  exit(-1);
   }

   Page page;
   /*
   if(fill_the_page(argv[1], &page) > 0)
   {
   }
   else
   {
	  printf("read title error\n");
   }
   */

   LineBuf* lb = (LineBuf*)malloc(sizeof(LineBuf));
   lb->next = NULL;

   fill_buf(argv[1], lb);
  // test_fillbuf(lb);
   fill_the_page(lb, &page);
   printf("title:%s\n", page.title);
   printf("content:%s\n", page.content);
   printf("author:%s\n", page.author);
   printf("click num:%s\n", page.click_count);
   printf("replay num:%s\n", page.replay_count);
   printf("time:%s\n", page.time);
   
   return 0;
}
