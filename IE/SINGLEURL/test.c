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
 
void test_lpp(LablePosPair* lpp, char* str)
{
   LablePosPair* p = lpp->next;
   while(p)
   {
	  printf("left:%d , right:%d, type:%d,", p->left, p->right, p->lt);
//	  printf(":%s\n", )
	  print_str(str, p->left, p->right);
	  p = p->next;
   }
}
void test_scope_lpp(LablePosPair* beglpp, LablePosPair* endlpp, char* str)
{
   while(beglpp != endlpp)
   {
	  printf("left:%d , right:%d, type:%d,", beglpp->left, beglpp->right, beglpp->lt);
//	  printf(":%s\n", )
	  print_str(str, beglpp->left, beglpp->right);
	  beglpp = beglpp->next;
   }
}

int test_illegal_lable(LineBuf* lb)
{
   int annobegNum = 0, annoendNum = 0, scriptbegNum = 0, scriptendNum = 0,\
					stylebegNum = 0, styleendNum = 0;
   
   count_illegal_lable(lb,&annobegNum, &annoendNum,\
		 &scriptbegNum, &scriptendNum,\
		 &stylebegNum, &styleendNum);

   printf("&annobegNum:%d, &annoendNum:%d,\
		 &scriptbegNum:%d, &scriptendNum:%d,\
		 &stylebegNum:%d, &styleendNum:%d\n",\
		 annobegNum, annoendNum,\
		 scriptbegNum, scriptendNum,\
		 stylebegNum, styleendNum);

}


