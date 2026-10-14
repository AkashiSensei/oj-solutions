/*
 * Rank article.txt sentences by summed non-stopword frequencies using hash tables.
 * Read stopwords.txt, print the top five sentences, and save the requested top N
 * to results.txt; retain this version alongside the closely related large project.
 */

#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define NHASH  3001
#define MULT  37
char Article[7000010];//文章
typedef struct word{//单词 后期考虑字典树
    char alpha_word[30];
    int fre;//出现频率
}word;
typedef struct sentence{//句子 后期考虑桶排序
    char whole_sentence[3000];//完整的将句子存储
    int sum_fre;//句子的总频率
}sentence;
sentence sentence_list[500000];//句子表
char word_temp[30];//temp
int work_out_sum_fre(char sentence_1[]);
int comp(const void*a,const void *b) 
{
    word aa = *(word*)a;
    word bb = *(word*)b;
    return aa.fre-bb.fre;
}
int comp_sentence(const void*a,const void *b) 
{
    sentence aa = *(sentence*)a;
    sentence bb = *(sentence*)b;
    return bb.sum_fre - aa.sum_fre;
}
struct Hash{
	char stopword[20];
	struct Hash *link;
	int flag;
	int frequency;
}s_t[3001]={"\0",NULL,0,0};
struct word_list
{
	char word[20];
	struct Hash *link;
	int flag;
	int frequency;
}w_l[3001]={"\0",NULL,0,0};
void hash(char *str)//放置停词 
{
	unsigned int h=0;
    char *p;
    struct Hash *q;
    for(p=str;*p!='\0';p++)
	{
    	h=MULT*h+*p;
	}
    h=h%NHASH;
    if(s_t[h].flag==0)
	{
    	strcpy(s_t[h].stopword,str);
    	s_t[h].flag=1;
	}
	else
	{
		for(q=&s_t[h];q->link!=NULL;q=q->link);
		q->link=(struct Hash*)malloc(sizeof(struct Hash));
		q=q->link;
		strcpy(q->stopword,str);
		q->link=NULL;
	}
}
void Hash(char *str)//放置非停词 
{
	unsigned int h=0;
    char *p;
    struct word_list *q;
    for(p=str;*p!='\0';p++)
	{
    	h=MULT*h+*p;
	}
    h=h%NHASH;
    if(w_l[h].flag==0)
	{
    	strcpy(w_l[h].word,str);
    	w_l[h].flag=1;
    	w_l[h].frequency=1;
	}
	else
	{
		for(q=&w_l[h];q->link!=NULL;q=q->link)
		{
			if(strcmp(q->word,str)==0)
			{
			q->frequency++;	
			return;
			}
		}
		if(strcmp(q->word,str)==0)
		{
			q->frequency++;	
			return;
		}
		q->link=(struct word_list*)malloc(sizeof(struct word_list));
		q=q->link;
		strcpy(q->word,str);
		q->frequency=1;
		q->link=NULL;
	}
}
int reHash(char *s)//输出频度 
{
	unsigned int h=0;
    char *p;
    struct word_list *q;
    for(p=s;*p!='\0';p++)
	{
    	h=MULT*h+*p;
	}
    h=h%NHASH;
    if(w_l[h].flag==0)
	{
    	return 0;
	}
	else
	{
		for(q=&w_l[h];q!=NULL;q=q->link)
		{
			if(strcmp(s,q->word)==0)
			{
				return q->frequency;
			}
		}
		return 0;
	}
} 
int rehash(char *s)//判断是否停词 
{
	unsigned int h=0;
    char *p;
    struct Hash *q;
    for(p=s;*p!='\0';p++)
	{
    	h=MULT*h+*p;
	}
    h=h%NHASH;
    if(s_t[h].flag==0)
	{
    	return 0;
	}
	else
	{
		for(q=&s_t[h];q!=NULL;q=q->link)
		{
			if(strcmp(s,q->stopword)==0)
			{
				return 1;
			}
			else 
			if(strcmp(s,q->stopword)<0)
			{
				return 0;
			}
		}
		return 0;
	}
}
char uppertolower(char s)
{
    if(s>='A'&&s<='Z')
	{
    	return 'a'+s-'A';
	}
	else
	{
		return s;
	} 
}
int work_out_sum_fre(char sentence_1[])
{
    int sum=0,p;
    int i;
    int lenth=strlen(sentence_1);
    int word_temp_pos=0;
    char al_x;
    for(p=0;p<29;p++)
	{
        word_temp[p]='\0';
    }
    for(i=0;i<lenth;i++){
        if(isalpha(sentence_1[i]))//如果是字母
		{
           
            word_temp[word_temp_pos++]=uppertolower(sentence_1[i]);//记录这个字母
            if(!isalpha(sentence_1[i+1])){
            	word_temp[word_temp_pos]='\0';
			}
        }
        else//不是字母，说明上一个单词结束了
		{
            sum+=reHash(word_temp);//寻找这个单词的频度
            word_temp_pos=0;
            for(p=0;p<29;p++)
			{
                word_temp[p]='\0';
            }
        }
    }
    return sum;
}
int main()
{
    FILE *stop,*in,*out;
    int N,i,Article_lenth,p;
	stop=fopen("stopwords.txt","r");
	in=fopen("article.txt","r");
	Article_lenth=fread(Article,1,7000010,in);
	Article_lenth=strlen(Article);

	char St[20];
	while(fscanf(stop,"%s",St)!=EOF)
	{
		hash(St);
	}
	fclose(in);
	fclose(stop);


	scanf("%d",&N);
	int sentence_pos=0,word_temp_pos=0,single_sentence_pos=0;
	char al_x;
    for(i=0;i<Article_lenth;i++)
	{
        if(single_sentence_pos==0&&Article[i]==' ') continue;
        sentence_list[sentence_pos].whole_sentence[single_sentence_pos++]=Article[i];
        if(isalpha(Article[i]))
		{
            word_temp[word_temp_pos++]=uppertolower(Article[i]);
            if(!isalpha(Article[i+1]))
			{
            	word_temp[word_temp_pos]='\0';
			}
        }
        else
		{
            if(rehash(word_temp)==0&&strlen(word_temp)!=0)
			{
            	Hash(word_temp);
			}
            for(p=0;p<word_temp_pos+1;p++)
			{
                word_temp[p]='\0';
            }
            word_temp_pos=0;
        }
        if(Article[i]=='.'||Article[i]=='?'||Article[i]=='!')
		{
            sentence_pos++;
            single_sentence_pos=0;
        }
    }
    for(i=0;i<sentence_pos;i++)
	{
        sentence_list[i].sum_fre=work_out_sum_fre(sentence_list[i].whole_sentence);
    }
    qsort(sentence_list,sentence_pos,sizeof(sentence_list[1]),comp_sentence);
   
    for(i=0;i<5;i++)
	{
        printf("%d %s\n",sentence_list[i].sum_fre,sentence_list[i].whole_sentence);
    }
    out=fopen("results.txt","w");
    for(i=0;i<N;i++)
	{
        fprintf(out,"%d %s\n",sentence_list[i].sum_fre,sentence_list[i].whole_sentence);
    }
    fclose(out);
    return 0;
}








