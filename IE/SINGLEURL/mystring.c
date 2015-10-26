/*************************************************************************
    > File Name: mystring.c
    > Author: lvchao0428
    > Mail: 410148119@qq.com 
    > Created Time: Sat Oct 10 17:51:23 2015
 ************************************************************************/

#include"mystring.h"

const char* mystrstri(const char* str, const char* subStr)
{
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
   while(father[i] != '\0')
   {
	  int j = 0;
	  if(father[i] == son[j])
	  {
		 pos = i;
		 while(son[j] != '\0')
		 {
			if(father[i+j] != son[j])
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

int scope_str_cmp(char* dest, char* from, int dest_beg)
{
   int i = dest_beg, j = 0;
   int len = strlen(from);
   while(dest[i] != '\0' && from[j])
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
   }	
   printf("wordlen:%d    lablelen:%d\n", wordTotalLen, lableTotalLen);
   return (wordTotalLen >= lableTotalLen);
}

int find_str_with_scope(char* str, char* word, int begPos, int endPos)
{//返回str里面，在begPos和endPos下标范围内，包含word的个数
   int i = begPos;

   int times = 0;
   while(str[i] != '\0' && i < endPos)
   {
	  //不包含重叠情况，也即，abababa，aba，应return 2；
	  int j = 0;
	  if(str[i] == word[j])
	  {
		 while(word[j] != '\0')
		 {
			if(str[i+j] != word[j])
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
   while(str[i] != '\0')
   {//不包含重叠情况，也即，abababa，aba，应return 2；
	  int j = 0;
	  if(character_to_lower(str[i]) == word[j])
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
	  i++;
   }

   return times;
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
			if(father[i+j] == son[j])
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
   while(beg != (beg+end))
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

