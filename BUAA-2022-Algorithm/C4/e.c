/*
 * Build a Huffman tree from character frequencies and report
 * the total bit length of the encoded input text.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman树结构
	char c;		
	int weight;					//树节点权重，叶节点为字符和它的出现次数
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL; 		//Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;						//实验步骤 
char INPUT[10000002];

char CODE[MAXSIZE];
int CTOP = -1;
void ergodic(struct tnode *);
	
void statCount();				//步骤1：统计文件中字符频率
void createHTree();				//步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();				//步骤3：根据Huffman树生成Huffman编码				//步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

int main()
{

	statCount();						//实验步骤1：统计文件中字符出现次数（频率）
	createHTree();						//实验步骤2：依据字符频率生成相应的Huffman树
	makeHCode();				   		//实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码

    long long int length = 0;
    int index = 0;
    while(INPUT[index]) {
		length += strlen(HCode[(int)INPUT[index]]);
        index++;
	}
    printf("%lld", length);
    return 0;
} 

//【实验步骤1】开始 

void statCount()
{
	gets(INPUT);
	int index = 0;
    //Ccount[0] = 1;
	while(INPUT[index]) {
		Ccount[(int)INPUT[index]]++;
        index++;
	}
}

//【实验步骤1】结束

//【实验步骤2】开始
//定义新的结构体，用于保存当前节点以及下一个节点地址，即采用链式结构保存节点，方便插入
struct fnode{
	struct tnode *p;
	struct fnode *pNext;
};
//定义一个停止函数判断while跳出，直观一些
int stop(struct fnode *pf, char cc, int wei) {
	if(pf->pNext == NULL)
	return 0;
	if(pf->pNext->p->weight < wei)
	return 1;
	if(pf->pNext->p->weight > wei)
	return 0;
	if(pf->pNext->p->c > cc)
	return 0;
	return 1;
}
//用于插入叶结点
struct fnode *insert1(struct fnode *pRootF, char cc, int wei) {
	struct tnode *p = malloc(sizeof(struct tnode));
	p->c = cc;
	p->weight = wei;
	p->left = p->right = NULL;
	struct fnode *pNew = malloc(sizeof(struct fnode)), *pf = pRootF;
	pNew->p = p;
	pNew->pNext = NULL;
	if(pRootF == NULL)
	return pNew;
	if(pRootF->p->weight > wei || (pRootF->p->weight == wei && (pRootF->p->c > cc))){
		pNew->pNext = pRootF;
		return pNew;
	}
	while(stop(pf, cc, wei)) {
		pf = pf->pNext;
	}
	pNew->pNext = pf->pNext;
	pf->pNext = pNew;
	return pRootF;
}
//用于插入合并后节点
struct fnode *insert2(struct fnode *pRootF, struct fnode *p1, struct fnode *p2) {
	struct tnode *p = malloc(sizeof(struct tnode));
	p->c = -1;  //将非叶节点字符值设置为-1，当个标签
	int wei = p1->p->weight + p2->p->weight;
	p->weight = wei;
	p->left = p1->p;
	p->right = p2->p;
	free(p1);  //释放无用节点
	free(p2);
	struct fnode *pNew = malloc(sizeof(struct fnode)), *pf = pRootF;
	pNew->p = p;
	pNew->pNext = NULL;
	if(pRootF == NULL)
	return pNew;
	if(pRootF->p->weight > wei){
		pNew->pNext = pRootF;
		return pNew;
	}
	while(pf->pNext != NULL && pf->pNext->p->weight <= wei) {
		pf = pf->pNext;
	}
	pNew->pNext = pf->pNext;
	pf->pNext = pNew;
	return pRootF;
}
void createHTree()
{
	struct fnode *fRoot = NULL;
	for(int i = 0; i < 128; i++) {
		if(Ccount[i]) {
			fRoot = insert1(fRoot, (char)i, Ccount[i]);
		}
	}
	while(fRoot->pNext != NULL) {
		fRoot = insert2(fRoot->pNext->pNext, fRoot, fRoot->pNext);
	}
	Root = fRoot->p;
}

//【实验步骤2】结束

//【实验步骤3】开始
//保存当前编码的数组，栈实现


void makeHCode()
{
	ergodic(Root);
	return;
} 
void ergodic(struct tnode *pNodeT) {
	if(pNodeT == NULL)
	return;
	CODE[++CTOP] = '0';
	ergodic(pNodeT->left);
	CODE[CTOP--] = '\0';
	if(pNodeT->c != -1) //仅处理叶结点
	memcpy(&HCode[(int)pNodeT->c][0], CODE, MAXSIZE);
	CODE[++CTOP] = '1';
	ergodic(pNodeT->right);
	CODE[CTOP--] = '\0';
	return;
}
//【实验步骤3】结束
