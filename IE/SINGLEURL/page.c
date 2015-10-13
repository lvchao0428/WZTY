/*************************************************************************
  > File Name: page.c
  > Author: lvchao0428
  > Mail: 410148119@qq.com 
  > Created Time: Tue Sep 22 10:13:23 2015
 ************************************************************************/

#include"page.h"


int is_discuz(LineBuf* pb)
{
   LineBuf* beglb,* endlb;
   beglb = endlb = pb->next;
   char temphead[100000];
   
   while(beglb->next != NULL && mystrstr(beglb->str, "</head>") != 1)
   {
	  strcat(temphead, beglb->str);
	  beglb = beglb->next;
   }
//   printf("head:%s\n", temphead);
   if((mystrstr(temphead, "Discuz") == 1) || (mystrstr(temphead, "discuz") == 1))
   {
	  return 1;
   }
   else
   {
	  return 0;
   }
}



