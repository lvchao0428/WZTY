#ifndef __DEF_H_
#define __DEF_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>



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

//先按行存储文件
typedef struct LineBuf
{
   char* str;
   struct LineBuf* next;

   //存储每行逗号的数量
   int comma_num;
   int line_num;
}LineBuf, *pLineBuf;

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


#endif
