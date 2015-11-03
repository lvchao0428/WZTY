#ifndef __MYSTRING_H_
#define __MYSTRING_H_

#include<stdio.h>
#include<string.h>
#include"def.h"

void filename_tail_clean(char* filename);

int mystrcmp(char* str, char* word);

const char* mystrstri(const char* str, const char* subStr);	//不区分大小写的字符串包含判断

int mystrstr(char* father, char* son);			//测试前面字符串里面是否包含后面的字符串

int mystrcpy(char* dest, char* from, int begPos, int endPos);	//把from字符串的下表范围里面的字符串拷贝到前面字符串

int mystrcpy_with_point(char* dest, char* from, char* begpos,char* endpos);//使用指针标示位置的字符串复制函数

//比较范围内的字符串是否匹配
int scope_str_cmp(char* dest, char* from, int dest_beg);

int find_comma_num_out(char* line);		//寻找括号外面逗号的数量

int word_length_get(char* line);		//获得字符串里面的内容长度

int lable_length_get(char* line);	//获得字符串里面的标签长度

int is_word_longer_than_lable(char* line);	//判断line里面的内容和标签那个更长，内容长返回1，否则返回0

int find_str_with_scope(char* line, char* son, int begPos, int endPos);	//寻找范围内的字符串数量

int mycatNoN(char* dest, char* from);			//把后面的字符串拼接到前面字符串，忽略换行符

char character_to_lower(char c);	//把字母返回小写

int find_str_times(char* str, char* word);		//寻找后面字符串在前面字符串中出现的次数

int anno_beg_end_times_fill(char* str, int* begtimes, int* endtimes);

int return_son_str_pos(char* father, char* son);	//返回第一次出现son字符串的结束位置

int print_str(char* str, int beg, int end);		//打印beg到end里面的字符串


int despace_betw_more_less(char* str);		//去掉大于号小于号之间的空格



#endif
