#include <iostream>
#include <stdio.h>
#include <malloc.h>
using namespace std;
#define  MAXSIZE 100
typedef int ElemType;	//数据元素的类型为ElemType，将ElemType定义为int类型

/* --------------------结构体定义 ------------------------ */
typedef struct     //三元组的类型定义
{    
    int  row;    //非零元素行号
	int  col;    //非零元素列号
    ElemType  val;	//非零元素值
}tupletype;

typedef struct      //三元组顺序表存储结构定义
{	
    tupletype data[MAXSIZE];		//非零元素的三元组表
    int  rnum;    	//矩阵行数
	int  cnum;   	//矩阵列数
	int  len;   	//矩阵总非零元素个数 
}table;


//按矩阵形式输出
void DispTable(table *m)
{  	
    int i,j,k,e;
    for(i=0;i<m->rnum;i++)
    { 
        for(j=0;j<m->cnum;j++)
        {
            e=0;
            for(k=0;k<m->len;k++)
            {
                if(i==m->data[k].row&&j==m->data[k].col)
                {
                    e=m->data[k].val;
                    break;
                }
            }
            cout<<e<<"\t";
       }
       cout<<endl;
    }
}

//按三元组表形式输出
void print(table *m)
{  	
    cout<<"按三元组表形式输出:\n";
    cout<<"行\t列\t值"<<endl;
    for(int i=0;i<m->len;i++)
    {
        cout<<m->data[i].row<<"\t"
            <<m->data[i].col<<"\t"
            <<m->data[i].val<<endl;
    }
}

//稀疏矩阵转置(普通转置）
void trans(table *ta,table *tb)
{	
    int k,p,q;    	 	 
    tb->rnum=ta->cnum;
    tb->cnum=ta->rnum;
    tb->len=ta->len;
    q=0;	/*q为tb->data的下标*/
    if (tb->len!=0) 
    {   
        for (k=0;k<ta->cnum;k++) 	
            for (p=0;p<ta->len;p++)  /*p为ta->data的下标*/
                if (ta->data[p].col==k) 
                {	  
                    tb->data[q].row=ta->data[p].col;
                    tb->data[q].col=ta->data[p].row;
                    tb->data[q].val=ta->data[p].val;
                    q++;
                }
    }
}


//稀疏矩阵转置（分段定位）
void _trans(table *ta,table *tb)
{    
    int k,q,i,p,j;
    int *num = new int[ta->cnum];
    int *pot = new int[ta->cnum];	
   	tb->rnum=ta->cnum;
	tb->cnum=ta->rnum;
	tb->len=ta->len;
    for (k=0;k<ta->cnum;k++) 	/*初始化num[  ]为0*/
    {	
        num[k]=0;
    }
    for (i=0;i<ta->len;i++) 	/*将三元组表ta扫描一遍，对于其中列号为k的元素，给相应的num[k]加1。*/
    {	
        num[ta->data[i].col]++;	
    }
    pot[0]=0;
    for (k=1;k<ta->cnum;k++)	 /*计算pot[  ]各数组元素的值*/
    {	
        pot[k]=pot[k-1]+num[k-1];
        cout<<pot[k]<<",";	
    }
    for (p=0;p<ta->len;p++) 
    {	
        j=ta->data[p].col;
        q=pot[j];	
        tb->data[q].row=ta->data[p].col;
        tb->data[q].col=ta->data[p].row;
        tb->data[q].val=ta->data[p].val;
        pot[j]++;		 /*矩阵A本列上下一个非零元素的位置，即矩阵B本行上下一个非零元素的位置*/
    }	
}
    
int tableAdd(table M, table N, table *Q)
{
    int i,j,k;
	//矩阵信息
	Q->cnum = M.cnum;
	Q->rnum = M.rnum;
	Q->len = 0;

	while (i < M.len && j < N.len)
	{
		// 如果 i j 指向元素是同一行的元素
		if (M.data[i].row == N.data[j].row)
		{
			// 如果 i 和 j 指向的元素指向的是同一个元素
			if (M.data[i].col == N.data[j].col)
			{
				Q->data[k].row = M.data[i].row;
				Q->data[k].col = M.data[i].col;
				Q->data[k].val = M.data[i].val + N.data[j].val;
				Q->len++;

				i++;
				j++;
				k++;
			}
			// 如果 i 指向元素的列下标大于 j 指向元素的列下标
			// 把下标小（j 指向的元素）的放入到 Q 矩阵中
			else if (M.data[i].col > N.data[j].col)
			{
				Q->data[k].row = N.data[j].row;
				Q->data[k].col = N.data[j].col;
				Q->data[k].val = N.data[j].val;
				Q->len++;

				j++;
				k++;
			}
			// 如果 i 指向元素的列下标小于 j 指向元素的列下标
			// 把下标小（i 指向的元素）的放入到 Q 矩阵中
			else if (M.data[i].col < N.data[j].col)
			{
				Q->data[k].row = M.data[i].row;
				Q->data[k].col = M.data[i].col;
				Q->data[k].val = M.data[i].val;
				Q->len++;

				i++;
				k++;
			}
		}
		// 如果 i 指向的元素行下标大于 j 指向元素的行下标
        // 把行下标小（j 指向的元素）的放入到 Q 矩阵中
		else if (M.data[i].row > N.data[j].row)
		{
			Q->data[k].row = N.data[j].row;
			Q->data[k].col = N.data[j].col;
			Q->data[k].val = N.data[j].val;
			Q->len++;

			k++;
			j++;
		}
		// 如果 i 指向元素行下标小于 j 指向元素的行下标
        // 把行下标小（i 指向的元素）的放入到 Q 矩阵中
		else if (M.data[i].row < N.data[j].row)
		{
			Q->data[k].row = M.data[i].row;
			Q->data[k].col = M.data[i].col;
			Q->data[k].val = M.data[i].val;
			Q->len++;

			i++;
			k++;
		}
	}

	// 如果还有剩余元素，按顺序把元素添加到结果矩阵中
	while (i < M.len)
	{
		Q->data[k].row = M.data[i].row;
		Q->data[k].col = M.data[i].col;
		Q->data[k].val = M.data[i].val;
		Q->len++;

		i++;
		k++;
	}

	while (j < N.len)
	{
		Q->data[k].row = N.data[j].row;
		Q->data[k].col = N.data[j].col;
		Q->data[k].val = N.data[j].val;

		Q->len++;

		j++;
		k++;
	}
}

//查找稀疏矩阵的i行j列的值
ElemType getVal(table *ta,int i,int j){
    for(int k=0;k<ta->len;k++){
        if(ta->data[k].row==i && ta->data[k].col == j){
            return ta->data[i].val;
        }
    }
    return 0;
}

//修改稀疏矩阵的i行j列的值
void editVal(table *ta,int i,int j,ElemType e){
    tupletype t;
    t.row = i;
    t.col = j;
    t.val = e;
    int k = 0;
    while(ta->data[k].row<t.row && k < ta->len){
        k++;
    }
    if(ta->data[k].row==t.row){
        while(ta->data[k].col<t.col && k < ta->len){
            k++;
        }
        if(ta->data[k].col==t.col){
            ta->data[k] = t;
            return;
        }
    }
    for(int a=ta->len;a>k;a--){  //右移，然后插入
        ta->data[a] = ta->data[a-1];
    }
    ta->data[k] = t;
    ta->len++;
    return;
}





void Inittable(table *m)	//对稀疏矩阵的三元组表初始化为0
{
    m->cnum=0;
    m->rnum=0;
    m->len=0;
}

void addTupletype(table *m,int row,int col,ElemType val)
{
    tupletype *t = &m->data[m->len];
    t->row = row;
    t->col = col;
    t->val = val;
    m->len++;
}


/* --------------------- mian函数 -------------------------- */
int main()
{
	char option;
	ElemType x;
    int i;
    table ta,tb,tc;
    tupletype t;

    int row;
    int col;
    ElemType val;
    Inittable(&ta);

    cout<<"输入矩阵的大小(格式 行 列):"<<endl;
    cin>>ta.rnum>>ta.cnum;

    cout<<"输入非零矩阵元素(格式 行 列 值)(行或列为-1结束):"<<endl;
    while(true)
    {
        cin>>row>>col>>val;
        if(row < 0 || col < 0)
            break;
        addTupletype(&ta,row,col,val);
    }

	cout<<endl;
	cout<<"*******************稀疏矩阵运算主菜单*******************"<<endl;
	cout<<" 1.进行稀疏矩阵的普通方法转置"<<endl;
	cout<<" 2.进行稀疏矩阵的分段定位方法转置(即快速转置)"<<endl;
	cout<<" 3.进行稀疏矩阵的加法运算(即a+b)"<<endl;
	cout<<" 4.查找稀疏矩阵的i行j列的值"<<endl;
    cout<<" 5.修改稀疏矩阵的i行j列的值"<<endl;
    cout<<" 6.输出"<<endl;
	cout<<" 0.退出"<<endl;
	cout<<"********************************************************"<<endl;
	while (1)
	{
		cout<<"---------------------------------------- "<<endl;

		cout<<" 选择你要的操作 (0 - 6): ";
		
        //option = getche();	//获取用户输入的操作符号
        cin>>option;
        //option = getchar();
		cout<<endl;

		switch (option)
		{
        case '1':
            cout<<"转置前:"<<endl;
            print(&ta);
            DispTable(&ta);

            trans(&ta,&tb);

            cout<<"转置后:"<<endl;
            print(&tb);
            DispTable(&tb);
			break;
		case '2':
            cout<<"转置前:"<<endl;
            print(&ta);
            DispTable(&ta);

            _trans(&ta,&tb);

            cout<<"转置后:"<<endl;
            print(&tb);
            DispTable(&tb);
			break;
        case '3':
            cout<<"------------矩阵相加------------"<<endl;
            DispTable(&ta);
            cout<<"------------相加------------"<<endl;
            DispTable(&tb);
            cout<<"------------等于------------"<<endl;
            tableAdd(ta,tb,&tc);
            cout<<"转置后:"<<endl;
            DispTable(&tc);
			break;
		case '4':
            cout<<"请输入(格式 行 列):";
            cin>>row>>col;
            cout<<"第"<<row<<"行,第"<<col<<"列的值为："<<getVal(&ta,row,col)<<endl;
			break;
		case '5':
            cout<<"请输入(格式 行 列 值):";
            cin>>row>>col>>val;
            editVal(&ta,row,col,val);
            print(&ta);
            DispTable(&ta);
            break;
        case '6':
            DispTable(&ta);
            break;
		case '0':
			return 0;
		}
    }
    
    return 0;
}