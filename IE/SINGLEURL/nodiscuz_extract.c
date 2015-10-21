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
	 // printf("%s\n", line);
	  //处理注释的区域
	 // deal_anno(&beglb);
	 // deal_script(&beglb);
	  switch(lt)
	  {
		 case TITLELABLE:
			if(page->title_filled != 1)
			{
			   printf("title checked\n");
			   deal_title(&beglb, page);
			}

			break;
		 case CONTENTLABLE:
			//检查所有div table标签，符合标准的一直找到标签为止
			if(page->content_filled != 1)
			{
			   printf("conetne checked\n");
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

   LablePosPair* lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   lpp->next = NULL;
   out_content_scope(tempstr, lpp);
   //如果符合条件，则一直搜索到标签的结尾，然后抽取所有的内容
   comma_num = find_comma_num_out(tempstr, lpp);
   if(comma_num > 5 )//&& is_word_longer_than_lable(tempstr) == 1)
   {
	 // analysis_content_lable(lb, tempstr);
	  printf("tempstr:%s\n", tempstr);
	  printf("comma_num:%d\n", comma_num); 
	  //printf("-------------------------------------------------------\n");
	  //printf("wordlen:%d\n", word_length_get(tempstr));
	  //printf("lablelen:%d\n", lable_length_get(tempstr));
	  printf("begin extract||||||||||||||||||||||||||||||||||||||\n");
	 // extract_content_with_punct(&endlf, tempstr);
	 // content_until_lable_end_extract(endlf, tempstr);
	 // LablePosPair* finalLpp = (LablePosPair*)malloc(sizeof(LablePosPair));
	 // finalLpp->next = NULL;
	  
	//  find_all_greater_lower(tempstr, finalLpp);
	 // dispos_son_lable(tempstr, finalLpp);
	 // printf("final string:%s\n", tempstr);
	  //tempstr 存储处理好的内容
	/*
	  page->content = (char*)malloc(sizeof(char)*(strlen(tempstr) + 1));
	  strcpy(page->content, tempstr);
	  */
	  page->content_filled = 1;
   }
   else if(comma_num == 0)
   {
	  *lb = endlf;
   }
   else
   {
	  *lb = beglf->next;
   }

}

LableType check_normal_lable(LineBuf** lb, char* line)
{//检查普通网页的标签类型
   
   LableType lt;

   if(mystrstr(line, "<title>") == 1)
   {
	  lt = TITLELABLE;
   }

   if(mystrstr(line, "<div") == 1 || mystrstr(line, "<table") == 1)
   {
	  //如果div标签开始，还要本行内容部分是否有文字如果有文字则看下面五行如果有标点则是内容可能性大
	  int wordLen = word_length_get(line);
	 // int lableLen = lable_length_get(line);
	  if(wordLen <= 5)
	  {
		 lt = NONLABLE;
	  }
	  else
	  {
		 LineBuf* templf = *lb;
		 int count = 0;
		 int comma_num = 0;
		 while(count < 5)
		 {
			comma_num += find_comma_num_out()
			count++;
		 }
	  }
	  lt = CONTENTLABLE;
   }
   
   return lt;
}


