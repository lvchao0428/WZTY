/*************************************************************************
    > File Name: normalstrstr.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Thu Sep 24 14:26:10 2015
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<time.h>

#define MAX_STRING_NUM 1024*1024


//比较几个字符串查找算法的优劣
//全遍历算法，kmp算法，bm算法

//返回是否包含字符串, father 包含 son
int mystrstr(char* father, char* son)
{
   int i = 0;
   while(father[i] != '\0')
   {
	  int j = 0;

	  if(father[i] == son[j])
	  {
		 while(son[j] != '\0')
		 {
			if(father[i+ j] != son[j])
			{
			   break;
			}
			else
			{
			   j++;
			}
		 }
		 if(son[j] == '\0')
			return 1;
	  }
	  i++;
   }
   if(father[i] == '\0')
	  return 0;
}

int create_str(char*** string)
{
   *string = (char**)malloc(sizeof(char*)*MAX_STRING_NUM);
   int i;
   srand(time(NULL));
/*
   FILE* fp;
  // fp = fopen("string", "w");
   //if(fp == NULL)
  // {
	  printf("open file wrong");
	  return -1;
   }
*/
   for(i = 0; i < MAX_STRING_NUM; ++i)
   {
	  (*string)[i] = (char*)malloc(sizeof(char)*20);
	  int j; 
	  for(j = 0; j < 19; ++j)
	  {
		 (*string)[i][j] = rand()%26 + 'a'; 
	  }
//	  fprintf(fp, "%s\n", (*string)[i]);
   }

}

int print_str(char** string)
{
   int i;
   for(i =0; i < MAX_STRING_NUM; ++i)
   {
	  printf("%s\n", string[i]);
   }
}

int find_all_str(char** string, char* s)
{
   int i;
   int num = 0;

   for(i = 0; i < MAX_STRING_NUM; ++i)
   {
	  if(mystrstr(string[i], s) == 1)
	  {
		 ++num;
	  }
   }

   return num;
}

int main(int argc, char* argv[])
{
   if(argc < 2)
   {
	  perror("not enough argv");
	  exit(-1);
   }
   char** string;
   create_str(&string);
   //print_str(string); 
   /*
   int rtn = mystrstr(argv[1], argv[2]);

   
   if(rtn == 0)
   {
	  printf("not\n");
   }
   else
   {
	  printf("yes\n");
   }
*/
   int beginTime, endTime;
   beginTime = clock();
   int num = find_all_str(string, argv[1]);
   endTime = clock();
   printf("total time is:%lf, spoted %d times\n", (double)(endTime-beginTime)/1000, num);
   return 0;
}
