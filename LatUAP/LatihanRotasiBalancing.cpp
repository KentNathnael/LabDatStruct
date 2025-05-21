#include <stdio.h>
#include <stdlib.h>

#define maxSize 100

struct nodes{
    int value;
    int height;
    nodes* left;
    nodes* right;
}*root = NULL;

nodes* createNewNode(int value){
    nodes* c = (nodes*)malloc(sizeof(nodes));
    c->value = value;
    c->height = 1;
    c->left = NULL;
    c->right = NULL;

    return c;
}

int max(int a, int b){
    return (a > b) ? a : b; // kalo a > b return a dan sebaliknya
}

int getHeight(nodes* c){
    if(c == NULL){
        return 0;
    }
    else{
        return c->height;
    }
}

int getBalance(nodes* c){
    return getHeight(c->left) - getHeight(c->right);
}

nodes* rightRotate(nodes* c){
    if(c == NULL || c->left == NULL) return c;

    nodes* currLeft = c->left;
    nodes* currLeftRigt = c->left->right;

    c->left->right = c;
    c->left = currLeftRigt;

    c->height = 1 + max(getHeight(c->left), getHeight(c->right));
    currLeft->height = 1 + max(getHeight(currLeft->left), getHeight(currLeft->right));

    return currLeft;
}

nodes* leftRotate(nodes* c){
    if (c == NULL || c->right == NULL) return c;
    nodes* currRight = c->right;
    nodes* currRightLeft = c->right->left;

    c->right->left = c;
    c->right = currRightLeft;

    c->height = 1 + max(getHeight(c->left), getHeight(c->right));
    currRight->height = 1 + max(getHeight(currRight->left), getHeight(currRight->right));

    return currRight;    
}

nodes* balance(nodes* c){
    // left left
    if(getBalance(c) > 1 && getBalance(c->left) >= 0){
        return rightRotate(c);
    }

    // right right
    if(getBalance(c) < -1 && getBalance(c->right) < 0){
        return leftRotate(c);
    }

    // left right
    if(getBalance(c) > 1 && getBalance(c->left) < 0){
        c->left = leftRotate(c->left);
        return rightRotate(c);
    }

    // right left
    if (getBalance(c) < -1 && getBalance(c->right) > 0){
        c->right = rightRotate(c->right);
        return leftRotate(c);
    }

    return c; // jangan lupa
}

nodes* insertAVL(nodes* c, int value){
    if(c == NULL){
        return createNewNode(value);
    }

    if(value < c->value){
        c->left = insertAVL(c->left, value);
    }
    else if(value > c->value){
        c->right = insertAVL(c->right, value);
    }

    c->height = 1 + max(getHeight(c->left), getHeight(c->right));

    return balance(c);
}

void inOrder(nodes* c){
    if(c == NULL) return;
    inOrder(c->left);
    printf("%d -> ", c->value);
    inOrder(c->right);
}

int main() {
    int values[] = {40, 20, 50, 10, 30, 25};
    int n = sizeof(values) / sizeof(values[0]);

    for(int i = 0; i < n; i++) {
        root = insertAVL(root, values[i]);
    }

    printf("Inorder traversal after inserts:\n");
    inOrder(root);
    printf("\n");

    return 0;
}