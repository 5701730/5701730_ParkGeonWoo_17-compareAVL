#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Node {
    int key;
    struct Node* left, * right;
} Node;

int compareCount = 0; // 비교 횟수
int searchCount = 0;  // 탐색 횟수

// AVL 트리 삽입 함수
Node* insertAVL(Node* root, int key) {
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (key < root->key)
        root->left = insertAVL(root->left, key);
    else if (key > root->key)
        root->right = insertAVL(root->right, key);
    return root;
}

// AVL 탐색 함수
Node* searchAVL(Node* root, int key) {
    while (root != NULL) {
        compareCount++;
        if (key < root->key)
            root = root->left;
        else if (key > root->key)
            root = root->right;
        else
            return root;
    }
    return NULL;
}

// AVL 배치 작업
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int operation = rand() % 3; // 0: 삽입, 1: 삭제, 2: 탐색 일때 
        int key = rand() % 1000;
        if (operation == 0) {
            root = insertAVL(root, key); // AVL을 삽입
        }
        else if (operation == 2) {
            searchCount++;
            searchAVL(root, key); // AVL을 탐색
        }
    }
}

// 이진 탐색 트리 삽입 함수
Node* insertBST(Node* root, int key) {
    if (root == NULL) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (key < root->key)
        root->left = insertBST(root->left, key);
    else if (key > root->key)
        root->right = insertBST(root->right, key);
    return root;
}

// 이진 탐색 트리 탐색 함수
Node* searchBST(Node* root, int key) {
    while (root != NULL) {
        compareCount++;
        if (key < root->key)
            root = root->left;
        else if (key > root->key)
            root = root->right;
        else
            return root;
    }
    return NULL;
}

// 이진 탐색 트리 배치 
void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int operation = rand() % 3; // 0: 삽입, 1: 삭제, 2: 탐색 설정ㅇ함
        int key = rand() % 1000;
        if (operation == 0) {
            root = insertBST(root, key); // BST 삽입
        }
        else if (operation == 2) {
            searchCount++;
            searchBST(root, key); // BST 탐색
        }
    }
}

// 트리 메모리 해제
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// 1초 대기 함수
void waitOneSecond() {
    time_t startTime = time(NULL);
    while (time(NULL) == startTime); // 현재 시간이 1초 증가할 때까지 대기
}


int main(int argc, char* argv[]) {
    for (int i = 0; i < 3; i++) { // 3번 실행
        Node* root = NULL;
        srand(time(NULL)); 
        float allCount = 0.0;

        // 과제에서 제시된 AVL에 대한 2000회 Batch 작업을 수행한다.
        doAVLBatch(root);
        allCount = (float)compareCount / searchCount;
        printf("average AVL compare count: %.2f\n", allCount);

        // 후위순회하며 AVL트리로 만들어졌던 모든 데이터를 free
        freeTree(root);
        root = NULL;
        compareCount = allCount = 0;
        

        // 과제에서 제시된 Binary Search Tree Batch를 수행한다.
        doBinaryBatch(root);
        allCount = (float)compareCount / searchCount;
        printf("average Bin compare count: %.2f\n", allCount);

        freeTree(root);

        // 1초 대기를 위하여
        if (i < 2) waitOneSecond(); // 마지막 반복에서는 대기를 하지 않음
    }
    return 0;
}









