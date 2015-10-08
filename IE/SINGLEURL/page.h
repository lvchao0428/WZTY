#ifndef _PAGE_H_
#define _PAGE_H_

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

#define BUFSIZE 1024

typedef int LableType;
#define TITLELABLE		0
#define AUTHORLABLE		1
#define TIMELABLE		2
#define CLICKNUMLABLE	3
#define REPLAYLABLE		4
#define CONTENTLABLE	5

typedef struct Page
{
   char* title;
   char* author;
   char* time;
   char* click_count;
   char* replay_count;
   char* content;
   int title_filled;
   int author_filled;
   int time_filled;
   int click_filled;
   int replay_filled;
   int content_filled;
}Page, *pPage;

void free_page(Page* page);

//先按行存储文件
typedef struct LineBuf
{
   char* str;
   struct LineBuf* next;
}LineBuf, *pLineBuf;

int fill_buf(char* filename, LineBuf* lb);

void test_fillbuf(LineBuf* lb);

typedef struct buf_queue
{
   char buf[1024];
   struct buf_queue* next;
   struct buf_queue* tail;
}buf_queue, *pBuf_queue;

typedef struct LableElem
{
   char key[30];
   char value[30];
   struct LableElem* next;
   struct LableElem* tail;
}LableElem, *pLableElem;



typedef struct Lable
{
   char name[60];
   struct Lable* next;
   struct Lable* tail;
   LableElem* le;
   char* content;		//如果为嵌套的外层标签，则此内容为空，如果为最内层标签，
   //则填充文字数值
   

}Lable, *pLable;

//存储大于号和小于号的位置，定位内容项里面的子标签
typedef struct LablePosPair
{
   int left;
   int right;
   struct LablePosPair* next;
}LablePosPair, *pLablePosPair;

LableType check_lable(char* line);		//检查此标签的对应内容的类型

int mycatNoN(char* dest, char* from);			//把后面的字符串拼接到前面字符串，忽略换行符

int find_str_times(char* str, char* word);		//寻找后面字符串在前面字符串中出现的次数

int return_son_str_pos(char* father, char* son);	//返回第一次出现son字符串的结束位置

int print_str(char* str, int beg, int end);		//打印beg到end里面的字符串

int mystrstr(char* father, char* son);			//测试前面字符串里面是否包含后面的字符串

int mystrcpy(char* dest, char* from, int begPos, int endPos);	//把from字符串的下表范围里面的字符串拷贝到前面字符串

//处理内容项
void test_lpp(LablePosPair* lpp);		//测试posPair

void dispos_son_lable(char* str, LablePosPair* lpp);


int file_read_full(char** dest, const char* filename);		//把整个文件读取成一个字符串

int Enqueue(buf_queue* bf, char* buf);			//固定块入队操作

int Dequeue(buf_queue* bf, char* buf);			//固定块出队操作

int fill_the_page(LineBuf* pb, Page* page);		//把行结构信息提取出需要的所有需要信息

int fill_buf(char* filename, LineBuf* lb);		//把文件内容按行读入

int read_html(char* url, buf_queue* bq);		//把文件内容按固定大小块读入

int read_queue(buf_queue* bq);					//读取固定块大小的文件内容


int read_title(char* filename, char* buf_title);	//从文件读取文章的标题内容

int read_author(char* filename, char* buf_author);	//从文件读取作者名字

int deal_title(LineBuf** lb, Page* page);			//从行存储结构中读取标题内容

int deal_time(LineBuf** lb, Page* page);			//从行存储结构中读取时间内容

int deal_clickAndreplay(LineBuf** lf, Page* page);	//从行存储结构中读取点击和回复数据

int deal_author(LineBuf** lf, Page* page);			//从行存储结构中读取作者信息

int deal_content(LineBuf** lf, Page* page);			//从行存储结构中读取内容信息

void free_page(Page* page);		//释放页面结构体成员
//test
void test_line_buf(LineBuf* lf);

#endif
