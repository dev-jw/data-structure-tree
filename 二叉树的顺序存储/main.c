//
//  main.c
//  二叉树的顺序存储
//
//  Created by neotv on 2020/4/28.
//  Copyright © 2020 neotv. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <math.h>

typedef int Status;
#define OK 1;
#define ERROR 0;
#define TRUE 1;
#define FALSE 0;

#define MAX_TREE_SIZE 100
typedef char TElemType;
TElemType Nil = '\0';
typedef TElemType SeqBiTree[MAX_TREE_SIZE];

void visit(TElemType e) {
    printf("%c ", e);
}

// 构造二叉树
Status initTree(SeqBiTree T) {
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        T[i] = Nil;
    }
    return OK;
}

// 清空二叉树
#define clearTree initTree

// 创建二叉树 - 按前序遍历的方式插入
Status createTree(SeqBiTree T, char *S) {
    /*
   1  0                  A
   2  1 2            B       C
   3  3 4 5 6     D    E   F    G
     */
    char *p = S;
    int i = 0;
    while (p != '\0' && i < strlen(S)) {
        T[i] = *p;
        if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != Nil) {
            printf("出现无双亲结点的非根结点");
            return ERROR;
        }
        i++;
        p++;
    }
    
    while (i < MAX_TREE_SIZE) {
        T[i] = Nil;
        i++;
    }
    return OK;
}

// 二叉树是否为空
int isEmptyTree(SeqBiTree T) {
    if (T[0] == Nil) {
        return TRUE;
    }else return FALSE;
}

// 二叉树的深度
/* 深度为h的二叉树最多有2^h-1个结点（h>=1），最少有h个结点 */
int deepOfTree(SeqBiTree T) {
    /* 深度 */
    int j = -1;
    /* 记录最后一个结点位置 */
    int i;
    
    for (i = MAX_TREE_SIZE; i >=0; i--) {
        if (T[i] != Nil) {
            break;
        }
    }
    
    do {
        j++;
    } while (powl(2, j) <= i);
    return j;
}

// 处于{层，本层序号}的结点值
TElemType valueOfPosition(SeqBiTree T, int leval, int order) {
    return T[(int)pow(2, leval) + order - 2];
}

/* 获取结点值e的双亲结点的值 */
TElemType parent(SeqBiTree T, TElemType e) {
    if (T[0] == Nil) {
        return Nil;
    }
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        if (T[i] == e) {
            return T[ (i + 1) / 2 -1];
        }
    }
    return Nil;
}

/* 获取某个结点的左孩子 */
TElemType leftChild(SeqBiTree T, TElemType e){
        if (T[0] == Nil) {
        return Nil;
    }
    for (int i = 0 ; i < MAX_TREE_SIZE-1; i++) {
        if (T[i] == e) {
            return T[ i * 2 + 1 ];
        }
    }
    return Nil;
}

/* 获取某个结点的右孩子 */
TElemType rightChild(SeqBiTree T, TElemType e){
        if (T[0] == Nil) {
        return Nil;
    }
    for (int i = 0 ; i < MAX_TREE_SIZE-1; i++) {
        if (T[i] == e) {
            return T[ i * 2 + 2 ];
        }
    }
    return Nil;
}

// 二叉树的前序遍历
void PreTraverse(SeqBiTree T,int e){
    
    //打印结点数据
    visit(T[e]);
    
    //先序遍历左子树
    if (T[2 * e + 1] != Nil) {
        PreTraverse(T, 2*e+1);
    }
    //最后先序遍历右子树
    if (T[2 * e + 2] != Nil) {
        PreTraverse(T, 2*e+2);
    }
}

Status PreOrderTraverse(SeqBiTree T){
    
    //树不为空
    if (!isEmptyTree(T)) {
        PreTraverse(T, 0);
    }
    printf("\n");
    return  OK;
}

// 二叉树的中序遍历
void InTraverse(SeqBiTree T, int e){
    
    /* 左子树不空 */
    if (T[2*e+1] != Nil)
        InTraverse(T, 2*e+1);
    
    visit(T[e]);
    
    /* 右子树不空 */
    if (T[2*e+2] != Nil)
        InTraverse(T, 2*e+2);
}

Status InOrderTraverse(SeqBiTree T){
    
    /* 树不空 */
    if (!isEmptyTree(T)) {
        InTraverse(T, 0);
    }
    printf("\n");
    return OK;
}

// 二叉树的后序遍历
void PostTraverse(SeqBiTree T,int e)
{   /* 左子树不空 */
    if(T[2*e+1]!=Nil)
        PostTraverse(T,2*e+1);
    /* 右子树不空 */
    if(T[2*e+2]!=Nil)
        PostTraverse(T,2*e+2);
    
    visit(T[e]);
}
Status PostOrderTraverse(SeqBiTree T)
{
    if(!isEmptyTree(T)) /* 树不空 */
        PostTraverse(T,0);
    printf("\n");
    return OK;
}

// 层次遍历
void levalOrder(SeqBiTree T) {
    /* 找到最后一个非空结点的序号 */
    int i = MAX_TREE_SIZE - 1;
    while (T[i] == Nil) {
        i--;
    }
    
    /* 从根结点起,按层序遍历二叉树 */
    for (int j = 0; j <= i; j++) {
        /* 只遍历非空结点 */
        if (T[j] != Nil) {
            visit(T[j]);
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    SeqBiTree T;
    
    initTree(T);
    
    createTree(T, "ABCDEFG");
    
    return 0;
}
    
