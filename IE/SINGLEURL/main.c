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

void test_annotate(LineBuf* lb)
{
   LineBuf* templb = lb->next;
   lb->next = NULL;
   while(templb)
   {
	  printf("%s", templb->str);
	  templb = templb->next;
   }
}

void test_illegal_Buf(LineBuf* lb)
{
   LineBuf* q = lb->next;
   while(q)
   {
	  printf("lineno:%d\t, str:%s\n",q->line_no, q->str);
	  q = q->next;
   }
}

void free_dest_lb(LineBuf* dest)
{
   LineBuf* p = dest->next;
   if(!p)
   {
	  return;
   }
   while(p)
   {
	  LineBuf* q = p;
	  p = p->next;
	  free(q);
   }
}
/*
void test_lb_comma(LineBuf* lb)
{
   LineBuf* p = lb->next;
   while(p)
   {
	  LablePosPair* lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
	  lpp->next = NULL;
	  int wordlen = word_length_get(p->str);
	  int lablelen  = lable_length_get(p->str);
	  int tempstr[100000] = {0 };
	  //printf("line_no:%d, \tstr:%s\n", p->line_no, p->str);
	  int commanum = find_comma_num_out(p->str);
	  //printf("wordlen:%d\t, lablelen:%d\n", wordlen, lablelen);
	  
	  //sprintf(tempstr, "line_no:%d, commanum:%d, str:%s\n", p->line_no, commanum, p->str);
	  p->str = (char*)realloc(p->str, strlen(tempstr)+1);
	  strcpy(p->str, tempstr);
//	  out_content_scope(p->str, lpp);
	  //printf("commanum:%d\n", commanum);
	  p = p->next;
   }
}
*/

void test_lbp(LineBuf* lbp[HTMLCOUNT])
{
   int i;
   for(i = 1; i <= 819; ++i)
   {
	  LineBuf* temp;
	  temp = lbp[i]->next;
	  while(temp)
	  {
		 printf("%s\n", temp->str);
		 temp = temp->next;
	  }
	  
   }
}

int main(int argc, char* argv[])
{
   //test read file
   
//   test_lable_stack();
  /*
   if(argc != 2)
   {
	  perror("two argv needed !\n");
	  exit(-1);
   }
*/
  /* 
   LineBuf* lbp[HTMLCOUNT];
   Page* page[HTMLCOUNT];
   int i = 0;
   for(i = 0; i < HTMLCOUNT; ++i)
   {
	  lbp[i] = (LineBuf*)malloc(sizeof(LineBuf));
	  lbp[i]->next = NULL;
	  page[i] = (Page*)malloc(sizeof(Page));
   }

   file_content_batching_deal(lbp);	//读取所有819个网页
   
//   int null_count =    page_null_count(lbp);
 //  printf("null count:%d\n", null_count);
   

   int correct_arr[HTMLCOUNT] = {0};
   
   //page_dis_count(lbp, page, correct_arr); 
   
  
   int num = 0;
   //抽样测试代码:
   while(num != -1)
   {
	  Page page;
	  printf("enter num:");
	  scanf("%d", &num);
	  if(is_discuz(lbp[num]))
	  {
		 discuz_fill_the_page
	  }
//	  printf("is dis:%d\n", is_discuz(lbp[num]));
	  if(strlen(page[num]->content) < 10)
	  {
		 printf("title:%s\n", page[num]->title);
		 printf("content extract failed\n");
	  }
	  else
	  {
		 printf("title:%s\n", page[num]->title);
		 printf("content:%s\n", page[num]->content);
	  }

   }
   
   //test_lbp(lbp);
   */
   //
   //单独测试代码
   Page page;

   LineBuf* lb = (LineBuf*)malloc(sizeof(LineBuf));
   lb->next = NULL;

   fill_buf(argv[1], lb, 0);
   
   LineBuf* dest = (LineBuf*)malloc(sizeof(LineBuf));
   dest->next = NULL; 
   
  // illegal_part_deal(lb);
   //count illegal lable
   //test_illegal_lable(lb);
   //file_buf_write(lb, "test_file.html");
   // discuz_fill_the_page(lb, &page);
   int is_discuz_flag = is_discuz(lb);
   if(is_discuz_flag)
   {
	  
	  printf("discuz dealing.................\n");
	 
   }
   else
   {

	  printf("nodiscuz dealing.................\n");

	 
   }
  

   if(is_discuz_flag)
   {

	  discuz_fill_the_page(lb, &page);
	  printf("title:%s\n", page.title);
	  printf("time:%s\n", page.time);
	  printf("clickcount:%s\n", page.click_count);
	  printf("replaycount:%s\n", page.replay_count);
	  printf("content:%s\n", page.content);
   }
   else
   {
	  
	  test_illegal_lable(lb);
//	  annotation_part_handle(lb);
//	  printf("wipe anno end\n");
	  illegal_part_deal(lb);
	  printf("end once illgel wipe\n");
	  test_illegal_lable(lb);
	  illegal_part_deal(lb);
	  printf("end twice illgel wipe\n");
	  test_illegal_lable(lb);
	  
	  file_buf_write(lb, "test.html");
	 // illegal_part_deal(lb);
	 // test_illegal_lable(lb);
   //illegal_part_deal(lb);
	 
	  test_illegal_lable(lb);
	  no_discuz_fill_the_page(lb, &page);
	  printf("title:%s\n", page.title);
	  printf("content:%s\n", page.content);
   }
   return 0;
}
