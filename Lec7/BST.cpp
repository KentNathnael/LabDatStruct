// avl tree -> self balacning 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct mahasiswa{
    int age;
    char name[100];
    mahasiswa* left;
    mahasiswa* right;
    int height;
};

mahasiswa *createNewMhs(int age, char* name){
    mahasiswa* c = (mahasiswa*)malloc(sizeof(mahasiswa));
    strcpy(c->name, name);
    c->age = age;
    c->left = NULL;
    c->right = NULL;
    c->height = 1;

    return c;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int getHeight(mahasiswa* curr){
    if(curr == NULL){
        return 0;
    }
    else{
        return curr->height;
    }
}

int getBalance(mahasiswa* curr){
    return getHeight(curr->left) - getHeight(curr->right);
}

mahasiswa* rightRotate(mahasiswa* curr){
    mahasiswa* currLeft = curr->left;
    mahasiswa* currLeftRight = curr->left->right;

    curr->left->right = curr;
    curr->left = currLeftRight;

    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    currLeft->height = 1 + max(getHeight(currLeft->left), getHeight(currLeft->right));

    return currLeft;
}

mahasiswa* LeftRotate(mahasiswa* curr){
    mahasiswa* currRIght = curr->right;
    mahasiswa* currRightLeft = curr->right->left;

    curr->right->left = curr;
    curr->right = currRightLeft;

    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));
    currRIght->height = 1 + max(getHeight(currRIght->left), getHeight(currRIght->right));

    return currRIght;
}

mahasiswa *insertAVL(mahasiswa* curr, int age, char* name){
    // kosong
    if(curr == NULL){
        return createNewMhs(age, name);
    }

    if(age < curr->age){
        curr->left = insertAVL(curr->left, age, name);
    }

    else if(age > curr->age){
        curr->right = insertAVL(curr->right, age, name);
    }

    // update height
    curr->height = 1 + max(getHeight(curr->left), getHeight(curr->right));

    // identity imbalance case
    // LL
    if(getBalance(curr) > 1 && getBalance(curr->left) >= 0){
        // right rotate
        return rightRotate(curr);
    }

    // RR
    else if(getBalance(curr) < -1 && getBalance(curr->right)<0){
        // left rotate
        return LeftRotate(curr);
    }

    // LR
    else if(getBalance(curr) > 1 && getBalance(curr->right) < 0){
        // left roatet subtree, right rotate tree
        curr->left = LeftRotate(curr->left);
        return rightRotate(curr);
    }

    // RL 
    else if(getBalance(curr) < -1 && getBalance(curr->right) > 0){
        // right roatet subtree, left rotaqte tree
        curr->right = rightRotate(curr->right);
        return LeftRotate(curr);
    }

    return curr;
}

void inOrder(mahasiswa* curr){
    if(!curr) return;
    inOrder(curr->left);
    printf("age : %d, name %s\n", curr->age, curr->name);
    inOrder(curr->right);
}


void preOrder(mahasiswa* curr){
    if(!curr) return;
    printf("age : %d, name %s\n", curr->age, curr->name);
    preOrder(curr->left);
    preOrder(curr->right);
}

void postOrder(mahasiswa* curr){
    if(!curr) return;
    postOrder(curr->left);
    postOrder(curr->right);
    printf("age : %d, name %s\n", curr->age, curr->name);
}

void updateTree(mahasiswa* curr, int age, char newName[100]){
    if(!curr) printf("Not Found\n");

    else if(age < curr->age){
        updateTree(curr->left, age, newName);
    }

    else if(age > curr->age){
        updateTree(curr->right, age, newName);
    }

    else if(age == curr->age){
        strcpy(curr->name, newName);
        printf("Name Updated!\n");
    }
}


int main(){
    mahasiswa* root = NULL;

    root = insertAVL(root, 3, "Cindy");
    root = insertAVL(root, 18, "Cindy");
    root = insertAVL(root, 21, "Cindy");
    root = insertAVL(root, 8, "Cindy");
    root = insertAVL(root, 7, "Cindy");
    root = insertAVL(root, 6, "Cindy");
    root = insertAVL(root, 23, "Cindy");

    inOrder(root);

    updateTree(root, 21, "Jovita");
    updateTree(root, 20, "lolo");

    inOrder(root);
    return 0;
}