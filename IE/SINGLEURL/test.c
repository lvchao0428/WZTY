/*************************************************************************
    > File Name: test.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Mon Oct 12 14:25:43 2015
 ************************************************************************/

#include<stdio.h>


void test_lable(char* line, LablePosPair* lpp)
{
   int i = 0;
   LablePosPair* p = lpp->next;
   while(p != NULL)
   {
	  i = p->left;
	  while(i < p->right)
	  {
		 printf("%c", line[i]);
		 i++;
	  }
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

