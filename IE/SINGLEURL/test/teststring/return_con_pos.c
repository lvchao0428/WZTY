/*************************************************************************
    > File Name: return_con_pos.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Fri Sep 25 17:17:32 2015
 ************************************************************************/

#include<stdio.h>

int return_son_str_pos(char* father, char* son)
{//返回第一次出现son字符串的结束位置
   int i = 0;
   while(father[i] != '\0')
   {
	  int j = 0;
	  if(father[i] == son[j])
	  {
		 while(son[j] != '\0')
		 {
			if(father[i+j] == son[j])
			{
			   j++;
			}
			else
			{
			   break;
			}
		 }
		 if(son[j] == '\0')
		 {
			return i+j;
		 }
	  }
	  i++;
   }
   if(father[i] == '\0')
   {
	  return -1;
   }
}

int main(int argc, char* argv[])
{
   printf("pos:%d\n", return_son_str_pos(argv[1], argv[2]));

   return 0;
}
