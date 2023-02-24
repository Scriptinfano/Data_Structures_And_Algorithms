#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct BSTree
{
    int num;
    char name[20];
    char sex[20];
    int age;
    char major[20];
    char school[20];
    struct BSTree* lchild, * rchild;
}BSTree;
int InputBSTree(BSTree* T, int* m);
int CreatBSTree(BSTree* T);
BSTree* FindBSTreeinsert(int num, BSTree* T, int* flag);
BSTree* FindBSTreeequal(int num, BSTree* T, int* flag);
int EditBSTree(BSTree* T);
BSTree* InsertBSTree(BSTree* T);
BSTree* DeleteBSTree(BSTree* T);
BSTree* DelBSTree(int num, BSTree* T, int* flag);
BSTree* Del(BSTree* T);
int SearchBSTree(BSTree* T);
int PrintBSTree(BSTree* T);
int Print(BSTree* T);
int Get_int(void);
int SaveBSTree(BSTree* T);
int Save(FILE* fp, BSTree* T);
int main()
{
    setbuf(stdout,NULL);
    BSTree* T = 0;
    int flag = 0, m = 0;
    while (!(T = (BSTree*)malloc(sizeof(BSTree))))
        continue;
    T->lchild = T->rchild = 0;
    printf("            ---------------------------------------------------------\n");
    printf("            |                                                       |\n");
    printf("            |             ^_^ 欢迎使用校友信息管理系统              |\n");
    printf("            | 每个学生信息包括：学号,姓名,性别,年龄,专业,毕业院校   |\n");
    printf("            ---------------------------------------------------------\n");
    do
    {
        printf("/n1,读入 | 2,编辑 | 3,插入 | 4,删除 | 5,查找(以学号)| 6,输出所有信息 | 0,退出/n操作=");
        flag = Get_int();
        switch (flag)
        {
            case 1: InputBSTree(T, &m); if (m) PrintBSTree(T); break;
            case 2: EditBSTree(T); PrintBSTree(T); break;
            case 3: T = InsertBSTree(T); PrintBSTree(T); break;
            case 4: T = DeleteBSTree(T); PrintBSTree(T); break;
            case 5: SearchBSTree(T); break;
            case 6: PrintBSTree(T); break;
            case 0: break;
            default: printf("/n*********对不起，选择无效！*******/n");
        }
    } while (flag);
    printf("/n您想保存吗？/n||1，保存|0,不保存||/n选择=");
    flag = Get_int();
    if (flag)
        SaveBSTree(T);
    printf("/n谢谢使用，按任意键继续/n");
    getchar();

    return 0;}
int InputBSTree(BSTree* T, int* m)
{
    int flag = 0;
    char address[100];
    char sex[20];
    int age=0;
    char c;
    FILE* fp = 0;
    BSTree* t = 0, * S = 0;
    printf("你想用什么方式读入学生信息？ /n1，键盘输入/n2,从硬盘读取/n选择=");
    flag = Get_int();
    if (flag == 1)
    {
        printf("每个学生信息包括：学号,姓名,性别,年龄,专业,毕业院校,并且学生的学号不能相同!/n");
        printf("第一个学生的学号应是所有学号的中间数,这样效率最高!/n");
        printf("当学号输入非数字时结束/n");
        printf("请输入学号/n学号=");
        if (scanf("%d", &T->num) != 1)
        {
            while (getchar() != '/n')
                continue;
            return 0;
        }
        while (getchar() != '/n')
            continue;
        if (T->num < 0)
        {
            printf("/n学号不能小于0!!!,读入失败!!!/n");
            return 0;
        }
        printf("请输入名字/n名字=");
        gets(T->name);
        printf("请输入性别/n性别=");
        gets(T->sex);
        char sex = c;
        if (c == 'M')
        {
            printf("输入的是男\n");
        }
        else
            printf("输入的是女\n");
        printf("请输入年龄");
        if (T->age < 0)
        {
            printf("/n年龄不能小于0!!!,读入失败!!!/n");
            return 0;
        }


        printf("请输入专业/n专业=");
        gets(T->major);
        printf("请输入毕业院校/n毕业院校=");
        gets(T->school);

        CreatBSTree(T);
    }
    else if (flag == 2)
    {
        printf("请输入要读取文件的地址：/n地址=");
        gets(address);
        if (!(fp = fopen(address, "r")))
        {
            printf("/n********读取失败，文件：%s打不开*********", address);
            return 0;
        }
        fscanf(fp, "/t%d/t%s/t%s/t%d/t%s/t%s", &T->num, T->name, T->sex,T->age, T->major, &T->school);
        while (feof(fp) != 1)
        {
            while (!(t = (BSTree*)malloc(sizeof(BSTree))))
                continue;
            t->lchild = t->rchild = 0;
            fscanf(fp, "/t%d/t%s/t%s/t%d/t%s/t%s", &t->num, t->name, t->sex, t->age,t->major, &t->school);
            flag = 0;
            S = FindBSTreeinsert(t->num, T, &flag);//查询
            if (flag)
            {
                if (t->num < S->num && !S->lchild)
                    S->lchild = t;
                else if (t->num > S->num && !S->rchild)
                    S->rchild = t;
            }
        }
        fclose(fp);
        printf("读取完毕");
    }
    *m = 1;
    return 1;
}
int CreatBSTree(BSTree* T)
{
    BSTree* t = 0, * S = 0;
    char c;
    int m = 0, flag = 0;
    while (1)
    {
        printf("当学号输入非数字时结束/n");
        printf("请输入学号/n学号=");
        if (scanf("%d", &m) != 1)
        {
            while (getchar() != '/n')
                continue;
            return 0;
        }
        while (getchar() != '/n')
            continue;
        if (m < 0)
        {
            printf("/n学号不能小于0!!!,请重新输入!!!/n");
            continue;
        }
        while (!(t = (BSTree*)malloc(sizeof(BSTree))))
            continue;
        t->lchild = t->rchild = 0;
        t->num = m;
        printf("请输入名字/n名字=");
        gets(t->name);
        printf("请输入性别/n性别=");
        gets(t->sex);
        char sex = c;
        if (c == 'M')
        {
            printf("输入的是男\n");
        }
        else
            printf("输入的是女\n");
        printf("请输入年龄");
        if (T->age < 0)
        {
            printf("/n年龄不能小于0!!!,读入失败!!!/n");
            return 0;
        }
        printf("请输入专业/n专业=");
        gets(t->major);
        printf("请输入毕业院校/n毕业院校=");
        gets(T->school);

        S = FindBSTreeinsert(t->num, T, &flag);
        if (flag == 1)
            S->lchild = t;
        else if (flag == 3)
            S->rchild = t;
        else
            printf("/n*********输入失败（可能学号已存在），请重新输入***************/n");
    }
    return 1;
}
BSTree* FindBSTreeinsert(int number, BSTree* T, int* flag)
{
    if (T)
    {
        if (number < T->num && !T->lchild)
        {
            *flag = 1;
            return T;
        }
        else if (number < T->num && T->lchild)
            FindBSTreeinsert(number, T->lchild, flag);
        else if (number > T->num && !T->rchild)
        {
            *flag = 3;
            return T;
        }
        else if (number > T->num && T->rchild)
            FindBSTreeinsert(number, T->rchild, flag);
    }
}
BSTree* FindBSTreeequal(int number, BSTree* T, int* flag)
{
    if (T)
    {
        if (number == T->num)
        {
            *flag = 2;
            return T;
        }
        else if (number < T->num && T->lchild)
            FindBSTreeequal(number, T->lchild, flag);
        else if (number > T->num && T->rchild)
            FindBSTreeequal(number, T->rchild, flag);
    }
}
int EditBSTree(BSTree* T)
{
    BSTree* S = 0, * t = 0; char c;
    int number = 0, flag = 0;
    if (!T)
    {
        printf("/n*******对不起，没有数据能够编辑，请首先输入！*******/n");
        return 0;
    }
    printf("请输入要编辑学生的学号：/n学号=");
    number = Get_int();
    S = FindBSTreeequal(number, T, &flag);
    if (flag == 2)
    {
        printf("/n***********************学号是%d的学生的信息如下：******************/n", number);
        printf("/n学号%d 姓名%s 性别%s  年龄%d  专业%s 毕业院校%s/n", S->num, S->name, S->sex, S->age,S->major, S->school);
        printf("/n************************************************************************/n");
        printf("/n请输入名字/n名字=");
        gets(S->name);
        printf("请输入性别/n性别=");
        gets(S->sex);
        char sex = c;
        if (c == 'M')
        {
            printf("输入的是男\n");
        }
        else
            printf("输入的是女\n");
        printf("请输入年龄");
        if (T->age < 0)
        {
            printf("/n年龄不能小于0!!!,读入失败!!!/n");
            return 0;
        }
        printf("请输入专业/n专业=");
        gets(S->major);
        printf("请输入毕业院校/n毕业院校=");
        gets(S->school);

        return 1;
    }
    else
    {
        printf("****对不起，没有学号是%d的学生************", number);
        printf("/n你想插入他的信息吗？（1，添加，0不添加）/n选择=");
        flag = Get_int();
        if (flag)
        {
            T = InsertBSTree(T);
            return 1;
        }
        else return 0;
    }
}
BSTree* InsertBSTree(BSTree* T)
{
    BSTree* S = 0, * t = 0;
    int flag = 0; char c;
    while (!(t = (BSTree*)malloc(sizeof(BSTree))))
        continue;
    printf("请输入学号/n学号=");
    t->num = Get_int();
    if (t->num < 0)
    {
        printf("/n插入失败!!!,学号不能小于0!!!");
        return 0;
    }
    printf("请输入名字/n名字=");
    gets(t->name);
    printf("请输入性别/n性别=");
    gets(t->sex);
    char sex = c;
    if (c == 'M')
    {
        printf("输入的是男\n");
    }
    else
        printf("输入的是女\n");
    printf("请输入年龄");
    if (T->age < 0)
    {
        printf("/n年龄不能小于0!!!,读入失败!!!/n");
        return 0;
    }
    printf("请输入专业/n专业=");
    gets(t->major);
    printf("请输入毕业院校/n毕业院校=");
    gets(t->school);

    t->lchild = t->rchild = 0;
    if (!T)
    {
        T = t;
        return T;
    }
    S = FindBSTreeinsert(t->num, T, &flag);
    if (flag == 1)
        S->lchild = t;
    else if (flag == 3)
        S->rchild = t;
    else printf("/n插入失败！可能插入的学生信息已经存在/n");
    return T;
}
BSTree* DeleteBSTree(BSTree* T) ///删除操作主函数
{
    int number, flag = 0;
    BSTree* S = 0;
    printf("请输入要删除学生的学号：/n学号=");
    number = Get_int();
    S = DelBSTree(number, T, &flag);
    if (flag == 0)
        printf("/n*******删除失败，没有学号是%d的学生的信息********/n", number);
    return S;
}
BSTree* DelBSTree(int number, BSTree* T, int* flag)//删除操作一级子函数
{
    int m;
    if (!T)
        *flag = 0;
    else if (number == T->num)
    {
        printf("******学号为%d学生的信息如下，确认要删除吗？********/n", number);
        printf("/n学号=%d, 姓名=%s, 性别=%s, 年龄=%d  专业=%s, 毕业院校=%s/n", T->num, T->name, T->sex,T->age, T->major, T->school);
        printf("/n****************************************************/n");
        printf("/n确认要删除吗？/n 1，删除 || 0，取消删除/n选择=");
        m = Get_int();
        if (m == 0)
        {
            *flag = 1;
            return T;
        }
        T = Del(T);
        *flag = 1;
    }
    else if (number < T->num)
        T->lchild = DelBSTree(number, T->lchild, flag);
    else T->rchild = DelBSTree(number, T->rchild, flag);
    return T;
}
BSTree* Del(BSTree* T) //删除操作二级子函数
{
    BSTree* S = 0, * Q;
    if (T->lchild)
    {
        S = T->lchild;
        while (S->rchild)
            S = S->rchild;
        S->rchild = T->rchild;
        Q = T->lchild;
        free(T);
        return Q;
    }
    else
    {
        Q = T->rchild;
        free(T);
        return Q;
    }
}
int SearchBSTree(BSTree* T)
{
    int number, flag = 0;
    BSTree* S = 0;
    printf("请输入要查找学生的学号/n学号=");
    number = Get_int();
    S = FindBSTreeequal(number, T, &flag);
    if (flag == 2)
    {
        printf("***********学号是%d的学生的信息如下：**************/n", number);
        printf("/n学号=%d/t姓名=%s/t性别=%s/t年龄=%d/t专业=%s/t毕业院校=%s/n", S->num, S->name, S->sex, S->age,S->major, S->school);
        printf("/n**********************************************************/n");
        return 1;
    }
    printf("/n******查找失败，没有 学号=%d 学生的信息*******/n", number);
    return 0;
}
int PrintBSTree(BSTree* T)
{
    if (!T)
    {
        printf("/n***********************没有学生信息*************************/n");
        return 0;
    }
    printf("/n***************************学生信息如下：***************************/n");
    Print(T);
    printf("/n********************************************************************/n");
    return 1;
}
int Print(BSTree* T)
{
    if (T)
    {
        Print(T->lchild);
        printf("/n学号=%d/t姓名=%s/t性别=%s/t年龄=%d/t专业=%s/t毕业院校%s", T->num, T->name, T->sex,T->age, T->major, T->school);
        Print(T->rchild);
        return 1;
    }
    return 0;
}
int Get_int(void)
{
    int m;
    while (scanf("%d", &m) != 1)
    {
        while (getchar() != '/n')
            continue;
        printf("/n请输入一个整数!/n输入=");
    }
    while (getchar() == '/n')
        continue;
    return m;
}
int SaveBSTree(BSTree* T)
{
    char address[100];
    FILE* fp = 0;
    printf("请输入保存的地址/n地址=");
    gets(address);
    if (!(fp = fopen(address, "w")))
    {
        printf("/n对不起，打不开%s", address);
        return 0;
    }
    Save(fp, T);
    printf("保存完毕，保存地址是：%s", address);
    fclose(fp);
    return 1;
}
int Save(FILE* fp, BSTree* T)
{
    if (!T) return 0;
    Save(fp, T->lchild);
    fprintf(fp, "/t%d/t%s/t%s/t%s/t%d/n", T->num, T->name, T->sex, T->major, T->school);
    Save(fp, T->rchild);
}

