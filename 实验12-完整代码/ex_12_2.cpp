//邻接表
#include <iostream>
using namespace std;
 
#define MAXVEX 1000         //最大顶点数
typedef char VertexType;        //顶点数据的类型
typedef int EdgeType;           //边上的权值的数据类型
 
typedef struct EdgeNode         //边表结点的结构
{   
    int adjvex;				//存储该顶点在顶点表对应的下标
    EdgeType weigth;        //用于存储权值，对于非网图不需要
    EdgeNode *next;      //链域，指向边表的下一个结点
}EdgeNode;
 
typedef struct VertexNode       //顶点表结点的结构
{
    VertexType data;        //顶点值域，存储顶点信息
    EdgeNode *firstedge;        //边表头指针
}VertexNode;
 
typedef struct
{
    VertexNode adjList[MAXVEX];
    int numVertexes, numEdges;  //图中当前顶点数和边数
}GraphList;
 
int Locate(GraphList *g, char ch)
{
    int i;
    for(i = 0; i < MAXVEX; i++)
    {
        if(ch == g->adjList[i].data)
        {
            break;
        }
    }
    if(i >= MAXVEX)
    {
        cout<<"there is no vertex.\n"<<endl;
        return -1;
    }
    return i;
}
 
//建立图的邻接表存储结构
void CreateGraph(GraphList *g)
{
    int i, k;
    EdgeNode *e;
    EdgeNode *f;
    cout<<"输入顶点数和边数:\n";
    cin>>g->numVertexes>>g->numEdges;
    cout<<"请输入顶点,每个顶点用单个字母或单个数字表示，并以回车键结束:"<<endl;
    for(i = 0; i < g->numVertexes; i++)
    {  
        cin>>g->adjList[i].data;          //输入顶点信息
		/*6*/g->adjList[i].firstedge = NULL;          //将边表置为空表
    }
    cout<<"你输入的顶点是：";
    for(i = 0; i < g->numVertexes; i++)
    {
       cout<<g->adjList[i].data;
    }
	cout<<endl;
    //建立边表
    for(k = 0; k < g->numEdges; k++)
    {
        cout<<"输入边(vi,vj)上的顶点vi名称，顶点vj名称和权值,每个输入后以回键结束:"<<endl;
        char vi, vj;
		int w;
        cin>>vi>>vj>>w;
        int m, n;
        m = Locate(g, vi);
        n = Locate(g, vj);
        if(m == -1 || n == -1)
        { 
            cout<<"输入顶点错误!\n";   
            return; 
        }
        //向内存申请空间，生成边表结点
        e =	/*7*/new EdgeNode;
        if(e == NULL)
        {
           cout<<"结点申请失败!\n";
           return;
        }
        e->adjvex = n;   //邻接点在顶点表的下标为n
        e->weigth=w;  //权值为w
		/*8*/e->next=g->adjList[m].firstedge; //将e指针指向当前边表的头指针所指向的结点
		g->adjList[m].firstedge = e;  //当前边表的头指针指向e所指向的结点
        //向内存申请空间，生成边表结点
		f=/*9*/new EdgeNode;
        if(f == NULL)
        {
           cout<<"结点申请失败!\n";
           return;
        }
        f->adjvex = m;
		f->weigth=w;
        f->next = g->adjList[n].firstedge;
        g->adjList[n].firstedge = f;
    }
}
//打印图的邻接表 
void printGraph(GraphList *g)
{
    int i = 0;
    cout<<"你的邻接表为："<<endl;
    while(g->adjList[i].firstedge != NULL && i <g->numVertexes)
    {
        cout<<"顶点:"<<g->adjList[i].data;
        EdgeNode *e = NULL;
        e = g->adjList[i].firstedge;
        while(e != NULL)
        { 
            cout<<"->" ;
            cout<<"("<<e->adjvex;
		    cout<<","<<e->weigth<<")";
		    e = e->next;
        }
        i++;
        cout<<endl;
    }
}
 
int main()
{
    GraphList g;
    CreateGraph(&g);
    printGraph(&g);
    return 0;
}
