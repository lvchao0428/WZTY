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
#include<math.h>


#define BUFSIZE 1024

typedef int LableType;
#define TITLELABLE		0
#define AUTHORLABLE		1
#define TIMELABLE		2
#define CLICKNUMLABLE	3
#define REPLAYLABLE		4
#define CONTENTLABLE	5
#define BEGINLABLE		6
#define ENDLABLE		7
#define NONLABLE		-1

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
   int file_no;
   int line_no;
   char* str;
   struct LineBuf* next;
   struct LineBuf* before;  
}LineBuf, *pLineBuf;

typedef struct buf_queue
{
   char buf[1024];
   struct buf_queue* next;
   struct buf_queue* tail;
}buf_queue, *pBuf_queue;

typedef struct LableElem
{
   LableType lt;		//存储是开始标签还是结束标签
   char val[30];
   struct LableElem* next;
}LableElem, *pLableElem;


//存储大于号和小于号的位置，定位内容项里面的子标签
typedef struct LablePosPair
{
   int left;
   int right;
   struct LablePosPair* next;
}LablePosPair, *pLablePosPair;


#endif
