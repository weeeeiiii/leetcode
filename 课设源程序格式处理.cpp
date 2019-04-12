#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//保留字表
static char reserveWord[32][20] = {
        "auto", "break", "case", "char", "const", "continue",
        "default", "do", "double", "else", "enum", "extern",
        "float", "for", "goto", "if", "int", "long",
        "register", "return", "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
};      // 1<=syn<=32
//界符运算符表
static char operatorOrDelimiter[36][10] = {
        "+", "-", "*", "/", "<", "<=", ">", ">=", "=", "==",
        "!=", ";", "(", ")", "^", ",", "\"", "\'", "#", "&",
        "&&", "|", "||", "%", "~", "<<", ">>", "[", "]", "{",
        "}", "\\", ".", "\?", ":", "!"
};    // 33<=syn<=68  (--45  ,--48  ;--44  {--62  )--46  }--43
static char operator_name[36][20] = {
        "加号", "减号", "乘号", "除号", "小于符", "小于等于符", "大于符", "大于等于符", "赋值符", "关系运算符",
        "关系运算符", "分号", "圆括号", "圆括号", "位异或", "逗号", "双引号", "单引号", "井号", "位与",
        "逻辑与", "位或", "逻辑或", "取余符", "单目运算符", "位运算符", "位运算符", "方括号", "方括号", "大括号",
        "大括号", "反斜杠", "小数点", "问号", "冒号", "感叹号"
};
/*常数99--整型数值，常数98--无符号整型数值，常数97--长整型数值，常数96--无符号长整型，
  常数95--双精度型（double），常数94--单精度浮点（float），常数93--字符，常数92--字符串，常数100--标识符*/

static char IDentifier[1000][50] = {""};    //存放标识符
char resourceProject[10000];     //存放输入的源程序
char token[20] = "";          //每次扫描的时候存放已经扫描的结果
int syn = -1;                  //syn为种别码
int pProject = 0;              //源程序指针，始终指向当前源程序待扫描位置
int get_token[10000];       //存放词法分析后的源程序
int w;                      //为语法分析当前单词的种别码
char token_text[10000][50] = {""};     //存放语法分析单词的值
char form[50] = "";
char token_0[50] = "";
int m = 0;
int num = 0;                 //记录当前语法分析读到的单词位置
int errors = 0;
char expretion[100][20] = {""};   //用于存放表达式
int ex = 0;                  //存放的表达式数目
int column = 1;               //报出哪一行错误
FILE *fp2;
char Ext[100][50] = {""};       //存放全局变量
int count_ext = 0;              //记录全局变量的总数
char Local[100][50] = {""};     //存放局部变量
int count_local = 0;            //记录局部变量的总数
char Formal[100][50] = {""};    //存放形参
int count_formal = 0;           //记录形参的总数
char define_1[100][20] = {""};
char define_2[100][20] = {""};
int define_num = 0;             //define定义的数目
char include_file[50][20]={""}; //文件包含的数组
int count_i=0;            //文件包含的数字

typedef struct BiTNode {
    char name[50];      //节点名称
    struct BiTNode *first_child, *second_child, *third_child;
} BiTNode, *BiTree;

//打印相关辅助信息
void put(char ch[])
{
    if(strcmp(ch,"int")==0||strcmp(ch,"float")==0||strcmp(ch,"double")==0||strcmp(ch,"char")==0) //若为关键字，打印类型
    {
        printf("类型：");
        return;
    }
    for(int i=0;i<count_ext;i++)          //若为变量，则打印ID
    {
        if(strcmp(Ext[i],ch)==0)
        {
            printf("ID:");
            return;
        }
    }
    for(int i=0;i<count_local;i++)
    {
        if(strcmp(Local[i],ch)==0)
        {
            printf("ID:");
            return;
        }
    }
    for(int i=0;i<count_formal;i++)
    {
        if(strcmp(Formal[i],ch)==0)
        {
            printf("ID:");
            return;
        }
    }
}

//缩进编排生成源程序文件
void source_program(BiTNode *r, int numbers) {
    if (r != NULL) {
        BiTNode *root;
        if (strcmp(r->name, "外部定义序列") == 0) {
            root = r->first_child;
        } else if (strcmp(r->name, "复合语句") == 0) {
            root = r;
        }
        if (root == NULL) return;
        if (strcmp(root->name, "外部变量定义") == 0)           //若为外部变量定义
        {
            fprintf(fp2, "%s ", root->first_child->name);
            printf("%s ", root->first_child->name);
            BiTNode *t = root->second_child;
            while (t != NULL && strcmp(t->name, "变量序列") == 0) {
                if (t->second_child != NULL && strcmp(t->second_child->name, "变量序列") == 0) {
                    fprintf(fp2, "%s,", t->first_child->name);
                    printf("%s,", t->first_child->name);
                    t = t->second_child;
                } else {
                    fprintf(fp2, "%s;\n", t->first_child->name);
                    printf("%s;\n", t->first_child->name);
                    t = t->second_child;
                }
            }
        }

        if (strcmp(root->name, "函数定义") == 0)              //若为函数定义
        {
            fprintf(fp2, "%s ", root->first_child->name);
            fprintf(fp2, "%s(", root->second_child->name);
            printf("%s ", root->first_child->name);
            printf("%s(", root->second_child->name);
            BiTNode *p = root->second_child->first_child;
            if (p == NULL) {
                fprintf(fp2, ")");
                printf(")");
            } else {
                while (p != NULL && strcmp(p->name, "形参序列") == 0) {
                    if (p->second_child != NULL && strcmp(p->second_child->name, "形参序列") == 0) {
                        fprintf(fp2, "%s %s,", p->first_child->first_child->name, p->first_child->second_child->name);
                        printf("%s %s,", p->first_child->first_child->name, p->first_child->second_child->name);
                        p = p->second_child;
                    } else {
                        fprintf(fp2, "%s %s)", p->first_child->first_child->name, p->first_child->second_child->name);
                        printf("%s %s)", p->first_child->first_child->name, p->first_child->second_child->name);
                        break;
                    }
                }
            }
            if (root->third_child == NULL) {
                fprintf(fp2, ";\n");
                printf(";\n");
            } else {
                fprintf(fp2, "\n{\n");
                printf("\n{\n");
                BiTNode *r = root->third_child->first_child;         //局部变量定义序列结点
                while (r != NULL && strcmp(r->name, "局部变量定义序列") == 0) {
                    for (int i = 0; i < numbers + 4; i++) {
                        fprintf(fp2, " ");
                        printf(" ");
                    }
                    fprintf(fp2, "%s ", r->first_child->first_child->name);
                    printf("%s ", r->first_child->first_child->name);
                    BiTNode *t = r->first_child->second_child;
                    while (t != NULL && strcmp(t->name, "变量名序列") == 0) {
                        if (t->second_child != NULL && strcmp(t->second_child->name, "变量名序列") == 0) {
                            fprintf(fp2, "%s,", t->first_child->name);
                            printf("%s,", t->first_child->name);
                            t = t->second_child;
                        } else {
                            fprintf(fp2, "%s;\n", t->first_child->name);
                            printf("%s;\n", t->first_child->name);
                            t = t->second_child;
                        }
                    }
                    r = r->second_child;
                }

                BiTNode *m = root->third_child->second_child;
                while (m != NULL && strcmp(m->name, "语句序列") == 0) {
                    BiTNode *r = m->first_child;
                    if (r != NULL && strcmp(r->name, "局部变量定义序列") == 0) {
                        while (r != NULL && strcmp(r->name, "局部变量定义序列") == 0) {
                            for (int i = 0; i < numbers + 4; i++) {
                                fprintf(fp2, " ");
                                printf(" ");
                            }
                            fprintf(fp2, "%s ", r->first_child->first_child->name);
                            printf("%s ", r->first_child->first_child->name);
                            BiTNode *t = r->first_child->second_child;
                            while (t != NULL && strcmp(t->name, "变量名序列") == 0) {
                                if (t->second_child != NULL && strcmp(t->second_child->name, "变量名序列") == 0) {
                                    fprintf(fp2, "%s,", t->first_child->name);
                                    printf("%s,", t->first_child->name);
                                    t = t->second_child;
                                } else {
                                    fprintf(fp2, "%s;\n", t->first_child->name);
                                    printf("%s;\n", t->first_child->name);
                                    t = t->second_child;
                                }
                            }
                            r = r->second_child;
                        }
                    } else if (m->first_child != NULL && strcmp(m->first_child->name, "do-while语句") == 0) {
                        for (int i = 0; i < numbers + 4; i++)       //打印空格
                        {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        printf("do\n");
                        fprintf(fp2,"do\n");
                        for (int i = 0; i < numbers + 4; i++)       //打印空格
                        {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        printf("{\n");
                        fprintf(fp2,"{\n");
                        source_program(m->first_child->first_child, numbers + 8);
                        for (int i = 0; i < numbers + 4; i++)       //打印空格
                        {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        printf("%s;\n", m->first_child->second_child->first_child->name);
                        fprintf(fp2,"%s;\n", m->first_child->second_child->first_child->name);
                    } else if (m->first_child != NULL && strcmp(m->first_child->name, "while语句") == 0) {
                        for (int i = 0; i < numbers + 4; i++)       //打印空格
                        {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        fprintf(fp2, "while(%s)\n", m->first_child->first_child->name);
                        printf("while(%s)\n", m->first_child->first_child->name);
                        for (int i = 0; i < numbers + 4; i++) {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        fprintf(fp2, "{\n");
                        printf("{\n");
                        source_program(m->first_child->second_child, numbers + 8);
                    }

                    else if (m->first_child != NULL && strcmp(m->first_child->name, "if-else子句") == 0)
                    {
                        for (int i = 0; i < numbers + 4; i++)
                        {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        fprintf(fp2, "if(%s)\n", m->first_child->first_child->name);
                        printf("if(%s)\n", m->first_child->first_child->name);
                        if(m->first_child->second_child!=NULL&&strcmp(m->first_child->second_child->name,"复合语句")==0)
                        {
                            for (int i = 0; i < numbers + 4; i++)
                            {
                                fprintf(fp2, " ");
                                printf(" ");
                            }
                            printf("{\n");
                            fprintf(fp2,"{\n");
                            source_program(m->first_child->second_child,numbers+8);       //处理if子句
                        }
                        else
                        {
                            for (int i = 0; i < numbers + 8; i++)
                            {
                                fprintf(fp2, " ");
                                printf(" ");
                            }
                            printf("%s;\n",m->first_child->second_child->name);
                            fprintf(fp2,"%s;\n",m->first_child->second_child->name);
                        }

                        BiTNode *r=m->first_child->third_child;                       //处理else语句
                        while(r!=NULL)
                        {
                            if(strcmp(r->name,"else-if子句")==0)
                            {
                                for (int i = 0; i < numbers + 4; i++)
                                {
                                    fprintf(fp2, " ");
                                    printf(" ");
                                }
                                printf("else if(%s)\n",r->first_child->name);
                                fprintf(fp2,"else if(%s)\n",r->first_child->name);
                                if(r->second_child!=NULL&&strcmp(r->second_child->name,"复合语句")==0)
                                {
                                    for (int i = 0; i < numbers + 4; i++)
                                    {
                                        fprintf(fp2, " ");
                                        printf(" ");
                                    }
                                    printf("{\n");
                                    fprintf(fp2,"{\n");
                                    source_program(r->second_child,numbers+8);
                                    r=r->third_child;
                                }
                                else
                                {
                                    for (int i = 0; i < numbers + 8; i++)
                                    {
                                        fprintf(fp2, " ");
                                        printf(" ");
                                    }
                                    printf("%s;\n",r->second_child->name);
                                    fprintf(fp2,"%s;\n",r->second_child->name);
                                    r=r->third_child;
                                }
                            }
                            else
                            {
                                for (int i = 0; i < numbers + 4; i++)
                                {
                                    fprintf(fp2, " ");
                                    printf(" ");
                                }
                                printf("else\n");
                                fprintf(fp2,"else\n");
                                if(r->second_child!=NULL&&strcmp(r->second_child->name,"复合语句")!=0)
                                {
                                    for (int i = 0; i < numbers + 8; i++)
                                    {
                                        fprintf(fp2, " ");
                                        printf(" ");
                                    }
                                    printf("%s;\n",r->second_child->name);
                                    fprintf(fp2,"%s;\n",r->second_child->name);
                                    break;
                                }
                                else
                                {
                                    for (int i = 0; i < numbers + 4; i++)
                                    {
                                        fprintf(fp2, " ");
                                        printf(" ");
                                    }
                                    printf("{\n");
                                    fprintf(fp2,"{\n");
                                    source_program(r->second_child,numbers+8);
                                    break;
                                }
                            }
                        }
                    }


                    else if (m->first_child != NULL && strcmp(m->first_child->name, "for语句") == 0) {
                        for (int i = 0; i < numbers + 4; i++) {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        fprintf(fp2, "for(%s;%s;%s)\n", m->first_child->first_child->first_child->name,
                                m->first_child->first_child->second_child->name,
                                m->first_child->first_child->third_child->name);
                        printf("for(%s;%s;%s)\n", m->first_child->first_child->first_child->name,
                               m->first_child->first_child->second_child->name,
                               m->first_child->first_child->third_child->name);
                        for (int i = 0; i < numbers + 4; i++) {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        fprintf(fp2, "{\n");
                        printf("{\n");
                        BiTNode *i = m->first_child->second_child;
                        source_program(i, numbers + 8);
                    } else if (m->first_child != NULL && strcmp(m->first_child->name, "return语句") == 0) {
                        for (int i = 0; i < numbers + 4; i++) {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        fprintf(fp2, "return %s;\n", m->first_child->first_child->name);
                        printf("return %s;\n", m->first_child->first_child->name);
                    } else {
                        for (int i = 0; i < numbers + 4; i++) {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        fprintf(fp2, "%s;\n", m->first_child->name);
                        printf("%s;\n", m->first_child->name);
                    }
                    m = m->second_child;
                }
                fprintf(fp2, "}\n");
                printf("}\n");
            }
        }
        if (strcmp(root->name, "复合语句") == 0) {
            BiTNode *r = root->first_child;
            while (r != NULL && strcmp(r->name, "局部变量定义序列") == 0)        //局部变量定义序列结点
            {
                for (int i = 0; i < numbers; i++) {
                    fprintf(fp2, " ");
                    printf(" ");
                }
                fprintf(fp2, "%s ", r->first_child->first_child->name);
                printf("%s ", r->first_child->first_child->name);
                BiTNode *t = r->first_child->second_child;
                while (t != NULL && strcmp(t->name, "变量名序列") == 0) {
                    if (t->second_child != NULL && strcmp(t->second_child->name, "变量名序列") == 0) {
                        fprintf(fp2, "%s,", t->first_child->name);
                        printf("%s,", t->first_child->name);
                        t = t->second_child;
                    } else {
                        fprintf(fp2, "%s,", t->first_child->name);
                        printf("%s;\n", t->first_child->name);
                        t = t->second_child;
                    }
                }
                r = r->second_child;
            }

            BiTNode *m = root->second_child;
            while (m != NULL && strcmp(m->name, "语句序列") == 0) {
                BiTNode *r = m->first_child;
                if (r != NULL && strcmp(r->name, "局部变量定义序列") == 0) {
                    while (r != NULL && strcmp(r->name, "局部变量定义序列") == 0) {
                        for (int i = 0; i < numbers; i++) {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        fprintf(fp2, "%s ", r->first_child->first_child->name);
                        printf("%s ", r->first_child->first_child->name);
                        BiTNode *t = r->first_child->second_child;
                        while (t != NULL && strcmp(t->name, "变量名序列") == 0) {
                            if (t->second_child != NULL && strcmp(t->second_child->name, "变量名序列") == 0) {
                                fprintf(fp2, "%s,", t->first_child->name);
                                printf("%s,", t->first_child->name);
                                t = t->second_child;
                            } else {
                                fprintf(fp2, "%s;\n", t->first_child->name);
                                printf("%s;\n", t->first_child->name);
                                t = t->second_child;
                            }
                        }
                        r = r->second_child;
                    }
                } else if (m->first_child != NULL && strcmp(m->first_child->name, "do-while语句") == 0) {
                    for (int i = 0; i < numbers; i++)       //打印空格
                    {
                        fprintf(fp2, " ");
                        printf(" ");
                    }
                    printf("do\n");
                    fprintf(fp2,"do\n");
                    for (int i = 0; i < numbers; i++)       //打印空格
                    {
                        fprintf(fp2, " ");
                        printf(" ");
                    }
                    printf("{\n");
                    fprintf(fp2,"{\n");
                    source_program(m->first_child->first_child, numbers + 4);
                    for (int i = 0; i < numbers; i++)       //打印空格
                    {
                        fprintf(fp2, " ");
                        printf(" ");
                    }
                    printf("%s;\n", m->first_child->second_child->first_child->name);
                    fprintf(fp2,"%s;\n", m->first_child->second_child->first_child->name);
                } else if (m->first_child != NULL && strcmp(m->first_child->name, "while语句") == 0) {
                    for (int i = 0; i < numbers; i++)       //打印空格
                    {
                        fprintf(fp2, " ");
                        printf(" ");
                    }
                    fprintf(fp2, "while(%s)\n", m->first_child->first_child->name);
                    printf("while(%s)\n", m->first_child->first_child->name);
                    for (int i = 0; i < numbers; i++) {
                        fprintf(fp2, " ");
                        printf(" ");
                    }
                    fprintf(fp2, "{\n");
                    printf("{\n");
                    source_program(m->first_child->second_child, numbers + 4);
                }

                else if (m->first_child != NULL && strcmp(m->first_child->name, "if-else子句") == 0)
                {
                    for (int i = 0; i < numbers; i++)
                    {
                        fprintf(fp2, " ");
                        printf(" ");
                    }
                    fprintf(fp2, "if(%s)\n", m->first_child->first_child->name);
                    printf("if(%s)\n", m->first_child->first_child->name);
                    if(m->first_child->second_child!=NULL&&strcmp(m->first_child->second_child->name,"复合语句")==0)
                    {
                        for (int i = 0; i < numbers; i++)
                        {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        printf("{\n");
                        fprintf(fp2,"{\n");
                        source_program(m->first_child->second_child,numbers+4);       //处理if子句
                    }
                    else
                    {
                        for (int i = 0; i < numbers + 4; i++)
                        {
                            fprintf(fp2, " ");
                            printf(" ");
                        }
                        printf("%s;\n",m->first_child->second_child->name);
                        fprintf(fp2,"%s;\n",m->first_child->second_child->name);
                    }

                    BiTNode *r=m->first_child->third_child;                       //处理else语句
                    while(r!=NULL)
                    {
                        if(strcmp(r->name,"else-if子句")==0)
                        {
                            for (int i = 0; i < numbers; i++)
                            {
                                fprintf(fp2, " ");
                                printf(" ");
                            }
                            printf("else if(%s)\n",r->first_child->name);
                            fprintf(fp2,"else if(%s)\n",r->first_child->name);
                            if(r->second_child!=NULL&&strcmp(r->second_child->name,"复合语句")==0)
                            {
                                for (int i = 0; i < numbers; i++)
                                {
                                    fprintf(fp2, " ");
                                    printf(" ");
                                }
                                printf("{\n");
                                fprintf(fp2,"{\n");
                                source_program(r->second_child,numbers+4);
                                r=r->third_child;
                            }
                            else
                            {
                                for (int i = 0; i < numbers + 4; i++)
                                {
                                    fprintf(fp2, " ");
                                    printf(" ");
                                }
                                printf("%s;\n",r->second_child->name);
                                fprintf(fp2,"%s;\n",r->second_child->name);
                                r=r->third_child;
                            }
                        }
                        else
                        {
                            for (int i = 0; i < numbers; i++)
                            {
                                fprintf(fp2, " ");
                                printf(" ");
                            }
                            printf("else\n");
                            fprintf(fp2,"else\n");
                            if(r->second_child!=NULL&&strcmp(r->second_child->name,"复合语句")!=0)
                            {
                                for (int i = 0; i < numbers + 4; i++)
                                {
                                    fprintf(fp2, " ");
                                    printf(" ");
                                }
                                printf("%s;\n",r->second_child->name);
                                fprintf(fp2,"%s;\n",r->second_child->name);
                                break;
                            }
                            else
                            {
                                for (int i = 0; i < numbers; i++)
                                {
                                    fprintf(fp2, " ");
                                    printf(" ");
                                }
                                printf("{\n");
                                fprintf(fp2,"{\n");
                                source_program(r->second_child,numbers+4);
                                break;
                            }
                        }
                    }
                }

                else if (m->first_child != NULL && strcmp(m->first_child->name, "for语句") == 0) {
                    for (int i = 0; i < numbers; i++) {
                        fprintf(fp2, " ");
                        printf(" ");
                    }
                    fprintf(fp2, "for(%s;%s;%s)\n", m->first_child->first_child->first_child->name,
                            m->first_child->first_child->second_child->name,
                            m->first_child->first_child->third_child->name);
                    printf("for(%s;%s;%s)\n", m->first_child->first_child->first_child->name,
                           m->first_child->first_child->second_child->name,
                           m->first_child->first_child->third_child->name);
                    for (int i = 0; i < numbers; i++) {
                        fprintf(fp2, " ");
                        printf(" ");
                    }
                    fprintf(fp2, "{\n");
                    printf("{\n");
                    BiTNode *i = m->first_child->second_child;
                    source_program(i, numbers + 4);
                } else if (m->first_child != NULL && strcmp(m->first_child->name, "return语句") == 0) {
                    for (int i = 0; i < numbers; i++) {
                        fprintf(fp2, " ");
                        printf(" ");
                    }
                    fprintf(fp2, "return %s;\n", m->first_child->first_child->name);
                    printf("return %s;\n", m->first_child->first_child->name);
                } else {
                    for (int i = 0; i < numbers; i++) {
                        fprintf(fp2, " ");
                        printf(" ");
                    }
                    fprintf(fp2, "%s;\n", m->first_child->name);
                    printf("%s;\n", m->first_child->name);
                }
                m = m->second_child;
            }
            for (int i = 0; i < numbers - 4; i++) {
                fprintf(fp2, " ");
                printf(" ");
            }
            fprintf(fp2, "}\n");
            printf("}\n");
        }
        source_program(r->second_child, 0);
    }
}

//抽象语法树显示函数
void ASTDisplay(BiTNode *root, int numbers) {
    if (root != NULL) {
        if (strcmp(root->name, "外部定义序列") == 0) {     //若为外部定义序列，则将numbers置于0
            numbers = 0;
        }
        for (int i = 0; i < numbers; i++) {
            printf(" ");
        }
        put(root->name);
        printf("%s\n", root->name);
        ASTDisplay(root->first_child, numbers + 4);
        if (root->second_child != NULL && strcmp(root->name, root->second_child->name) == 0) {
            ASTDisplay(root->second_child, numbers);
            ASTDisplay(root->third_child, numbers + 4);
        } else {
            ASTDisplay(root->second_child, numbers + 4);
            ASTDisplay(root->third_child, numbers + 4);
        }
    }
}

//判断运算符优先级函数
char precede(char T1[], char T2[]) {
    char t1 = T1[0], t2 = T2[0];
    switch (t2) {
        case '+': {
            if (t1 == '+' || t1 == '-' || t1 == '*' || t1 == '/' || t1 == '%' || t1 == ')' || t1 == '=')
                return '>';
            else return '<';
        }
        case '-': {
            if (t1 == '+' || t1 == '-' || t1 == '*' || t1 == '/' || t1 == '%' || t1 == ')')
                return '>';
            else return '<';
        }
        case '*': {
            if (t1 == '*' || t1 == '/' || t1 == '%' || t1 == ')')
                return '>';
            else return '<';
        }
        case '/': {
            if (t1 == '*' || t1 == '/' || t1 == '%' || t1 == ')')
                return '>';
            else return '<';
        }
        case '%': {
            if (t1 == '*' || t1 == '/' || t1 == '%' || t1 == ')')
                return '>';
            else return '<';
        }
        case '(': {
            if (t1 == ')')
                return '>';
            else return '<';
        }
        case ')': {
            if (t1 == '(')
                return '=';
            else return '>';
        }
        case '=': {
            if (strcmp(T2, "==") == 0) {
                if (t1 == '+' || t1 == '-' || t1 == '*' || t1 == '/' || t1 == '%' || t1 == '(' || t1 == ')' ||
                    t1 == '>' || t1 == '<' || strcmp(T1, "==") == 0 || strcmp(T1, "!=") == 0)
                    return '>';
                else return '<';
            } else return '<';
        }
        case '>': {
            if (t1 == '+' || t1 == '-' || t1 == '*' || t1 == '/' || t1 == '%' || t1 == '(' || t1 == ')' || t1 == '>' ||
                t1 == '<')
                return '>';
            else return '<';
        }
        case '<': {
            if (t1 == '+' || t1 == '-' || t1 == '*' || t1 == '/' || t1 == '%' || t1 == '(' || t1 == ')' || t1 == '>' ||
                t1 == '<')
                return '>';
            else return '<';
        }
        case '!': {
            if (strcmp(T2, "!=") == 0) {
                if (t1 == '+' || t1 == '-' || t1 == '*' || t1 == '/' || t1 == '%' || t1 == '(' || t1 == ')' ||
                    t1 == '>' || t1 == '<' || strcmp(T1, "==") == 0 || strcmp(T1, "!=") == 0)
                    return '>';
                else return '<';
            } else {
                printf("不支持单目运算符!\n");
                return '<';
            }
        }
        case '&': {
            if (strcmp(T2, "&&") == 0) {
                if (t1 == '+' || t1 == '-' || t1 == '*' || t1 == '/' || t1 == '%' || t1 == '(' || t1 == ')' ||
                    t1 == '>' || t1 == '<' || strcmp(T1, "==") == 0 || strcmp(T1, "!=") == 0 || strcmp(T1, "&&") == 0)
                    return '>';
                else return '<';
            } else {
                printf("不支持单目运算符!\n");
                return '<';
            }
        }
        case '|': {
            if (strcmp(T2, "||") == 0) {
                if (t1 == '+' || t1 == '-' || t1 == '*' || t1 == '/' || t1 == '%' || t1 == '(' || t1 == ')' ||
                    t1 == '>' || t1 == '<' || strcmp(T1, "==") == 0 || strcmp(T1, "!=") == 0 || strcmp(T1, "&&") == 0 ||
                    strcmp(T1, "||") == 0)
                    return '>';
                else return '<';
            } else {
                printf("不支持单目运算符!\n");
                return '<';
            }
        }
        case '#':
            if (t1 != '#')
                return '>';
            else return '=';
    }
}

//前序遍历抽象子树函数
void preorder(BiTNode *root) {
    if (root != NULL) {
        printf("%s\n", root->name);
        preorder(root->first_child);
        preorder(root->second_child);
        preorder(root->third_child);
    }
}

//子程序--表达式
BiTree exp(int endsym) {
    char op[100][10] = {""};
    int top_1 = 0;
    strcpy(op[top_1++], "#");                      //初始化，将起止符#入栈
    BiTree opn[100] = {NULL};
    int error = 0;
    int top_2 = 0;

    while ((w != 51 || strcmp(op[top_1 - 1], "#") != 0) && !error)     //当运算符栈栈顶不是起止符号，并没有错误时
    {
        if (w == 100 || (w >= 94 && w <= 99)) {
            BiTree p = (BiTree) malloc(sizeof(BiTNode));
            strcpy(p->name, token_text[num - 1]);
            p->first_child = NULL;
            p->second_child = NULL;
            p->third_child = NULL;
            opn[top_2++] = p;
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
        } else if ((33 <= w && w <= 43) || w == 53 || w == 55) {
            switch (precede(op[top_1 - 1], token_text[num - 1])) {
                case '<': {
                    strcpy(op[top_1++], token_text[num - 1]);
                    w = get_token[num++];
                    while (w == -1) {
                        column++;
                        w = get_token[num++];
                    }
                    break;
                }
                case '=': {
                    if (!op[--top_1]) {
                        error++;
                    }
                    w = get_token[num++];
                    while (w == -1) {
                        column++;
                        w = get_token[num++];
                    }
                    break;
                }
                case '>': {
                    BiTree t2 = opn[--top_2];
                    if (!t2) error++;
                    BiTree t1 = opn[--top_2];
                    if (!t1) error++;
                    BiTree t = (BiTree) malloc(sizeof(BiTNode));
                    strcpy(t->name, op[--top_1]);
                    t->first_child = t1;
                    t->second_child = t2;
                    t->third_child = NULL;
                    opn[top_2++] = t;
                    break;
                }
                default: {
                    if (w == endsym) {
                        w = 51;
                    } else error = 1;
                }
            }
        } else if (w == endsym) w = 51;
        else error = 1;
    }
    while (w != endsym && w != 51) {
        w = get_token[num++];
        while (w == -1) {
            column++;
            w = get_token[num++];
        }
    }
    BiTree root = (BiTNode *) malloc(sizeof(BiTNode));
    strcpy(root->name, expretion[ex - 1]);
    root->first_child = NULL;
    root->second_child = NULL;
    root->third_child = NULL;
    return root;

}

//子程序--语句
BiTree statement();

//子程序--语句序列
BiTree SentenceList();

//子程序--局部变量序列
BiTree LocalVar() {
    BiTree root = (BiTree) malloc(sizeof(BiTNode));
    root->first_child = NULL;
    root->second_child = NULL;
    root->third_child = NULL;
    strcpy(root->name, "局部变量定义序列");

    root->first_child = (BiTree) malloc(sizeof(BiTNode));
    root->first_child->second_child = NULL;
    root->first_child->third_child = NULL;
    strcpy(root->first_child->name, "局部变量定义");

    root->first_child->first_child = (BiTree) malloc(sizeof(BiTNode));
    root->first_child->second_child = (BiTree) malloc(sizeof(BiTNode));

    root->first_child->first_child->first_child = NULL;
    root->first_child->first_child->second_child = NULL;
    root->first_child->first_child->third_child = NULL;

    root->first_child->second_child->first_child = NULL;
    root->first_child->second_child->second_child = NULL;
    root->first_child->second_child->third_child = NULL;

    strcpy(root->first_child->first_child->name, token_text[num - 1]);
    w = get_token[num++];
    while (w == -1) {
        column++;
        w = get_token[num++];
    }
    if (w != 100) {
        printf("第%d行有错误！\n", column);
        exit(0);
    }

    strcpy(root->first_child->second_child->name, "变量名序列");

    BiTNode *p = root->first_child->second_child;
    p->first_child = (BiTree) malloc(sizeof(BiTNode));
    p->first_child->first_child = NULL;
    p->first_child->second_child = NULL;
    p->first_child->third_child = NULL;

    for (int i = 0; i < count_local; i++)                          //判断该变量是否存在
    {
        if (strcmp(token_text[num - 1], Local[i]) == 0) {
            printf("局部变量%s已存在！无需重新定义\n", Local[i]);
            printf("第%d行有错误！\n", column);
            exit(10);
        }
    }
    strcpy(Local[count_local++], token_text[num - 1]);            //存放一个局部变量

    strcpy(p->first_child->name, token_text[num - 1]);
    w = get_token[num++];
    while (w == -1) {
        column++;
        w = get_token[num++];
    }
    while (1) {
        if (w != 48 && w != 44) {
            printf("语法错误！（局部变量序列）\n");
            free(root);
            printf("第%d行有错误!\n", column);
            exit(0);
        }
        if (w == 44) {
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            if (w == 17 || w == 4 || w == 13 || w == 9 || w == 18 || w == 21) {
                root->second_child = LocalVar();
                return root;
            } else {
                return root;
            }
        }
        w = get_token[num++];
        while (w == -1) {
            column++;
            w = get_token[num++];
        }
        if (w != 100)               //若不是标识符，释放root为根的全部结点，返回空指针
        {
            printf("语法错误(局部变量序列)!\n");
            free(root);
            printf("第%d行有错误!\n", column);
            exit(0);
        }

        for (int i = 0; i < count_local; i++)                          //判断该变量是否存在
        {
            if (strcmp(token_text[num - 1], Local[i]) == 0) {
                printf("局部变量%s已存在！无需重新定义\n", Local[i]);
                printf("第%d行有错误！\n", column);
                exit(10);
            }
        }
        strcpy(Local[count_local++], token_text[num - 1]);            //存放一个局部变量

        BiTNode *q = (BiTNode *) malloc(sizeof(BiTNode));    //生成变量名序列结点，根指针为q，作为p的第二个孩子，插入到树中
        q->first_child = NULL;
        q->second_child = NULL;
        q->third_child = NULL;

        strcpy(q->name, "变量名序列");
        p->second_child = q;
        p = q;

        BiTNode *i = (BiTNode *) malloc(sizeof(BiTNode));         //根据tokenText的变量名生成一个变量结点，作为p的第一个孩子
        i->first_child = NULL;
        i->second_child = NULL;
        i->third_child = NULL;
        strcpy(i->name, token_text[num - 1]);
        p->first_child = i;

        w = get_token[num++];
        while (w == -1) {
            column++;
            w = get_token[num++];
        }

    }
}

//子程序--复合语句
BiTree ComplexList() {
    BiTree root = (BiTree) malloc(sizeof(BiTNode));
    root->first_child = NULL;
    root->second_child = NULL;
    root->third_child = NULL;
    strcpy(root->name, "复合语句");
    w = get_token[num++];
    while (w == -1) {
        column++;
        w = get_token[num++];
    }
    if (w == 44) {                      //若为空子句，只为一个分号
        w = get_token[num++];
        while (w == -1) {
            column++;
            w = get_token[num++];
        }
        w = get_token[num++];
        while (w == -1) {
            column++;
            w = get_token[num++];
        }
        root->first_child = (BiTNode *) malloc(sizeof(BiTNode));
        strcpy(root->first_child->name, ";");
        root->first_child->second_child = NULL;
        root->first_child->first_child = NULL;
        root->first_child->third_child = NULL;
        return root;
    }
    if (w == 17 || w == 4 || w == 13 || w == 9 || w == 18 || w == 21)   //若w为类型关键字
    {
        root->first_child = LocalVar();
    }

    root->second_child = SentenceList();
    if (w != 63) {
        return root;
    }
    w = get_token[num++];
    while (w == -1) {
        column++;
        w = get_token[num++];
    }
    return root;
}

//子程序--形参
BiTree FormalVar() {
    w = get_token[num++];
    while (w == -1) {
        column++;
        w = get_token[num++];
    }
    if (w == 46) {
        w = get_token[num++];
        while (w == -1) {
            column++;
            w = get_token[num++];
        }
        return NULL;
    }//若为无参函数，则直接返回NULL

    BiTree root = (BiTNode *) malloc(sizeof(BiTNode));
    root->first_child = NULL;
    root->second_child = NULL;
    root->third_child = NULL;

    strcpy(root->name, "形参序列");
    root->first_child = (BiTNode *) malloc(sizeof(BiTNode));
    root->first_child->first_child = (BiTNode *) malloc(sizeof(BiTNode));
    root->first_child->first_child->first_child = NULL;
    root->first_child->first_child->second_child = NULL;
    root->first_child->first_child->third_child = NULL;

    root->first_child->second_child = (BiTNode *) malloc(sizeof(BiTNode));
    root->first_child->second_child->first_child = NULL;
    root->first_child->second_child->second_child = NULL;
    root->first_child->second_child->third_child = NULL;
    root->first_child->third_child = NULL;

    if (w != 17 && w != 4 && w != 13 && w != 9 && w != 18 && w != 21) {
        printf("%s不是关键字！\n", token_text[num - 1]);
        printf("第%d行有错误!\n", column);
        exit(1);
    }

    strcpy(root->first_child->name, "形参");
    strcpy(root->first_child->first_child->name, token_text[num - 1]);
    w = get_token[num++];
    while (w == -1) {
        column++;
        w = get_token[num++];
    }

    for (int i = 0; i < count_formal; i++)                        //判断形参是否存在
    {
        if (strcmp(token_text[num - 1], Formal[i]) == 0) {
            printf("形参%s已存在！\n", token_text[num - 1]);
            printf("第%d行有错误!\n", column);
            exit(10);
        }
    }
    strcpy(Formal[count_formal++], token_text[num - 1]);      //不存在则存入数组

    strcpy(root->first_child->second_child->name, token_text[num - 1]);

    BiTNode *p = (BiTree) malloc(sizeof(BiTree));
    p->first_child = NULL;
    p->second_child = NULL;
    p->third_child = NULL;

    p = root;
    w = get_token[num++];
    while (w == -1) {
        column++;
        w = get_token[num++];
    }


    while (1) {
        if (w != 48 && w != 46) {
            printf("语法错误（形参处理）!\n");
            free(root);
            printf("第%d行有错误!\n", column);
            exit(0);
        }
        if (w == 46) {
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            return root;
        }
        w = get_token[num++];
        while (w == -1) {
            column++;
            w = get_token[num++];
        }
        if (w != 17 && w != 4 && w != 13 && w != 9 && w != 18 &&
            w != 21)                          //若不是保留字或标识符，释放root为根的全部结点，返回空指针
        {
            printf("%s不是关键字\n", token_text[num - 1]);
            printf("第%d行有错误!\n", column);
            exit(1);
        }
        BiTNode *q = (BiTNode *) malloc(sizeof(BiTNode));    //生成形参序列结点，根指针为q，作为p的第二个孩子，插入到树中
        q->first_child = NULL;
        q->second_child = NULL;
        q->third_child = NULL;

        strcpy(q->name, "形参序列");
        q->first_child = (BiTree) malloc(sizeof(BiTNode));
        strcpy(q->first_child->name, "形参");
        q->second_child = NULL;
        q->third_child = NULL;

        q->first_child->first_child = (BiTree) malloc(sizeof(BiTNode));
        q->first_child->second_child = (BiTree) malloc(sizeof(BiTNode));
        q->first_child->third_child = NULL;

        strcpy(q->first_child->first_child->name, token_text[num - 1]);
        w = get_token[num++];
        while (w == -1) {
            column++;
            w = get_token[num++];
        }

        for (int i = 0; i < count_formal; i++)                        //判断形参是否存在
        {
            if (strcmp(token_text[num - 1], Formal[i]) == 0) {
                printf("形参%s已存在！\n", token_text[num - 1]);
                printf("第%d行有错误!\n", column);
                exit(10);
            }
        }
        strcpy(Formal[count_formal++], token_text[num - 1]);      //不存在则存入数组

        strcpy(q->first_child->second_child->name, token_text[num - 1]);
        q->first_child->first_child->first_child = NULL;
        q->first_child->first_child->second_child = NULL;
        q->first_child->first_child->third_child = NULL;
        q->first_child->second_child->first_child = NULL;
        q->first_child->second_child->second_child = NULL;
        q->first_child->second_child->third_child = NULL;

        p->second_child = q;
        p = q;

        w = get_token[num++];
        while (w == -1) {
            column++;
            w = get_token[num++];
        }
    }
}

//子程序--函数定义
BiTree FuncDef() {
    BiTree root = (BiTree) malloc(sizeof(BiTNode));    //生成函数定义结点root；
    root->first_child = NULL;
    root->second_child = NULL;
    root->third_child = NULL;
    strcpy(root->name, "函数定义");

    BiTNode *p = (BiTNode *) malloc(sizeof(BiTNode)); //生成返回值类型结点，作为root的第一个孩子
    p->first_child = NULL;
    p->second_child = NULL;
    p->third_child = NULL;
    strcpy(p->name, form);
    root->first_child = p;

    root->second_child = (BiTree) malloc(sizeof(BiTNode));
    strcpy(root->second_child->name, token_0);
    strcpy(Ext[count_ext++], token_0);
    root->second_child->first_child = FormalVar();             //调用形参子程序，得到参数部分的子树根指针，无参函数得到NULL，该子树作为root的第二棵子树
    root->second_child->second_child = NULL;
    root->second_child->third_child = NULL;
    if (w == 44)                          //若为分号，就是函数原型声明。函数体子树为空
    {
        w = get_token[num++];
        while (w == -1) {
            column++;
            w = get_token[num++];
        }
        root->third_child = NULL;
    } else if (w == 62)                   //若为正大括号，则调用函数体（复合语句）子程序
    {
        root->third_child = ComplexList();
    } else {
        printf("语法错误！（函数定义）\n");
        printf("第%d行有错误!\n", column);
        exit(0);
    }
    return root;
}

//子程序--外部变量定义
BiTree ExtVarDef() {
    BiTree root = (BiTNode *) malloc(sizeof(BiTNode));
    root->first_child = NULL;
    root->second_child = NULL;
    root->third_child = NULL;

    strcpy(root->name, "外部变量定义");
    root->first_child = (BiTNode *) malloc(sizeof(BiTNode));
    root->first_child->first_child = NULL;
    root->first_child->second_child = NULL;
    root->first_child->third_child = NULL;

    strcpy(root->first_child->name, form);

    BiTNode *p = (BiTree) malloc(sizeof(BiTree));
    p->first_child = NULL;
    p->second_child = NULL;
    p->third_child = NULL;

    strcpy(p->name, "变量序列");
    root->second_child = p;

    p->first_child = (BiTree) malloc(sizeof(BiTNode));
    p->first_child->first_child = NULL;
    p->first_child->second_child = NULL;
    p->first_child->third_child = NULL;

    for (int i = 0; i < count_ext; i++)                     //判断该变量是否存在
    {
        if (strcmp(token_0, Ext[i]) == 0) {
            printf("外部变量%s已存在！无需重新定义\n", Ext[i]);
            printf("第%d行有错误！\n", column);
            exit(10);
        }
    }
    strcpy(Ext[count_ext++], token_0);            //存放一个全局变量

    strcpy(p->first_child->name, token_0);

    while (1) {
        if (w != 48 && w != 44) {
            printf("语法错误（外部变量定义）!\n");
            free(root);
            printf("第%d行有错误!\n", column);
            exit(0);
        }
        if (w == 44) {
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            return root;
        }
        w = get_token[num++];
        while (w == -1) {
            column++;
            w = get_token[num++];
        }
        if (w != 100)                                      //若不是标识符，释放root为根的全部结点，返回空指针
        {
            printf("语法错误(外部变量定义)!\n");
            free(root);
            printf("第%d行有错误!\n", column);
            exit(0);
        }
        BiTNode *q = (BiTNode *) malloc(sizeof(BiTNode));    //生成外部变量序列结点，根指针为q，作为p的第二个孩子，插入到树中
        q->first_child = NULL;
        q->second_child = NULL;
        q->third_child = NULL;

        strcpy(q->name, "变量序列");
        p->second_child = q;
        p = q;

        BiTNode *i = (BiTNode *) malloc(sizeof(BiTNode));     //根据tokenText的变量名生成一个变量结点，作为p的第一个孩子
        i->first_child = NULL;
        i->second_child = NULL;
        i->third_child = NULL;

        for (int i = 0; i < count_ext; i++)                     //判断该变量是否存在
        {
            if (strcmp(token_text[num - 1], Ext[i]) == 0) {
                printf("外部变量%s已存在！无需重新定义\n", Ext[i]);
                printf("第%d行有错误！\n", column);
                exit(10);
            }
        }
        strcpy(Ext[count_ext++], token_text[num - 1]);            //存放一个全局变量

        strcpy(i->name, token_text[num - 1]);
        p->first_child = i;

        w = get_token[num++];
        while (w == -1) {
            column++;
            w = get_token[num++];
        }
    }
}

//子程序--外部定义
BiTree ExtDef() {
    if (w != 17 && w != 4 && w != 13 && w != 9 && w != 18 && w != 21 && w != 0) {
        printf("外部定义里不是类型关键字！\n");
        printf("第%d行有错误!\n", column);
        exit(0);
    }
    if (w == 0)                           //为退出符，直接退出程序
    {
        return NULL;
    }
    strcpy(form, reserveWord[w - 1]);                 //保存类型说明符
    w = get_token[num++];
    while (w == -1) {
        column++;
        w = get_token[num++];
    }
    if (w != 100) {
        printf("语法错误（外部定义）!\n");
        printf("第%d行有错误!\n", column);
        exit(0);
    }
    strcpy(token_0, token_text[num - 1]);             //定义了一个全局变量
    w = get_token[num++];
    while (w == -1) {
        column++;
        w = get_token[num++];
    }

    BiTree p;
    if (w != 45)             //不为左括号
    {
        p = ExtVarDef();     //调用外部变量定义子程序
    } else {
        p = FuncDef();       //调用函数定义子程序
    }
    if (p != NULL) {
        return p;
    } else {
        printf("外部定义失败!\n");
        printf("第%d行有错误!\n", column);
        exit(0);
    }
}

//子程序--外部定义序列
BiTree ExtDefList() {
    if (w != 17 && w != 4 && w != 13 && w != 9 && w != 18 && w != 21 && w != 0) {
        printf("%s不是关键字\n", token_text[num - 1]);
        printf("第%d行有错误!\n", column);
        exit(2);
    }
    if (w == 0)                          //为推出符，直接退出程序
    {
        return NULL;
    }
    BiTree root = (BiTNode *) malloc(sizeof(BiTNode));
    root->first_child = NULL;
    root->second_child = NULL;
    root->third_child = NULL;        //初始化

    strcpy(root->name, "外部定义序列");
    root->first_child = ExtDef();    //处理一个外部定义，得到一颗子树，作为root的第一颗子树
    root->second_child = ExtDefList();

    return root;                     //返回根指针
}

//子程序--程序
BiTree program() {
    w = get_token[num++];
    while (w == -1) {
        column++;
        w = get_token[num++];
    }
    if (BiTNode *root = ExtDefList()) {
        printf("语法分析完成！\n\n");
        return root;
    } else {
        printf("程序有语法错误！\n");
        printf("第%d行有错误!\n", column);
        exit(0);
    }
}

//查找保留字函数
int searchReserve(char reserveWord[][20], char s[]) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(reserveWord[i], s) == 0) {
            return i + 1;             //查找成功，则返回种别码
        }
    }
    return -1;                 //查找失败，则返回-1，即为标识符
}

//判断是否为字母
int Isletter(char letter) {
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') || letter == '_') {
        return 1;          //若为字母，返回1
    } else return 0;         //否则返回0
}

//判断是否为数字
int Isnumber(char number) {
    if (number >= '0' && number <= '9') {
        return 1;         //若为数字，返回1
    } else return 0;        //否则返回0
}

//处理define语句
void define_process(char r[]) {
    int i = 0;
    while(!(r[i] == '#'&&r[i+1]=='d'))
    {
        i++;
    }
    while (r[i] == '#'&&r[i+1]=='d') {
        i = i + 8;
        int j = 0;
        while (r[i] != ' ') {
            define_1[define_num][j++] = r[i++];
        }
        i = i + 1;
        j = 0;
        while (r[i] != '\n') {
            define_2[define_num][j++] = r[i++];
        }
        define_num++;
        i++;
    }
}

//编译预处理，取出没用的字符和注释
void compile_precess(char r[]) {
    char temp[10000];
    int count = 0;
    int i = 0;

    while (r[i] != '\0') {
        if (r[i] == '/' && r[i + 1] == '/')   //若为"//"单行注释，则从此处省略该行
        {
            while (r[i] != '\n') {
                i++;             //向后移动
            }
        }
        if (r[i] == '/' && r[i + 1] == '*')    //若为块注释，则去掉该内容
        {
            i += 2;
            while (r[i] != '*' || r[i + 1] != '/')  //寻找"*/"
            {
                i++;
                if (r[i] == '$') {
                    printf("出现错误，没有找到'*/'！");   //没找到则报错
                    printf("第%d行有错误!\n", column);
                    exit(0);
                }
            }
            i += 2;             //找到则跳过
        }
        if (r[i] != '\t' && r[i] != '\v' && r[i] != '\r')    //若出现无用字符，则过滤，否则保存
        {
            temp[count++] = r[i];
        }
        i++;
    }
    temp[count] = '\0';
    strcpy(r, temp);       //将净化之后的程序覆盖到原来程序
}

//根据DFA状态转换图设计分析子程序
void scanner(int &syn, char resourceProject[], char token[20],
             int &pProject) {//syn为返回的种别码，resourceProject为净化完成的源程序，token用来保存此次扫描的结果，pProject始终指向当前源程序待扫描位置
    int i, count = 0;
    char ch = resourceProject[pProject];   //ch为当前待扫描位置

    for (i = 0; i < 20; i++) {
        token[i] = '\0';    //每次扫描前首先初始化
    }

    while (ch == ' ')       //若为空格，则跳过
    {
        pProject++;
        ch = resourceProject[pProject];
    }

    while(ch=='#'&&resourceProject[pProject+1]=='i')
    {
        pProject+=9;
        ch=resourceProject[pProject];
        int j=0;
        while(ch!='>')
        {
            include_file[count_i][j++]=ch;
            ch=resourceProject[pProject++];
        }
        count_i++;
        pProject++;
        ch=resourceProject[pProject];
    }

    while (ch == ' ')       //若为空格，则跳过
    {
        pProject++;
        ch = resourceProject[pProject];
    }

    while (ch == '#'&&resourceProject[pProject+1]=='d') {
        pProject++;
        ch = resourceProject[pProject];
        while (ch != '\n') {
            pProject++;
            ch = resourceProject[pProject];
        }
        pProject++;
        ch = resourceProject[pProject];
    }

    while (ch == ' ')       //若为空格，则跳过
    {
        pProject++;
        ch = resourceProject[pProject];
    }


    if (resourceProject[pProject] == '\'')       //识别字符
    {
        if (resourceProject[pProject + 2] != '\'') {
            printf("字符单词不合法！\n");
            printf("第%d行有错误!\n", column);
            exit(0);
        } else {
            token[0] = '\'';
            pProject++;
            token[1] = resourceProject[pProject];
            token[2] = '\'';
            syn = 93;
            pProject++;
            pProject++;
            return;
        }
    } else if (resourceProject[pProject] == '\"') {
        pProject++;
        token[count++] = '\"';
        while (resourceProject[pProject] != '\"') {
            token[count++] = resourceProject[pProject];
            pProject++;
        }
        pProject++;
        token[count] = '\"';
        syn = 92;
        return;
    }

    //开头为字母
    if (Isletter(resourceProject[pProject])&&resourceProject[pProject]!='_') {
        token[count++] = resourceProject[pProject];   //收集
        pProject++;  //后移
        while (Isletter(resourceProject[pProject]) || Isnumber(resourceProject[pProject]) ||
               resourceProject[pProject] == '[' || resourceProject[pProject] == ']') {   //后接字母和数字

            if(resourceProject[pProject]==operatorOrDelimiter[i][0]&&resourceProject[pProject]!='['&&resourceProject[pProject]!=']')
            {
                printf("%s字符后不能接符号",token);
                exit(0);
            }
            token[count++] = resourceProject[pProject]; //收集
            pProject++;
        }   //读完结束，pProject则为下次将要开始的指针位置
        token[count] = '\0';    //token为找到的字符
        for (int i = 0; i < define_num; i++) {
            if (strcmp(token, define_1[i]) == 0) {
                for (int j = 0; j < strlen(define_2[i]); j++) {
                    token[j] = define_2[i][j];
                }
                token[strlen(define_2[i])] = '\0';
                if (Isnumber(token[0])) {
                    syn = 99;
                    return;
                } else if (Isletter(token[0])) {
                    syn = 100;
                    return;
                }
            }
        }
        syn = searchReserve(reserveWord, token);   //访问表找到种别码
        if (syn == -1) {
            syn = 100;   //若为-1，则表示保留字中不存在当前字符，即为标识符
        }
        return;
    }

    if (Isnumber(resourceProject[pProject]) && Isletter(resourceProject[pProject + 1])) {
        if (resourceProject[pProject + 1] != 'x' && resourceProject[pProject + 1] != 'X') {
            printf("数字后面不能接下划线或者字母!\n");
            printf("第%d行有错误!\n", column);
            exit(0);
        }
    }

    //开头为数字
    if (Isnumber(resourceProject[pProject])) {   //有6种形式的数值，依次识别
        while (Isnumber(resourceProject[pProject]) || Isletter(resourceProject[pProject]) ||
               resourceProject[pProject] == '.') {
            token[count++] = resourceProject[pProject];
            pProject++;
        }
        token[count] = '\0';
        for (int i = 0; i < define_num; i++) {
            if (strcmp(token, define_1[i]) == 0) {
                strcpy(token, define_2[i]);
            }
        }

        for (int i = 0; token[i] != '\0'; i++) {
            if (token[i] == '.' && (token[count - 1] == 'f' || token[count - 1] == 'F'))  //为float型
            {
                for (int j = 0; j < count - 1; j++) {
                    if (Isletter(token[j])) {
                        printf("%s定义错误！\n", token);
                        exit(0);
                    }
                }
                syn = 94;
                return;
            } else if (token[i] == '.' && (token[count - 1] != 'f' && token[count - 1] != 'F'))  //为double型
            {
                for (int j = 0; j < count - 1; j++) {
                    if (Isletter(token[j])) {
                        printf("%s定义错误！\n", token);
                        exit(0);
                    }
                }
                syn = 95;
                return;
            }
        }

        if (token[0] == '0' && (token[1] == 'x' || token[1] == 'X'))         //若为整型
        {
            for (int j = 2; j < count; j++) {
                if ((token[j] <= 'z' && token[j] > 'f') || (token[j] <= 'Z' && token[j] >= 'F') || token[j] == '_') {
                    printf("%s定义错误！\n", token);
                    exit(0);
                }
            }
            syn = 99;
            return;
        }
        if (token[0] == '0' && token[1] != 'x' && token[1] != 'X') {
            for (int j = 1; j < count; j++) {
                if (!(token[j] >= 0 && token[j] <= '8')) {
                    printf("%s定义错误！\n", token);
                    exit(0);
                }
            }
            syn = 99;
            return;
        } else if (token[count - 1] == 'u' || token[count - 1] == 'U')       //若为无符号整型
        {
            for (int j = 0; j < count - 1; j++) {
                if (Isletter(token[j])) {
                    printf("%s定义错误！\n", token);
                    exit(0);
                }
            }
            syn = 98;
            return;
        } else if ((token[count - 1] == 'l' || token[count - 1] == 'L') &&
                   (token[count - 2] != 'U' && token[count - 2] != 'u'))     //若为长整型
        {
            for (int j = 0; j < count - 2; j++) {
                if (Isletter(token[j])) {
                    printf("%s定义错误！\n", token);
                    exit(0);
                }
            }
            syn = 97;
            return;
        } else if ((token[count - 1] == 'l' || token[count - 1] == 'L') &&
                   (token[count - 2] == 'U' || token[count - 2] == 'u'))     //若为无符号长整型
        {
            for (int j = 0; j < count - 2; j++) {
                if (Isletter(token[j])) {
                    printf("%s定义错误！\n", token);
                    exit(0);
                }
            }
            syn = 96;
            return;
        } else {
            for (int i = 0; i < count; i++) {
                if (Isletter(token[i])) {
                    printf("字符%s定义错误!\n", token);
                    exit(0);
                }
            }
            syn = 99;
            return;
        }
    }
        //若为界符运算符
    else if (ch == '/' || ch == '^' || ch == '~'|| ch == '\\' || ch == '\?' || ch == ':') {
        token[0] = resourceProject[pProject];
        if(Isletter(resourceProject[pProject+1])||Isnumber(resourceProject[pProject+1]))
        {
            printf("%c字符后面不能接字母或数字!",token[0]);
            exit(0);
        }
        token[1] = '\0';  //形成单字符串
        for (i = 0; i < 36; i++) {
            if (strcmp(token, operatorOrDelimiter[i]) == 0) //找到
            {
                syn = 33 + i;
                break;
            }
        }
        pProject++;
        return;
    }
    else if (ch == '+' || ch == '-' || ch == '*'  || ch == ';' || ch == '(' || ch == ')'
             || ch == ',' || ch == '\"' || ch == '\'' || ch == '#' || ch == '%' || ch == '['
             || ch == ']' || ch == '{' || ch == '}'  || ch == '.') {
        token[0] = resourceProject[pProject];
        token[1] = '\0';  //形成单字符串
        for (i = 0; i < 36; i++) {
            if (strcmp(token, operatorOrDelimiter[i]) == 0) //找到
            {
                syn = 33 + i;
                break;
            }
        }
        pProject++;
        return;
    }

    else if (resourceProject[pProject] == '<') {
        pProject++;
        if (resourceProject[pProject] == '=') {
            syn = 38;
        } else {
            pProject--;
            syn = 37;
        }
        pProject++;
        return;
    } else if (resourceProject[pProject] == '>') {
        pProject++;
        if (resourceProject[pProject] == '=') {
            syn = 40;
        } else {
            pProject--;
            syn = 39;
        }
        pProject++;
        return;
    } else if (resourceProject[pProject] == '=') {
        pProject++;
        if (resourceProject[pProject] == '=') {
            syn = 42;
        } else {
            pProject--;
            syn = 41;
        }
        pProject++;
        return;
    } else if (resourceProject[pProject] == '!') {
        pProject++;
        if (resourceProject[pProject] == '=') {
            syn = 43;
        } else {
            syn = 68;
            pProject--;
        }
        pProject++;
        return;
    } else if (resourceProject[pProject] == '&') {
        pProject++;
        if (resourceProject[pProject] == '&') {
            syn = 53;
        } else {
            pProject--;
            syn = 52;
        }
        pProject++;
        return;
    } else if (resourceProject[pProject] == '|') {
        pProject++;
        if (resourceProject[pProject] == '|') {
            syn = 55;
        } else {
            pProject--;
            syn = 54;
        }
        pProject++;
        return;
    } else if (resourceProject[pProject] == '\0')     //若为结束符，种别码为0
    {
        syn = 0;
        return;
    } else if (resourceProject[pProject] == '\n') {
        syn = -1;
        pProject++;
        return;
    } else                       //若不能被以上词法识别，则出错
    {
        printf("error：不存在%c字符\n", ch);
        printf("第%d行有错误!\n", column);
        exit(0);
    }
}

int main() {
    char file_name[20];
    char route[100] = "/Users/wei/CLionProjects/wei/";
    FILE *fp, *fp1, *fp3;
    printf("请输入需要打开的文件名称：");
    scanf("%s", file_name);
    strcat(route, file_name);

    if ((fp = fopen(route, "r")) == NULL) {
        printf("打开文件错误！\n");
        exit(0);
    } else printf("打开成功！\n");


    for (int i = 0; !feof(fp); i++) {
        fscanf(fp, "%c", &resourceProject[i]);
    }
    fclose(fp);                                     //关闭文件

    printf("源程序为%s\n", resourceProject);         //将源文件输出

    define_process(resourceProject);
    compile_precess(resourceProject);               //净化源程序
    printf("过滤之后的程序为%s\n", resourceProject);  //将净化后的源程序输出
    pProject = 0;           //重置pProject

    if ((fp1 = fopen("/Users/wei/CLionProjects/wei/resource_compile.txt", "w+")) == NULL) {
        printf("打开文件错误！\n");
        printf("第%d行有错误!\n", column);
        exit(0);
    }


    int count_ID = 0;   //记录存放的标识符个数
    while (syn != 0) {
        scanner(syn, resourceProject, token, pProject);
        if (syn == 100)  //若为标识符，则判断是否在表中
        {
            for (int i = 0; i < 1000; i++) {
                if (strcmp(IDentifier[i], token) == 0)   //已在表中
                {
                    break;
                }
                if (strcmp(IDentifier[i], "") == 0)      //若不在表中，则加入到表中
                {
                    strcpy(IDentifier[i], token);
                    count_ID++;
                    break;
                }
            }
            printf("（标识符 ，%s）\n", token);
            fprintf(fp1, "（标识符 ，%s）\n", token);
            get_token[m++] = 100;
            strcpy(token_text[m - 1], token);
        } else if (syn >= 1 && syn <= 32)   //若为保留字
        {
            printf("（关键字 ，%s）\n", reserveWord[syn - 1]);
            fprintf(fp1, "（关键字 ，%s）\n", reserveWord[syn - 1]);
            get_token[m++] = syn;
            strcpy(token_text[m - 1], reserveWord[syn - 1]);
        } else if (syn == 99) {
            printf("（整型数值 ，%s）\n", token);
            fprintf(fp1, "（整型数值 ,%s)\n", token);
            get_token[m++] = syn;
            strcpy(token_text[m - 1], token);
        } else if (syn == 98) {
            printf("（无符号整型数值 ，%s）\n", token);
            fprintf(fp1, "（无符号整型数值 ,%s)\n", token);
            get_token[m++] = syn;
            strcpy(token_text[m - 1], token);
        } else if (syn == 97) {
            printf("（长整型数值 ，%s）\n", token);
            fprintf(fp1, "（长整型数值 ,%s)\n", token);
            get_token[m++] = syn;
            strcpy(token_text[m - 1], token);
        } else if (syn == 96) {
            printf("（无符号长整型数值 ，%s）\n", token);
            fprintf(fp1, "（无符号长整型数值 ,%s)\n", token);
            get_token[m++] = syn;
            strcpy(token_text[m - 1], token);
        } else if (syn == 95) {
            printf("（双精度数值 ，%s）\n", token);
            fprintf(fp1, "（双精度数值 ,%s)\n", token);
            get_token[m++] = syn;
            strcpy(token_text[m - 1], token);
        } else if (syn == 94) {
            printf("（单精度数值 ，%s）\n", token);
            fprintf(fp1, "（单精度数值 ,%s)\n", token);
            get_token[m++] = syn;
            strcpy(token_text[m - 1], token);
        } else if (syn == 93) {
            printf("（字符 ，%s）\n", token);
            fprintf(fp1, "（字符 ,%s)\n", token);
            get_token[m++] = syn;
            strcpy(token_text[m - 1], token);
        } else if (syn == 92) {
            printf("（字符串 ，%s）\n", token);
            fprintf(fp1, "（字符串 ,%s)\n", token);
            get_token[m++] = syn;
            strcpy(token_text[m - 1], token);
        } else if (syn >= 33 && syn <= 68)    //界符运算符
        {
            printf("（%s ，%s）\n", operator_name[syn - 33], operatorOrDelimiter[syn - 33]);
            fprintf(fp1, "（%s ，%s）\n", operator_name[syn - 33], operatorOrDelimiter[syn - 33]);
            get_token[m++] = syn;
            strcpy(token_text[m - 1], operatorOrDelimiter[syn - 33]);
        } else if (syn == -1) {
            printf("（换行符 ，\\n)\n");
            fprintf(fp1, "（换行符 ，\\n）\n");
            get_token[m++] = syn;
            strcpy(token_text[m - 1], "换行符");
        }
    }

    for (int i = 0; i < count_ID; i++) {
        printf("第%d个标识符：%s\n", i + 1, IDentifier[i]);
        fprintf(fp1, "第%d个标识符：%s\n", i + 1, IDentifier[i]);
    }
    fclose(fp1);

    column += define_num;
    column+=count_i+1;
    BiTree rm = program();

    printf("\n抽象语法树如下:\n\n");
    for(int i=0;i<count_i;i++)
    {
        printf("文件包含：include<%s>\n",include_file[i]+1);
    }
    ASTDisplay(rm, 0);

    if ((fp2 = fopen("/Users/wei/CLionProjects/wei/wei.cpp", "w+")) == NULL) {
        printf("打开文件错误！\n");
        printf("第%d行有错误!\n", column);
        exit(0);
    }
    for(int i=0;i<count_i;i++)
    {
        printf("#include<%s>\n",include_file[i]+1);
        fprintf(fp2,"#include<%s>\n",include_file[i]+1);
    }
    source_program(rm, 0);
    fclose(fp2);
}

//子程序--语句
BiTree statement() {
    switch (w) {
        case 44: {
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            BiTNode *root = (BiTNode *) malloc(sizeof(BiTNode));
            strcpy(root->name, ";");
            root->first_child = NULL;
            root->second_child = NULL;
            root->third_child = NULL;
            return root;
        }
        case 17:
        case 4:
        case 13:
        case 9:
        case 18:
        case 21: {
            BiTNode *root = LocalVar();
            return root;
        }

        case 8:                           //若为do-while语句
        {
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            if (w != 62) {
                printf("do后面不是大括号！\n");
                printf("第%d行有错误！\n");
                exit(10);
            }
            BiTNode *root = (BiTNode *) malloc(sizeof(BiTNode));
            strcpy(root->name, "do-while语句");
            root->first_child = ComplexList();
            root->third_child = NULL;
            if (w != 32) {
                printf("do后面不是while！\n");
                printf("第%d行有错误！\n");
                exit(0);
            }
            root->second_child = (BiTNode *) malloc(sizeof(BiTNode));
            strcpy(root->second_child->name, "循环条件");

            int j = num - 1;
            int i = get_token[j];
            char s[20] = "";
            while (strcmp(token_text[j], ")") != 0) {
                while (strcmp(token_text[j], "换行符") == 0) {
                    printf("第%d行出现错误！\n", column);
                    exit(0);
                }
                if (i == 100) {
                    int tag = 0;
                    for (int t = 0; t < count_local; t++) {
                        if (strcmp(Local[t], token_text[j]) == 0) {
                            tag = 1;
                            break;
                        }
                    }
                    for (int t = 0; t < count_formal; t++) {
                        if (strcmp(Formal[t], token_text[j]) == 0) {
                            tag = 1;
                            break;
                        }
                    }
                    if (tag != 1) {
                        for (int t = 0; t < count_ext; t++) {
                            if (strcmp(Ext[t], token_text[j]) == 0) {
                                tag = 1;
                                break;
                            }
                        }
                        if (tag != 1) {
                            printf("变量%s未定义！\n", token_text[j]);
                            printf("第%d行有错误！\n", column);
                            exit(20);
                        }
                    }
                }
                strcat(s, token_text[j]);
                j++;
                i = get_token[j];
            }
            strcat(s, ")");
            strcpy(expretion[ex++], s);
            root->second_child->first_child = exp(46);
            root->second_child->second_child = NULL;
            root->second_child->third_child = NULL;
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            return root;

        }
        case 16: {                        //分析条件语句if
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            if (w != 45) {
                printf("if后面不是左小括号！\n");
                w = get_token[num++];
                while (w == -1) {
                    column++;
                    w = get_token[num++];
                }
                return NULL;
            }
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            int j = num - 1;
            int i = get_token[j];
            char s[20] = "";
            while (strcmp(token_text[j], ")") != 0) {
                while (strcmp(token_text[j], "换行符") == 0) {
                    printf("第%d行出现错误！\n", column);
                    exit(0);
                }
                if (i == 100) {
                    int tag = 0;
                    for (int t = 0; t < count_local; t++) {
                        if (strcmp(Local[t], token_text[j]) == 0) {
                            tag = 1;
                            break;
                        }
                    }
                    for (int t = 0; t < count_formal; t++) {
                        if (strcmp(Formal[t], token_text[j]) == 0) {
                            tag = 1;
                            break;
                        }
                    }
                    if (tag != 1) {
                        for (int t = 0; t < count_ext; t++) {
                            if (strcmp(Ext[t], token_text[j]) == 0) {
                                tag = 1;
                                break;
                            }
                        }
                        if (tag != 1) {
                            printf("变量%s未定义！\n", token_text[j]);
                            printf("第%d行有错误！\n", column);
                            exit(20);
                        }
                    }
                }
                strcat(s, token_text[j]);
                j++;
                i = get_token[j];
            }
            strcpy(expretion[ex++], s);
            BiTree p1 = exp(46);             //结束符号为反小括号
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }

            BiTree p2 = NULL;                //判断if后面是单子句还是复合语句
            if (w == 62) {
                p2 = ComplexList();
            } else {
                p2 = statement();
            }

            BiTree p3 = (BiTree) malloc(sizeof(BiTNode));
            strcpy(p3->name, "else子句");
            p3->first_child = NULL;
            p3->second_child = NULL;
            p3->third_child = NULL;
            BiTNode *p4 = p3;
            int tag_1 = 0;

            if (w == 10)         //若为if-else子句
            {
                while (w == 10) {
                    if (p3 == NULL) {
                        p3 = (BiTNode *) malloc(sizeof(BiTNode));
                        p3->first_child = NULL;
                        p3->second_child = NULL;
                        p3->third_child = NULL;
                    }
                    w = get_token[num++];
                    while (w == -1) {
                        column++;
                        w = get_token[num++];
                    }
                    if (w == 16) {
                        w = get_token[num++];
                        while (w == -1) {
                            column++;
                            w = get_token[num++];
                        }
                        tag_1 = 1;
                    }
                    if (tag_1 == 0) {
                        if (w == 62)
                        {
                            p3->second_child = ComplexList();
                        }
                        else
                        {

                            int j = num - 1;
                            int i = get_token[j];
                            char s[20] = "";
                            while (strcmp(token_text[j], ";") != 0) {
                                while (strcmp(token_text[j], "换行符") == 0) {
                                    printf("第%d行出现错误！\n", column);
                                    exit(0);
                                }
                                if (i == 100) {
                                    int tag = 0;
                                    for (int t = 0; t < count_local; t++) {
                                        if (strcmp(Local[t], token_text[j]) == 0) {
                                            tag = 1;
                                            break;
                                        }
                                    }
                                    for (int t = 0; t < count_formal; t++) {
                                        if (strcmp(Formal[t], token_text[j]) == 0) {
                                            tag = 1;
                                            break;
                                        }
                                    }
                                    if (tag != 1) {
                                        for (int t = 0; t < count_ext; t++) {
                                            if (strcmp(Ext[t], token_text[j]) == 0) {
                                                tag = 1;
                                                break;
                                            }
                                        }
                                        if (tag != 1) {
                                            printf("变量%s未定义！\n", token_text[j]);
                                            printf("第%d行有错误！\n", column);
                                            exit(20);
                                        }
                                    }
                                }
                                strcat(s, token_text[j]);
                                j++;
                                i = get_token[j];
                            }
                            strcpy(expretion[ex++], s);
                            p3->second_child=exp(44);
                            w = get_token[num++];
                            while (w == -1) {
                                column++;
                                w = get_token[num++];
                            }
                        }
                        BiTNode *root = (BiTNode *) malloc(sizeof(BiTNode));
                        strcpy(root->name, "if-else子句");
                        strcpy(p3->name, "else子句");
                        root->first_child = p1;
                        root->second_child = p2;
                        root->third_child = p4;
                        return root;
                    } else {
                        if (w != 45) {
                            printf("else-if后面不是小括号！\n");
                            printf("第%d行有错误!\n", column);
                            exit(1);
                        } else {
                            w = get_token[num++];
                            while (w == -1) {
                                column++;
                                w = get_token[num++];
                            }
                            tag_1 = 0;
                            strcpy(p3->name, "else-if子句");
                            int j = num - 1;
                            int i = get_token[j];
                            char s[20] = "";
                            while (strcmp(token_text[j], ")") != 0) {
                                while (strcmp(token_text[j], "换行符") == 0) {
                                    printf("第%d行出现错误！\n", column);
                                    exit(0);
                                }
                                if (i == 100) {
                                    int tag = 0;
                                    for (int t = 0; t < count_local; t++) {
                                        if (strcmp(Local[t], token_text[j]) == 0) {
                                            tag = 1;
                                            break;
                                        }
                                    }
                                    for (int t = 0; t < count_formal; t++) {
                                        if (strcmp(Formal[t], token_text[j]) == 0) {
                                            tag = 1;
                                            break;
                                        }
                                    }
                                    if (tag != 1) {
                                        for (int t = 0; t < count_ext; t++) {
                                            if (strcmp(Ext[t], token_text[j]) == 0) {
                                                tag = 1;
                                                break;
                                            }
                                        }
                                        if (tag != 1) {
                                            printf("变量%s未定义！\n", token_text[j]);
                                            printf("第%d行有错误！\n", column);
                                            exit(20);
                                        }
                                    }
                                }
                                strcat(s, token_text[j]);
                                j++;
                                i = get_token[j];
                            }
                            strcpy(expretion[ex++], s);

                            p3->first_child = exp(46);
                            if(!(Isnumber(p3->first_child->name[0])||Isletter(p3->first_child->name[0])))
                            {
                                printf("else if里面不能为空！\n");
                                printf("第%d行有错误！\n",column);
                                exit(0);
                            }
                            w = get_token[num++];
                            while (w == -1) {
                                column++;
                                w = get_token[num++];
                            }

                            if (w == 62) p3->second_child = ComplexList();
                            else
                            {
                                int j = num - 1;
                                int i = get_token[j];
                                char s[20] = "";
                                while (strcmp(token_text[j], ";") != 0) {
                                    while (strcmp(token_text[j], "换行符") == 0) {
                                        printf("第%d行出现错误！\n", column);
                                        exit(0);
                                    }
                                    if (i == 100) {
                                        int tag = 0;
                                        for (int t = 0; t < count_local; t++) {
                                            if (strcmp(Local[t], token_text[j]) == 0) {
                                                tag = 1;
                                                break;
                                            }
                                        }
                                        for (int t = 0; t < count_formal; t++) {
                                            if (strcmp(Formal[t], token_text[j]) == 0) {
                                                tag = 1;
                                                break;
                                            }
                                        }
                                        if (tag != 1) {
                                            for (int t = 0; t < count_ext; t++) {
                                                if (strcmp(Ext[t], token_text[j]) == 0) {
                                                    tag = 1;
                                                    break;
                                                }
                                            }
                                            if (tag != 1) {
                                                printf("变量%s未定义！\n", token_text[j]);
                                                printf("第%d行有错误！\n", column);
                                                exit(20);
                                            }
                                        }
                                    }
                                    strcat(s, token_text[j]);
                                    j++;
                                    i = get_token[j];
                                }
                                strcpy(expretion[ex++], s);
                                p3->second_child=exp(44);
                                w = get_token[num++];
                                while (w == -1) {
                                    column++;
                                    w = get_token[num++];
                                }
                            }
                            if(w==10)
                            {
                                p3->third_child = (BiTNode *) malloc(sizeof(BiTNode));
                                p3 = p3->third_child;
                                p3->first_child = NULL;
                                p3->second_child = NULL;
                                p3->third_child = NULL;
                            }
                        }
                    }
                }
                BiTNode *root = (BiTNode *) malloc(sizeof(BiTNode));
                strcpy(root->name, "if-else子句");
                root->first_child = p1;
                root->second_child = p2;
                root->third_child = p4;
                return root;
            } else {
                BiTNode *root = (BiTNode *) malloc(sizeof(BiTNode));
                strcpy(root->name, "if子句");
                root->first_child = p1;
                root->second_child = p2;
                root->third_child = NULL;
                return root;
            }
        }

        case 62: {                       //为大括号
            BiTree root = ComplexList();
            return root;
        }
        case 32: {                       //为while
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            if (w != 45) {
                printf("while后面不是左小括号！\n");
                printf("第%d行有错误!\n", column);
                exit(0);
            } else {
                w = get_token[num++];
                while (w == -1) {
                    column++;
                    w = get_token[num++];
                }
                BiTree root = (BiTree) malloc(sizeof(BiTNode));
                strcpy(root->name, "while语句");
                int j = num - 1;
                int i = get_token[j];
                char s[20] = "";
                while (strcmp(token_text[j], ")") != 0) {
                    while (strcmp(token_text[j], "换行符") == 0) {
                        printf("第%d行出现错误！\n", column);
                        exit(0);
                    }
                    if (i == 100) {
                        int tag = 0;
                        for (int t = 0; t < count_local; t++) {
                            if (strcmp(Local[t], token_text[j]) == 0) {
                                tag = 1;
                                break;
                            }
                        }
                        for (int t = 0; t < count_formal; t++) {
                            if (strcmp(Formal[t], token_text[j]) == 0) {
                                tag = 1;
                                break;
                            }
                        }
                        if (tag != 1) {
                            for (int t = 0; t < count_ext; t++) {
                                if (strcmp(Ext[t], token_text[j]) == 0) {
                                    tag = 1;
                                    break;
                                }
                            }
                            if (tag != 1) {
                                printf("变量%s未定义！\n", token_text[j]);
                                printf("第%d行有错误！\n", column);
                                exit(20);
                            }
                        }
                    }
                    strcat(s, token_text[j]);
                    j++;
                    i = get_token[j];
                }
                strcpy(expretion[ex++], s);
                root->first_child = exp(46);        //以反小括号为结束符
                w = get_token[num++];
                while (w == -1) {
                    column++;
                    w = get_token[num++];
                }
                root->second_child = statement();
                root->third_child = NULL;
                return root;
            }
        }

        case 14:                       //为for语句
        {
            w = get_token[num++];      //w为左括号
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            if (w != 45) {
                printf("for后面不是左小括号!\n");
                printf("第%d行有错误!\n", column);
                exit(0);
            } else {
                w = get_token[num++];
                while (w == -1) {
                    column++;
                    w = get_token[num++];
                }
                BiTree root = (BiTree) malloc(sizeof(BiTNode));
                strcpy(root->name, "for语句");
                root->first_child = (BiTree) malloc(sizeof(BiTNode));
                int j = num - 1;
                int i = get_token[j];
                char s[20] = "";
                while (strcmp(token_text[j], ";") != 0) {
                    while (strcmp(token_text[j], "换行符") == 0) {
                        printf("第%d行出现错误！\n", column);
                        exit(0);
                    }
                    if (i == 100) {
                        int tag = 0;
                        for (int t = 0; t < count_local; t++) {
                            if (strcmp(Local[t], token_text[j]) == 0) {
                                tag = 1;
                                break;
                            }
                        }
                        for (int t = 0; t < count_formal; t++) {
                            if (strcmp(Formal[t], token_text[j]) == 0) {
                                tag = 1;
                                break;
                            }
                        }
                        if (tag != 1) {
                            for (int t = 0; t < count_ext; t++) {
                                if (strcmp(Ext[t], token_text[j]) == 0) {
                                    tag = 1;
                                    break;
                                }
                            }
                            if (tag != 1) {
                                printf("变量%s未定义！\n", token_text[j]);
                                printf("第%d行有错误！\n", column);
                                exit(20);
                            }
                        }
                    }
                    strcat(s, token_text[j]);
                    j++;
                    i = get_token[j];
                }
                strcpy(expretion[ex++], s);
                root->first_child->first_child = exp(44);
                w = get_token[num++];
                while (w == -1) {
                    column++;
                    w = get_token[num++];
                }
                j = num - 1;
                i = get_token[j];
                strcpy(s, "");
                while (strcmp(token_text[j], ";") != 0) {
                    while (strcmp(token_text[j], "换行符") == 0) {
                        printf("第%d行出现错误！\n", column);
                        exit(0);
                    }
                    if (i == 100) {
                        int tag = 0;
                        for (int t = 0; t < count_local; t++) {
                            if (strcmp(Local[t], token_text[j]) == 0) {
                                tag = 1;
                                break;
                            }
                        }
                        for (int t = 0; t < count_formal; t++) {
                            if (strcmp(Formal[t], token_text[j]) == 0) {
                                tag = 1;
                                break;
                            }
                        }
                        if (tag != 1) {
                            for (int t = 0; t < count_ext; t++) {
                                if (strcmp(Ext[t], token_text[j]) == 0) {
                                    tag = 1;
                                    break;
                                }
                            }
                            if (tag != 1) {
                                printf("变量%s未定义！\n", token_text[j]);
                                printf("第%d行有错误！\n", column);
                                exit(20);
                            }
                        }
                    }
                    strcat(s, token_text[j]);
                    j++;
                    i = get_token[j];
                }
                strcpy(expretion[ex++], s);
                root->first_child->second_child = exp(44);
                if(!(Isnumber(root->first_child->second_child->name[0])||Isletter(root->first_child->second_child->name[0])))
                {
                    printf("for的循环条件里面不能为空！\n");
                    printf("第%d行有错误！\n",column);
                    exit(0);
                }
                w = get_token[num++];
                while (w == -1) {
                    column++;
                    w = get_token[num++];
                }
                j = num - 1;
                i = get_token[j];
                strcpy(s, "");
                while (strcmp(token_text[j], ")") != 0) {
                    while (strcmp(token_text[j], "换行符") == 0) {
                        printf("第%d行出现错误！\n", column);
                        exit(0);
                    }
                    if (i == 100) {
                        int tag = 0;
                        for (int t = 0; t < count_local; t++) {
                            if (strcmp(Local[t], token_text[j]) == 0) {
                                tag = 1;
                                break;
                            }
                        }
                        for (int t = 0; t < count_formal; t++) {
                            if (strcmp(Formal[t], token_text[j]) == 0) {
                                tag = 1;
                                break;
                            }
                        }
                        if (tag != 1) {
                            for (int t = 0; t < count_ext; t++) {
                                if (strcmp(Ext[t], token_text[j]) == 0) {
                                    tag = 1;
                                    break;
                                }
                            }
                            if (tag != 1) {
                                printf("变量%s未定义！\n", token_text[j]);
                                printf("第%d行有错误！\n", column);
                                exit(20);
                            }
                        }
                    }
                    strcat(s, token_text[j]);
                    j++;
                    i = get_token[j];
                }
                strcpy(expretion[ex++], s);
                root->first_child->third_child = exp(46);
                w = get_token[num++];
                while (w == -1) {
                    column++;
                    w = get_token[num++];
                }
                strcpy(root->first_child->name, "for语句循环条件");
                root->second_child = statement();
                root->third_child = NULL;
                return root;
            }
        }

        case 20:                           //为return语句
        {
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            BiTree root = (BiTree) malloc(sizeof(BiTNode));
            strcpy(root->name, "return语句");
            int j = num - 1;
            int i = get_token[j];
            char s[20] = "";
            while (strcmp(token_text[j], ";") != 0) {
                while (strcmp(token_text[j], "换行符") == 0) {
                    printf("第%d行出现错误！\n", column);
                    exit(0);
                }
                if (i == 100) {
                    int tag = 0;
                    for (int t = 0; t < count_local; t++) {
                        if (strcmp(Local[t], token_text[j]) == 0) {
                            tag = 1;
                            break;
                        }
                    }
                    for (int t = 0; t < count_formal; t++) {
                        if (strcmp(Formal[t], token_text[j]) == 0) {
                            tag = 1;
                            break;
                        }
                    }
                    if (tag != 1) {
                        for (int t = 0; t < count_ext; t++) {
                            if (strcmp(Ext[t], token_text[j]) == 0) {
                                tag = 1;
                                break;
                            }
                        }
                        if (tag != 1) {
                            printf("变量%s未定义！\n", token_text[j]);
                            printf("第%d行有错误！\n", column);
                            exit(20);
                        }
                    }
                }
                strcat(s, token_text[j]);
                j++;
                i = get_token[j];
            }
            strcpy(expretion[ex++], s);
            root->first_child = exp(44);       //以分号为结束符
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            root->second_child = NULL;
            root->third_child = NULL;
            return root;
        }
        case 2:                       //为break语句或者continue语句
        case 6: {
            BiTree root = (BiTNode *) malloc(sizeof(BiTNode));
            strcpy(root->name, token_text[num - 1]);
            root->first_child = NULL;
            root->second_child = NULL;
            root->third_child = NULL;
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            if (w != 44) {
                printf("%s后面不是分号！\n", token_text[num - 2]);
                printf("第%d行有错误!\n", column);
                exit(0);
            }
            w = get_token[num++];
            while (w == -1) {
                column++;
                w = get_token[num++];
            }
            return root;
        }

        case 45:         //为（
        case 100:        //为标识符
        case 94:         //为常数
        case 95:
        case 96:
        case 97:
        case 98:
        case 99: {
            int j = num - 1;
            int i = get_token[j];
            char s[20] = "";
            while (strcmp(token_text[j], ";") != 0) {
                while (strcmp(token_text[j], "换行符") == 0) {
                    printf("第%d行出现错误！\n", column);
                    exit(0);
                }
                if (i == 100) {
                    int tag = 0;
                    for (int t = 0; t < count_local; t++) {
                        if (strcmp(Local[t], token_text[j]) == 0) {
                            tag = 1;
                            break;
                        }
                    }
                    for (int t = 0; t < count_formal; t++) {
                        if (strcmp(Formal[t], token_text[j]) == 0) {
                            tag = 1;
                            break;
                        }
                    }
                    if (tag != 1) {
                        for (int t = 0; t < count_ext; t++) {
                            if (strcmp(Ext[t], token_text[j]) == 0) {
                                tag = 1;
                                break;
                            }
                        }
                        if (tag != 1) {
                            printf("变量%s未定义！\n", token_text[j]);
                            printf("第%d行有错误！\n", column);
                            token_text[num - 1];
                            exit(20);
                        }
                    }
                }
                strcat(s, token_text[j]);
                j++;
                i = get_token[j];
            }
            strcpy(expretion[ex++], s);
            BiTree root = exp(44);       //分号为结束符
            if (root != NULL) {
                w = get_token[num++];
                while (w == -1) {
                    column++;
                    w = get_token[num++];
                }
            }
            return root;
        }

        case 63: {                       //为右大括号，结束语句
            return NULL;
        }

        default: {
            errors += 1;
            printf("语法错误！（语句）\n");
            printf("第%d行有错误!\n", column);
            exit(0);
        }
    }
}

//子程序--语句序列
BiTree SentenceList() {
    BiTree root = NULL;
    BiTNode *r1;                              //调用处理一条语句的子程序；返回其子树根指针r1
    r1 = statement();
    if (r1 == NULL)                           //没有分析到1条语句，errors>0时处理错误
    {
        if (errors > 0) {
            printf("出现错误！（语句序列）\n");
            return NULL;
        } else {
            printf("语句序列处理结束！\n");
            return NULL;
        }
    } else {
        root = (BiTree) malloc(sizeof(BiTNode));
        strcpy(root->name, "语句序列");
        root->first_child = r1;
        root->second_child = SentenceList();
        root->third_child = NULL;
        return root;
    }
}








