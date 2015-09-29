#ifndef _LABLE_H_
#define _LABLE_H_

#include<stdio.h>

typedef int labletype;


#define BEGINLABLE	0
#define ENDLABLE	1

typedef struct LableElem
{
   char key[30];
   char value[30];
   struct LableElem* next;
   
}Lable, *pLable;

typedef struct Lable
{
   char name[20];
   struct Lable* next;
   LableElem* le;		//本标签的属性序列
   LableElem* leTail;
   labletype lt;
   int beginPos;
   int endPos;	//
   //如果为最内层标签，则下一个字符则为content内容
   int content_beginPos;
   int content_endPos;		//最内层标签包含的开始和结束位置
}Lable,*pLable;


int addElem(Lable* l, LableElem* le);


int readElem(Lable* l);


int fill_lable(Lable* l);


#endif
