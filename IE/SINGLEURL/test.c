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
	  printf("left:%d\t\tright:%d\n", p->left, p->right);
	  p = p->next;
   }
}
/*
const char* mystrstri(const char* str, const char* subStr)
{
   int len = strlen(subStr);
   if(len == 0)
   {
	  return NULL;
   }

   while(*str)
   {
	  if(strncasecmp(str, subStr, len) == 0)
	  {
		 return str;
	  }
	  ++str;
   }
   return NULL;
}

			   print_str(str, )
int main(int argc, char* argv[])
{
   if(argc < 3)
   {
	  perror("need more args");
	  exit(-1);
   }

   char* p = mystrstri(argv[1], argv[2]);
   printf("p-1:%c, p:%c\n", *(p-1), *p);


   return 0;
}i
*/
