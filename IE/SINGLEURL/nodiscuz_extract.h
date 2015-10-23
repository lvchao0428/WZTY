#ifndef _NODISCUZ_EXTRACT_H_
#define _NODISCUZ_EXTRACT_H_

#include"def.h"

void deal_normal_content(LineBuf** lb, Page* page);	//处理普通网页的内容部分


int no_discuz_fill_the_page(LineBuf* pb, Page* page);

LableType check_normal_lable(LineBuf* lb, char* line);


#endif
