// Import Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_table 10

struct Node {
    char name [40];
    Node *next;
} *head[max_table];

Node *createNewNode (char *nama){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy (newNode->name, nama);
    newNode->next = NULL;
    return newNode;
}
int hash (char *name){
    int key = 0;
    for (int i = 0; i < strlen(name); i++){
        key += name[i];
    }
    return key % max_table;
    
}

void push (char *nama){
    Node *newNode = createNewNode(nama);
    // Calculate hash key
    int pos = hash(nama);
    // Push
    if (head [pos] == NULL){
        head[pos] = newNode; 
        return;
    }
    // 2. ketika headnya ada (push tail)
    Node *temp = head[pos];
    while (temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newNode;
    return;
}

void print(){
    for (int i = 0; i < max_table; i++){
        Node *temp = head[i];
        printf("%d: ", i+1);
        while (temp){
            printf ("%s -> ", temp->name);
            temp = temp->next;
        }
        printf("NULL!\n");
    }
    
}

void pop(char *name){
    int pos = hash(name);
    // ga ada head[pos]nya

    if(head[pos]==NULL){
        printf("Ga ada\n");
        return;
    }
    else{
        if(strcmp(head[pos]->name, name)==0){
            Node *temp = head[pos];
            head[pos]= temp->next;
            free(temp);
        }
        else{
            Node *temp = head[pos];
            while (temp->next!= NULL && strcmp(temp->next->name, name)!= 0)
            {
                temp = temp->next;
            }
            Node *topop = temp->next; // temp2 
            temp->next = topop->next;
            free(topop);
        }
    }
}

int main(){
    push("budi");
    push("lala");
    push("andi");
    push("agus");
    push("neo");
    push("ziva");
    push("jaden");
    push("nana");
    push("webe");
    print();
    pop("lele");
    print();
}