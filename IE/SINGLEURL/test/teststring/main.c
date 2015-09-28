/*************************************************************************
    > File Name: main.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Thu Sep 24 10:34:10 2015
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int mystrcat(char* dest, char* from)
{
   int i = 0;
   int j = 0;
   while(dest[i] != '\0') i++;
   while(from[j] != '\0')
   {
	  if(from[j] == '\n')
	  {
		 j++;
		 continue;
	  }
	  dest[i++] = from[j++];
   }
   dest[++i] = '\0';
}

int find_str_times(char* str, char* word)
{
   int i = 0;
   int times = 0;
   while(str[i] != '\0' && i < strlen(str))
   {
	  int j = 0;
	  if(str[i] == word[j])
	  {
		 while(word[j] != '\0')
		 {
			if(str[i+j] != word[j])
			{
			   break;
			}
			else
			{
			   j++;
			}
		 }
		 if(word[j] == '\0')
		 {
			i+=j;
			printf("%d:%c\n", i, str[i]);
			times++;
		 }
	  }
		 i++;
   }

   return times;
}


int main(int argc, char* argv[])
{
   

//   mystrcat(dest, c);
  // printf("dest:%s\n", dest);
   printf("%d times\n", find_str_times(argv[1], argv[2]));

   return 0;
}
