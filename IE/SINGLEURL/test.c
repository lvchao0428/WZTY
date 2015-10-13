/*************************************************************************
    > File Name: test.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Mon Oct 12 14:25:43 2015
 ************************************************************************/

#include"def.h"
#include"mystring.h"
#include"test.h"


void test_fillbuf(LineBuf* lb)
{
   LineBuf* p = lb->next;

   while(p)
   {
	  printf("%s\n", lb->str);
	  p = p->next;
   }
}

void test_lable(char* line, LablePosPair* lpp)
{//不能对此直接测试
   int i = 0;
   LablePosPair* p = lpp->next;
   while(p != NULL)
   {
	  printf("%c%c", line[p->left], line[p->right-1]);
	  
	  
	  p = p->next;

   }
}


void test_lpp(LablePosPair* lpp)
{
   LablePosPair* p = lpp->next;
   while(p != NULL)
   {
	  printf("left: %d, right: %d\n", p->left, p->right);
	  p = p->next;
   }
}
/*
int main(int argc, char* argv[])
{
   int c = find_str_with_scope(argv[1], argv[2], 3, 10);
   
   printf("comma_num:%d\n", c);

   return 0;
}
*/
