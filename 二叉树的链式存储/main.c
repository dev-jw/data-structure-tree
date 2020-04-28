//
//  main.c
//  二叉树的链式存储
//
//  Created by neotv on 2020/4/28.
//  Copyright © 2020 neotv. All rights reserved.
//

#include <stdio.h>

#define MAX_TREE_SIZE 100

typedef int TElemType;

TElemType Nil = 0;

typedef struct TreeNode {
    TElemType data;
    struct TreeNode *leftTree;
    struct TreeNode *rightTree;
}BitTreeNode, *BitTree;

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
