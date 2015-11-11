/*************************************************************************
    > File Name: discuz_extract.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Mon Oct 12 14:28:13 2015
 ************************************************************************/

#include"discuz_extract.h"
#include"lable_deal.h"
#include"mystring.h"


int discuz_fill_the_page(LineBuf* pb, Page* page)
{//提取论坛内容
   
   int has_post = has_postmessage(pb);
   printf("has_post:%d\n", has_post);
   char* line = NULL;
   LineBuf* p = pb->next;
   
   while(p != NULL)
   {
	  int i = 0;
	 
	  if(strlen(p->str) < 3)
	  {
		 p = p->next;
		 continue;
	  }

	  line = p->str;
	  LableType lt = -1;
	  //printf("line:%d ", p->line_no);
	  lt = check_lable(line);
	  switch(lt)
	  {
		 case TITLELABLE:
			//有可能是title项
			if(page->title_filled != 1)
			{//如果标题项还没有被填充过，则把之后内容当做标题处理
			   deal_title(&p, page);
			}
			
			printf("title type ,%s\n", line);
			break;
		 case CONTENTLABLE:
			if(page->content_filled != 1)
			{//如果可能是内容选项，而且还没有被填充过，则当内容项处理时候的内容
			   deal_content(&p, page, has_post);
			}
			printf("content type ,%s\n", line);
			break;
		 case AUTHORLABLE:
			if(page->author_filled != 1)
			{//如果被判定为可能的作者项，则把之后内容当做作者项处理
			   deal_author(&p, page);
			}
			break;
		 case TIMELABLE:
			if(page->time_filled != 1)
			{
			   deal_time(&p, page);
			}
			break;
		 case REPLAYLABLE:
			if(page->replay_filled != 2)
			{
			   deal_clickAndreplay(&p, page);
			}
			break;
		 default:
			break;

	  }
	  p = p->next;
   }
}

//提取时间信息
int deal_time(LineBuf** lf, Page* page)
{
   LineBuf* templf = *lf;
   LineBuf* endlf = templf;
   char* line = endlf->str;
   char tempstr[200] = {0};
  // printf("str: %s\n", endlf->str); 
   //int begPos = 0, endPos = 0;
   //find begPos
   LablePosPair* lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   lpp->next = NULL;
   printf("time:%s\n", endlf->str);
   find_all_greater_lower(line, lpp);
   strcpy(tempstr, line);
/*
   while(line[begPos] != '\0' && line[begPos++] != '>');
   endPos = begPos;
  */ 
  // printf("time begin: %d\n", begPos);
   //find endPos
  
   //while(line[endPos] != '\0' && line[endPos] != '<') endPos++;
   
  // printf("time end: %d\n", endPos);
 
   page->time = (char*)malloc(sizeof(char)*(strlen(line) + 1));

   dispos_son_lable(tempstr, lpp);
   strcpy(page->time, tempstr);
   //mystrcpy(page->time, line, begPos, endPos);
   page->time_filled = 1;
   *lf = templf->next;
   return 1;
}

//提取查看和回复次数
int deal_clickAndreplay(LineBuf** lf, Page* page)
{
   LineBuf* templf = *lf;
   char tempstr[2000];
   tempstr[0] = '\0';
   LineBuf* endlf = templf;
   int click_pos, replay_pos;
   char* line;
   if((mystrstr(endlf->str, "查看") != -1) && (mystrstr(endlf->str, "回复") != -1))
   {  //查看和回复在同一行
	  //两个数值一般都在span标签中间，找到两块span标签即可
	  int check_beg_pos, check_end_pos, replay_beg_pos, replay_end_pos;

	  check_beg_pos = mystrstr(endlf->str, "查看");	//先找到查看的位置，然后往后找span标签的位置
	  check_beg_pos += mystrstr(endlf->str + check_beg_pos, "<span");	//找到后面查看数的span开始标签位置
	  check_end_pos = check_beg_pos + return_son_str_pos(endlf->str + check_beg_pos, "</span>");	//找到查看span结束标签的开始位置
	  
	  replay_beg_pos = mystrstr(endlf->str, "回复");
	  replay_beg_pos += mystrstr(endlf->str + replay_beg_pos, "<span");
	  replay_end_pos = replay_beg_pos + return_son_str_pos(endlf->str + replay_beg_pos, "</span>");


	  char temp_check_str[100] = {0};
	  char temp_replay_str[100] = {0};
	  mystrcpy(temp_check_str, endlf->str, check_beg_pos, check_end_pos);
	  mystrcpy(temp_replay_str, endlf->str, replay_beg_pos, replay_end_pos);
	 
	  printf("checkbegpos:%d, checkendpos:%d\n", check_beg_pos, check_end_pos);
	  printf("replaybegpos:%d, replayendpos:%d\n", replay_beg_pos, replay_end_pos);
	  printf("test click:%s\n", temp_check_str);
	  printf("test replay_str:%s\n", temp_replay_str);
	  printf("double checked\n"); 
	  //提取点击的次数
	  LablePosPair* check_lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
	  check_lpp->next = NULL;
	  find_all_greater_lower(temp_check_str, check_lpp);
	  test_lpp(check_lpp, temp_check_str);
	  dispos_son_lable(temp_check_str, check_lpp);
	  
	  //提取回复的次数
	  LablePosPair* replay_lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
	  replay_lpp->next = NULL;
	  find_all_greater_lower(temp_replay_str, replay_lpp);
	  test_lpp(replay_lpp, temp_replay_str);
	  dispos_son_lable(temp_replay_str, replay_lpp);

	  page->click_count = (char*)malloc(sizeof(char)*(strlen(temp_check_str) + 1));
	  strcpy(page->click_count, temp_check_str);

	  page->replay_count = (char*)malloc(sizeof(char*)*20);
	  strcpy(page->replay_count, temp_replay_str);

	  page->replay_filled = 2;
   }
   else
   //如果是查看和回复在多行的情况下的处理方式
   {
	  if(mystrstr(endlf->str, "查看") != -1)
	  {//处理查看和回复不在同一行的情况
		 int click_beg_pos, click_end_pos;
		 printf("single chakan.................******...........\n");
		 click_beg_pos = mystrstr(endlf->str, "查看");
		 click_beg_pos += mystrstr(endlf->str, "<span");
		 click_end_pos = click_beg_pos + return_son_str_pos(endlf->str, "</span>");

		 char temp_click_str[100] = {0};
		 mystrcpy(temp_click_str, endlf->str, click_beg_pos, click_end_pos);

		 LablePosPair* click_lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
		 click_lpp->next = NULL;
		 find_all_greater_lower(temp_click_str, click_lpp);
		 dispos_son_lable(temp_click_str, click_lpp);

		 page->click_count = (char*)malloc(sizeof(char)*(strlen(temp_click_str) + 1));
		 strcpy(page->click_count, temp_click_str);
		 page->replay_filled = 1;
	  }
	  
	  if((replay_pos = mystrstr(endlf->str, "回复")) != -1)
	  {
		 int replay_beg_pos, replay_end_pos;
		 printf("single huifu**************............*************\n");
		 replay_beg_pos = mystrstr(endlf->str, "回复");
		 replay_beg_pos += mystrstr(endlf->str, "<span");
		 replay_end_pos = replay_beg_pos + return_son_str_pos(endlf->str, "</span>");

		 char temp_replay_str[100] = {0};
		 mystrcpy(temp_replay_str, endlf->str, replay_beg_pos, replay_end_pos);

		 LablePosPair* replay_lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
		 replay_lpp->next = NULL;
		 find_all_greater_lower(temp_replay_str, replay_lpp);
		 dispos_son_lable(temp_replay_str, replay_lpp);

		 page->replay_count = (char*)malloc(sizeof(char)*(strlen(temp_replay_str)+1));
		 strcpy(page->replay_count, temp_replay_str);
		 page->replay_filled = 2;
	  }

   }

   *lf = templf;


}

//提取名字
int deal_author(LineBuf** lf, Page* page)
{
   LineBuf* templf = *lf;
   char* line = templf->str;
   LineBuf* endlf = templf;

   //div标签结尾，所以要找到div包含的所有内容，即为姓名
   //find begPos
   char tempstr[1000] = {0};
   while(mystrstr(endlf->str, "</div>") == -1)
   {
	  strcat(tempstr, endlf->str);
	  endlf = endlf->next;
   }
   
   page->author = (char*)malloc(sizeof(char)*50);
   LablePosPair* lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   lpp->next = NULL;
   find_all_greater_lower(tempstr, lpp);
   dispos_son_lable(tempstr, lpp);
   strcpy(page->author, tempstr);
   *lf = endlf->next;
   //让begPos直接跳过div的开始标签
  /*
   begPos += 2;
   while(line[begPos] != '\0' && line[begPos++] != '>');
   //find endPos
   endPos = begPos;
   while(line[endPos] != '\0' && line[endPos] != '<') endPos++;

   page->author = (char*)malloc(sizeof(endPos-begPos+1));
   mystrcpy(page->author, line, begPos, endPos);
   
   endlf = endlf->next;
   */
   page->author_filled = 1;
   return 1;
}


//提取内容
int deal_content(LineBuf** lf, Page* page, int has_post)
{
   LineBuf* templf = *lf; 
   //假设网页都是合理的网页，则找到table标签的结束标签
   //在这个函数里面吧table标签的头尾连接起来，并且改变buf的指针
   //把table的信息存储在一个字符串里面然后进行查找最内层内容。
   int nlen = 0;
   char tempstr[100000];
   tempstr[0] = '\0';
   LineBuf* endlf = templf;
     //把table闭合标签里面的内容存起来再分析
	  //内容提取的要素是，table标签里面的内容，有嵌套标签包含的都去掉
	  //这里代表discuz的正文抽取，如果是有postmessage就不检查pid，如果没有
	  //则通过以下方案搜索
	  //1.先找到pid和下面几行如果没有正文长度则跳过
	  //2.如果有正文长度，返回起始指针，然后向下找到table标签的结尾处

   //分为postmessage和pid两种
   if(mystrstr(endlf->str, "\"postmessage") != -1 && has_post == 1)
   {
	  while(endlf != NULL && (mystrstr(endlf->str, "</table>") == -1))
	  {
		 strcat(tempstr, endlf->str);
		 endlf = endlf->next;	  
	  }
	  strcat(tempstr, endlf->str);
	  printf("whole str is:\n", tempstr);
	  
	  LablePosPair* lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
	  lpp->next = NULL;
	  find_all_greater_lower(tempstr, lpp);
	  dispos_son_lable(tempstr, lpp);

	  page->content = (char*)malloc(sizeof(char)*(strlen(tempstr) + 1));
	  //mystrcpy(page->content, tempstr, begPos, endPos);
	  strcpy(page->content, tempstr);
	  
	  //把除去标签的部分都赋值给内容项

	  endlf = endlf->next;
	  page->content_filled = 1;
	  *lf = endlf->next;
   }
   else if(mystrstr(endlf->str, "\"pid") != -1 && has_post == -1)
   {
	  //查找下面10行。然后检查正文长度，和标点
	  int count = 10;

	  while(count > 0)
	  {
		 strcat(tempstr, endlf->str);
		 endlf = endlf->next;
		 count--;
	  }
	  int word_len = word_length_get(tempstr);
	  if(word_len > 10)
	  {
		 tempstr[0] = '\0';
		 endlf = templf;
		 while(mystrstr(endlf->str, "</table>") == -1)
		 {
			strcat(tempstr, endlf->str);
			endlf = endlf->next;
		 }
		 strcat(tempstr, endlf->str); 
		 LablePosPair* content_lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
		 content_lpp->next = NULL;
		 find_all_greater_lower(tempstr, content_lpp);
		 dispos_son_lable(tempstr, content_lpp);
		 page->content = (char*)malloc(sizeof(char)*(strlen(tempstr) + 1));
		 strcpy(page->content, tempstr);

		 page->content_filled = 1;
	  }
	  *lf = endlf->next;
   }

   return 1;
}

//处理标题
int deal_title(LineBuf** lf, Page* page)
{
   int i = 0;
   char lable[10];
   int j = 0;
   LineBuf* templf = *lf;
   char* line = templf->str;
   char temptitle[300];
 //  printf("%s\n", line);
   int begPos = 0, endPos = 0;
   strcpy(temptitle, line);
   LablePosPair* lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   lpp->next = NULL;
   find_all_greater_lower(temptitle, lpp);
   dispos_son_lable(temptitle, lpp);
/*
   //find begPos
   while(line[begPos] != '\0' && line[begPos++] != '>');
   //find endPos
   endPos = begPos;
   while(line[endPos] != '\0' && line[endPos] != '<') endPos++;
//   printf("begpos: %d\n", begPos);
//   printf("endpos: %d\n", endPos);
*/
   page->title = (char*)malloc(sizeof(char)*(strlen(temptitle)+1));
//   mystrcpy(page->title, temptitle, begPos, endPos);
   strcpy(page->title, temptitle);

   templf = templf->next;
   page->title_filled = 1;
   return 1;
}

int has_postmessage(LineBuf* lb)
{
   LineBuf* templb = lb->next;
   int has_post = -1;
   
   while(templb)
   {
	  if(mystrstr(templb->str, "<table") != -1)
	  {
		 if(mystrstr(templb->str, "\"postmessage") != -1)
		 {
			has_post = 1;
		 }
	  }
	  templb = templb->next;
   }
   
   return has_post;
}
