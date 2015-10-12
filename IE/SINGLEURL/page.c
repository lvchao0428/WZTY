/*************************************************************************
  > File Name: page.c
  > Author: lvchao0428
  > Mail: 410148119@qq.com 
  > Created Time: Tue Sep 22 10:13:23 2015
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include"page.h"
#include<errno.h>




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
   printf("head:%s\n", temphead);
   if((mystrstr(temphead, "Discuz") == 1) || (mystrstr(temphead, "discuz") == 1))
   {
	  return 1;
   }
   else
   {
	  return 0;
   }
}



int Enqueue(buf_queue* bq, char* buf)
{
   buf_queue* p = (buf_queue*)malloc(sizeof(buf_queue));
   memcpy(p->buf, buf, 1024);
   p->next = NULL;

   if(bq->next == NULL)
   {
	  bq->next = p;
	  bq->tail = p;
   }
   else
   {
	  bq->tail->next = p;
	  bq->tail = p;
   }

   return 1;
}

int Dequeue(buf_queue* bq, char* buf)
{
   if(bq->next == NULL)
   {
	  memset(buf, 0, 1024);
	  return 0;
   }
   else
   {
	  buf_queue* q = bq->next;
	  memcpy(buf, q->buf, 1024);
	  bq->next = bq->next->next;
	  return strlen(buf);
   }
}

int read_html(char* url, buf_queue* bq)
{
   int fd, read_n;
   char buf[BUFSIZE];

   fd = open(url, O_RDONLY);
   if(fd == -1)
   {
	  perror("fail:");
	  return 0;
   }

   while(memset(buf, 0, 1024), read_n = read(fd, buf, 1024))
   {
	  Enqueue(bq, buf);
   }

   close(fd);
}

int read_queue(buf_queue* bq)
{
   buf_queue* p;

   if(bq->next == NULL)
   {
	  perror("null queue");
	  return 0;
   }

   p = bq->next;
   while(p != NULL)
   {
	  printf("%s\n", p->buf);
	  p = p->next;
   }

   return 1;
}

int read_title(char* filename, char* buf_title)
{
   FILE* fp;
   char* line = NULL;
   size_t len = 0;
   ssize_t read;

   fp = fopen(filename, "r");
   if(fp == NULL)
   {
	  perror("FILE read error\n");
	  exit(EXIT_FAILURE);
   }
   //*buf_title = '\0';
   int line_no = 0;
   while((read = getline(&line, &len, fp)) != -1)
   {
	  int i = 0;
	  line_no++;
	  if(line_no > 10)
	  {
		 break;
	  }

	  char temp[9];
	  int isFind = 0;

	  // printf("line %d:%s\n", line_no, line);
	  if(line[1] != 't')
	  {
		 continue;
	  }

	  int j =0;
	  while(line[i] != '\0')
	  {
		 if(i < 7)
		 {
			temp[i] = line[i];
		 }
		 else if(i == 7)
		 {
			temp[i] = '\0';
			buf_title[j++] = line[i];
			if(strcmp(temp, "<title>") != 0)
			{
			   break;
			}
		 }
		 else if(i > 7)
		 {
			if(line[i] != '<')
			{
			   buf_title[j++] = line[i];
			}
			else
			{
			   buf_title[j] = '\0';
			   isFind = 1;
			   break;
			}
		 }
		 i++;
	  }

	  if(isFind == 1)
	  {
		 break;
	  }

   }

   free(line);

   return strlen(buf_title);
}
//
//<div class="authi">

int read_author(char* filename, char* buf_author)
{
   char* line;
   size_t len;
   ssize_t read_n;
   FILE* fp;


   while((read_n = getline(&line, &len, fp)) != -1)
   {
	  if(line[0] != '<')
	  {
		 continue;
	  }
	  int i = 0;
	  while(line[i] != '\0')
	  {

	  }

   }
}

void free_page(Page* page)
{
   free(page->title);
   free(page->author);
   free(page->time);
   free(page->content);
}
