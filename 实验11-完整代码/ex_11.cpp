#include <iostream>
using namespace std;
#define MAX 50
#define MAXNUM 60
typedef struct	//哈夫曼树结点结构
{
	char data;
	int weight;
	int parent;
	int lchild;
	int rchild;
}HuffNode;

typedef struct
{
	char cd[MAX];	//存放字符的编码
	int start;	//编码的起始位置

}HuffCode;

void Select(HuffNode huffTree[],int k,int &i1,int &i2) 
{
    /*选择根结点权值最小的两个结点。*/  
	int i,j;
    for(i=0;i<k;i++)
        if(huffTree[i].parent ==-1)	
        {
            i1=i;
            break;
        }
    for(j=i+1;j<k;j++)
        if(huffTree[j].parent ==-1)	
        {
            i2=j;
            break;
        }
    for(i=0;i<k;i++)
        if((huffTree[i].parent==-1)&&(huffTree[i].weight<huffTree[i1].weight)&&(i2!=i))
        {
            i1=i;
        }
    for(j=0;j<k;j++)
        if((huffTree[j].parent==-1)&&(huffTree[j].weight<huffTree[i2].weight)&&(i1!=j))
        {
            i2=j;
        }
    }

void HuffmanTree(HuffNode huffTree[],int n)
{
    /*构造哈夫曼树huffTree [n]， w[ ]存放n个权值。*/  
	int i,k;
    for (i = 0; i <2*n-1; i++)
    {		
        huffTree [i].parent = -1;
        huffTree [i].lchild = -1;
        huffTree [i].rchild = -1;   
    }

    for (k = n; k < 2*n-1; k++) {	
        int i1,i2;
        Select(huffTree, k,i1, i2); 
        /* 在 huffTree [0] ~ huffTree [k-1] 的范围内选择两个parent为-1且
        weight最小的结点，其序号分别赋值给i1、i2返回 */
        huffTree[k].weight = huffTree[i1].weight+huffTree[i2].weight;
        huffTree[i1].parent = k; huffTree[i2].parent = k; 
        huffTree[k].lchild = i1; huffTree[k].rchild = i2;
    }
}
/*Encoding函数基本思想：从哈夫曼树的叶结点ht[i]出发，通过结点的parent值，找到其双亲结点
ht[f]，通过ht[f]的lchild和rchild值，可知ht[i]是ht[f]的左孩子还是右孩子，若是左孩子，生成编码号0，
若是右孩子，生成编码号1，编码号存在数组cd[start]中，然后把ht[f]作为出发点，重复上述过程，直到找到树根
为止。显然，这样得到的编码序列与要求的编码序列相反，为了得到正确的编码，把最先生成的编码号存到数组第n
个位置处，再次生成的编码号存到数组的第n-1位置，以此类推，用变量start指示编码在数组cd中的起始位置，
start初值为n，每生成一个编码，start的值减1*/
void Encoding(HuffNode ht[],HuffCode hcd[],int n)
{
    HuffCode d;
    int i,k,f,c;
    for(i=0;i<n;i++)
    {
        d.start=n+1;
        c=i;
        f=ht[i].parent;
        while(f!=-1)
        {
            if(ht[f].lchild==c)
            {	d.start--;d.cd[d.start]='0';}
            else
            {
                d.start--;d.cd[d.start]='1';
            }
            c=f;
            f=ht[f].parent;
        }
        hcd[i]=d;
    }
    cout<<"输出哈夫曼编码"<<endl;
    for(i=0;i<n;i++)
    {
        cout<<ht[i].data<<":";
        for(k=hcd[i].start;k<=n;k++)
        {
            cout<<hcd[i].cd[k];
        }
        cout<<endl;
    }
}


int main()
{
	int n,i;
	HuffNode huffTree[MAXNUM];
	HuffCode hcd[MAXNUM];
	cout<<"请输入字符个数"<<endl;
	cin>>n;
	for(i=0;i<n;i++)
	{
		cout<<"输入第"<<i+1<<"个字符:";
		cin>>huffTree[i].data;
		cout<<"输入第"<<i+1<<"个字符的权值:";
		cin>>huffTree[i].weight;
	}

	HuffmanTree(huffTree,n);

	Encoding(huffTree,hcd,n);
    
    return 0;
}