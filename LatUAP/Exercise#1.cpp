#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 100

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

int getMax(int a, int b){
    return (a > b) ? a : b;
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

nodes* leftRotate(nodes* c){
    if(c == NULL || c->right == NULL) return c;

    nodes* currRight = c->right;
    nodes* currRightLeft = c->right->left;

    c->right->left = c;
    c->right = currRightLeft;

    c->height = 1 + getMax(getHeight(c->left), getHeight(c->right));
    currRight->height = 1 + getMax(getHeight(currRight->left), getHeight(currRight->right));

    return currRight;
}

nodes* rightRotate(nodes* c){
    if(c == NULL || c->left == NULL) return c;

    nodes* currLeft = c->left;
    nodes* currLeftRight = c->left->right;

    c->left->right = c;
    c->left = currLeftRight;

    c->height = 1 + getMax(getHeight(c->left), getHeight(c->right));
    currLeft->height = 1 + getMax(getHeight(currLeft->left), getHeight(currLeft->right));

    return currLeft;
}

nodes* balancing(nodes* c){
    // left-left
    if(getBalance(c) > 1 && getBalance(c->left) >= 0){
        return rightRotate(c);
    }
    
    // right right
    if(getBalance(c) < 1 && getBalance(c->right) < 0){
        return leftRotate(c);
    }

    // left right
    if(getBalance(c) > 1 && getBalance(c->left) < 0){
        c->left = leftRotate(c->left);
        return rightRotate(c);
    }
    
    // right left
    if(getBalance(c) < 1 && getBalance(c->right) > 0){
        c->right = rightRotate(c->right);
        return leftRotate(c);
    }

    return c;
}

nodes* insertAVL(nodes* c , int value){
    if(c == NULL){
        return createNewNode(value);
    }
    
    if(c->value < value){
        c->left = insertAVL(c->left, value);
    }

    if(c->value > value){
        c->right = insertAVL(c->right, value);
    }

    c->height = 1 + getMax(getHeight(c->left), getHeight(c->right));

    return balancing(c);
}

nodes* deleteAVL(nodes* c, int value){
    if(c == NULL){
        return NULL;
    }
    
    if(c->value < value){
        c->left = deleteAVL(c->left, value);
    }   

    if(c->value > value){
        c->right = deleteAVL(c->right, value);
    }

    
}