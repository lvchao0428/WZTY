/*************************************************************************
    > File Name: clean_res.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Mon Oct 12 14:29:55 2015
 ************************************************************************/

#include"clean_res.h"



void free_page(Page* page)
{
   free(page->title);
   free(page->author);
   free(page->time);
   free(page->content);
}
