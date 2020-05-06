//
//  main.c
//  哈夫曼树
//
//  Created by neotv on 2020/4/30.
//  Copyright © 2020 neotv. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MaxBit = 4;

#define maxN 10

typedef struct HaffNode{
    int weight;
    int flag;
    int parent;
    int leftChild;
    int rightChild;
}HaffNode, *HaffTree;

typedef struct HaffCode{
    int bit[MaxBit];
    int start;
    int weight;
}HaffCode;


void createHaffTree(int weights[], int n, HaffTree haffTree) {
    /* 1. 初始化哈夫曼树 */
    int maxNodeCount = 2*n - 1;
    for (int i = 0; i < maxNodeCount; i++) {
        if (i < n) {
            haffTree[i].weight = weights[i];
        }else {
            haffTree[i].weight = 0;
        }
        haffTree[i].parent     = 0;
        haffTree[i].flag       = 0;
        haffTree[i].leftChild  = -1;
        haffTree[i].rightChild = -1;
    }
    
    /* 构建哈夫曼树n-1个非叶子结点 */
    int min1, min2;
    int x1, x2;
    for (int i = 0; i < n - 1; i++) {
        min1 = min2 = UINT16_MAX;
        x1 = x2 = 0;
        
        /* 找出森林中权值最小的2个结点 */
        for (int j = 0; j < n + i; j++) {
            if (haffTree[j].weight < min1 && haffTree[j].flag == 0) {
                min2 = min1;
                x2 = x1;
                min1 = haffTree[j].weight;
                x1 = j;
            }else if (haffTree[j].weight < min2 && haffTree[j].flag == 0) {
                min2 = haffTree[j].weight;
                x2 = j;
            }
        }
        
        /* 2个结点，合成一棵新树 */
        haffTree[x1].parent = n + i;
        haffTree[x2].parent = n + i;
        
        /* 将用过的结点标记为1，表示从森林中删除 */
        haffTree[x1].flag = 1;
        haffTree[x2].flag = 1;
        
        /* 修改新树的权值 */
        haffTree[n + i].weight = haffTree[x1].weight + haffTree[x2].weight;
        
        /* 修改新树的左右子树 */
        haffTree[n + i].leftChild = x1;
        haffTree[n + i].rightChild = x2;
    }
}

/*
2.哈夫曼编码
由n个结点的哈夫曼树haffTree构造哈夫曼编码haffCode
7 5 2 4
*/
void initHaffCode(HaffTree haffTree, int n, HaffCode codes[]) {
    HaffCode *code = malloc(sizeof(HaffCode));
    int child, parent;
    
    for (int i = 0; i < n; i++) {
        
        code->start = 0;
        
        code->weight = haffTree[i].weight;
        
        child = i;
        
        parent = haffTree[i].parent;
        
        while (parent != 0) {
            if (haffTree[parent].leftChild == child) {
                code->bit[code->start] = 0;
            }else code->bit[code->start] = 1;
            
            code->start++;
            
            child = parent;
            
            parent = haffTree[parent].parent;
        }
        
        int temp = 0;
        
        for (int j = code->start - 1; j >= 0; j--) {
            temp = code->start - j - 1;
            codes[i].bit[temp] = code->bit[j];
        }
        
        codes[i].start = code->start;
        codes[i].weight = code->weight;
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");

    int n = 4;
    int maxNodeCount = 2*n - 1;
    int weights[] = {7, 5, 2, 4};
        
    if (n > maxN) {
        printf("定义的N越界，修改为MaxN\n");
        return 0;
    }
    
    HaffTree haffTree = malloc(sizeof(HaffNode) * maxNodeCount);
    
    createHaffTree(weights, n, haffTree);

    HaffCode *codes = malloc(sizeof(HaffCode) * n);
    
    initHaffCode(haffTree, n, codes);
    
    //3.
    int m = 0;
    for (int i = 0; i<n; i++)
    {
        printf("Weight = %d\n",codes[i].weight);
        for (int j = 0; j<codes[i].start; j++)
            printf("%d",codes[i].bit[j]);
        m = m + codes[i].weight*codes[i].start;
         printf("\n");
    }
    printf("Huffman's WPS is:%d\n",m);

    
    return 0;
}
