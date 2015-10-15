/*************************************************************************
    > File Name: nodiscuz_extract.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Mon Oct 12 14:22:04 2015
 ************************************************************************/

#include"nodiscuz_extract.h"
#include"mystring.h"
#include"lable_deal.h"


int no_discuz_fill_the_page(LineBuf* pb, Page* page)
{
   char* line = NULL;

   LineBuf* beglb = pb->next;

   while(beglb != NULL)
   {
	  line = beglb->str;
	  
	  LableType lt;

	  lt = check_normal_lable(line);

	  switch(lt)
	  {
		 case TITLELABLE:
			if(page->title_filled != 1)
			{
			   deal_title(&beglb, page);
			}

			break;
		 case CONTENTLABLE:
			//检查所有div table标签，符合标准的一直找到标签为止
			if(page->content_filled != 1)
			{
			   deal_normal_content(&beglb, page);			
			}

			break;
		 default:
			break;
	  }
	  beglb = beglb->next;
   }
}

void deal_normal_content(LineBuf** lb, Page* page)
{
   LineBuf* beglf, *endlf;
   beglf = endlf = *lb;

   int nlen = 0;
   char tempstr[100000];
   int line_num = 0;

   int comma_num = 0;
   
   while(endlf != NULL && line_num < 5)
   {
	  strcat(tempstr, endlf->str);
	  endlf = endlf->next;
	  line_num++;	  
   }
   //如果符合条件，则一直搜索到标签的结尾，然后抽取所有的内容
   if(find_comma_num_out(tempstr) > 5 && is_word_longer_than_lable(tempstr) == 1)
   {
	  analysis_content_lable(lb, tempstr);
	  //tempstr 存储处理好的内容
	  page->content_filled = 1;
   }
   else
   {
	  *lb = beglf->next;
   }

}

LableType check_normal_lable(char* line)
{//检查普通网页的标签类型
   
   LableType lt;

   if(mystrstr(line, "<title>") == 1)
   {
	  lt = TITLELABLE;
   }

   if(mystrstr(line, "<div") == 1 || mystrstr(line, "<table") == 1)
   {
	  lt = CONTENTLABLE;
   }
   
   return lt;
}


