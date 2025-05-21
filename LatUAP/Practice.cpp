#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define size 100
#define gc getchar();

struct nodes{
    char name[105];
    int price;
    char cat[105];
    char avail[105];
    int height;
    nodes* left;
    nodes* right;
    int key;
}*node = NULL;

int Findkey(char* name){
    int key = 0;
    for(int i = 0; i < strlen(name); i++){
        key += name[i];
    }
    return key %= size;
}

nodes *createNewNodes(char* name, int price, char* cat, char* avail, int key){
    nodes* c = (nodes*)malloc(sizeof(nodes));
    strcpy(c->name, name);
    strcpy(c->cat, cat);
    strcpy(c->avail, avail);
    c->price = price;
    c->key = key;
    c->height = 1;
    c->left = NULL;
    c->right = NULL;

    return c;
}

// bikin max
int max(int a, int b){
    return (a > b) ? a : b;
}

// bikin height
int getHeight(nodes* c){
    if (c == NULL){
        return 0;
    }
    else{
        return c->height;
    }
}

// bikin get balance buat dipake pas balancing (height kiri - height kanan);
int getBalance(nodes* c){
    return getHeight(c->left) - getHeight(c->right);
}

// right rotate = bikin current left terus leftRight, terus mainin di left right jadi curr, terus left jadi leftRight
nodes* rightRotate(nodes* c){
    if (c == NULL || c->left == NULL) return c;
    nodes* currLeft = c->left;
    nodes* currLeftRight = c->left->right;

    c->left->right = c;
    c->left = currLeftRight;

    c->height = 1 + max(getHeight(c->left), getHeight(c->right));
    currLeft->height = 1 + max(getHeight(currLeft->left), getHeight(currLeft->right));
    
    return currLeft;
}

// left Rotate = bikin current right terus bikin right left, terus mainin right left jadi curr terus curr right jadi right Left
nodes* leftRotate(nodes* c){
    if (c == NULL || c->right == NULL) return c;
    nodes* currRight = c->right;
    nodes* currRightLeft  = c->right->left;

    c->right->left = c;
    c->right = currRightLeft;

    c->height = 1 + max(getHeight(c->left), getHeight(c->right));
    currRight->height = 1 + max(getHeight(currRight->left), getHeight(currRight->right));

    return currRight;
}

// function buat balancing
nodes* balancing(nodes* c){
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
    if(getBalance(c) < -1 && getBalance(c->right) > 0){
        c->right = rightRotate(c->right);
        return leftRotate(c);
    }

    return c;
}


int countWord(char* name){
    int count = 1;
    for(int i = 0; i < strlen(name);i++){
        if(name[i] == ' ' && name[i+1] != ' '){
            count++;
        }
    }
    return count;
}

bool validName(char* name){
    if(name[0] != 'S' || name[1] != 'a' || name[2] != 'l' || name[3] != 'l' || name[4] != 'y'){
        return false;
    }

    return true;
}
nodes* insertAVL(nodes* c, char* name, int price, char* cat, char* avail, int key){
    if(c == NULL){
        return createNewNodes(name, price, cat, avail, key);
    }
    else if(key < c->key){
        c->left = insertAVL(c->left, name, price, cat, avail, key);
    }
    else if(key > c->key){
        c->right  = insertAVL(c->right, name, price, cat, avail, key);
    }

    //update height
    c->height = 1 + max(getHeight(c->left), getHeight(c->right));

    return balancing(c);
}

void menuInsert(){
    char name[21];
    int price;
    char cat[105];
    char avail[105];
    int key;

    do{
        printf("Enter Treatment Name : ");
        scanf("%[^\n]", name); gc
    }while(countWord(name) < 2 || strlen(name) < 5 || strlen(name) > 20 || !validName(name));

    do{
        printf("Enter Treatment price : ");
        scanf("%d", &price); gc
    }while(price < 50000 || price > 1000000);

    do{
        printf("Enter Treatment Category : ");
        scanf("%[^\n]", cat); gc
    }while(strcmp(cat, "Hair Care")!= 0 && strcmp(cat, "Nail Care")!= 0 && strcmp(cat, "Body Care")!= 0);

    do{
        printf("Enter Treatment Availbity : ");
        scanf("%[^\n]", avail); gc
    }while(strcmp(avail, "Available")!= 0 && strcmp(avail, "Unavailable")!= 0);

    key = Findkey(name);

    node = insertAVL(node, name, price, cat, avail, key);
}


void inOrder(nodes* c){
    if(!c) return;
    inOrder(c->left);
    printf("%s || %s || %d || %s\n", c->name, c->cat, c->price, c->avail);
    inOrder(c->right);
}

void preOrder(nodes* c){
    if(!c) return;
    printf("%s || %s || %d || %s\n", c->name, c->cat, c->price, c->avail);
    preOrder(c->left);
    preOrder(c->right);
}

void postOrder(nodes* c){
    if(!c) return;
    postOrder(c->left);
    postOrder(c->right);
    printf("%s || %s || %d || %s\n", c->name, c->cat, c->price, c->avail);
}

void Menuview(){
    if(!node){
        printf("No data\n");
        return;
    }
    else{
        char selection[10];
        do{
            printf("input view order [pre | in | post]: ");
            scanf("%[^\n]", selection); gc
        }while(strcmp(selection, "pre") != 0 && strcmp(selection, "in") != 0 && strcmp(selection, "post") != 0);

        if(strcmp(selection, "pre") == 0){
            preOrder(node);
            return;
        }
        if(strcmp(selection, "in") == 0){
            inOrder(node);
            return;
        }
        if(strcmp(selection, "post") == 0){
            postOrder(node);
            return;
        }
    }
}

void printMenu(){
    puts("Sally Salon");
    puts("===========");
    puts("Menu:");
    puts("1. View Availabe Treatment");
    puts("2. Insert New Treatment");
    puts("3. Delete Treatment");
    puts("4. Exit");
    puts("[1-4]");
    printf(">> ");
}


int main(){
    do{
        int choice = -1;
        do{
            printMenu();
            scanf("%d", &choice); gc
        }while(choice < 1 || choice > 5);

        switch(choice){
            case 1:
                Menuview();
                break;
            case 2:
                menuInsert();
                break;
            case 3:
                break;
            case 4:
                return 0;
        }
    }while(1);

    return 0;
}