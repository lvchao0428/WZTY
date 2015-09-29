#ifndef _PAGE_H_
#define _PAGE_H_

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct Page
{
   char* title;
   char* author;
   char* time;
   char* click_count;
   char* replay_count;
   char* content;
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

LableType check_lable(char* line);

int mycatNoN(char* dest, char* from);

int find_str_times(char* str, char* word);

int return_son_str_pos(char* father, char* son);

int print_str(char* str, int beg, int end);

int mystrstr(char* father, char* son);

int mystrcpy(char* dest, char* from, int begPos, int endPos);

void testtwostart(LineBuf** lb);

int Enqueue(buf_queue* bf, char* buf);

int Dequeue(buf_queue* bf, char* buf);

int fill_the_page(LineBuf* pb, Page* page);
   
int read_html(char* url, buf_queue* bq);

int read_queue(buf_queue* bq);

//int read_title(buf_queue* bq, char* buf_title);

int read_title(char* filename, char* buf_title);

int read_author(char* filename, char* buf_author);

int deal_title(LineBuf** lb, Page* page);

int deal_time(LineBuf** lb, Page* page);

int deal_clickAndreplay(LineBuf** lf, Page* page);

int deal_author(LineBuf** lf, Page* page);

int desl_content(LineBuf** lf, Page* page);



#endif
