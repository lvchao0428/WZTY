/*************************************************************************
    > File Name: artical.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Mon Nov 16 14:41:58 2015
 ************************************************************************/

#include<stdio.h>
#include"artical.h"



int artical_extract(const char* html, size_t len, const char* url, Page *res)
{
   LineBuf* lb = (LineBuf*)malloc(sizeof(LineBuf));
   memset(lb, 0, sizeof(*lb));
   whole_str_to_linebuf(html, len, lb);
   int is_discuz_flag = is_discuz(lb);
   if(is_discuz_flag)
   {

//	  printf("discuz dealing.................\n");

   }
   else
   {

//	  printf("nodiscuz dealing.................\n");


   }


   if(is_discuz_flag)
   {
	  //test_illegal_lable(lb);
	  //	  annotation_part_handle(lb);
	  //	  printf("wipe anno end\n");
	  illegal_part_deal(lb);
	  res->ct = DISCUZTYPE;
//	  file_buf_write(lb, "test.html");
	  discuz_fill_the_page(lb, res);
	  //printf("title:%s\n", page.title);
	  //printf("author:%s\n", page.author);
	  //printf("time:%s\n", page.time);
	  //printf("clickcount:%s\n", page.click_count);
	  //printf("replaycount:%s\n", page.replay_count);
	  //printf("content:%s\n", page.content);
   }
   else
   {

	  //test_illegal_lable(lb);
	  //	  annotation_part_handle(lb);
	  //	  printf("wipe anno end\n");
	  illegal_part_deal(lb);
	  res->ct = NORMALTYPE;
	 // printf("end once illgel wipe\n");
	 // test_illegal_lable(lb);

	  // file_buf_write(lb, "test.html");
	  // illegal_part_deal(lb);
	  // printf("end twice illgel wipe\n");
	  // test_illegal_lable(lb);

	  // illegal_part_deal(lb);
	  // test_illegal_lable(lb);
	  //illegal_part_deal(lb);
	  no_discuz_fill_the_page(lb, res);

   }
   //释放lienbuf
   free_linebuf(lb); 
   
}
