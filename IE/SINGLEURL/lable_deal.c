/***********************************************************************
    > File Name: lable_deal.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Mon Oct 12 14:25:23 2015
 ************************************************************************/

#include"lable_deal.h"
#include"mystring.h"

void find_lable(LineBuf* lb, LineBuf* dest)
{
   LineBuf* p = lb->next;
   LineBuf* pdest = dest;
   if(pdest->next)
   {
	  pdest->next = NULL;
   }
   while(p)
   {
	  if(mystrstri(p->str, "<script") ||
			mystrstri(p->str, "<style") ||
			mystrstri(p->str, "<!--"))
	  {
		 LineBuf* q = (LineBuf*)malloc(sizeof(LineBuf));
		 q->next = NULL;
		 q->line_no = p->line_no;
		 q->str = (char*)malloc(sizeof(char)*(strlen(p->str) + 1));
		 strcpy(q->str, p->str);
		 pdest->next = q;
		 pdest = pdest->next;
	  }
	  p = p->next;
   }
}

void count_illegal_lable(LineBuf* lb, 
	  int* annobegNum, int* annoendNum, 
	  int* scriptbegNum, int* scriptendNum,
	  int* stylebegNum, int* styleendNum)
{
   LineBuf* p = lb->next;
   while(p)
   {
	  
	  if(mystrstr(p->str,"<!--") || mystrstr(p->str, "-->"))
	  {
		 *annobegNum += find_str_times(p->str, "<!--");
		 *annoendNum += find_str_times(p->str, "-->");
	  }
	  if(mystrstri(p->str, "<style") || mystrstri(p->str, "</style>"))
	  {
		 *stylebegNum += find_str_times(p->str, "<style");
		 *styleendNum += find_str_times(p->str, "</style>");
	  }
	  if(mystrstri(p->str, "<script") || mystrstri(p->str, "</script>"))
	  {
		 *scriptbegNum += find_str_times(p->str, "<script");
		 *scriptendNum += find_str_times(p->str, "</script>");
	  }
	  p = p->next;
   }
}

void illegal_part_deal(LineBuf* lb)
{
   LineBuf* beglb = lb->next;

   //删除注释信息和style 和script包含的信息
   char *p;
   while(beglb)
   {
//	  printf("check beglb:%s\n", beglb->str);
	  if((mystrstr(beglb->str, "<!--")== -1) && 
			!(mystrstri(beglb->str, "<style")) &&
			!(mystrstri(beglb->str, "<script")))
	  {
		 beglb = beglb->next;
		 continue;
	  }
	  else if(mystrstr(beglb->str, "<!--") >= 0)
	  {//优先清除注释信息
		// printf("annotation:lineno:%d %s\n", beglb->line_no, beglb->str);
		 //annotation_part_handle(&beglb);
		 //printf("\n\n");
		 illegal_lable_wipe(&beglb, "<!--", "-->");

		// printf("after handle annotation:%s\n\n\n", beglb->str);

	  }
	  else if(mystrstri(beglb->str, "<style"))
	  {
		
		//	printf("sylte:lineno:%d %s\n", beglb->line_no, beglb->str);
			illegal_lable_wipe(&beglb, "<style", "</style>") ;
		//	printf("after handle style:%s\n\n\n", beglb->str);


	  }
	  else if(mystrstri(beglb->str, "<script"))
	  {
	//	 printf("script:lineno:%d %s\n", beglb->line_no, beglb->str);

		//	printf("beg ille wipe\n");
			illegal_lable_wipe(&beglb, "<script", "</script>");
	//		printf("after handle scipt:%s\n\n\n", beglb->str);
		 
	  }
	  beglb = beglb->next;
   }
}

void illegal_lable_wipe(LineBuf** lb, char* beglable, char* endlable)
{//清除注释区域
  LablePosPair* templpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   templpp->next = NULL;
   LablePosPair* p = templpp;
   LineBuf* beglb, *endlb, *templb;
   beglb = endlb = *lb;
   int done = 0;	//如果此次寻找注释区域已经完全则视为处理完成
  
//   printf("%s lable check\n", beglable);
   if(endlb)
   {
	  int begLableNum, endLableNum;
	  //js代码的转义后字符已排除在外如"\'<script>"

	  begLableNum = find_str_times(endlb->str, beglable);
	  endLableNum = find_str_times(endlb->str, endlable);
	  //printf("str:%s\b", endlb->str); 
//	  printf("beglableNum:%d\tbeglable:%s\t", begLableNum, beglable);
	  int begLableCount = 0;

//	  printf("endlableNum:%d\tendlable:%s\n", endLableNum, endlable);
//	  printf("endlstr:%s\n", endlb->str);
	  if(begLableNum == endLableNum)
	  {//此句话有偶数个注释标签，所以此行的注释不会延伸到下一行，把
		 //此行注释处理后把剩下的信息赋值回去。
		 int i = 0;
		 char* c = endlb->str;
//	  printf("single line detect\n"); 
	//	 printf("begin start lable getting\n");
		// printf("len:%d\n", strlen(c));
		 int len = strlen(c);
		 for(i = 0; i < len && begLableCount < begLableNum; ++i)
		 {//找到所有的"<!--"
			
			if(scope_str_cmp(c, beglable, i))
			{
			   if(c != &endlb->str[0] && *(c-1) == '\'' )
			   {
				  continue;
			   }
		//	   printf("%c\n", c[i]);
			   LablePosPair* q = (LablePosPair*)malloc(sizeof(LablePosPair));
			   q->next = NULL;
			   q->left = i;
			   p->next = q;
			   p = p->next;
			   begLableCount++;
			}

		 }

		 p = templpp->next;
		 
		 i = 0;
		 //找到结束字符的结束位置
		 while(p && c[i+strlen(endlable)-1])
		 {
			i = p->left;
			while(p && c[i+strlen(endlable)-1])
			{
			   if(scope_str_cmp(c, endlable, i))
			   {
				  p->right = i+strlen(endlable)-1;
				  break;
			   }
			   i++;
			}
			p = p->next;
		 }

		 //test lpp
	//	 printf("lieno:%d,\ttest lpp\n", endlb->line_no);
//		 test_lpp(templpp);

		 //生成剩下的内容范围
		 p = templpp->next;
		 //如果是只有一对非法标签
		 if(p->next == NULL)
		 {//如果非法标签只存在一组，则分成三种情况
		 	//printf("single lpp \n");
			if(p->left == 0)
			{//标签在最前面，则后面的全是合法内容
			   p->left = p->right+1;
			   p->right = strlen(endlb->str)-1;
			}
			else if(p->left > 0 && p->right < (strlen(endlb->str) - 3))//跳过\r\n
			{//标签在中间，则两边的是合法内容，需要重新新建一个内容标签
			   LablePosPair* contentLpp = (LablePosPair*)malloc(sizeof(LablePosPair));
			   contentLpp->next = NULL;
			   int templeft = p->left;
			   int tempright = p->right;

			   contentLpp->left = p->right + 1;
			   contentLpp->right = strlen(endlb->str)-1;
			   p->left = 0;
			   p->right = templeft-1;
			   p->next = contentLpp;
			}
			else
			{//如果标签在最后面,则应该前面的都是内容部分
			   p->right = p->left-1;
			   p->left = 0;
			}
		 }
		 else
		 {
			//两对以上的非法标签
			//先把最前面的合法标签取出来
			p = templpp;
			LablePosPair* beforeLpp = (LablePosPair*)malloc(sizeof(LablePosPair));
			if(p->next->left > 0)
			{//如果最前面有合法标签则增加一个节点
			   beforeLpp->next = p->next;
			   beforeLpp->left = 0;
			   beforeLpp->right = p->next->left-1;
			   p->next = beforeLpp;
			   p = beforeLpp->next;
			}
			else
			{//如果最前面没有合法标签则直接从第一个标签处理
			   p = templpp->next;
			}
			//把中间的内容标签填满
			while(p && p->next)
			{
			   p->left = p->right+1;
			   p->right = p->next->left-1;
			   if(p->next->next == NULL)
			   {
				  if(p->next->right < strlen(endlb->str)-3)
				  {//如果最后还有合法标签，则最后一个符号标签组保留为内容标签组
					 p->next->left = p->next->right+1;
					 p->next->right = strlen(endlb->str)-1;
				  }
				  else
				  {//如果结尾处是非法标签则删除最后一个符号标签组
					 LablePosPair* temp = p->next;
					 p->next = NULL;
					 free(temp);
				  }
			   }
			   p = p->next;
			}

		 }

		 //printf("test content lablepari:\n");
		 //test_lpp(templpp);
		 p = templpp->next;
		 c = endlb->str;
		 //单行注释位置已经被标记完毕，把剩下内容赋值给原字符串
		 int j = 0;
		 i = p->left;
		 while(p)
		 {
			i = p->left;
			while(i <= p->right)
			{
			   c[j++] = c[i++];
			}
			p = p->next;
		 }
	//	 printf("endlb deal end\tline_no:%d\n", endlb->line_no);
		 c[j] = '\0';
		 
	  }
	  else if(begLableNum > endLableNum)
	  {//如果是多行注释则合并成一行，下一回合处理
		// printf("multi line\n");
	//	 printf("endlb->str:%s\n", endlb->str);
		 LineBuf* temptemplb = endlb;	//保存开始的指针，先计算长度，然后第二遍才分配空间
		 int buffLen = 0;
		 LineBuf* needToBeDeleteLb;
		 char tempstr[100000] = {0};

		 
		 buffLen+= strlen(temptemplb->str);
		 if(endlb->next)
		 {//结束标签指针往后遍历一个然后再找结束标签
			endlb = endlb->next;
		 }
	   
		 while(endlb && (!mystrstri(endlb->str, endlable)))
		 {
			//printf("endlb no:%d, endstr:%s\n", endlb->line_no, endlb->str);

			buffLen += strlen(endlb->str);
			endlb = endlb->next;
		 }
		 

		 if(endlb == NULL)
		 {
		//	printf("beglablenum:%d, endlableNum:%d\n", begLableNum, endLableNum);
//			LineBuf* ttlb = temptemplb->next;
		//	printf("temptemptempstr:%s\nlieno:%d\n", temptemplb->str, temptemplb->line_no);
		//	printf("NULLNULLNULL****************\n");
		 }
		 buffLen += strlen(endlb->str); 
		 strcpy(tempstr, temptemplb->str);		//把第一个节点先赋值给tempstr，等复制完后几个节点一并付给lb->str
		 //这时候需要把temptemplb->next 一直到endlb的str付给temptemplb，并且把多余节点删掉
		 LineBuf* q;
		 
		 needToBeDeleteLb = temptemplb->next;
	
		 if(needToBeDeleteLb != endlb)
		 {
			while(needToBeDeleteLb && needToBeDeleteLb->next && needToBeDeleteLb != endlb &&
				  needToBeDeleteLb->next != endlb)
			{//注意！ 双向链表
			   //			printf("need lb:%s\n", needToBeDeleteLb->str);
			   strcat(tempstr, needToBeDeleteLb->str);
			   //printf("need to be:%d\n", endlb->line_no);
			   q = needToBeDeleteLb;

			   temptemplb->next = needToBeDeleteLb->next;
			   needToBeDeleteLb->next->before = temptemplb;
			   needToBeDeleteLb = temptemplb->next;
			   free(q);
			}

		 }

		 if(needToBeDeleteLb == endlb)
		 {
			if(endlb->next != NULL)
			{
			   q = endlb;
			   temptemplb->next = endlb->next;
			   endlb->next->before = temptemplb;
			   strcat(tempstr, q->str);
			   //free(q);
			}
			else
			{//endlb->next == NULL
			   q = endlb;
			   temptemplb->next = NULL;
			   strcat(tempstr, q->str);
			}
		 }//needToBeDeleteLb != endlb
		 else if(needToBeDeleteLb->next && needToBeDeleteLb->next == endlb)
		 {
		//	printf("need == endl\n");

			q = needToBeDeleteLb;
			//needToBeDeleteLb
			temptemplb->next = needToBeDeleteLb->next;
			needToBeDeleteLb->next->before = temptemplb;
			strcat(tempstr, needToBeDeleteLb->str);
			//endlb
			if(endlb->next)
			{
			   q = endlb;
			   temptemplb->next = endlb->next;
			   endlb->next->before = temptemplb;
			   strcat(tempstr, q->str);
			}
			else
			{//endlb->next == NULL
			   q = endlb;
			   temptemplb->next = NULL;
			   strcat(tempstr, q->str);
			}
		 }
		 
		 temptemplb->str = (char*)realloc(temptemplb->str, sizeof(char)*(buffLen+1));
		 strcpy(temptemplb->str, tempstr);

		 //printf("mul_len:%d %s\n", buffLen, temptemplb->str);
		 //printf("before:buflineno:%d\n", temptemplb->line_no);

		 
		 *lb = (temptemplb->before->before);
		 if(endlb == NULL)
		 {
			*lb = NULL;
		 }
	  }
   }
  
}

//标记注释区域
void annotation_part_handle(LineBuf** lb)
{
   LablePosPair* templpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   templpp->next = NULL;
   LablePosPair* p = templpp;
   LineBuf* beglb, *endlb, *templb;
   beglb = endlb = *lb;
   int done = 0;	//如果此次寻找注释区域已经完全则视为处理完成
   
   if(endlb)
   {
	  int begLableNum, endLableNum;
	  
	  begLableNum = find_str_times(endlb->str, "<!--");
	  endLableNum = find_str_times(endlb->str, "-->");
	  
	  //printf("beglableNum:%d\t", begLableNum);
	  int begLableCount = 0;
	  //printf("endlableNum:%d\n", endLableNum);
	  if(begLableNum == endLableNum)
	  {//此句话有偶数个注释标签，所以此行的注释不会延伸到下一行，把
		 //此行注释处理后把剩下的信息赋值回去。
		 int i = 0;
		 char* c = endlb->str;
	//	 printf("begin start lable getting\n");
		// printf("len:%d\n", strlen(c));
		 int len = strlen(c);
		 for(i = 0; i < len && begLableCount < begLableNum; ++i)
		 {//找到所有的"<!--"
			
			if(c[i] == '<' && c[i+1] == '!')
			{
		//	   printf("%c\n", c[i]);
			   LablePosPair* q = (LablePosPair*)malloc(sizeof(LablePosPair));
			   q->next = NULL;
			   q->left = i;
			   p->next = q;
			   p = p->next;
			   begLableCount++;
			}

		 }
		 p = templpp->next;
		 
		 i = 0;
		 //找到"-->"
		 while(p && c[i+1] && c[i])
		 {
			i = p->left;
			while(p && c[i+1] && c[i])
			{
			   if(c[i] == '-' && c[i+1] == '>')
			   {
				  p->right = i+1;
				  break;
			   }
			   i++;
			}
			p = p->next;
		 }

		 //test lpp
	//	 printf("test lpp\n");
	//	 test_lpp(templpp);

		 //生成剩下的内容范围
		 p = templpp->next;
		 if(p->next == NULL)
		 {
			p->left = p->right+1;
			p->right = strlen(endlb->str);
		 }
		 
		 while(p && p->next)
		 {
			p->left = p->right+1;
			p->right = p->next->left-1;
			if(p->next->next == NULL)
			{
			   LablePosPair* temp = p->next;
			   p->next = NULL;
			   free(temp);
			}
			p = p->next;
		 }
		 
		 p = templpp->next;
		 c = endlb->str;
		 //单行注释位置已经被标记完毕，把剩下内容赋值给原字符串
		 int j = 0;
		 i = p->left;
		 while(p && c[j])
		 {
			i = p->left;
			while(i <= p->right)
			{
			   c[j++] = c[i++];
			}
			p = p->next;
		 }
		 c[j] = '\0';
		 
	  }
	  else if(begLableNum > endLableNum)
	  {//如果是多行注释则合并成一行，下一回合处理
		// printf("endlb->str:%s\n", endlb->str);
		 LineBuf* temptemplb = endlb;	//保存开始的指针，先计算长度，然后第二遍才分配空间
		 int buffLen = 0;
		 LineBuf* needToBeDeleteLb = temptemplb->next;
		 char tempstr[10000];
		 strcpy(tempstr, endlb->str);
		 while(endlb && (mystrstr(endlb->str, "-->") == -1))
		 {
			buffLen += strlen(endlb->str);
			endlb = endlb->next;
		 }
		 buffLen += strlen(endlb->str);
		 temptemplb->str = (char*)realloc(temptemplb->str, sizeof(char)*(buffLen+1));
		 //这时候需要把temptemplb->next 一直到endlb的str付给temptemplb，并且把多余节点删掉
		 LineBuf* q;
		 
		 while(needToBeDeleteLb != endlb)
		 {
//			printf("need lb:%s\n", needToBeDeleteLb->str);
			strcat(tempstr, needToBeDeleteLb->str);
			q = needToBeDeleteLb;
			temptemplb->next = needToBeDeleteLb->next;
			needToBeDeleteLb = needToBeDeleteLb->next;
			free(q);
		 }
		 q = endlb;
		 strcat(tempstr, endlb->str);
		// free(temptemplb->str);
		 //printf("len:%d\n", buffLen);
		 temptemplb->str = (char*)malloc(sizeof(char)*(buffLen+1));
		 temptemplb->next = endlb->next;
		 strcpy(temptemplb->str, tempstr);
		 
		 //printf("mul_len:%d %s\n", buffLen, temptemplb->str);
		 *lb = temptemplb->before->before;
	  }
   }
   
}


LablePosPair* out_content_scope(char* line, LablePosPair* lpp)
{//把字符串中内容项的范围存储到lpp里面，也即除去标签之外的内容部分的下标范围
   
   find_all_greater_lower(line, lpp);		//先把lpp里面存上大于号和小于号的位置，
  // LablePosPair* scan = lpp->next;
  
   /*
   while(scan)
   {
	  printf("left:%d  right:%d\n", scan->left, scan->right);
	  scan = scan->next;
   }
*/
  // printf("test greater lable:\n");
  // test_lpp(lpp);

   //小于号和大于号之间即为内容范围
   LablePosPair* p = lpp->next;
   LablePosPair* q;
   //如果
   //
   if(lpp->next == NULL)
   {//如果不含大于号小于号标签，则都视为内容
	  LablePosPair* templpp = (LablePosPair*)malloc(sizeof(LablePosPair));
	  templpp->next = NULL;
	  templpp->left = 0;
	  templpp->right = strlen(line)-1;
	  lpp->next = templpp;
   }
   else if(p && p->next == NULL)
   {//如果符号标签只有一个，分成三种情况，在内容最前面，在内容中间，在内容后面
	  //在内容最前面
	  if(p->left == 0 && p->right < strlen(line)-1)
	  {//后面的都是内容部分
		 p->left = p->right+1;
		 p->right = strlen(line)-1;
	  }
	  else if(p->left > 0 && p->right < strlen(line)-1)
	  {//前面和后面是内容部分
		 LablePosPair* endLpp = (LablePosPair*)malloc(sizeof(LablePosPair));
		 endLpp->next = NULL;
		 endLpp->left = p->right+1;
		 endLpp->right = strlen(line)-1;

		 p->right = p->left-1;
		 p->left = 0;
		 p->next = endLpp;
	  }
	  else if(p->left > 0 && p->right == strlen(line) -3)
	  {//前面是内容部分
		 p->right = p->left-1;
		 p->left = 0;
	  }
	  else if(p->left == 0 && p->right == strlen(line) -3)
	  {//全是标签，无内容
		 p->left = -1;
		 p->right = -1;
	  }
	  
   }
   else
   {//两对以上标签的需要注意，最前面和最后面都可能是内容，可能没有标签包含；
	  //同样分成两个区域需要注意，
	  //1.最前面的标签前面有内容
	  //2.最后面的标签后面有内
	  //p == lpp->next
	  LablePosPair* begLpp = (LablePosPair*)malloc(sizeof(LablePosPair));
	  begLpp->next = NULL;
	  LablePosPair* endLpp = (LablePosPair*)malloc(sizeof(LablePosPair));
	  endLpp->next = NULL;
	  if(p->left > 0)
	  {//最前面有内容
		 begLpp->left = 0;
		 begLpp->right = p->left-1;
	  }
	  
	  LablePosPair* endpoint = p;
	  while(endpoint->next)
	  {
		 endpoint = endpoint->next;
	  }
	  if(endpoint->right < strlen(line)-1)
	  {//最后面有内容
		 endLpp->left = endpoint->right+1;
		 endLpp->right = strlen(line)-1;
	  }
	  
	  while(p->next->next && p->next) 
	  {//获取中间的内容标签
		 p->left = p->right+1;
		 p->right = p->next->left-1;
		 p = p->next;
	  }

	  if(p->next->next == NULL)
	  {
		 q = p->next;
		 p->left = p->right+1;
		 p->right = p->next->left-1;
		 p->next = NULL;
		 free(q);
	  }//p->next == NULL
	  begLpp->next = lpp->next;
	  lpp->next = begLpp;
	  p->next = endLpp;
	 
   }
   // printf("test content lpp:\n");
   //test_lpp(lpp);
   //有些大于号和小于号之间没有内容，把这些无用的范围消除掉
   p = lpp;
   while(p->next)
   {
	  if(p->next->left >= p->next->right || abs(p->next->left - p->next->right) <= 2)
	  {
		 q = p->next;
		 p->next = p->next->next;
		 free(q);
	  }
	  else
	  {
		 p = p->next;
	  }
   }

   return lpp;
}

LableType check_lable(char* line)
{//检查此行标签的可能内容，并返回可能的标签
   int i = 0;
   LableType lt = -1;
   char lable[60];
   int j = 0;
   //printf("char 0 : %c\n", line[0]);
   while(line[i] != '>' && line[i] != ' ')
   {
	  lable[j++] = line[i++];
   }
   //printf("read lable end\n");
   lable[j] = '\0';

//   printf("test check lable: %s\n", lable);
//   printf("line:%s\n", line);
   if(strcmp(lable, "<title") == 0)
   {
	  lt = TITLELABLE;
//	  printf("title checked\n");
   }
   //内容标签里面有可能包含的postmessage
   else if((strcmp(lable, "<div") == 0) && mystrstr(line, "authi"))
   {
	  lt = AUTHORLABLE;

//	  printf("author checked\n");
   }
   else if(mystrstr(line, "authorposton") == 1)
   {
	  lt = TIMELABLE;
//	  printf("time checked\n");
   }
   
   else if(mystrstr(line, "查看") && mystrstr(line, "回复"))
   {
	  lt = REPLAYLABLE;
//	  printf("replay checked\n");
   }
   else if(((strcmp(lable, "<div") == 0) || (strcmp(lable, "<table") == 0)) && 
		 ((mystrstr(line, "postmessage") == 1 || (mystrstr(line, "pid") == 1))))
   {//此个网页内容部分包含在talbe中，以后可以在这里扩展内容页可能存在的标签
	  lt = CONTENTLABLE;
//	  printf("content checked\n");
   }

   return lt;
}

void find_all_greater_lower(char* line, LablePosPair* lpp)
{//找到所有的大于号和小于号的位置
   int i = 0;
   //找到所有'<'的位置
   LablePosPair* p = lpp;
   while(line[i] != '\0')
   {
	  if(line[i] == '<' && ((line[i+1] >= 'a' && line[i+1] <= 'z') || (line[i+1] == '/') || (line[i+1] == '!')) )
	  {
		 LablePosPair* q = (LablePosPair*)malloc(sizeof(LablePosPair));
		 q->left = i;
		 q->next = NULL;
		 p->next = q;
		 p = p->next;
	  }
	  i++;
   }

   p = lpp->next;
   i = 0;
   int j = 0;
   //找到所有的大于号的位置
   int lineLen = strlen(line);
   while(i < lineLen && line[i] != '\0' && p)
   {
	  i = p->left;
	  //find right
	  while(i < lineLen && line[i] != '>')i++;
	  p->right = i;
	  p = p->next;
	  i++;
   }
   
 
}

void dispos_son_lable(char* str, LablePosPair* lpp)
{
   LablePosPair* p = lpp->next;
   int i = 0, j = 0;
   while(str[i] != '\0' && p)
   {
	  if(p != NULL)
	  {
		 i = p->right+1;
		 p = p->next;
	  }
	  else
	  {
		 while(str[i] != '\0')
		 {
			str[j++] = str[i++];
		 }
	  }
	  while(p && str[i] != '\0' && i < p->left) 
	  {
		 str[j++] = str[i++]; 
	  }
	  
	  
   }
   str[j] = '\0';
}

void copy_scope_str_to_str(char* str, LablePosPair* lpp)
{
   LablePosPair* p = lpp->next;
   int i = 0, j = 0;
   while(str[i] != '\0' && p != NULL)
   {
	  i = p->left;
	  while(str[i] != '\0' && i <= p->right)
	  {
		 str[j++] = str[i++];
	  }
	  p = p->next;
   }
   str[j] = '\0';
}


int content_until_lable_end_extract(LineBuf* lb, char* line)
{
   LineBuf* templf = lb;
   LineBuf* endlf = templf;

   int count = 5;
   int is_end = 0;
   //往回回溯5行，如果有结束标签则内容全面
   //否则向后找到结束标签为止
   while(count-- > 0)
   {
	  if(mystrstr(endlf->str, "</div>"))
	  {
		 is_end = 1;
		 break;	 
	  }
	  else
	  {
		 endlf = endlf->before;	 
	  }
   }

   if(is_end == 1)
   {
	  return 1;
   }
   else
   {
	  //向后追溯结束标签
	  while(templf)
	  {
		 if(!mystrstr(templf->str, "</div>"))
		 {
			strcat(line, templf->str); 
			templf = templf->next;
		 }
		 else
		 {
			strcat(line, templf->str);
			return 1;
		 }
	  }

   }

}

int extract_content_with_punct(LineBuf** lb, char* line)
{
   LablePosPair* lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   lpp->next = NULL;

   //获取内容的范围列表,初始五行
   char tempstr[100000] = {0};		//存储所有的粗糙内容部分
   strcpy(tempstr, line);
   LineBuf* templf = *lb;
   //步长为3如果三行里面的符号数量小于5个，就视为内容的最后一个节点
   int step = 0;
   while(templf)
   {
	  step = 0;
	  char temptempstr[100000]={0 };//存储追加的可能内容部分，符合的话归并到上述内容部分。
	  while(templf && step != 5)
	  {
		 strcat(temptempstr, templf->str);
		 templf = templf->next;
		 step++;
	  }
	  //templf = templf->next;
	  LablePosPair* templpp = (LablePosPair*)malloc(sizeof(LablePosPair));
	  templpp->next = NULL;
	  out_content_scope(temptempstr, templpp);	//找到最近三行的所有标签和标点数量
	  int comma_num = find_comma_num_out(temptempstr);
	  free_LablePosPair(templpp);
	  if(comma_num >= 5)
	  {
	//	 printf("comma num:%d\n", comma_num);
		 strcat(tempstr, temptempstr);
	//	 printf("temptempstr:%s\n", temptempstr);
		 
	  }
	  else if(comma_num < 5 && comma_num > 0)
	  {
		 //如果标点符号处于低谷值，那么作为结束的三行内容初始行。开始提取内容
		 //否则继续往后面继续寻找
		 //deal content
	//	 printf("comma num:%d\n", comma_num);
		 strcat(tempstr, temptempstr);

	//	 printf("over check\n--------------------------------\n%s\n", line);
		 break;
	  }
	  else if(comma_num == 0)
	  {
		 
		 
		 break;
	  }

	  if(templf != NULL)
	  {
		 templf = templf->next;
	  }

   }
   //find_all_greater_lower(tempstr, lpp);
   //dispos_son_lable(tempstr, lpp);
  // int comNum = find_comma_num_out(tempstr);
   out_content_scope(tempstr, lpp);
   copy_scope_str_to_str(tempstr, lpp);
  // printf("commanum:%d\n", comNum);
   strcpy(line, tempstr);
   *lb = templf;
}
/*
int analysis_content_lable(LineBuf** lb, char* line)
{//分析content的标签
   LableElem* head = (LableElem*)malloc(sizeof(LableElem));
   head->next = NULL;

   LablePosPair* lpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   lpp->next = NULL;
    
   int i = 0;
  // find_all_greater_lower(line, lpp);
   LablePosPair* tpp = lpp->next;
   
   //找到第一个开始标签
   while(tpp && line[tpp->left+1] == '/')
   {
	  tpp = tpp->next;
   }

   char temp[20];
   int j = 0;
   i = tpp->left;
   while(tpp && i <= tpp->right && line[i] != ' ')
   {
	  temp[j++] = line[i++];	  
   }
   temp[j] = '\0';
   push_lable(head, temp);

   tpp = tpp->next;
   //解析剩余标签，初始传入的部分标签先解析出来
   while(line[i] && tpp)
   {
	  j = 0;
	  if(line[tpp->left+1] == '/')
	  {
		 pop_lable(head);
	  }
	  else
	  {
		 i = tpp->left;
		 while(i <= tpp->right && line[i] != ' ')
		 {
	  		i++;
			temp[j++] = line[i];
		 }
		 temp[j] = '\0';
		 push_lable(head, temp);
	  }
	  
   }

   //每次读取五行直到标点符号的密度小于每行三个，（界定规则之后详细探讨）

   char tempstr[100000];
   LineBuf* lbp = *lb;
   //recv tempstr until tpp is NULL
   while(tpp)
   {
	  //
   }
}
*/
LableElem* push_lable(LableElem* le, char* val)
{
   LableElem* p = (LableElem*)malloc(sizeof(LableElem));
   strcpy(p->val, val);
   p->next = NULL;

   if(le->next == NULL)
   {
	  le->next = p;
   }
   else
   {
	  p->next = le->next;
	  le->next = p;
   }

   return le;
}

LableElem* top_lable(LableElem* le)
{
   if(le->next == NULL)
   {
	  return NULL;
   }
   else
   {
	  return le->next;
   }
}

void pop_lable(LableElem* le)
{
   if(le->next == NULL)
   {
	  return;
   }
   else
   {

	  LableElem* p = le->next;
		 le->next = le->next->next;
	  free(p);
   }
}

int get_elem_stack_size(LableElem* head)
{
   LableElem* p = head->next;

   int size = 0;
   while(p)
   {
	  p = p->next;
	  size++;
   }

   return size;
}


void deal_anno(LineBuf** lb)		//跳过注释区域
{
   LineBuf* templf = *lb;
   //增加更详细的跳过策略
   if(mystrstr(templf->str, "<!--") == 1)
   {
	  while(templf && mystrstr(templf->str, "-->") != 1)
	  {
		 templf = templf->next;
	  }
   }
   else
   {
	  return;
   }
   *lb = templf;
}


void deal_script(LineBuf** lb)		//跳过javascript代码
{
   LineBuf* templf = *lb;

   if(mystrstr(templf->str, "<script") ||
		 mystrstr(templf->str, "<SCRIPT>"))
   {
	  while(mystrstr(templf->str, "</SCRIPT>") ||
			mystrstr(templf->str, "</script>"))
	  {
		 templf = templf->next;
	  }
   }
   else
   {
	  return;

   }

   *lb = templf;
}

void free_LablePosPair(LablePosPair* lpp)
{
   LablePosPair* templpp = lpp;
   while(templpp)
   {
	  LablePosPair* q = templpp;
	  templpp = templpp->next;
	  free(q);
   }
}
