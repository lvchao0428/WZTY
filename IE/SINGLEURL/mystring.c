/*************************************************************************
    > File Name: mystring.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Sat Oct 10 17:51:23 2015
 ************************************************************************/

#include"mystring.h"

void whole_str_to_linebuf(char* str, int len, LineBuf* lb)
{
   //把整篇html的源码转换成按行读取的结构中。
   LineBuf* p = lb;
   int i = 0;
<<<<<<< HEAD
   if(!str || len == 0)
   {
	  return;
   }
=======

>>>>>>> 4bbf6f7d3945798cbac5d053fe43d1ce7c87f581
   while(i < len && str[i] != 0)
   {
	  if(str[i] == '\n' || str[i] == '\r')
	  {
		 i++;
	  }
	  char tempstr[100000];
	  memset(tempstr, 0, sizeof(char)*(strlen(tempstr)+1));
	  int line_len = 0;
	  int j = 0;
	  while(str[i] != '\n' && str[i] != '\r' && i < len && str[i] != 0)
	  {
		 tempstr[j++] = str[i++];
	  }
	  tempstr[j] = '\0';
	  LineBuf* q = (LineBuf*)malloc(sizeof(LineBuf));
	  q->next = NULL;
	  q->str = (char*)malloc(sizeof(char)*(strlen(tempstr) + 1));
	  p->next = q;
	  
	  q->before = p;
	  strcpy(q->str, tempstr);
	  p = p->next;

	  
   }
}
<<<<<<< HEAD

=======
>>>>>>> 4bbf6f7d3945798cbac5d053fe43d1ce7c87f581

void filename_tail_clean(char* filename)
{
   int i = 0;
   while(filename[i] != '\0') i++;
   i--;
   while(filename[i] == '\n' || filename[i] == '\r')
   {
	  filename[i] = '\0';
	  i--;
   }

}

int mystrcmp(char* str, char* word)
{
   int i = 0;
   if(!str)
   {
	  return 0;
   }
   if(!word)
   {
	  return 1;
   }
   while(str[i] != '\0')
   {
	  if(character_to_lower(str[i]) != word[i])
	  {
		 return 0;
	  }
	  i++;
   }
   return 1;
}

const char* mystrstri(const char* str, const char* subStr)
{
   if(!str)
   {
	  return NULL;
   }
   int len = strlen(subStr);
   if(len == 0)
   {
	  return NULL;
   }

   while(*str)
   {
	  if(strncasecmp(str, subStr, len) == 0)
	  {
		 return str;
	  }
	  ++str;
   }
   return NULL;
}

int mystrstr(char* father, char* son)
{//测试前面的字符串是否包含后面字符串,返回son在father里面出现的开始位置
   int i = 0;
   int pos = 0;
   //printf("father:%s, son:%s\n", father, son);
   while(father && father[i] != '\0')
   {
	  //printf("i:%d char:%c\n", i, father[i]);
	  int j = 0;
	  if(father[i] == son[j])
	  {
		 pos = i;
		 while(son[j] != '\0')
		 {
			if(character_to_lower(father[i+j]) != son[j])
			{
			   break;
			}
			else
			{
			   j++;
			}
		 }
		 if(son[j] == '\0')
		 {
			return pos;
		 }
	  }
	  i++;
   }
   if(father && father[i] == '\0')
   {
	  return -1;
   }
}

int mylableStrstr(char* father, char* son)	//专门用来寻找标签的字符串查找函数，区分几种特殊标签的混淆
{
   int i = 0;
   int pos = 0;

   //判断是否是<script和<!--
   int is_script = mystrcmp(son, "<script");
   int is_anno = mystrcmp(son, "<!--");
   //
   //
   while(father[i] != '\0')
   {
	  int j = 0;
	  if(character_to_lower(father[i]) == son[j])
	  {
		 if((i > 0 && father[i-1] == '\'' && father[i+1] != '/') || 
			   (is_script && i > 0 && (father[i-1] == '"' || father[i-1] == '\'' || father[i-1] == '\\')))
		 {
			i++;
			continue;
		 }

		 pos = i;
		 while(son[j] != '\0')
		 {
			if(character_to_lower(father[i+j]) != son[j])
			{
			   break;
			}
			else
			{
			   j++;
			}
		 }
		 if(son[j] == '\0')
		 {
			return pos;
		 }
	  }
	  i++;
   }
   if(father[i] == '\0')
   {
	  return -1;
   }
}

int mystrcpy(char* dest, char* from, int begPos, int endPos)
{//把from范围内的字符串拷贝到目标字符串里面，左闭右包
   int i = begPos, j = 0;
   while(from[i] != '\0' && i != endPos)
   {
	  dest[j++] = from[i++];
   }

   dest[j] = '\0';
}


int mystrcpy_with_point(char* dest, char* from, char* begpos,char* endpos)//使用指针标示位置的字符串复制函数
{
   int i = 0;
   while(*begpos != '\0' && begpos != endpos)
   {
	  dest[i++] = *begpos;
	  begpos++;
   }
   dest[i] = '\0';
}

int scope_str_cmp(char* dest, char* from, int dest_beg)
{//从dest的dest_beg开始如果接下来的几个字符和from完全一致，则认为包含
   int i = dest_beg, j = 0;
   int len = strlen(from);
   while(dest[i] && from[j])
   {
	  if(character_to_lower(dest[i]) != from[j])
	  {
		 break;
	  }
	  i++;
	  j++;
   }

   if(j == len)
   {
	  return 1;
   }
   else
   {
	  return 0;
   }
}

int find_comma_num_out(char* line)		//找到里面内容部分的标点数量
{//找到字符串里面目标符号的数量
   
   char comma[4][5] = {
	  {","},
	  {"、"},
	  {"，"},
	  {"。"},
   };
   int comma_num = 0;
   LablePosPair* wordPair = (LablePosPair*)malloc(sizeof(LablePosPair));
   wordPair->next = NULL;
   out_content_scope(line, wordPair);
   LablePosPair* p = wordPair->next;

   while(p)
   {
	  int j = 0;
	  while(j < 4)
	  {
		 comma_num += find_str_with_scope(line, comma[j], p->left, p->right);
		 j++;
	  }
	  p = p->next;
   }
   free_LablePosPair(wordPair); 
   return comma_num;
}


int word_length_get(char* line)		//获得字符串里面的内容长度
{
   LablePosPair* wordLpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   wordLpp->next = NULL;

   out_content_scope(line, wordLpp);
  // test_lpp(wordLpp);
   int wordlenSum = 0;
   LablePosPair* p = wordLpp->next;
   while(p)
   {
	  wordlenSum += (p->right - p->left);
	  p = p->next;
   }
   free_LablePosPair(wordLpp);
   return wordlenSum;
}


int lable_length_get(char* line)	//获得字符串里面的标签长度
{
   LablePosPair* lableLpp = (LablePosPair*)malloc(sizeof(LablePosPair));
   lableLpp->next = NULL;

   find_all_greater_lower(line, lableLpp);

   int lablelenSum = 0;
   LablePosPair* p = lableLpp->next;

   while(p)
   {
	  lablelenSum += (p->right - p->left);
	  p = p->next;
   }
   free_LablePosPair(lableLpp);
   return lablelenSum;
}



int is_word_longer_than_lable(char* line)
{
   int wordTotalLen = 0;
   int lableTotalLen = 0;

   LablePosPair* wordPairVector = (LablePosPair*)malloc(sizeof(LablePosPair));
   LablePosPair* lablePairVector = (LablePosPair*)malloc(sizeof(LablePosPair));

   find_all_greater_lower(line, lablePairVector);
   out_content_scope(line, wordPairVector);

   LablePosPair* p = wordPairVector->next;

   while(p)
   {//求出单词的总长度
	  wordTotalLen += (p->right - p->left);
	  p = p->next;
   }
   p = lablePairVector->next;
   while(p)
   {//求出标签的总长度
	  lableTotalLen += (p->right - p->left);
	  p = p->next;
<<<<<<< HEAD
   }
   free_LablePosPair(wordPairVector);
   free_LablePosPair(lablePairVector);
=======
   }	
>>>>>>> 4bbf6f7d3945798cbac5d053fe43d1ce7c87f581
   //printf("wordlen:%d    lablelen:%d\n", wordTotalLen, lableTotalLen);
   return (wordTotalLen >= lableTotalLen);
}

int find_str_with_scope(char* str, char* word, int begPos, int endPos)
{//返回str里面，在begPos和endPos下标范围内，包含word的个数
   int i = begPos;

   int times = 0;
   while(i < strlen(str) && str[i] != '\0' && i < endPos)
   {
	  //不包含重叠情况，也即，abababa，aba，应return 2；
	  int j = 0;
	  if(character_to_lower(str[i]) == word[j])
	  {
		 while(word[j] != '\0')
		 {
			if(character_to_lower(str[i+j]) != word[j])
			{
			   break;
			}
			else
			{
			   j++;
			}
		 }
		 if(word[j] == '\0' )
		 {
			i+=j;
			times ++;
		 }
	  }
	  i++;
   }

   return times;

}


int mycatNoN(char* dest, char* from)
{//把后面字符串拼接到前面，但是跳过换行符
   int i = 0;
   while(dest[i] != '\0') i++;
   int j =0;
   while(from[j] != '\0')
   {
	  if(from[j] == '\n' || from[j] == '\r') 
	  {
		 j++;
		 continue;
	  }
	  dest[i++] = from[j++];
   }
   dest[i] = '\0';
}

char character_to_lower(char c)
{
   if(c >= 'A' && c <= 'Z')
   {
	  return  c + 32;
   }
   else
   {
	  return c;
   }
}

int find_str_times(char* str, char* word)
{//寻找str里面包含word字符串的数量
   int i = 0;
   int times = 0;
   int len = strlen(str);
   int wordlen = strlen(word);

   //先判断word是否是<script
   int is_script = mystrcmp(word, "<script");
   int is_anno = mystrcmp(word, "<!--");

   if(!is_anno)
   {
	  while(str[i] != '\0' && i < len)
	  {//不包含重叠情况，也即，abababa，aba，应return 2；
		 int j = 0;
		 if(character_to_lower(str[i]) == word[j])
		 {
			if((i > 0 && str[i-1] == '\'' && str[i+1] != '/' )||
				  (is_script && i > 0 && str[i] == '<' && (str[i-1] == '"' || str[wordlen] == '"' || str[i-1] == '\'' || str[wordlen] == '\'' || str[i-1] == '\\')) )

			{
			   i++;
			   continue;
			}
			else
			{
			   while(word[j] != '\0')
			   {//不区分大小写的比较，str里面容许有大写字母
				  if(character_to_lower(str[i+j]) != word[j])
				  {
					 break;
				  }
				  else
				  {
					 j++;
				  }
			   }
			   if(word[j] == '\0')
			   {
				  i+=j;
				  times ++;
			   }
			}

		 }
		 i++;
	  }

   }
   return times;
}

int anno_beg_end_times_fill(char* str, int* begtimes, int* endtimes)
{
   int i = 0;
   int begt = 0, endt = 0;
   int len = strlen(str);
   while(i < len)
   {
	  if(i+3 < len && str[i] == '<' && str[i+1] == '!' && str[i+2] == '-' && str[i+3] == '-')
	  {
		 begt++;
		// printf("begtimes:%d\n", *begtimes);
		// printf("****************************");
		 i+=3;
		 //直接在找到开始标签的位置找结束标签，再次嵌套其中的开始标签就被过滤掉了
		 while(i < len)
		 {
			if(i+2 < len && str[i] == '-' && str[i+1] == '-' && str[i+2] == '>')
			{
			   endt++;
   			   i+=2;
			   break;
			}
			i++;
		 }
	  }
	  if(i+2 < len && str[i] == '-' && str[i+1] == '-' && str[i+2] == '>')
	  {
		 endt++;
	  }
	  i++;
   }

   *begtimes = begt;
   *endtimes = endt;
}


int lable_beg_end_times_fill(char* str, char* beglable, char* endlable, int* begtimes, int* endtimes)
{
   int i = 0;
   int begt = 0, endt = 0;
   int beglableCount = 0, endlableCount = 0;
   int len = strlen(str);
   int nolable = 0;
   
   int count = 0;
   int tempbeg = 0, tempend = 0;
   
   beglableCount = find_str_times(str, beglable);
   endlableCount = find_str_times(str, endlable);
	  
//   printf("str:%s\nbeglable:%s,times:%d, endlable:%s,times:%d\n", str, beglable, beglableCount\
		 , endlable, endlableCount);
   //  return 1;
   if(beglableCount > endlableCount && beglableCount >= 2)
   {//如果两个连续的script标签中间没有结束标签，则第二个为嵌入标签
	  int tempbeg1 = -1, tempbeg2 = -1;
	  tempbeg1 = mystrstr(str, beglable);
	  tempbeg2 = mystrstr(str + tempbeg1 + strlen(beglable) , beglable);
	  int endtimes = -1;
	  if(tempbeg2 != -1)
	  {

		 endtimes = find_str_with_scope(str, endlable, tempbeg1, tempbeg2);
	  }
	  if(endtimes == 0)
	  {
		 beglableCount--;
	  }
	  

   }
   *begtimes = beglableCount;
   *endtimes = endlableCount;
   /*
   //处理两对同样的非法标签
   
   begt = mystrstr(str, beglable);
   endt = return_son_str_pos(str, endlable);
   if(begt != -1)
   {
	  beglableCount++;
	  tempbeg = return_son_str_pos(str + begt, endlable);
	  if(tempbeg != -1)
	  {
		 endt = begt + tempbeg;
	  }
   }
   else if(endt != -1)
   {
	  endlableCount++;
	  tempbeg = mylableStrstr(str + endt, beglable);

   }

   endt = endt > begt ? endt : begt;
   tempbeg = mystrstr(str + endt, beglable);
   //去除第二组标签
   if(tempbeg != -1)
   {
	  begt = tempbeg + endt;
	  beglableCount++;
	  tempend = return_son_str_pos(str + begt, endlable);
	  if(tempend != -1)
	  {
		 endt = tempend + begt;
		 endlableCount++;
	  }
   }
  
   *begtimes = beglableCount;
   *endtimes = endlableCount;
   */
}

int return_son_str_pos(char* father, char* son)
{//返回第一次出现son字符串的结束位置
   int i = 0;
   while(father[i] != '\0')
   {
	  int j = 0;
	  if(father[i] == son[j])
	  {
		 while(son[j] != '\0')
		 {
			if(character_to_lower(father[i+j]) == son[j])
			{
			   j++;
			}
			else
			{
			   break;
			}
		 }
		 if(son[j] == '\0')
		 {
			return i + j;
		 }
	  }
	  i++;
   }
   if(father[i] == '\0')
   {
	  return -1;
   }
}


int print_str(char* str, int beg, int end)
{
   int i = beg;
   while(beg <= end)
   {
	  printf("%c", str[beg]);
	  beg++;
   }
   printf("\n");
   return 1;
}


//去掉> <之间的空格
int despace_betw_more_less(char* str)
{
   int i = 0;
   int j = 0;
   while(str[i] != '\0')
   {
	  if(str[i] == '>')
	  {
		 str[j] = str[i];
		 if(str[i+1] == ' ')
		 {
			i++;
			while(str[i] == ' ')
			{
			  i++; 
			  if(str[i] == '<')
			  {
				 break;
			  }
			}
		 }
	  }
	  else
	  {
		 str[j] = str[i];
		 i++;
		 j++;
	  }
   }
   str[j] = '\0';
}

