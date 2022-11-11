#define INFINITY 999999

#include <stdio.h>
#include <malloc.h>

typedef char PointType;//������������
typedef int LineType;//�ߵ�Ȩֵ����
typedef struct {
    PointType head;//�ߵ�ʼ��
    PointType tail;//�ߵ��յ�
    LineType value;//�ߵ�Ȩֵ
} Edge;

typedef struct {
    PointType *pointArray;//�洢��������飬�����ÿ��Ԫ����һ��char����ʶ�ö��������
    LineType **adjacentMatrix;//�ڽӾ����ά����
    int pointSize;//ͼ�Ķ������
    int lineSize;//ͼ�ı���
    Edge *edgeArray;//�ߵĸ������飬ÿ��Ԫ����һ���ṹ�壬��ʶÿ���ߵ���ʼ����յ�
    int *pointSet;//����ĸ������飬��ʶ����������������ͨ��������ʼʱÿ��Ԫ�ص�ֵ���Լ����������±꣬��ʾ�������Գ�һ����ͨ����
} Graph;

Graph *createGraph() {
    printf("�������ܵĶ�������");
    Graph *theGraph = (Graph *) malloc(sizeof(Graph));
    scanf("%d", &(theGraph->pointSize));
    getchar();
    printf("�������ܵı�����");
    scanf("%d", &(theGraph->lineSize));
    getchar();

    //��ʼ��һά�Ķ�������Ͷ�ά���ڽӾ�������
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
            theGraph->adjacentMatrix[i][j] = INFINITY;//ÿһ���ߵ�Ȩֵ����Ϊ�����
        }
    }

    theGraph->edgeArray = (Edge *) malloc(sizeof(Edge) * (theGraph->lineSize));

    //��������ÿ���ߵ�Ȩֵ
    for (int i = 0; i < theGraph->lineSize; i++) {
        printf("�����%d���ߵ���Ϣ����������ߵ����������Լ���Ӧ��Ȩֵ��������Ϣ֮���ÿո�ֿ�����", i + 1);
        int x, y, value;//ÿ������Ҫ¼��ߵ���������ı���Լ���Ӧ�ıߵ�Ȩֵ
        scanf("%d %d %d", &x, &y, &value);
        getchar();
        theGraph->adjacentMatrix[x][y] = value;
        theGraph->edgeArray[i].head = theGraph->pointArray[x];
        theGraph->edgeArray[i].tail = theGraph->pointArray[y];
        theGraph->edgeArray[i].value = value;
    }

    theGraph->pointSet = (int *) malloc(sizeof(int) * (theGraph->pointSize));
    for (int i = 0; i < theGraph->pointSize; i++) {
        theGraph->pointSet[i] = i;//�п�����Ϊ-1������
    }
    return theGraph;
}

//�Դ�������鰴������ÿ��Ԫ�ص�Ȩֵ��С��������
void sortEdge(Edge *theEdgeArray) {

}

//���ݴ�����ַ�ȷ���õ��Ӧ�ڽӾ��������
int locateLine(char headOrTail, int lineSize) {

}

//��³˹�����㷨������С������
void createMiniSpanTree_Kruskal(Graph *theGraph) {
    sortEdge(theGraph->edgeArray);//������edgeArray�е�Ԫ�ذ�Ȩֵ��С����
    for (int i = 0; i < theGraph->lineSize; i++) {
        //����edgeArray��ȷ��ÿ��Ԫ��������ıߵ�ʼ����յ�ı��
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


