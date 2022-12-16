#include "graph.h"

int main() {
    setbuf(stdout, NULL);//调试时输出到窗口
    Graph *theGraph = createGraph();//用户输入信息，构造图
    createMiniSpanTree_Kruskal(theGraph);//调用克鲁斯卡尔算法生成最小生成树，输出每一条边
    deleteGraph(theGraph);//释放内部各数组所占的空间

    return 0;
}