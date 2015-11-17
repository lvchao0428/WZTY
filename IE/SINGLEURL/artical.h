#ifndef ARTICAL_H_
#define ARTICAL_H_

#include<stdio.h>
#include"page.h"
#include"discuz_extract.h"
#include"nodiscuz_extract.h"
#include"def.h"
#include"myfiledeal.h"

/*
typedef struct Page
{
   char* title;
   char* author;
   char* time;
   char* click_count;
   char* replay_count;
   char* content;
   int title_filled;
   int author_filled;
   int time_filled;
   int click_filled;
   int replay_filled;
   int content_filled;
}Page, *pPage;
*/
/*
 *	@html[in]:网页原始内容
 *	@len[in]:网页内容长度
 *	@url[in]:网页url
 *	@res[out]:网页抽取结果输出
 * */

int artical_extract(const char* html, size_t len, const char* url, Page *res);



#endif
