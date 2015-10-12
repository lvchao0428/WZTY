#ifndef _DISCUZ_EXTRACT_H_
#define _DISCUZ_EXTRACT_H_



int discuz_fill_the_page(LineBuf* pb, Page* page);		//把行结构信息提取出需要的所有需要信息

int deal_title(LineBuf** lb, Page* page);			//从行存储结构中读取标题内容

int deal_time(LineBuf** lb, Page* page);			//从行存储结构中读取时间内容

int deal_clickAndreplay(LineBuf** lf, Page* page);	//从行存储结构中读取点击和回复数据

int deal_author(LineBuf** lf, Page* page);			//从行存储结构中读取作者信息

int deal_content(LineBuf** lf, Page* page);			//从行存储结构中读取内容信息

void dispos_son_lable(char* str, LablePosPair* lpp);		//去掉discuz内容子标签


#endif
