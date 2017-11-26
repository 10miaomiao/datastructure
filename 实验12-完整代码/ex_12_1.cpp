//邻接矩阵
#include <iostream>
using namespace std; 

typedef char VertexType;             //定义顶点的数据类型
typedef int EdgeType;              //定义边上的权值的数据类型
 
#define MAXVEX  10             //最大顶点数
typedef struct
{
    VertexType vexs[MAXVEX];        //顶点表
    EdgeType arc[MAXVEX][MAXVEX];   //邻接矩阵，存储边
    int numVertexes, numEdges;      //当前图的顶点数和边数
}Graph;
 //定位
int locates(Graph *g,char ch)
{
    int i = 0;
    for(i = 0; i < g->numVertexes; i++)
    {
        if(g->vexs[i] == ch)
        {
            break;
        }
    }
    if(i >= g->numVertexes)
    {
        return -1;
    }
    return i;
}
//使用邻接矩阵存储一个无向网图
void CreateGraph(Graph *g)
{
    int i, j, k, w;
    cout<<"输入顶点数和边数:"<<endl;
    cin>>g->numVertexes>>g->numEdges;
  
    cout<<"请输入顶点名称，每个顶点用单个字母或单个数字表示，并以回车键结束："<<endl;
    for(i = 0; i < g->numVertexes; i++)
    {
		cin>>g->vexs[i];
    }
    cout<<"你输入的顶点是：";
    for(i = 0; i < g->numVertexes; i++)
    {
       cout<<g->vexs[i];
    }
    cout<<endl;
    for(i = 0; i < g->numVertexes; i++)
    {
        for(j = 0; j < g->numVertexes; j++)
        {
			/*1*/if(i==j) g->arc[i][j]=0; //邻接矩阵对角线初始化为每个存储单元为零
			/*2*/else g->arc[i][j]=-1; //邻接矩阵其它存储单元初始化为-1,假设-1是不可能取得的权值
        }
    }
    for(k = 0; k < g->numEdges; k++)
    {
        char vi, vj;
        cout<<"输入边(vi,vj)上的顶点vi名称，顶点vj名称和权值,每个输入后以回键结束"<<endl;
        cin>>vi>>vj>>w;    
        int m = -1;
        int n = -1;
        m = locates(g, vi);//找到顶点vi在顶点表中的下标i
        n = locates(g, vj);//找到顶点vj在顶点表中的下标j
        if(/*3*/n==-1 || m==-1)
        {
            cout<<"there is no this vertex.\n"; //显示输入有错信息
            return;
        }
        g->arc[m][n] = w;	//将邻接矩阵的第i行第j列的元素值置为权值w
        g->arc[n][m] = /*4*/w;  //因为是无向图，矩阵对称
    }
}
//打印图的邻接矩阵
void printGraph(Graph g)
{
    int i, j;
    cout<<"这个邻接矩阵为："<<endl;
    for(i = 0; i < g.numVertexes; i++)
    {
        for(j = 0; j < g.numVertexes; j++)
        {
           cout<<g.arc[i][j]<<"  ";
        }
       cout<<endl;
    }
}
int main()
{		
    
    Graph g;
    CreateGraph(&g); //使用邻接矩阵存储图
	/*5*/printGraph(g); //打印图的邻接矩阵
    return 0;
}
