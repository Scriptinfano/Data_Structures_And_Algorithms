#include "HashTable.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int examples = 10;//测试样本数
const int max = 10;//随机样本数的最大值
const int min = 1;//随机样本数的最小值
const int hashTableSize = 5;//哈希表表长
#define MAXLENGTH 10 //字符串的最大长度

int *createRandomArray(int size, int minNum, int maxNum) {
    int *randomArray = (int *) malloc(sizeof(int) * size);//保存随机数样本的数组
    for (int i = 0; i < size; i++) {
        int tag = 0;
        int randomNumber = rand() % (maxNum - minNum + 1) + minNum;//生成随机数保存到数组中
        for (int j = 0; j < i; j++) {
            if (randomArray[j] == randomNumber) {
                tag = 1;
                break;
            }
        }
        if (tag == 1) {
            i--;
            continue;
        } else randomArray[i] = randomNumber;
    }
    return randomArray;
}

int main() {
    setbuf(stdout, NULL);//调试时将数据输出到控制台
    srand((unsigned int) time(NULL));//根据时间提供随机数种子
    Table *theTable = createHashTable(hashTableSize);//创建哈希表

    //生成一个随机数数组，该数组中没有重复的数字
    int *randomArray = createRandomArray(examples, min, max);
    //char str[examples][MAXLENGTH];
    char **str = (char **) malloc(sizeof(char *) * examples);
    str[0]="apple";
    str[1]="banana";
    str[2]="car";
    str[3]="truck";
    str[4]="rubbish";
    str[5]="rabbit";
    str[6]="like";
    str[7]="mike";
    str[8]="sense";
    str[9]="fine";

/*
    printf("依次输入每一个数据项的字符串数据：");
    for(int i = 0; i < examples; i++){
        gets(str[i]);
    }
*/


    printf("输出生成的关键字与相应的数据：");
    for (int i = 0; i < examples; i++) {
        hashInsert(theTable, randomArray[i], str[i]);
        printf("(%d,%s) ", randomArray[i], str[i]);
    }
    printf("\n");

    //开始哈希查找
    while (true) {
        printf("输入你要查找的节点的关键字（%d到%d）,输入-1结束输入:", min, max);
        int theNumber = 0;
        scanf("%d", &theNumber);
        getchar();
        printf("输入你要查找的节点的数据(长度不得大于10):");
        char str[MAXLENGTH];
        gets(str);//gets()会读取并丢弃换行符，无需使用getchar()吞掉换行符
        if (theNumber == -1) {
            break;
        } else if (theNumber > max || theNumber < min) {
            printf("查询的关键字不在范围之内\n");
            continue;
        } else {
            Node *theSearchNode = createNode(theNumber, str);
            if (hashSearch(theTable, theSearchNode)) {
                printf("找到了\n");
            } else printf("未找到\n");
        }
    }


    return 0;
}