#ifndef _LABLE_DEAL_H_
#define _LABLE_DEAL_H_

#include"def.h"

LablePosPair* out_content_scope(char* line, LablePosPair* lpp);		//生成内容的下标范围

LableType check_lable(char* line);		//检查此标签的对应内容的类型

void find_all_greater_lower(char* line, LablePosPair* lpp);		//找到所有的大于号和小于号

void dispos_son_lable(char* str, LablePosPair* lpp);	//去掉子标签

void copy_scope_str_to_str(char* str, LablePosPair* lpp);	//把lpp内存储范围内的字符串，赋值给原来的字符串

int analysis_content_lable(char* line, LableElem* le);		//分析content line里面的标签

LableElem* push_lable(LableElem* le, char* val);		//push lable

char* top_lable(LableElem* le);		//top lable

LableElem* pop_lable(LableElem* le);		//pop lable



#endif
