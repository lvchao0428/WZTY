#ifndef _PAGE_H_
#define _PAGE_H_

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>


//通用的页面处理算法

//把时间转化成统一的格式

int is_discuz(LineBuf* pb);			//判断页面是否是discuz论坛


//处理内容项


void find_all_greater_lower(char* line, LablePosPair* lpp);	//找到所有大于号小于号





#endif
