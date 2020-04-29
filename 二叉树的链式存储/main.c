//
//  main.c
//  二叉树的链式存储
//
//  Created by neotv on 2020/4/28.
//  Copyright © 2020 neotv. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Status;
#define OK 1;
#define ERROR 0;
#define TRUE 1;
#define FALSE 0;

#define MAX_TREE_SIZE 100
typedef char TElemType;
TElemType Nil = 0;

typedef struct BTreeNode {
    TElemType data;
    struct BTreeNode *leftTree;
    struct BTreeNode *rightTree;
}BTreeNode, *BitTree;

// 构建一个二叉树的字符串
typedef TElemType String[MAX_TREE_SIZE];
Status strAssign(String S, char *chars) {
    if (strlen(chars) > MAX_TREE_SIZE) {
        return ERROR;
    }else {
        int i = 0;
        char *ch = chars;
        while (*ch != '\0') {
            S[i] = *ch;
            ch++;
            i++;
        }
        return TRUE;
    }
    return OK;
}

// 打印
void visit(TElemType e) {
    printf("%c ", e);
}

// 构造二叉树
Status initTree(BitTree *T) {
    *T = NULL;
    return OK;
}

// 清空二叉树
Status clearTree(BitTree *T) {
    if (*T) {
        if ((*T)->leftTree) {
            clearTree(&(*T)->leftTree);
        }
        if ((*T)->rightTree) {
            clearTree(&(*T)->rightTree);
        }
        free(*T);
        *T = NULL;
    }
    return OK;
}

// 销毁二叉树
#define DestroyTree clearTree

// 创建二叉树 - 按前序遍历的方式插入
String str;
int idx = 0;
Status createTree(BitTree *T) {
    TElemType ch = str[idx++];

    if (ch != '#') {
        *T = (BitTree)malloc(sizeof(BTreeNode));
        (*T)->data = ch;
        
        createTree(&(*T)->leftTree);
        createTree(&(*T)->rightTree);
    }else {
        *T = NULL;
    }
    return OK;
}

// 二叉树是否为空
Status isEmptyTree(BitTree T) {
    if (T) {
        return FALSE;
    }else return TRUE;
}

// 二叉树的深度
int deepOfTree(BitTree T) {
    int left, right;
    
    if (!T) {
        return 0;
    }
    
    if (T->leftTree) {
        left = deepOfTree(T->leftTree);
    }else {
        left = 0;
    }
    
    if (T->rightTree) {
        right = deepOfTree(T->rightTree);
    }else {
        right = 0;
    }
    
    return left > right ? left + 1 : right + 1;
}

// 二叉树的前序遍历
void preOrderTraverse(BitTree T) {
    if (T) {
        visit(T->data);
        preOrderTraverse(T->leftTree);
        preOrderTraverse(T->rightTree);
    }
}

// 非递归实现
// 利用栈的思想
void preOrder(BitTree T) {
    BTreeNode *stack[MAX_TREE_SIZE];
    int top = -1;
    stack[++top] = T;
    
    BTreeNode *temp;
    while (top != -1) {
        while ((temp = stack[top]) != NULL) {
            visit(temp->data);
            stack[++top] = temp->leftTree;
        }
        top--;
        if (top != -1) {
            temp = stack[top--];
            stack[++top] = temp->rightTree;
        }
    }
}

void preOrderEx(BitTree T) {
    BTreeNode *stack[MAX_TREE_SIZE];
    int top = -1;
    BTreeNode *temp = T;
    while (temp || top != -1) {
        if (temp) {
            stack[++top] = temp;
            visit(temp->data);
            temp = temp->leftTree;
        }else {
            temp = stack[top--];
            temp = temp->rightTree;
        }
    }
}

// 二叉树的中序遍历
void inOrderTraverse(BitTree T) {
    if (T) {
        inOrderTraverse(T->leftTree);
        visit(T->data);
        inOrderTraverse(T->rightTree);
    }
}

void inOrder(BitTree T) {
    BTreeNode *stack[MAX_TREE_SIZE];
    int top = -1;
    stack[++top] = T;
    
    BTreeNode *temp;
    while (top != -1) {
        while ((temp = stack[top]) != NULL) {
            stack[++top] = temp->leftTree;
        }
        top--;
        if (top != -1) {
            temp = stack[top--];
            visit(temp->data);
            stack[++top] = temp->rightTree;
        }
    }
}

void inOrderEx(BitTree T) {
    BTreeNode *stack[MAX_TREE_SIZE];
    int top = -1;
    BTreeNode *temp = T;
    while (temp || top != -1) {
        if (temp) {
            stack[++top] = temp;
            temp = temp->leftTree;
        }else {
            temp = stack[top--];
            visit(temp->data);
            temp = temp->rightTree;
        }
    }
}

// 二叉树的后序遍历
void postOrderTraverse(BitTree T) {
    if (T) {
        postOrderTraverse(T->leftTree);
        postOrderTraverse(T->rightTree);
        visit(T->data);
    }
}

// 非递归实现
/**
 1. 先从左遍历到头
 2. 判断当前的结点是否有右子树，或者说有右子树并且没有被访问，则进栈，再从左遍历到头
 3. 到头后如果没有孩子，或者有右子树但是被访问过，则输出结点信息，并将游标指向它
 */
void postOrder(BitTree T) {
    BTreeNode *stack[MAX_TREE_SIZE];
    int top = -1;
    BTreeNode *temp = T;
    BTreeNode *cur  = NULL; // 游标指向上一个被访问的结点
    
    while (temp || top != -1) {
        if (temp) {
            stack[++top] = temp;
            temp = temp->leftTree;
        }else {
            temp = stack[top];
            if (temp->rightTree && temp->rightTree != cur) {
                temp = temp->rightTree;
                stack[++top] = temp;
                temp = temp->leftTree;
            }else {
                temp = stack[top--];
                visit(temp->data);
                cur = temp;
                temp = NULL;
            }
        }
    }
}

// 层次遍历
void levalTree(BitTree T, int leval) {
    if (T == NULL) {
        return;
    }else if (leval == 1) {
        visit(T->data);
    }else {
        levalTree(T->leftTree, leval -1);
        levalTree(T->rightTree, leval -1);
    }
}

void levalOrder(BitTree T) {
    int deep = deepOfTree(T);
    int i = 1;
    while (i != deep) {
        levalTree(T, i++);
    }
}




int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    BitTree T;
    initTree(&T);
        
    strAssign(str, "ABDH#K###E##CFI###G#J##");
    createTree(&T);

    printf("=====先序遍历=====\n");
    preOrderTraverse(T);
    printf("\n");

    preOrder(T);
    printf("\n");
    
    preOrderEx(T);
    printf("\n");
    
    printf("=====中序遍历=====\n");
    inOrderTraverse(T);
    printf("\n");
    
    inOrder(T);
    printf("\n");
    
    inOrderEx(T);
    printf("\n");
    
    printf("=====后序遍历=====\n");
    postOrderTraverse(T);
    printf("\n");
    
    postOrder(T);
    printf("\n");
    
    printf("=====层次遍历=====\n");
    levalOrder(T);
    printf("\n");

    return 0;
}
