//
//  main.c
//  线索二叉树
//
//  Created by neotv on 2020/4/30.
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

/*
 Link = 0，表示指向左右子树
 Thread = 1, 表示指向前驱或者后继
 */
typedef enum { Link, Thread } PointerTag;

typedef struct BiThrNode {
    TElemType data;
    struct BiThrNode *leftChild, *rightChild;
    PointerTag LTag, RTag;
}BiThrNode, *BiThrTree;


// 构建一个二叉树的字符串
typedef TElemType String[MAX_TREE_SIZE];
String str;
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

// 前序创建二叉树
int idx;
Status createBitThrTree(BiThrTree *T) {
    
    TElemType ch = str[idx++];

    if (ch == '#') {
        *T = NULL;
    }else {
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        if (*T == NULL) {
            exit(0);
        }
        (*T)->data = ch;
        
        createBitThrTree(&(*T)->leftChild);
        if ((*T)->leftChild) {
            (*T)->LTag = Link;
        }
        
        createBitThrTree(&(*T)->rightChild);
        if ((*T)->rightChild) {
            (*T)->RTag = Link;
        }
    }
    
    return OK;
}

// 中序遍历线索化
void inThreading(BiThrTree T, BiThrNode **pre) {
    if (!T) {
        return;
    }
    
    inThreading(T->leftChild, pre);
    
    if (!T->leftChild) {
        T->LTag = Thread;
        T->leftChild = *pre;
    }
    
    if (!(*pre)->rightChild) {
        (*pre)->RTag = Thread;
        (*pre)->rightChild = T;
    }
    
    *pre = T;
    
    inThreading(T->rightChild, pre);
}

// 为线索二叉树添加头结点
void inOrderThreading(BiThrTree T, BiThrNode **head) {
    *head = (BiThrTree)malloc(sizeof(BiThrNode));
    if (head == NULL) {
        return;
    }
    (*head)->LTag = Link;
    (*head)->RTag = Thread;
    (*head)->rightChild = *head;
    if (!T) {
        (*head)->leftChild = *head;
        return;
    }
    
    BiThrTree pre = *head;
    (*head)->leftChild = T;
    inThreading(T, &pre);
    
    pre->rightChild = *head;
    pre->RTag = Thread;
    (*head)->rightChild = pre;
}


//非递归遍历线索二叉树
//Status InOrderTraverse(BiThrTree T) {
//  BiThrNode *p = T->leftChild;
//  while(p!=T){
//    while(p->LTag==Link) p = p->leftChild;    //走向左子树的尽头
//    printf("%c",p->data );
//    while(p->RTag==Thread && p->rightChild!=T) {  //访问该结点的后续结点
//      p = p->rightChild;
//      printf("%c",p->data );
//    }
//    p = p->rightChild;
//  }
//  return OK;
//}

void InOrderTraverse(BiThrTree T) {
    BiThrNode *p = T->leftChild;

    while (p != T) {
        while (p->LTag == Link) {
            p = p->leftChild;
        }
        printf("%c  ", p->data);
        
        while (p->RTag == Thread && p->rightChild != T) {
            p = p->rightChild;
            printf("%c  ", p->data);
        }
        p = p->rightChild;
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    strAssign(str, "ABDH#K###E##CFI###G#J##");
    
    BiThrTree T;
    createBitThrTree(&T);
    
    BiThrTree head;
    inOrderThreading(T, &head);
    
    InOrderTraverse(head);
    
    printf("\n");
    
    return 0;
}
