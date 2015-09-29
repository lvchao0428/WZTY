/*************************************************************************
  > File Name: page.c
  > Author: lvchao0428
  > Mail: 410148119@qq.com 
  > Created Time: Tue Sep 22 10:13:23 2015
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include"page.h"
#include<errno.h>

#define BUFSIZE 1024

typedef int LableType;
#define TITLELABLE		0
#define AUTHORLABLE		1
#define TIMELABLE		2
#define CLICKNUMLABLE	3
#define REPLAYLABLE		4
#define CONTENTLABLE	5


int fill_buf(char* filename, LineBuf* lb)
{
   FILE* fp;
   char* line = NULL;
   size_t len = 0;
   ssize_t read_n;

   fp = fopen(filename, "r");
   if(fp == NULL)
   {
	  perror("read file error.");
	  return -1;
   }
   LineBuf* p = lb->next;
   int no =0;
   //getline len的参数为当前line的最大长度
   while((read_n = getline(&line, &len, fp)) != -1)
   {
	  no++;

	  // printf("lineno:%d, len:%d, %s\n",no, len, line);
	  if(line[0] == '\n')
		 continue;
	  LineBuf* q = (LineBuf*)malloc(sizeof(LineBuf));
	  //	  printf("len:%d, %s\n", strlen(line), line);
	  q->str = (char*)malloc(sizeof(char)*(strlen(line)+1));

	  q->next = NULL;
	  strcpy(q->str, line);

	  if(lb->next == NULL)
	  {
		 lb->next = q;
		 p = q;
	  }
	  else
	  {
		 p->next = q;
		 p = p->next;
	  }

   }

   free(line);
}

void test_fillbuf(LineBuf* lb)
{
   LineBuf* p = lb->next;
   int no = 0;
   while(p != NULL)
   {
	  no++;
	  printf("len: %d, %s\n",strlen(p->str), p->str );
	  p = p->next;
   }
}

void testtwostar(LineBuf** lb)
{
   LineBuf* ll = (*lb)->next;
   while(ll != NULL)
   {
	  printf("lien:%s\n", ll->str);
	  ll = ll->next;
   }
}

int mystrstr(char* father, char* son)
{
   int i = 0;
   while(father[i] != '\0')
   {
	  int j = 0;
	  if(father[i] == son[j])
	  {
		 while(son[j] != '\0')
		 {
			if(father[i+j] != son[j])
			{
			   break;
			}
			else
			{
			   j++;
			}
		 }
		 if(son[j] == '\0')
		 {
			return 1;
		 }
	  }
	  i++;
   }
   if(father[i] == '\0')
   {
	  return 0;
   }
}

int file_read_full(char** dest, const char* filename)
{
   FILE* fp;
   struct stat file_stats;
   int nItems, nBytesRead;

   *dest = NULL;
   if((fp = fopen(filename, "r")) == NULL)
   {
	  fprintf(stderr, "failed to open %s - %s\n", filename, strerror(errno));
	  return(-1);
   }
   fstat(fileno(fp), &file_stats);

   if((*dest = (char*)malloc(file_stats.st_size+1)) == NULL)
   {
	  fclose(fp);
	  fprintf(stderr, "failed to allocate memory for reading file%s\n", filename);
	  return(-2);
   }
   nBytesRead = 0;
   while((nItems = fread(*dest + nBytesRead, 1, BUFSIZ,fp)) > 0)
   {
	  nBytesRead += nItems;
   }
   fclose(fp);
   *(*dest + nBytesRead) = '\0';

   return (nBytesRead);
}

int fill_the_page(LineBuf* pb, Page* page)
{
   int title_len;
   int author_len;
   int time_len;
   int click_count_len;
   int repaly_count_len;
   int content_len;

   char* line = NULL;
   LineBuf* p = pb->next;
   int num = 0;
   while(p != NULL)
   {
	  line = p->str;
	  int i = 0;
	  char temp[50];
	  //所有属性都是‘<’打头，所以如果是'.''{'开头的则不是属性项
	  if(line[i] != '<')
	  {
		 p = p->next;
		 continue;
	  }
	  num++;
	  LableType lt;
	  //title，如果开头是title则是标题项，继续向后面找到结束标签即可
	  switch(line[1])
	  {
		 case 't':
			//有可能是title项
			//check lable
			lt = check_lable(line);
			if(lt == TITLELABLE)
			{
			   deal_title(&p, page);
			   //  printf("title type ,   %s", line);
			}
			if(lt == CONTENTLABLE)
			{
			   deal_content(&p, page);
			   //	   printf("content type ,   %s", line);
			}
			break;
		 case 'd':
			//有可能是div项。如果是div项则有可能是作者项，要查看属性里面的class是否是authi
			lt = check_lable(line);
			if(lt == AUTHORLABLE)
			{
			   deal_author(&p, page);
			}
			break;
		 case 'e':
			//有可能是em标签，如果是em标签则有可能是发表时间项,如果后面的id属性包含authorposton则是发表时间
			lt = check_lable(line);
			if(lt == TIMELABLE)
			{
			   deal_time(&p, page);

			}
			break;
		 case 's':
			//有可能是span标签，如果是span标签则检查被此span标签包含的文字，如果是的查看则后面
			//是查看次数，点击次数继续搜寻即可
			lt = check_lable(line);
			if(lt == REPLAYLABLE)
			{
			   deal_clickAndreplay(&p, page);
			}
			break;
		 default:
			break;
	  }
	  p = p->next;

   }

   return 1;
}

LableType check_lable(char* line)
{
   int i = 0;
   LableType lt = -1;
   char lable[60];
   int j = 0;
   //printf("char 0 : %c\n", line[0]);
   while(line[i] != '>' && line[i] != ' ')
   {
	  lable[j++] = line[i++];
   }
   //printf("read lable end\n");
   lable[j] = '\0';

   printf("test check lable: %s\n", lable);

   if(strcmp(lable, "<title") == 0)
   {
	  lt = TITLELABLE;
   }
   else if(strcmp(lable, "<div") == 0)
   {
	  lt = AUTHORLABLE;
   }
   else if(strcmp(lable, "<em") == 0)
   {
	  lt = TIMELABLE;
   }
   else if(strcmp(lable, "<span") == 0)
   {
	  lt = REPLAYLABLE;
   }
   //此个网页内容部分包含在talbe中，以后可以在这里扩展内容页可能存在的标签
   else if(strcmp(lable, "<table") == 0)
   {
	  lt = CONTENTLABLE;
   }

   return lt;
}

int mystrcpy(char* dest, char* from, int begPos, int endPos)
{
   int i = begPos, j = 0;
   while(from[i] != '\0' && i != endPos)
   {
	  dest[j++] = from[i++];
   }
   dest[j] = '\0';
}

int mycatNoN(char* dest, char* from)
{
   int i = 0;
   while(dest[i] != '\0') i++;
   int j =0;
   while(from[j] != '\0')
   {
	  if(from[j] == '\n' || from[j] == '\r') 
	  {
		 j++;
		 continue;
	  }
	  dest[i++] = from[j++];
   }
   dest[i] = '\0';
}

int find_str_times(char* str, char* word)
{
   int i = 0;
   int times = 0;
   while(str[i] != '\0')
   {//不包含重叠情况，也即，abababa，aba，应return 2；
	  int j = 0;
	  if(str[i] == word[j])
	  {
		 while(word[j] != '\0')
		 {
			if(str[i+j] != word[j])
			{
			   break;
			}
			else
			{
			   j++;
			}
		 }
		 if(word[j] == '\0')
		 {
			i+=j;
			times ++;
		 }
	  }
		 i++;
   }

   return times;
}

//去掉> <之间的空格
int despace_betw_more_less(char* str)
{
   int i = 0;
   int j = 0;
   while(str[i] != '\0')
   {
	  if(str[i] == '>')
	  {
		 str[j] = str[i];
		 if(str[i+1] == ' ')
		 {
			i++;
			while(str[i] == ' ')
			{
			  i++; 
			  if(str[i] == '<')
			  {
				 break;
			  }
			}
		 }
	  }
	  else
	  {
		 str[j] = str[i];
		 i++;
		 j++;
	  }
   }
   str[j] = '\0';
}

int return_son_str_pos(char* father, char* son)
{//返回第一次出现son字符串的结束位置
   int i = 0;
   while(father[i] != '\0')
   {
	  int j = 0;
	  if(father[i] == son[j])
	  {
		 while(son[j] != '\0')
		 {
			if(father[i+j] == son[j])
			{
			   j++;
			}
			else
			{
			   break;
			}
		 }
		 if(son[j] == '\0')
		 {
			return i + j;
		 }
	  }
	  i++;
   }
   if(father[i] == '\0')
   {
	  return -1;
   }
}

int print_str(char* str, int beg, int end)
{
   int i = beg;
   while(beg != end)
   {
	 // printf("%c", str[beg]);
	  beg++;
   }
   printf("\n");
   return 1;
}

//提取时间信息
int deal_time(LineBuf** lf, Page* page)
{
   LineBuf* templf = *lf;
   char tempstr[2000];
   tempstr[0] = '\0';
   LineBuf* endlf = templf;

   if(mystrstr(endlf->str, "authorposton") != 1)
   {
	  return 0;
   }
   printf("str: %s\n", endlf->str); 
   int begPos = 0, endPos = 0;
   //find begPos
   while(tempstr[begPos] != '\0')
   {
	  if(tempstr[begPos] == '>')
	  {
		 break;
	  }
	  begPos++;
   }
   endPos = begPos;
   printf("begpos:%d\n", begPos);
   while(tempstr[endPos] != '\0')
   {
	  if(tempstr[endPos] == '<')
	  {
		 break;
	  }
	  endPos++;
   }
   printf("endpos:%d\n", endPos);
   page->time = (char*)malloc(sizeof(char)*100);
   mystrcpy(page->time, tempstr, begPos, endPos);

}


//提取查看和回复次数
int deal_clickAndreplay(LineBuf** lf, Page* page)
{
   LineBuf* templf = *lf;
   char tempstr[2000];
   tempstr[0] = '\0';
   LineBuf* endlf = templf;
   
   if(mystrstr(endlf->str, "查看") != 1)
   {
	  return 0;
   }
  // printf("after check chakan %s\n", endlf->str);
   //printf("begin </span>\n");
   do{
	  if(mystrstr(endlf->str, "</span>") == 1)
	  {
		 endlf = endlf->next;
		 break;
	  }
	  endlf = endlf->next;
   }while(mystrstr(endlf->str, "</span>") != 1);
   
   //printf("begin non\n");
   do{
	  mycatNoN(tempstr, templf->str);
	  templf = templf->next;
   }while(templf != NULL && templf != endlf);

   
   //printf("begin despace\n");
   //despace_betw_more_less(tempstr);
   printf("after despace str:%s\n", tempstr);
   //find the first place after "查看" 's '><'
   int clickbegPos = 0, clickendPos = 0;
   int replaybegPos = 0, replayendPos = 0;
   clickbegPos = return_son_str_pos(tempstr, "查看");
   printf("return son pos:%d\n", clickbegPos);
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
   printf("begin pos:%d\n", clickbegPos);
   //print_str(tempstr, clickbegPos, clickendPos+5);

   //find clickendPos
   clickendPos = clickbegPos;
   while(tempstr[clickendPos] != '\0')
   {
	  printf("bb pos:%d\n", clickendPos);
	  if(tempstr[clickendPos] == '<')
	  {
		 break;
	  }
	  clickendPos++;
   }
   printf("clickend pos:%d\n", clickendPos);
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
   printf("replay beg:%d\n", replaybegPos);
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
   printf("replay end pos:%d\n", replayendPos);
   page->replay_count = (char*)malloc(sizeof(char)*10);
   mystrcpy(page->replay_count, tempstr, replaybegPos, replayendPos);

   return 1;
}


//提取名字
int deal_author(LineBuf** lf, Page* page)
{
   LineBuf* templf = *lf;
   char* line = templf->str;
   //同样查询div标签里面的class值，如果包含authi，则把整个div的包含部分double取
   //出来，如果在查询一次authi出现的次数，如果只出现一次，则为用户名字段
   char tempstr[2000];
   tempstr[0] = '\0';
   //div标签不会换行显示，也即class一定在div的头标签里面
   //如果头标签包含authi，就继续找到</div>出现的位置，并把全部的标签内容包含
   //到一起，搜寻authi出现的次数
   LineBuf* endlf = templf;
   if(mystrstr(endlf->str, "authi") != 1){
	  return 0;
   }

   while(mystrstr(endlf->str, "</div>") != 1)
   {
	  endlf = endlf->next;
   }

   do
   {
   	  mycatNoN(tempstr, templf->str);
   	  templf = templf->next;
   }while(templf != NULL && templf != endlf);
   
   if(find_str_times(tempstr, "authi") != 1)
   {
	  return 0;
   }
   int endPos = strlen(tempstr), begPos = 0;
   //find end pos
   while(endPos--)
   {
	  if(tempstr[endPos] == '<' && tempstr[endPos-1] != '>')
	  {
		 break;
	  }
   }

   //find beg pos
   while(begPos != endPos)
   {
	  if(tempstr[begPos] == '>' && tempstr[begPos + 1] != '<')
	  {
		 begPos++;
		 break;
	  }

	  begPos++;
   }

   page->author = (char*)malloc(sizeof(endPos-begPos+1));
   mystrcpy(page->author, tempstr, begPos, endPos);
   lf = &endlf;
   return 1;
}

//提取内容
int deal_content(LineBuf** lf, Page* page )
{
   LineBuf* templf = *lf; 
   char* line = templf->str;
   //假设网页都是合理的网页，则找到table标签的结束标签
   //在这个函数里面吧table标签的头尾连接起来，并且改变buf的指针
   //把table的信息存储在一个字符串里面然后进行查找最内层内容。
   int nlen = 0;
   char tempstr[10000] = "";
   tempstr[0] = '\0';
   LineBuf* endlf = templf;
    
   do
   {
	  nlen += strlen(endlf->str);

	  endlf = endlf->next;	  
	  if(mystrstr(endlf->str, "</table>") == 1)
	  {
		// printf("fined line:%s\n", endlf->str);
	  }
   }while(endlf != NULL && mystrstr(endlf->str, "</table>") != 1);

   //printf("nlen:%d\n", nlen);
   


   //把table闭合标签里面的内容存起来再分析
   //char* str_wholeTableContent = (char*)malloc(sizeof(char)*(nlen+1))
   do
   {
	  mycatNoN(tempstr, templf->str);
	  //strcat(tempstr, templf->str);
	  templf = templf->next;
   }while(templf != NULL && templf != endlf);
   strcat(tempstr, templf->str);
  
   //如果里面没有标记位就不是内容项
   if(mystrstr(tempstr, "postmessage") != 1)
   {
	  return 0;
   }

   int endPos, begPos = 0;
   //找到内容的结束位置
   endPos = strlen(tempstr);
   
   while(endPos--)
   {
	  if(tempstr[endPos] == '<' && tempstr[endPos-1] != '>')
	  {
		 break;
	  }
   }
   
   //找到开始内容的位置
   while(begPos != endPos)
   {
	  if(tempstr[begPos] == '>' && tempstr[begPos+1] != '<')
	  {
		 break;
	  }
	  begPos++;
   }
   //printf("begpos:%d, endPos:%d\n", begPos, endPos);
   begPos++;

   //printf("tempstr:%s\n", tempstr);
   page->content = (char*)malloc(sizeof(char)*(2048 + 1));
   mystrcpy(page->content, tempstr, begPos, endPos);
   //printf("cpy end\n"); 
   lf = &endlf;
   return 1;
}



//处理标题
int deal_title(LineBuf** lf, Page* page)
{
   int i = 0;
   char lable[10];
   int j = 0;
   char* line = (*lf)->str;
   if(line[0] != '<')
   {
	  return 0;
   }
   int title_len = 0;
   char temptitle[100];
   while(line[i] != '\0')
   {
	  if(i < 7)
	  {
		 lable[i] = line[i];
	  }
	  if(i == 7)
	  {
		 lable[i] = '\0';
		 //		 printf("lable:%s\n", lable);
		 if(strcmp(lable, "<title>") != 0)
		 {
			return 0;
		 }
	  }

	  if(i >= 7)
	  {
		 if(line[i] != '<')
			temptitle[j++] = line[i];
		 else
		 {
			temptitle[j] = '\0';
			page->title = (char*)malloc(strlen(temptitle) + 1);
			strcpy(page->title, temptitle);
			return strlen(temptitle);
		 }
	  }
	  i++;
   }
}

int Enqueue(buf_queue* bq, char* buf)
{
   buf_queue* p = (buf_queue*)malloc(sizeof(buf_queue));
   memcpy(p->buf, buf, 1024);
   p->next = NULL;

   if(bq->next == NULL)
   {
	  bq->next = p;
	  bq->tail = p;
   }
   else
   {
	  bq->tail->next = p;
	  bq->tail = p;
   }

   return 1;
}

int Dequeue(buf_queue* bq, char* buf)
{
   if(bq->next == NULL)
   {
	  memset(buf, 0, 1024);
	  return 0;
   }
   else
   {
	  buf_queue* q = bq->next;
	  memcpy(buf, q->buf, 1024);
	  bq->next = bq->next->next;
	  return strlen(buf);
   }
}

int read_html(char* url, buf_queue* bq)
{
   int fd, read_n;
   char buf[BUFSIZE];

   fd = open(url, O_RDONLY);
   if(fd == -1)
   {
	  perror("fail:");
	  return 0;
   }

   while(memset(buf, 0, 1024), read_n = read(fd, buf, 1024))
   {
	  Enqueue(bq, buf);
   }

   close(fd);
}

int read_queue(buf_queue* bq)
{
   buf_queue* p;

   if(bq->next == NULL)
   {
	  perror("null queue");
	  return 0;
   }

   p = bq->next;
   while(p != NULL)
   {
	  printf("%s\n", p->buf);
	  p = p->next;
   }

   return 1;
}

/*
   int read_title(buf_queue* bq, char* buf_title)
   {
   if(bq->next == NULL)
   {
   perror("null buf queue");
   return 0;
   }

   buf_queue* p = bq->next;

   while(p != NULL)
   {
   char temp[10];
   int i = 0;
   if(bq->buf[0] != '<' || bq->buf[1] != 't')
   {
   continue;
   }

   while(bq->buf[i] != '\0')
   {

   if(i < 8)
   {
   temp[i++] = bq->buf[i];
   }
   else if(i == 8)
   {
   temp[i] = '\0';
   i++;
   }
   else
   {
   if(strcmp(temp, "<title>") == 0)
   {
   if(bq->buf[i] != '<')
   {
   buf_title[i++] = bq->buf[i];
   }
   else
   {
   buf_title[i++] = '\0';
   break;
   }
   }
   else
   {
   continue;
   }
   }

   }

   }
   return strlen(buf_title);
   }
   */

int read_title(char* filename, char* buf_title)
{
   FILE* fp;
   char* line = NULL;
   size_t len = 0;
   ssize_t read;

   fp = fopen(filename, "r");
   if(fp == NULL)
   {
	  perror("FILE read error\n");
	  exit(EXIT_FAILURE);
   }
   //*buf_title = '\0';
   int line_no = 0;
   while((read = getline(&line, &len, fp)) != -1)
   {
	  int i = 0;
	  line_no++;
	  if(line_no > 10)
	  {
		 break;
	  }

	  char temp[9];
	  int isFind = 0;

	  // printf("line %d:%s\n", line_no, line);
	  if(line[1] != 't')
	  {
		 continue;
	  }

	  int j =0;
	  while(line[i] != '\0')
	  {
		 if(i < 7)
		 {
			temp[i] = line[i];
		 }
		 else if(i == 7)
		 {
			temp[i] = '\0';
			buf_title[j++] = line[i];
			if(strcmp(temp, "<title>") != 0)
			{
			   break;
			}
		 }
		 else if(i > 7)
		 {
			if(line[i] != '<')
			{
			   buf_title[j++] = line[i];
			}
			else
			{
			   buf_title[j] = '\0';
			   isFind = 1;
			   break;
			}
		 }
		 i++;
	  }

	  if(isFind == 1)
	  {
		 break;
	  }

   }

   free(line);

   return strlen(buf_title);
}
//
//<div class="authi">

int read_author(char* filename, char* buf_author)
{
   char* line;
   size_t len;
   ssize_t read_n;
   FILE* fp;


   while((read_n = getline(&line, &len, fp)) != -1)
   {
	  if(line[0] != '<')
	  {
		 continue;
	  }
	  int i = 0;
	  while(line[i] != '\0')
	  {

	  }

   }
}

void free_page(Page* page)
{
   free(page->title);
   free(page->author);
   free(page->time);
   free(page->content);
}
