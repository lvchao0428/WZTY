/*************************************************************************
    > File Name: main.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Sep 22 10:29:35 2015
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
   int fd, read_n;
   char buf[1024];
   if(argc != 2)
   {
	  printf("two few args!\n");
   }



   fd = open(argv[1], O_RDONLY);
   if(fd == -1)
   {
	  perror("fail:");
	  exit(-1);
   }



   printf("fd:%d\n", fd);

   while(memset(buf, 0, 1024), read_n = read(fd, buf, 1024))
   {
	  printf("read_n:%d\n", read_n);
	  printf("%s\n", buf);
   }
   close(fd);


   return 0;
}
