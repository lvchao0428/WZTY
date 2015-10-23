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


void test_lpp(LablePosPair* lpp)
{
   LablePosPair* p = lpp->next;
   while(p)
   {
	  printf("left:%d\tright:%d\n", p->left, p->right);
	  p = p->next;
   }
}

/*
int main(int argc, char* argv[])
{
   if(argc < 3)
   {
	  perror("need more args");
	  exit(-1);
   }

   printf("pos:%d\n", mystrstr(argv[1],argv[2]));

   return 0;
}
*/
