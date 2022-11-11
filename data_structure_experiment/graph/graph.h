#define INFINITY 999999

#include <stdio.h>
#include <malloc.h>

typedef char PointType;//顶点数据类型
typedef int LineType;//边的权值类型
typedef struct {
    PointType head;//边的始点
    PointType tail;//边的终点
    LineType value;//边的权值
} Edge;

typedef struct {
    PointType *pointArray;//存储顶点的数组，数组的每个元素是一个char，标识该顶点的名字
    LineType **adjacentMatrix;//邻接矩阵二维数组
    int pointSize;//图的顶点个数
    int lineSize;//图的边数
    Edge *edgeArray;//边的辅助数组，每个元素是一个结构体，标识每个边的起始点和终点
    int *pointSet;//顶点的辅助数组，标识各个顶点所属的联通分量，初始时每个元素的值是自己在数组中下标，表示各顶点自成一个联通分量
} Graph;

Graph *createGraph() {
    printf("请输入总的顶点数：");
    Graph *theGraph = (Graph *) malloc(sizeof(Graph));
    scanf("%d", &(theGraph->pointSize));
    getchar();
    printf("请输入总的边数：");
    scanf("%d", &(theGraph->lineSize));
    getchar();

    //初始化一维的顶点数组和二维的邻接矩阵数组
    theGraph->pointArray = (PointType *) malloc(sizeof(PointType) * (theGraph->pointSize));
    for (int i = 0; i < theGraph->pointSize; i++) {
        int transform = 97 + i;
        char character = (char) transform;
        theGraph->pointArray[i] = character;
    }
    theGraph->adjacentMatrix = (LineType **) malloc(sizeof(LineType *) * (theGraph->pointSize));
    for (int i = 0; i < theGraph->pointSize; i++) {
        theGraph->adjacentMatrix[i] = (LineType *) malloc(sizeof(LineType) * (theGraph->pointSize));
        for (int j = 0; j < theGraph->pointSize; j++) {
            theGraph->adjacentMatrix[i][j] = INFINITY;//每一个边的权值先设为无穷大
        }
    }

    theGraph->edgeArray = (Edge *) malloc(sizeof(Edge) * (theGraph->lineSize));

    //依次设置每个边的权值
    for (int i = 0; i < theGraph->lineSize; i++) {
        printf("输入第%d个边的信息（连续输入边的两个坐标以及相应的权值，所有信息之间用空格分开）：", i + 1);
        int x, y, value;//每个即将要录入边的两个顶点的编号以及相应的边的权值
        scanf("%d %d %d", &x, &y, &value);
        getchar();
        theGraph->adjacentMatrix[x][y] = value;
        theGraph->edgeArray[i].head = theGraph->pointArray[x];
        theGraph->edgeArray[i].tail = theGraph->pointArray[y];
        theGraph->edgeArray[i].value = value;
    }

    theGraph->pointSet = (int *) malloc(sizeof(int) * (theGraph->pointSize));
    for (int i = 0; i < theGraph->pointSize; i++) {
        theGraph->pointSet[i] = i;//有可能设为-1更合适
    }
    return theGraph;
}

//对传入的数组按照其中每个元素的权值大小进行排序
void sortEdge(Edge *theEdgeArray) {

}

//根据传入的字符确定该点对应邻接矩阵的坐标
int locateLine(char headOrTail, int lineSize) {

}

//克鲁斯卡尔算法生成最小生成树
void createMiniSpanTree_Kruskal(Graph *theGraph) {
    sortEdge(theGraph->edgeArray);//将数组edgeArray中的元素按权值大小排序
    for (int i = 0; i < theGraph->lineSize; i++) {
        //遍历edgeArray，确定每个元素所代表的边的始点和终点的编号
        int x = locateLine(theGraph->edgeArray[i].head, theGraph->lineSize);
        int y = locateLine(theGraph->edgeArray[i].tail, theGraph->lineSize);
        int connectedComponent = theGraph->pointSet[x];
        int connectedComponent2 = theGraph->pointSet[y];
        if(connectedComponent!=connectedComponent2)
        {
            printf("%c %c",theGraph->edgeArray[i].head,theGraph->edgeArray[i].tail);
            for (int j = 0; j < theGraph->pointSize; ++j) {
                if(theGraph->pointSet[j]==connectedComponent2)
                    theGraph->pointSet[j]=connectedComponent;
            }
        }

    }

}


