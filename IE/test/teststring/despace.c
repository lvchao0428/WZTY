/*************************************************************************
    > File Name: despace.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Fri Sep 25 15:44:49 2015
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int despace(char* str)
{
   int i = 0;
   int j = 0;
   while(str[i] != '\0')
   {
	  if(str[i+1] == ' ' || str[i+1] == '　')
	  {
		 i++;
		 while(str[i] == ' ' || str[i] == '　')
		 {
			i++;
		 }
	  }
	  else
	  {
		 str[j] = str[i];
		 i++;
		 j++;
	  }
   }
   str[j] = '\0';
}

int main()
{
   char a[100] = "china japan　American";
   despace(a);
   printf("%s\n", a);

   return 0;
}
