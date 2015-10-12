#ifndef __MYSTRING_H_
#define __MYSTRING_H_

#include<stdio.h>
#include<string.h>
#include"def.h"

int mystrstr(char* father, char* son);			//测试前面字符串里面是否包含后面的字符串

int mystrcpy(char* dest, char* from, int begPos, int endPos);	//把from字符串的下表范围里面的字符串拷贝到前面字符串

int find_comma_num_out(char* line);		//寻找括号外面逗号的数量

int find_str_with_scope(char* line, char* son, int begPos, int endPos);	//寻找范围内的字符串数量


int mycatNoN(char* dest, char* from);			//把后面的字符串拼接到前面字符串，忽略换行符

int find_str_times(char* str, char* word);		//寻找后面字符串在前面字符串中出现的次数

int return_son_str_pos(char* father, char* son);	//返回第一次出现son字符串的结束位置

int print_str(char* str, int beg, int end);		//打印beg到end里面的字符串


int despace_betw_more_less(char* str);		//去掉大于号小于号之间的空格


#endif
