/*************************************************************************
    > File Name: test.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Mon Oct 12 14:25:43 2015
 ************************************************************************/

#include"def.h"
#include"mystring.h"
#include"test.h"
#include"lable_deal.h"

void test_fillbuf(LineBuf* lb)
{
   LineBuf* p = lb->next;

   while(p)
   {
	  printf("%s\n", lb->str);
	  p = p->next;
   }
}

