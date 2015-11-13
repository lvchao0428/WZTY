#ifndef _PAGE_H_
#define _PAGE_H_
//通用的页面处理算法
#include"def.h"
#include"myfiledeal.h"


//把时间转化成统一的格式

int is_null(LineBuf* pb);		//判断网页是否为空

int is_discuz(LineBuf* pb);			//判断页面是否是discuz论坛

int page_null_count(LineBuf* lbp[HTMLCOUNT]);

void page_dis_count(LineBuf* lbp[HTMLCOUNT], Page* page[HTMLCOUNT], int* corr);		//计数网页里面含有多少个discuz型网页

void page_free(Page* page);

#endif
