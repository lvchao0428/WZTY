/*************************************************************************
  > File Name: page.c
  > Author: lvchao0428
  > Mail: 410148119@qq.com 
  > Created Time: Tue Sep 22 10:13:23 2015
 ************************************************************************/

#include"page.h"


int is_null(LineBuf* pb)		//判断网页是否为空
{
   LineBuf* p = pb->next;
   //判断是否行数过于少，如果少于五行则都认为为空
   int line_count = 0;
   while(p)
   {
	  line_count++;
	  p = p->next;
   }

   if(line_count < 6)
   {
	  return 1;
   }
   else
   {
	  return 0;
   }
}

int is_discuz(LineBuf* pb)
{
   LineBuf* beglb,* endlb;
   beglb = endlb = pb->next;
   char temphead[100000];
   temphead[0] = '\0'; 
   while(beglb && beglb->next != NULL && mystrstr(beglb->str, "</head>") < 0)
   {
	  strcat(temphead, beglb->str);
	  printf("beg:str""%s\n", beglb->str);
	  beglb = beglb->next;
   }
   strcat(temphead, beglb->str);
   printf("head:%s fileno:%d\n", temphead, beglb->file_no);
   if(!beglb)
   {
	  return 0;
   }
   if((mystrstr(temphead, "Discuz") != -1) || (mystrstr(temphead, "discuz") != -1))
   {
	  return 1;
   }
   else
   {
	  return 0;
   }
}

int page_null_count(LineBuf* lbp[HTMLCOUNT])
{
   int i = 1;
   int null_counter = 0;
   while(i <= 819)
   {
	  if(is_null(lbp[i]) == 1)
	  {
		 null_counter++;
	  }
	  i++;
   }

   return null_counter;
}

	  

void page_dis_count(LineBuf* lbp[HTMLCOUNT], Page* page[HTMLCOUNT], int* correct_arr)		//计数网页里面含有多少个discuz型网页
{
   int i;
   int dis_count = 0;
   int total_count = 819;
   double dis_ratio = 0;
   int corr_j = 0;
   for(i = 1; i <= 819; ++i)
   {
	  if(is_null(lbp[i]) == 1)
	  {
		 total_count--;
		 
	  }
	  else
	  {
		 printf("corrnum:%d\n", corr_j);
		 //correct_arr[corr_j++] = i;	//累计正确的网页编号
		 printf("count dis:%d\n", i);
		 if(is_discuz(lbp[i]))
		 {
			dis_count++;
			//extract dis_zhengwen
			discuz_fill_the_page(lbp[i], page[i]);
		 }
		 else
		 {	
			//extract no_dis_zhengwen
			no_discuz_fill_the_page(lbp[i], page[i]);
		 }

	  }

	  
   }
   printf("html:%d extract complete\n", i);
   dis_ratio = (double)dis_count/total_count;
   printf("dis_count is :%d,total_count:%d, dis_ratio is:%lf\n", dis_count, total_count, dis_ratio);
}

