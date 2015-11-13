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
   int max_content_len = 0;
   LineBuf* beglb = pb->next;
   LineBuf* content_buf = (LineBuf*)malloc(sizeof(LineBuf));
   content_buf->next = NULL;
   while(beglb != NULL)
   {
	  line = beglb->str;
	  
	  LableType lt;
	  
	  //printf("checked %dth line\n%s\n", beglb->line_no, beglb->str);
	  lt = check_normal_lable(beglb, line);
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
			   printf("conetne checked!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			  // deal_normal_content(&beglb, page, content_buf);
			   printf("over extract contennt..........................\n\n\n");
			   //test wordlen
			   //int wordlen = word_length_get(beglg->str);
			break;
		 default:
			break;
	  }
	  /*
	  if(page->content_filled == 1)
	  {
		 break;
	  }
	  */
	  beglb = beglb->next;
   }

   //find longest content
	 LineBuf* tempcontent = content_buf->next;
   LineBuf* longestContent;
   while(tempcontent)
   {
	  
	  int templen = strlen(tempcontent->str);
	  
	 // printf("str:%s\n", tempcontent->str);
	 // printf("length:%d\n", strlen(tempcontent->str));
	  if(max_content_len < templen)
	  {

		 max_content_len = templen;
		 longestContent = tempcontent;
	  }
	  tempcontent = tempcontent->next;
   }

   if(max_content_len > 0)
   {
	  page->content = (char*)realloc(page->content, sizeof(char)*(strlen(longestContent->str)+1));
	  strcpy(page->content, longestContent->str);
   }
   else
   {
	  if(page->content == NULL)
	  {
		 page->content = (char*)malloc(sizeof(char)*20);
		 strcpy(page->content, "NULL CONTENT");
	  }
	  else if(strlen(page->content) <= 20)
	  {
		 page->content = (char*)realloc(page->content, sizeof(char)*20);
		 strcpy(page->content, "NULL CONTENT");
	  }
   }
   if(page->content == NULL)
   {
	  page->content = (char*)malloc(sizeof(char)*20);
	  strcpy(page->content, "NULL CONTENT");
   }
}

void deal_normal_content(LineBuf** lb, Page* page, LineBuf* content_buf)
{
   LineBuf* beglf, *endlf;
   beglf = endlf = *lb;

   LineBuf* tempcontent = content_buf;
   while(tempcontent->next)
   {//find content_buf end
	  tempcontent = tempcontent->next;
   }
   int nlen = 0;
   char tempstr[100000] = {0};
   int line_num = 0;
   
   int comma_num = 0;
   

   strcpy(tempstr, endlf->str);
   endlf = endlf->next;
   while(endlf && line_num < 10)
   {
	  strcat(tempstr, endlf->str);
	  endlf = endlf->next;
	  line_num++;	  
   }
   
   LablePosPair* lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   lpp->next = NULL;
   out_content_scope(tempstr, lpp);
   //copy_scope_str_to_str(tempstr, lpp);
   if(comma_num > 1)
   {
	 // printf("test comma str:%d\n", tempstr);
   }
   //如果符合条件，则一直搜索到标签的结尾，然后抽取所有的内容
   comma_num = find_comma_num_out(tempstr);
  // printf("commaNum:%dstr:%s\n", comma_num, tempstr);
   if(comma_num > 5 )//&& is_word_longer_than_lable(tempstr) == 1)
   {
	  //printf("tempstr:%s\n", tempstr);
	  extract_content_with_punct(&endlf, tempstr);
	  
	  //tempstr 存储处理好的内容
	  page->content = (char*)malloc(sizeof(char)*(strlen(tempstr) + 1));
	  strcpy(page->content, tempstr);
	  
	  LineBuf* tempbuf = (LineBuf*)malloc(sizeof(LineBuf));
	  tempbuf->next = NULL;
	  tempbuf->str = (char*)malloc(sizeof(char)*(strlen(tempstr) + 1));
	  strcpy(tempbuf->str, tempstr);
	  
	  tempcontent->next = tempbuf;
	  tempcontent = tempcontent->next;
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

LableType check_normal_lable(LineBuf* lb, char* line)
{//检查普通网页的标签类型
   
   LableType lt;

   if(mystrstr(line, "<title>") != -1)
   {
	  lt = TITLELABLE;
	  return TITLELABLE;
   }

   int wordlen = word_length_get(lb->str);
   int comma = find_comma_num_out(lb->str);
  // printf("wordlen:%d\t,commanum:%d\t line:%s\n", wordlen, comma, line);
//   if(//mystrstr(line, "<div") != -1 || mystrstr(line, "<table") != -1)
   if(wordlen > 5)
   {
	  //如果div标签开始，还要本行内容部分是否有文字如果有文字则看下面五行如果有标点则是内容可能性大
	 // printf("lb->lieno%d\t%s\n", lb->line_no, line);
	  //int wordLen = word_length_get(line);
	//  printf("wordlen:%d\n", wordlen);
	  // int lableLen = lable_length_get(line);
	  LineBuf* templf = lb;
	  int count = 0;
	  int comma_num = 0;
	  char tempstr[100000] = {0};
	  while(templf && count < 10)
	  {
		 strcat(tempstr, templf->str);
		 count++;
		 templf = templf->next;
	  }
	  comma_num = find_comma_num_out(tempstr);
	  wordlen = word_length_get(tempstr);
	  //	printf("comma_num:%d\tlineno:%d, str:%s\n", comma_num,templf->line_no, tempstr); 
		// printf("lineno:%d\tcontent lable possible..................................\n", lb->line_no);
	  if(comma_num <  5)
	  {
		 lt = NONLABLE;
	  }
	  else
	  {
		 //if(templf)
			//printf("lineno:%d\t%s\n", lb->line_no, tempstr);
		 lt = CONTENTLABLE;
	  }
	  // printf("lineno:%d\tcomma_num:%d\n\n\n", lb->line_no, comma_num);
   }
   else
   {
	  lt = NONLABLE;
   }
   
   return lt;
}


