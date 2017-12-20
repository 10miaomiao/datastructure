#include <iostream>
#include "stdio.h"
#include "stdlib.h"
using namespace std;
#define ERROR 0
#define OK 1
#define OVERFLOW -2
#define MAXSIZE 100000 //用户自己规定排序的数字的长度

typedef int Status;

typedef struct
{
    int   *r; // r[0]闲置
    int   length; //顺序表的总长度
}Sqlist;

//构造一个空线性表
Status InitSqlist(Sqlist &L)											
{
	L.r=(int *)malloc(MAXSIZE*sizeof(int));	 //分配存储空间
	if(!L.r)                                                            
	{
		printf("存储分配失败！");
		exit(0);
	} //存储分配失败
	L.length=0;//初始长度为0
	return OK;
}

//输入待排序整数
Status ScanfSqlist(int &N,Sqlist &L)									
{
	int i;

	cout<<"请输入要排序的元素个数N: "<<endl;
	cin>>N;
	cout<<"请输入"<<N<<"个要排序的整数: "<<endl;
	for(i=1;i<=N;i++)
		cin>>L.r[i]; //输入待排序整数
	
	printf("\n\n");
	L.length=N; //存储线性表的长度
	return OK;
}

//输出排序之后的数据
Status PrintfSqlist(int N,Sqlist L)				
{
	int i;
	
	cout<<"数据个数："<<L.length<<endl;//输出数据个数
	
	cout<<"排序后的数据：(从左向右依次增大)"<<endl;//输出数据
	for(i=1;i<=N;i++)
	cout<<L.r[i]<<"  ";
	cout<<endl;

	return OK;
}

//***************************************************************
//                    直接插入排序
//***************************************************************
Status InsertSort(Sqlist &L)			//参考课件	
{
	int i,j;

	if(L.length==0)
	{
		printf("要排序的数据为空！");
		return ERROR;
	}

	for(i=2;i<=L.length;i++)
	{
		if(L.r[i]<L.r[i-1])  //将L.r[i]插入有序子表	
		{
			L.r[0] = L.r[i]; //复制为监视哨
			j=i-1;
			while( L.r[0]<L.r[j])                                          
			{
				L.r[j+1]=L.r[j];  //记录后移
				j--;
			}
			L.r[j+1] = L.r[0];
		}
	}
	return OK;
}

//***************************************************************
//                      二分插入排序
//***************************************************************
Status BInsertSort(Sqlist &L)			     	
{
	int i,j,mid,low,high;

	if(L.length==0)
	{
		printf("要排序的数据为空！");
		return ERROR;
	}
	
	for(i=2;i<=L.length;i++)
	{
		L.r[0]=L.r[i];  //将L.r[i]暂存在L.r[0]
		low=1;
        high=i-1;		//记录high的初值
		
		while(low<=high)  //在r[low..high]中二分查找有序插入的位置
		{
			mid=(low+high)/2;
			
			if(L.r[0]<L.r[mid])  //插入点在低半区                      
			{
				high=mid-1;
			}
			else 
			{
                low=mid+1;//插入点在高半区
			}
		}//while
		for(j=i-1;j>=low;j--)  //插入点后的数据后移				
		{
            L.r[j+1]=L.r[j];    //插入点后的数据后移										 
		}
		L.r[low]=L.r[0];	  //将数据插入
	}//for
	return OK;
}

/********************************************************************************
                              希尔排序
*********************************************************************************/
                                                                 
Status ShellInsert(Sqlist &L,int dk)			//希尔插入排序 
{			
	int i,j;															//前后位置的增量是dk

	for(i=dk+1;i<=L.length;i++)											//r[0]只是暂存单元，不是哨兵，
	{				
		if(L.r[i]<L.r[i-dk])											//将L.r[i]插入有序增量子表
		{
			L.r[0] = L.r[i];										//暂存至L.r[0]
			for(j=i-dk;j>0 && L.r[0]<L.r[j];j-=dk)
			{
				L.r[j+dk]=L.r[j];										//记录后移,查找插入位置
			}
		    L.r[j+dk] = L.r[0];										//插入
		}
	}
	return OK;
}

Status ShellSort(Sqlist &L,int dlta[5],int t)      //希尔排序 
{		
	int i;

	if(L.length==0)
	{
		printf("要排序的数据为空！");
		return ERROR;
	}

	for(i=0;i<t;i++)
	{
		ShellInsert(L,dlta[i]);			//一趟增量为dlta[k]的插入排序
	}
	return OK;
}


//**************************************************************
//                         冒泡排序
//**************************************************************
Status BubbleSort(Sqlist &L)				
{
	int i,j,t;

	if(L.length==0)
	{
		printf("要排序的数据为空！");
		return ERROR;
	}

	
	for(i=1;i<=L.length-1;i++)											
	{
		for(j=1;j<=L.length-i;j++)
		{
			if(L.r[j]>L.r[j+1])	 //前面的数据>后面数据时
			{		
				t=L.r[j+1];												
				L.r[j+1]=L.r[j];
				L.r[j] = t; //将元素交换
			}
		}
	}
	return OK;
}

//****************************************************
//                   快速排序
//****************************************************

int Partition(Sqlist &L, int low, int high) //交换顺序表中子表L.r[low..high]的记录，使得枢轴记录到位，并返回其所在位置，此时在它之前（后）的记录均不大于它
{
	int pivotkey;  //记录关键字
	L.r[0] = L.r[low]; //用子表的第一个纪录作枢轴纪录 
	pivotkey=L.r[low];  //用枢轴纪录关键字                               
	while (low<high)                                        
	{
		while(low<high && L.r[high]>=pivotkey) 
		{
			high--;
        }
        L.r[low] = L.r[high];       //将比枢轴记录小的记录移到低端
		while(low<high && L.r[low]<=pivotkey) 
		{
			low++;
		}
        L.r[high] = L.r[low];       //将比枢轴记录大的数移到高端
   }
     L.r[low]=L.r[0];  //枢轴记录到位
     return low;
}//Partition函数

void Qsort (Sqlist &L,int low, int high) 
{
	int pivotloc;
	if  (low<high)  //长度大于1，可以进行                      
	{
		pivotloc=Partition(L, low ,high);
		Qsort(L,low,pivotloc-1);   //对低子表递归排序，pivotloc是枢轴位置
		Qsort(L,pivotloc+1,high);  //对高子表递归排序
	}
}//Qsort函数

Status  QuickSort (Sqlist &L) 
{
    if(L.length==0)
	{
		printf("要排序的数据为空！");
		return ERROR;
	}
	Qsort(L,1,L.length);
	return OK;
}//QuickSort



//**********************************************
//                 简单选择排序
//**********************************************
Status ChooseSort(Sqlist &L)					
{
	int i,j,min,t;

	if(L.length==0)
	{
		printf("没有数据！");
		return ERROR;
	}
	
	for(i=1;i<L.length;i++)  //排序的趟数
	{
		min=i;
		for(j=i+1;j<L.length;j++)  //比较第i个元素以及其后的数据中最小的 
		{
			if(L.r[j]<L.r[min])
				min=i;
		}
		
		if(i!=min)  //将最小数据赋值给L.r[i]
		{
			t=L.r[i];
			L.r[i]=L.r[min];
			L.r[min]=t;
		}
	}
	return OK;
}


//**************************************
//                     主函数
//**************************************
int main()
{
	Sqlist L;
	Sqlist L0;
	InitSqlist(L);  //初始化L
	InitSqlist(L0); 
	
	int m,i,t;
	int dlta[10];	          
    int choice;
								//向L中输入元素

	printf("\n   ************************************************************************\n");
	printf("                                                                               \n");
	printf("                                排序算法                            \n");
	printf("                                                                               \n");
	printf("   ***************************************************************************\n");
    printf("   以下是各个排序算法的代号：\n\n");
	printf("       1、直接插入排序      \n");
	printf("       2、二分插入排序      \n");
	printf("       3、希尔排序          \n");
	printf("       4、快速排序\n");
	printf("       5、冒泡排序\n");
	printf("       6、简单选择排序\n");       
    printf("       7、退出该系统\n\n");	
	
	ScanfSqlist(m,L0);	//输入待排序整数
	

	printf("\n");
	printf("       1、直接插入排序      \n");
	printf("       2、二分插入排序      \n");
	printf("       3、希尔排序          \n");
	printf("       4、快速排序\n");
	printf("       5、冒泡排序\n");
	printf("       6、简单选择排序\n");           
    printf("       7、退出该系统\n\n");	
	printf("\n请选择排序的方式,数字1-6: \n");
	
	scanf("%d",&choice);  //选择排序方式赋值choice，用于后面的函数选择
	
	while(choice<1||choice>8)
	{
		printf("输入方式有误。\n请输入1-6选择排序方式，或者选择7退出系统");
		scanf("%d",&choice);
	}
	
	while(choice!=7)
	{
		for(i=1;i<=L0.length;i++)
			L.r[i]=L0.r[i];
		L.length=L0.length;

		switch(choice)
		{
		case 1://直接插入排序
			cout<<"完成直接插入排序"<<endl;	
			InsertSort(L);
			break;
		case 2://二分插入排序
			BInsertSort(L);
			cout<<"完成二分插入排序"<<endl;					                              
			break;
		case 3://希尔排序
			cout<<"请输入希尔排序中增量个数：";
			cin>>t;
			cout<<endl;
			cout<<"请依次输入希尔排序中的增量：";
			for(i=0;i<t;i++)
			cin>>dlta[i];
			ShellSort(L,dlta,t);
			cout<<"完成希尔排序"<<endl;															
			break;
		case 4://快速排序
			QuickSort(L);
			cout<<"完成快速排序"<<endl;									             		 
			break;
		case 5://冒泡排序
			BubbleSort(L);
			cout<<"完成冒泡排序"<<endl;												
			break;
		case 6://简单选择排序
			ChooseSort(L);
			cout<<"完成简单选择排序"<<endl;													
			break;
		case 7://直接退出
			break;
		}
		
		PrintfSqlist(m,L);  //输出数据和L的长度
		
        printf("   本次排序结束。\n");
		printf("  ___________________________________________________________________\n");
    	printf("   继续本系统吗？\n\n");
    	printf("   以下是各个排序算法的代号：\n");
	    printf("       1、直接插入排序\n");
	    printf("       2、二分插入排序\n");
    	printf("       3、希尔排序\n");
    	printf("       4、快速排序\n");
    	printf("       5、冒泡排序\n");
    	printf("       6、简单选择排序\n");          
        printf("       7、退出该系统\n");	

		printf("\n请请输入1-6选择排序方式，或者选择7退出系统:");
		scanf("%d",&choice);
		while(choice<1||choice>7)
		{
			printf("输入方式有误。\n请输入1-6选择排序方式，或者选择7退出系统");
			scanf("%d",&choice);
		}
    }
    
    return 0;
}
