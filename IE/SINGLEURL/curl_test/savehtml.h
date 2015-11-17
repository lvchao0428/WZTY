#ifndef SAVEHTML_H_
#define SAVEHTML_H_


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<malloc.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<errno.h>

#define HTMLCOUNT 1024

typedef struct FileLink
{
   char* str;
   char type[20];
   struct FileLink* next;
}FileLink;


int file_read_full(char** dest, const char* filename);

int read_all_files();

int test_filelink(FileLink* head);

#endif
