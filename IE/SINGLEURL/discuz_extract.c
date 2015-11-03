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
   
   char* line = NULL;
   LineBuf* p = pb->next;
   while(p != NULL)
   {
	  line = p->str;
	  int i = 0;
	  //所有属性都是‘<’打头，所以如果是'.''{'开头的则不是属性项
	  if(line[i] != '<')
	  {
		 p = p->next;
		 continue;
	  }
	  LableType lt;

	  lt = check_lable(line);
	  switch(lt)
	  {
		 case TITLELABLE:
			//有可能是title项
			if(page->title_filled != 1)
			{//如果标题项还没有被填充过，则把之后内容当做标题处理
			   deal_title(&p, page);
			}

		//	printf("title type ,%s\n", line);
			break;
		 case CONTENTLABLE:
			if(page->content_filled != 1)
			{//如果可能是内容选项，而且还没有被填充过，则当内容项处理时候的内容
			   deal_content(&p, page);
			}
			//printf("content type ,%s\n", line);
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
			if(page->replay_filled != 1)
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
   
  // printf("str: %s\n", endlf->str); 
   int begPos = 0, endPos = 0;
   //find begPos
   while(line[begPos] != '\0' && line[begPos++] != '>');
   endPos = begPos;
   
  // printf("time begin: %d\n", begPos);
   //find endPos
   while(line[endPos] != '\0' && line[endPos] != '<') endPos++;
   
  // printf("time end: %d\n", endPos);
   page->time = (char*)malloc(sizeof(char)*(endPos-begPos+1));
   mystrcpy(page->time, line, begPos, endPos);
   page->time_filled = 1;
   templf = templf->next;
   return 1;
}

//提取查看和回复次数
int deal_clickAndreplay(LineBuf** lf, Page* page)
{
   LineBuf* templf = *lf;
   char tempstr[2000];
   tempstr[0] = '\0';
   LineBuf* endlf = templf;
   
   if(mystrstr(endlf->str, "查看") == -1)
   {
	  return 0;
   }
   do{
	  if(mystrstr(endlf->str, "</span>") > 0)
	  {
		 endlf = endlf->next;
		 break;
	  }
	  endlf = endlf->next;
   }while(mystrstr(endlf->str, "</span>") > 0);
   
   //printf("begin non\n");
   do{
	  mycatNoN(tempstr, templf->str);
	  templf = templf->next;
   }while(templf != NULL && templf != endlf);

   
   //printf("begin despace\n");
   //despace_betw_more_less(tempstr);
   //printf("after despace str:%s\n", tempstr);
   //find the first place after "查看" 's '><'
   int clickbegPos = 0, clickendPos = 0;
   int replaybegPos = 0, replayendPos = 0;
   clickbegPos = return_son_str_pos(tempstr, "查看");
   //printf("return son pos:%d\n", clickbegPos);
   //find clickbegPos
   while(tempstr[clickbegPos] != '\0')
   {
	  if(tempstr[clickbegPos] == '>')
	  {
		 if(tempstr[clickbegPos + 1] == '>')
		 {
			clickbegPos++;
		 }
		 else if(tempstr[clickbegPos+1] == ' ' && tempstr[clickbegPos+2] == '<')
		 {
			clickbegPos+=2;
		 }
		 else if(tempstr[clickbegPos+1] != ' ' && tempstr[clickbegPos+2] != '<' ){
			clickbegPos++;
			break;
		 }
	  }
	  clickbegPos++;
   }
 //  printf("begin pos:%d\n", clickbegPos);
   //print_str(tempstr, clickbegPos, clickendPos+5);

   //find clickendPos
   clickendPos = clickbegPos;
   while(tempstr[clickendPos] != '\0')
   {
//  printf("bb pos:%d\n", clickendPos);
	  if(tempstr[clickendPos] == '<')
	  {
		 break;
	  }
	  clickendPos++;
   }
//   printf("clickend pos:%d\n", clickendPos);
   //find replaybegPos
   page->click_count = (char*)malloc(sizeof(char)*20);
   mystrcpy(page->click_count, tempstr, clickbegPos, clickendPos);
   replaybegPos = return_son_str_pos(tempstr, "回复");
   //printf("replaybegPos:%d,  str:%s\n", replaybegPos,tempstr);
   //printf("len:%d\n", strlen(tempstr));
   while(tempstr[replaybegPos] != '\0')
   {
	  if(tempstr[replaybegPos] == '>')
	  {
		 if(tempstr[replaybegPos + 1] == '>')
		 {
			replaybegPos++;
		 }
		 else if(tempstr[replaybegPos+1] == '<')
		 {
			replaybegPos++;
		 }
		 else if(tempstr[replaybegPos+1] == ' ' && tempstr[replaybegPos+2] == '<')
		 {
			replaybegPos+=2;
		 }
		 else if(tempstr[replaybegPos+1] != ' '){
			replaybegPos++;
			break;
		 }
	  }
	  replaybegPos++;
   }
 //  printf("replay beg:%d\n", replaybegPos);
   //find replay end 
   replayendPos = replaybegPos;
   while(tempstr[replayendPos] != '\0')
   {
	  if(tempstr[replayendPos] == '<')
	  {
		 break;
	  }
	  else
	  {
		 replayendPos++;
	  }
   }
 //  printf("replay end pos:%d\n", replayendPos);
   page->replay_count = (char*)malloc(sizeof(char)*10);
   mystrcpy(page->replay_count, tempstr, replaybegPos, replayendPos);
   page->replay_filled = 1;
   return 1;
}

//提取名字
int deal_author(LineBuf** lf, Page* page)
{
   LineBuf* templf = *lf;
   char* line = templf->str;
   LineBuf* endlf = templf;

   int begPos = 0, endPos = 0;
   //find begPos
   begPos = return_son_str_pos(line, "authi");
   //让begPos直接跳过div的开始标签
   begPos += 2;
   while(line[begPos] != '\0' && line[begPos++] != '>');
   //find endPos
   endPos = begPos;
   while(line[endPos] != '\0' && line[endPos] != '<') endPos++;

   page->author = (char*)malloc(sizeof(endPos-begPos+1));
   mystrcpy(page->author, line, begPos, endPos);
   
   endlf = endlf->next;
   page->author_filled = 1;
   return 1;
}


//提取内容
int deal_content(LineBuf** lf, Page* page )
{
   LineBuf* templf = *lf; 
   //假设网页都是合理的网页，则找到table标签的结束标签
   //在这个函数里面吧table标签的头尾连接起来，并且改变buf的指针
   //把table的信息存储在一个字符串里面然后进行查找最内层内容。
   int nlen = 0;
   char tempstr[100000];
   tempstr[0] = '\0';
   LineBuf* endlf = templf;
   
   while(endlf != NULL && (mystrstr(endlf->str, "</table>") == -1))
   {
	  nlen += strlen(endlf->str);
	  mycatNoN(tempstr, endlf->str);
	  endlf = endlf->next;	  
   }

   nlen += strlen(endlf->str);
   mycatNoN(tempstr, endlf->str);
   //如果table标签在一行里面出现了超过2则为段内容或无内容标签，根据书写习惯判定为非内容字段
   if(find_str_times(tempstr, "table") > 2)
   {
	  return 0;
   }

 //  printf("tempcontentline: %s\n", tempstr);

   //把table闭合标签里面的内容存起来再分析
    //内容提取的要素是，table标签里面的内容，有嵌套标签包含的都去掉
   int begPos = 0, endPos = nlen+1;
	
	//find begin table end
   while(tempstr[begPos] != '\0' && tempstr[begPos++] != '>'); 
   //find end table begin
   while(endPos > 0 && tempstr[endPos] != '<') endPos--;
   //dispose son lable

   page->content = (char*)malloc(sizeof(char)*(endPos-begPos + 1));
   mystrcpy(page->content, tempstr, begPos, endPos);

   //把嵌套子标签去掉
   LablePosPair* greaterLpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   LablePosPair* wordLpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   printf("begin check out content lable:\n\n\n\n\n\n\n"); 
   //printf("content raw:\n%s\n", page->content);
   find_all_greater_lower(page->content, greaterLpp);
   out_content_scope(page->content, wordLpp); 
   
  // test_lpp(greaterLpp);

  // test_lpp(wordLpp);

   if(is_word_longer_than_lable(page->content) == 1)
   {

   }
   int comma_num = find_comma_num_out(page->content);

   printf("comma_num:%d\n", comma_num);
   //把除去标签的部分都赋值给内容项
   dispos_son_lable(page->content, greaterLpp);   
   //
   //copy_scope_str_to_str(page->content, lpp);

   endlf = endlf->next;
   page->content_filled = 1;

   return 1;
}

//处理标题
int deal_title(LineBuf** lf, Page* page)
{
   int i = 0;
   char lable[10];
   int j = 0;
   LineBuf* templf = *lf;
   char* line = (*lf)->str;
   char temptitle[300];
 //  printf("%s\n", line);
   int begPos = 0, endPos = 0;

   //find begPos
   while(line[begPos] != '\0' && line[begPos++] != '>');
   //find endPos
   endPos = begPos;
   while(line[endPos] != '\0' && line[endPos] != '<') endPos++;
//   printf("begpos: %d\n", begPos);
//   printf("endpos: %d\n", endPos);

   page->title = (char*)malloc(sizeof(char)*(endPos-begPos+1));
   mystrcpy(page->title, line, begPos, endPos);
   
   templf = templf->next;
   page->title_filled = 1;
   return 1;
}

