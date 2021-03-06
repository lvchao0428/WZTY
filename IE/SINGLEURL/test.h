#ifndef _TEST_H_
#define _TEST_H_

#include<stdio.h>
#include"def.h"

void test_fillbuf(LineBuf* lb);			//测试linebuf

void test_lpp(LablePosPair* lpp, char* str);

void test_lable(char* line, LablePosPair* lpp);		//测试lable位置结构体数组的生成结果

void test_scope_lpp(LablePosPair* beglpp, LablePosPair* endlpp, char* str);

void count_comma(LineBuf* lb);

int test_illegal_lable(LineBuf* lb);

#endif
