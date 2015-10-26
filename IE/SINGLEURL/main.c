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

void test_lable_fun(LineBuf* lb)
{

   LineBuf* templb = lb->next;
  
   while(templb)
   {
	  if(strlen(templb->str) < 5)
	  {
		 templb = templb->next;
		 continue;
	  }
	  LablePosPair* lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
	  lpp->next = NULL;
	  printf("lineno:%d\tstrlen:%d\n", templb->line_no, strlen(templb->str));
	  //find_all_greater_lower(templb->str, lpp);
	  out_content_scope(templb->str, lpp);
	  test_lpp(lpp);
	  templb = templb->next;
   }

   /*
   LablePosPair* wordLpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   wordLpp->next = NULL;
   out_content_scope(lb->str, wordLpp);
   LablePosPair* q = wordLpp->next;
   //test greater & lower is embrace all 

   

   LablePosPair* p = lpp->next;
   while(p)
   {
	  printf("lable left:%d %c\tright:%d %c\n", p->left, (lb->str[p->left]), p->right, (lb->str[p->right]));
	  p = p->next;
   }

   while(q)
   {
	  printf("word left:%d \tright:%d\n", q->left, q->right);
	  q = q->next;
   }
*/

}

void test_annotate(LineBuf* lb)
{
   LineBuf* templb = lb->next;
   while(templb)
   {
	  printf("%s", templb->str);
	  templb = templb->next;
   }
}

int main(int argc, char* argv[])
{
   //test read file
   
//   test_lable_stack();
   if(argc != 2)
   {
	  perror("two argv needed !\n");
	  exit(-1);
   }

   Page page;

   LineBuf* lb = (LineBuf*)malloc(sizeof(LineBuf));
   lb->next = NULL;

   fill_buf(argv[1], lb);
   
   illegal_part_deal(lb);
  // test_lable_fun(lb);
   //test_annotate(lb); 
   file_buf_write(lb, "test_file.html");
   /*   if(is_discuz(lb) == 1)
   {
	  discuz_fill_the_page(lb, &page);
	  
   }
   else//非discuz网站
   {
   }
*/
	  no_discuz_fill_the_page(lb, &page);
  /*
   if(is_discuz(lb) == 1)
   {
	  printf("title:%s\n", page.title);
	  printf("content:%s\n", page.content);
	  printf("author:%s\n", page.author);
	  printf("click num:%s\n", page.click_count);
	  printf("replay num:%s\n", page.replay_count);
	  printf("time:%s\n", page.time);
   }
   */
 //  else
 //  {
	  printf("title:%s\n", page.title);
	  printf("content:%s\n", page.content);
//   }
  
   //   test_line_buf(lb);
//   free_page(&page);
   
   return 0;
}
