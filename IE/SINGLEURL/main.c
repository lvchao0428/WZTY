/*************************************************************************
    > File Name: main.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Sep 22 11:31:43 2015
 ************************************************************************/

#include<stdio.h>
#include"page.h"
#include"discuz_extract.h"
#include"nodiscuz_extract.h"
#include"def.h"
#include"myfiledeal.h"
#include<stdlib.h>
#include"test.h"

#define TITLE_LEN 50

int main(int argc, char* argv[])
{
   //test read file
   
   test_lable_stack();
  /* 
   if(argc != 2)
   {
	  perror("two argv needed !\n");
	  exit(-1);
   }

   Page page;

   LineBuf* lb = (LineBuf*)malloc(sizeof(LineBuf));
   lb->next = NULL;

   fill_buf(argv[1], lb);
   
   if(is_discuz(lb) == 1)
   {
	  discuz_fill_the_page(lb, &page);
	  
   }
   else//非discuz网站
   {
	  no_discuz_fill_the_page(lb, &page);
   }

   if(is_discuz(lb) == 1)
   {
	  printf("title:%s\n", page.title);
	  printf("content:%s\n", page.content);
	  printf("author:%s\n", page.author);
	  printf("click num:%s\n", page.click_count);
	  printf("replay num:%s\n", page.replay_count);
	  printf("time:%s\n", page.time);
   }
   else
   {
	  printf("title:%s\n", page.title);
	  printf("content:%s\n", page.content);
   }
  
   //   test_line_buf(lb);
//   free_page(&page);
   
*/
   return 0;
}
