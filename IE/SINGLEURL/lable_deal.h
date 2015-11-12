#ifndef _LABLE_DEAL_H_
#define _LABLE_DEAL_H_

#include"def.h"

void find_lable(LineBuf* lb, LineBuf* dest);

void merge_illegal_lable(LineBuf* lb);

void count_illegal_lable(LineBuf* lb, 
	  int* annobegNum, int* annoendNum, 
	  int* scriptbegNum, int* scriptendNum,
	  int* stylebegNum, int* styleendNum);

void illegal_part_deal(LineBuf* lb);		//非法部分处理


void illegal_lable_wipe(LineBuf** lb, char* beglable, char* endlable);	//删除被被该字符串包裹的部分

void annotation_part_handle(LineBuf* lb);	//处理注释部分

LablePosPair* out_content_scope(char* line, LablePosPair* lpp);		//生成内容的下标范围

LableType check_lable(char* line);		//检查此标签的对应内容的类型

void find_all_greater_lower(char* line, LablePosPair* lpp);		//找到所有的大于号和小于号

void dispos_son_lable(char* str, LablePosPair* lpp);	//去掉子标签

void copy_scope_str_to_str(char* str, LablePosPair* lpp);	//把lpp内存储范围内的字符串，赋值给原来的字符串

int content_until_lable_end_extract(LineBuf* lb, char* line);	//提取内容的方法2

int deal_adver(char* tempstr, LablePosPair* lpp, LablePosPair* lastlpp[LASTLINKNUM]);

//int href_extract(char* tempstr, LablePosPair* lpp);

int extract_content_with_punct(LineBuf** lb, char* line);	//使用标点符号密度定位内容部分

int analysis_content_lable(char* line, LableElem* le);		//分析content line里面的标签

LableElem* push_lable(LableElem* le, char* val);		//push lable

LableElem* top_lable(LableElem* le);		//top lable

void pop_lable(LableElem* le);		//pop lable

int get_elem_stack_size(LableElem* head);

void deal_anno(LineBuf** lb);		//跳过注释区域

void free_LablePosPair(LablePosPair* lpp);

#endif
