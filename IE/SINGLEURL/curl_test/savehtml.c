/*************************************************************************
    > File Name: savehtml.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Mon Nov  2 14:29:27 2015
 ************************************************************************/

#include<stdio.h>
#include"savehtml.h"
#include"code_convert.h"

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

int read_all_files()
{
  // FileLink* p = head;
   int filenum = 1;
   //统计编码类型
   FILE* fp;
 

   for(filenum = 1; filenum <= 819; ++filenum)
   {
	  char filename[50];
	  char type[20];
	  sprintf(filename, "./bbshtmls/%d.html", filenum);
	  //FileLink* q = (FileLink*)malloc(sizeof(FileLink));
	  char outfilename[50];
	  sprintf(outfilename, "./utf_html/%d.html", filenum);
	  if((fp = fopen(outfilename, "w")) == NULL)
	  {
		 fprintf(stderr, "failed, to open %s - %s\n", outfilename, strerror(errno));
		 return -1;
	  }

	  char* str;
	  //q->next = NULL;
	  file_read_full(&str, filename);
	  //p->next = q;
	  //p = p->next;
	  size_t inlen, outlen;
	  inlen = strlen(str);
	  outlen = 2*inlen;
   	  code_type_get(str, type);
	  char* outfile;
	  if(strcmp(type, "utf-8") == 0 || type[0] == '\0')
	  {
		 fwrite(str, sizeof(char), strlen(str), fp);
	  }
	  else
	  {
		 char* outfile = (char*)malloc(sizeof(char)*(2*strlen(str)));
		 code_convert(type, "utf-8", str, inlen, outfile, outlen);
		 fwrite(outfile, sizeof(char), strlen(outfile), fp);
		 char* temp = outfile;
		 free(outfile);
	  }
	  fclose(fp);

	  printf("%d complete,\t\ttype:%s \n", filenum, type );
//	  char line[50];
//	  sprintf(line, "line:%d, type:%s\n", filenum, type);
//	  fwrite(line, sizeof(char), strlen(line), fp);
   }

   //fclose(fp);
}

int test_filelink(FileLink* head)
{
   FileLink* p = head->next;
   while(p)
   {
	  printf("%s\n", p->str);
	  p = p->next;
   }
   return 0;
}

