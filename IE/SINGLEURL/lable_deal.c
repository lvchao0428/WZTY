/*************************************************************************
    > File Name: lable_deal.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Mon Oct 12 14:25:23 2015
 ************************************************************************/

#include"lable_deal.h"
#include"mystring.h"

LablePosPair* out_content_scope(char* line, LablePosPair* lpp)
{//把字符串中内容项的范围存储到lpp里面，也即除去标签之外的内容部分的下标范围
   find_all_greater_lower(line, lpp);		//先把lpp里面存上大于号和小于号的位置，
   //小于号和大于号之间即为内容范围
   LablePosPair* p = lpp->next;
   LablePosPair* q;
   while(p->next != NULL && p->next->next != NULL) 
   {
	  p->left = p->right+1;
	  p->right = p->next->left-1;
	  p = p->next;

   }
   p->left = p->right+1;
   p->right = p->next->left-1;
   q = p->next;
   p->next = NULL;
   free(q);
   
   //有些大于号和小于号之间没有内容，把这些无用的范围消除掉
   p = lpp;
   while(p->next != NULL && p->next->next != NULL)
   {
	  if(p->next->left >= p->next->right)
	  {
//		 printf("dealing...left:%d\tright%d\n", p->next->left, p->next->right);
		 q = p->next;
		 p->next = p->next->next;
		 free(q);
	  }
	  else
	  {
		 p = p->next;
	  }
   }
   
   if(p->next != NULL)
   {
	  if(p->next->left >= p->next->right)
	  {
		 q = p->next;
		 p->next = NULL;
		 free(q);
	  }
   }
   return lpp;
}

LableType check_lable(char* line)
{//检查此行标签的可能内容，并返回可能的标签
   int i = 0;
   LableType lt = -1;
   char lable[60];
   int j = 0;
   //printf("char 0 : %c\n", line[0]);
   while(line[i] != '>' && line[i] != ' ')
   {
	  lable[j++] = line[i++];
   }
   //printf("read lable end\n");
   lable[j] = '\0';

//   printf("test check lable: %s\n", lable);
//   printf("line:%s\n", line);
   if(strcmp(lable, "<title") == 0)
   {
	  lt = TITLELABLE;
//	  printf("title checked\n");
   }
   //内容标签里面有可能包含的postmessage
   else if((strcmp(lable, "<div") == 0) && mystrstr(line, "authi"))
   {
	  lt = AUTHORLABLE;

//	  printf("author checked\n");
   }
   else if(mystrstr(line, "authorposton") == 1)
   {
	  lt = TIMELABLE;
//	  printf("time checked\n");
   }
   
   else if(mystrstr(line, "查看") && mystrstr(line, "回复"))
   {
	  lt = REPLAYLABLE;
//	  printf("replay checked\n");
   }
   else if(((strcmp(lable, "<div") == 0) || (strcmp(lable, "<table") == 0)) && 
		 ((mystrstr(line, "postmessage") == 1 || (mystrstr(line, "pid") == 1))))
   {//此个网页内容部分包含在talbe中，以后可以在这里扩展内容页可能存在的标签
	  lt = CONTENTLABLE;
//	  printf("content checked\n");
   }

   return lt;
}


void find_all_greater_lower(char* line, LablePosPair* lpp)
{//找到所有的大于号和小于号的位置
   int i = 0;
   //找到所有'<'的位置
   LablePosPair* p = lpp;
   while(line[i] != '\0')
   {
	  if(line[i] == '<' && ((line[i+1] >= 'a' && line[i+1] <= 'z') || line[i+1] == '/'))
	  {
		 LablePosPair* q = (LablePosPair*)malloc(sizeof(LablePosPair));
		 q->left = i;
		 q->next = NULL;
		 p->next = q;
		 p = p->next;
	  }
	  i++;
   }

   p = lpp->next;
   i = 0;
   int j = 0;
   while(line[i] != '\0' && p != NULL)
   {
	  j = p->left;
	  //find right
	  while(line[j] != '>')j++;
	  p->right = j;
	  p = p->next;
	  i++;
   }
}


void dispos_son_lable(char* str, LablePosPair* lpp)
{
   LablePosPair* p = lpp->next;
   int i = 0, j = 0;
   while(str[i] != '\0')
   {
	  if(p != NULL)
	  {
		 i = p->right+1;
		 p = p->next;
	  }
	  else
	  {
		 while(str[i] != '\0')
		 {
			str[j++] = str[i++];
		 }
	  }
	  while(str[i] != '\0' && i < p->left) 
	  {
		 str[j++] = str[i++]; 
	  }
	  
	  
   }
   str[j] = '\0';
}

void copy_scope_str_to_str(char* str, LablePosPair* lpp)
{
   LablePosPair* p = lpp->next;
   int i = 0, j = 0;
   while(str[i] != '\0' && p != NULL)
   {
	  i = p->left;
	  while(str[i] != '\0' && i <= p->right)
	  {
		 str[j++] = str[i++];
	  }
	  p = p->next;
   }
   str[j] = '\0';
}

LableElem* push_lable(LableElem* le, char* val)
{
   LableElem* p = (LableElem*)malloc(sizeof(LableElem));
   strcpy(p->val, val);
   p->next = NULL;

   if(le->next == NULL)
   {
	  le->next = p;
   }
   else
   {
	  p->next = le->next;
	  le->next = p;
   }

   return le;
}

char* top_lable(LableElem* le)
{
   if(le->next == NULL)
   {
	  return '\0';
   }
   else
   {
	  return le->next->val;
   }
}

LableElem* pop_lable(LableElem* le)
{
   if(le->next == NULL)
   {
	  return le;
   }
   else
   {
	  LableElem* p = le->next;
	  le->next = le->next->next;
	  free(p);
   }
   return le;
}


