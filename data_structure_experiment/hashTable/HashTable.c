#include "HashTable.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const int examples = 10;//测试样本数
const int max = 10;//随机样本数的最大值
const int min = 1;//随机样本数的最小值
const int hashTableSize = 5;//哈希表表长

//返回随机的不重复的键值数组，第一个参数是返回数组的大小，第二个参数是生成随机数的最小值，第三个参数是生成随机数的最大值
int *createRandomArray(int size, int minNum, int maxNum) {
    int *randomArray = (int *) malloc(sizeof(int) * size);//保存随机数样本的数组
    for (int i = 0; i < size; i++) {
        int tag = 0;
        int randomNumber = rand() % (maxNum - minNum + 1) + minNum;//生成随机数保存到数组中
        //检查之前是否生成了重复的随机数，如果有重复的，则需要重新生成
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

void hashSearchTest(Table *theTable);

bool checkKey(int key);

void elementDeleteTest(Table *theTable);

int main() {
    setbuf(stdout, NULL);//调试时将数据输出到控制台
    srand((unsigned int) time(NULL));//根据时间提供随机数种子
    Table *theTable = createHashTable(hashTableSize);//根据指定的大小创建哈希表

    //生成一个随机数数组，其中每个值作为待插入哈希表对象的键
    int *randomArray = createRandomArray(examples, min, max);
    //开辟字符串数组空间，录入待插入的字符串，这些字符串作为待插入哈希表对象的值
    char **str = (char **) malloc(sizeof(char *) * examples);
    //以下是待测试的字符串，仅在测试时保留，一般情况下采用用户输入的方法
    str[0] = "apple";
    str[1] = "banana";
    str[2] = "car";
    str[3] = "truck";
    str[4] = "rubbish";
    str[5] = "rabbit";
    str[6] = "like";
    str[7] = "mike";
    str[8] = "sense";
    str[9] = "fine";
    /*用户输入的方式录入字符串
    printf("依次输入每一个数据项的字符串数据：");
    for(int i = 0; i < examples; i++){
        gets(str[i]);
    }
    */

    printf("输出生成的关键字与相应的数据：");
    for (int i = 0; i < examples; i++) {
        hashInsert(theTable, randomArray[i], str[i]);//将由整型键值和字符型值的待插入哈希表对象插入哈希表
        printf("(%d,%s) ", randomArray[i], str[i]);
    }

    printf("\n");
    printf("测试首次哈希查找\n");
    hashSearchTest(theTable);
    printf("测试删除哈希元素\n");
    elementDeleteTest(theTable);
    printf("测试删除元素之后的哈希查找");
    hashSearchTest(theTable);

    return 0;
}

void hashSearchTest(Table *theTable) {
    //开始哈希查找
    while (true) {
        printf("输入你要查找的节点的关键字（%d到%d）,输入-1结束输入:", min, max);
        int theNumber = 0;
        scanf("%d", &theNumber);
        getchar();//吞掉换行符
        if (!checkKey(theNumber)) {
            printf("你输入的关键字不在范围之内，请重新输入");
            continue;
        }
        if (theNumber == -1) {
            break;
        } else {
            Node *searchPointer = hashSearch(theTable, theNumber);
            if (searchPointer) {
                printf("找到了，其值为%s\n", searchPointer->info);
            } else printf("未找到\n");
        }
    }
}

void elementDeleteTest(Table *theTable) {
    while (true) {
        printf("输入你要删除的节点的关键字（%d到%d）,输入-1结束输入:", min, max);
        int theNumber = 0;
        scanf("%d", &theNumber);
        getchar();//吞掉换行符
        if (!checkKey(theNumber)) {
            printf("你输入的关键字不在范围之内，请重新输入");
            continue;
        }
        if (theNumber == -1) {
            break;
        } else {
            if (hashElementDelete(theTable, theNumber)) {
                printf("删除成功\n");
            } else printf("未找到待删除元素\n");
        }
    }
}
//检查输入的关键字是否在范围之内，如果不在范围之内则返回false
bool checkKey(int key) {
    if(key==-1)return true;//-1是特例，说明用户要结束输入
    return !(key < min || key > max);
}
