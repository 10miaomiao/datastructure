#include <iostream>
using namespace std;


typedef char ElemType;
//二叉树的定义
typedef struct Node     //结点结构
{
    ElemType data;
    struct Node *lchild, *rchild;
}BNode,*BiTree;    //结点类型别名和指针类型别名


//构造二叉树
BiTree CreateBitree()
{
    BiTree p;	
    ElemType x;
    cin>>x;  //读入一个结点值
    if(x=='#')
        return  NULL;  //读到空
    p=new BNode; 	//生成一个新结点
    p->data=x; 
    p->lchild=CreateBitree(); //递归的构造左子树
    p->rchild=CreateBitree(); //递归的构造右子树
    return p;  //返回本次所生成结点的地址（指针值）
}
//先序遍历
void PreOrder(BiTree T)
{
    if (T==NULL)  
        return; //递归调用的结束条件
    else 
    {
        cout<<T->data; //访问根结点T的数据域
        PreOrder(T->lchild); //前序递归遍历根结点T的左子树
        PreOrder(T->rchild); //前序递归遍历根结点T的右子树  
    }
}
//中序遍历
void InOrder(BiTree T)
{
    if (T==NULL)  
        return; //递归调用的结束条件
    else 
    {
        InOrder(T->lchild); //前序递归遍历根结点T的左子树
        cout<<T->data; //访问根结点T的数据域
        InOrder(T->rchild); //前序递归遍历根结点T的右子树  
    }
}
//后序遍历
void PostOrder(BiTree T)
{
    if (T==NULL)  
        return; //递归调用的结束条件
    else
    {
        PostOrder(T->lchild); //前序递归遍历根结点T的左子树
        PostOrder(T->rchild); //前序递归遍历根结点T的右子树 
        cout<<T->data; //访问根结点T的数据域 
    }
}

//获取二叉树的高度
int BitreeDepth(BiTree T)
{
    int ldepth, rdepth, depth;
    if (T==NULL)
        depth=0;
    else
    {
        ldepth=BitreeDepth(T->lchild);
        rdepth=BitreeDepth(T->rchild);
        depth=1+(ldepth>rdepth?ldepth:rdepth);
    }
    return depth;
}


//获取二叉树的叶子结点数
void CountLeaf(BiTree root,int &count)
{
    if(root==NULL)
        return;
    else 
    {
        if(root->lchild==NULL && root->rchild==NULL)
            count++;    /* 对叶子结点计数*/
        CountLeaf (root->lchild,count);/* 统计左子树 */
        CountLeaf (root->rchild,count); /* 统计右子树 */
    }
}

//获取二叉树的叶子结点
void PreOrderLeaf(BiTree root)
{
    /* 先序遍历输出二叉树中的叶子结点,  root为指向二叉树根结点的指针 */
    if (root==NULL)
        return;
    else 
    {
        if (root->lchild==NULL&&root->rchild==NULL)
		    cout<<root->data;/* 输出叶子结点 */
        PreOrderLeaf(root->lchild); /* 先序遍历左子树 */
        PreOrderLeaf(root->rchild); /* 先序遍历右子树 */
    }
}


int main()
{
    BiTree bt;
    int n=0;
	cout<<"请输入扩充的先序序列:"<<endl;
	bt=CreateBitree();//构造二叉树，返回根结点
	cout<<"二叉树构造完成"<<endl;
	cout<<"先序遍历:";
	PreOrder(bt);
	cout<<endl;
    cout<<"中序遍历:";
	InOrder(bt);
	cout<<endl;
	cout<<"后序遍历:";
	PostOrder(bt);
	cout<<endl;
	cout<<"二叉树的高度:"<<BitreeDepth(bt)<<endl;
	CountLeaf(bt,n);
	cout<<"二叉树的叶子结点数:"<<n<<endl;
	cout<<"二叉树的叶子结点:";
	PreOrderLeaf(bt);
	cout<<endl;
    return 0;
}