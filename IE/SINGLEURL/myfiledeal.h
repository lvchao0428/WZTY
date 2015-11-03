#ifndef _MYFILEDEAL_H_
#define _MYFILEDEAL_H_


#include"def.h"
#define HTMLCOUNT 1024



void file_content_batching_deal(LineBuf* lbp[HTMLCOUNT]);

int fill_buf(char* filename, LineBuf* lb);	//把文件内容读取到linebuf里面

int file_read_full(char** dest, const char* filename);		//把整个文件读取成一个字符串

int Enqueue(buf_queue* bf, char* buf);			//固定块入队操作

int Dequeue(buf_queue* bf, char* buf);			//固定块出队操作


int read_html(char* url, buf_queue* bq);		//把文件内容按固定大小块读入

int read_queue(buf_queue* bq);					//读取固定块大小的文件内容

int read_title(char* filename, char* buf_title);	//从文件读取文章的标题内容(discuz)

int read_author(char* filename, char* buf_author);	//从文件读取作者名字(discuz)


#endif

