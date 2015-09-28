/*************************************************************************
    > File Name: gethtml.cpp
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Tue Sep 22 10:05:31 2015
 ************************************************************************/

#include<iostream>
#include "gethtml.h"
#include<netinet/in.h>
using namespace std;

string GetHtmlByGet(string url)
{
   string strHtmlContent = "";
   int sockfd;
   struct sockaddr_in addr;
   struct hostent *pURL;
   char text[RECVBUF];

   UrlInfo urlInfo = ParseURL(url);

}
