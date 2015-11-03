/*************************************************************************
    > File Name: myfiledeal.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Sat Oct 10 17:59:07 2015
 ************************************************************************/

#include"myfiledeal.h"


void file_content_batching_deal(LineBuf* lbp[HTMLCOUNT])
{
  
   //819 urls;
   int filenum = 1;
   while(filenum <= 819)
   {
	  char filename[50];
	  sprintf(filename, "./utf_html/%d.html", filenum);

	  
	  LineBuf* temphead = lbp[filenum]; 
	  fill_buf(filename, temphead, filenum); 
	  printf("read html %d complete...\n", filenum);

	  filenum++;
   }

}

int fill_buf(char* filename, LineBuf* lb, int file_num)
{
   FILE* fp;
   char* line = NULL;
   size_t len = 0;
   ssize_t read_n;

   fp = fopen(filename, "r");
   if(fp == NULL)
   {
	  perror("read file error.");
	  return -1;
   }

   LineBuf* p = lb;
   int no =0;
   //getline len的参数为当前line的最大长度
   while((read_n = getline(&line, &len, fp)) != -1)
   {
	  no++;

	  //printf("lineno:%d, len:%d, %s\n",no, len, line);
	  if(line[0] == '\n' || line[0] == '\r')
		 continue;
	  LineBuf* q = (LineBuf*)malloc(sizeof(LineBuf));
	  //printf("len:%d, %s\n", strlen(line), line);
	  q->str = (char*)malloc(sizeof(char)*(strlen(line)+1));
	  q->file_no = file_num;
	  q->next = NULL;
	  strcpy(q->str, line);
	  q->line_no = no; 
	  if(lb->next == NULL)
	  {
		 lb->next = q;
		 q->before = lb;
		 p = p->next;
	  }
	  else
	  {
		 p->next = q;
		 q->before = p;
		 p = p->next;
	  }

   }

   free(line);
}

int file_buf_write(LineBuf* lb, const char* filename)
{
   FILE* fp;
   LineBuf* templb = lb->next;
   if(!(fp = fopen(filename, "w")))
   {
	  perror("cannot write file");
	  exit(-1);
   }

   while(templb)
   {
	  fwrite(templb->str,sizeof(char), strlen(templb->str), fp);
//	  printf("%s", templb->str);
	  templb = templb->next;
   }
   fclose(fp);

   return 1;
}
int file_read_full(char** dest, const char* filename)
{//把整个文件读成一个字符串
   FILE* fp;
   struct stat file_stats;
   int nItems, nBytesRead;

   *dest = NULL;
   if((fp = fopen(filename, "r")) == NULL)
   {
	  fprintf(stderr, "failed to open %s - %s\n", filename, strerror(errno));
	  return(-1);
   }
   fstat(fileno(fp), &file_stats);

   if((*dest = (char*)malloc(file_stats.st_size+1)) == NULL)
   {
	  fclose(fp);
	  fprintf(stderr, "failed to allocate memory for reading file%s\n", filename);
	  return(-2);
   }
   nBytesRead = 0;
   while((nItems = fread(*dest + nBytesRead, 1, BUFSIZ,fp)) > 0)
   {
	  nBytesRead += nItems;
   }
   fclose(fp);
   *(*dest + nBytesRead) = '\0';
   
   return (nBytesRead);
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

