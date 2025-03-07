#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define size 50 
#define gc getchar();

struct tnode{
    char name[100];
    char type[100];
    int dur;
    tnode* next;
}*hash_table[size];

void printMenu(){
    puts("NeLson's Garage");
    puts("===============");
    puts("1. \tInsert");
    puts("2. \tView");
    puts("3. \tUpdate");
    puts("4. \tExit");
    printf(">> ");
}

void push(char* name, char* type, int dur, int key){
    tnode* c = (tnode*)malloc(sizeof(tnode));
    strcpy(c->name, name);
    strcpy(c->type, type);
    c->dur = dur;
    c->next = NULL;

    if(hash_table[key] == NULL){
        hash_table[key] = c;
    }
    else{
        tnode* temp = hash_table[key];
        while(temp->next){
            temp = temp->next;
        }
        temp->next = c;
    }
       
}

int hash(char* name1, char* name2){
    int key = 0;
    for(int i = 0; i < strlen(name1);i++){
        key += name1[i];
    }
    for(int i = 0; i < strlen(name2);i++){
        key += name2[i];
    }

    return key % size;
}

void insert(){
    char name[100];
    char type[100];
    int dur;
    int flag = 0;
    char name1[100] = "";
    char name2[100] = "";

    do{
        printf("Enter Car's Name: ");
        scanf("%[^\n]", name); gc

        int counter = 0;

        for(int i = 0, j = 0; i < strlen(name); i++){
            if(name[i] == ' ' && isalpha(name[i+1])){
                counter++;
            }
            else if(counter == 0){
                name1[i] = name[i];
            }
            else{
                name2[j] = name[i];
                j++;
            }
        }


        // printf("n : %s  name 2 : %s\n", name1, name2);
        if(counter != 0 && strcmp(name1, name2)!=0) flag = 1;
        
        if(flag == 0){
            puts("Please input 2 words and unique");
        }

        strcpy(name1, "");
        strcpy(name2, "");
    }while(flag == 0);

    do{
        printf("Enter Car's type: ");
        scanf("%s", type); gc
        if(strcmp(type, "SUV")!= 0 && strcmp(type, "Sedan") && strcmp(type,"Hatchback") != 0){
            puts("Please input 2 words and unique");
        }
    }while(strcmp(type, "SUV")!= 0 && strcmp(type, "Sedan") && strcmp(type,"Hatchback") != 0);

    do{
        printf("Enter duration :");
        scanf("%d", &dur); gc

        if(dur < 0){
            puts("Please input more than equal 1 day");
        }
    }while(dur < 0);

    char choice;
    do{
        printf("want to continue [Y/N]:");
        scanf("%c", &choice); gc
    }while(choice != 'Y' && choice != 'N');

    if(choice=='N'){
        return;
    }

    int key = hash(name1, name2);

    push(name, type, dur, key);
}

void view(){
    int flag = 0;
    for(int i = 0; i < size; i++){
        if(hash_table[i]==NULL){
            continue;
        }
        else{
            tnode* temp = hash_table[i];
            while(temp){
                printf("Name\t: %s\n", temp->name);
                printf("Type\t: %s\n", temp->type);
                printf("Duration\t: %d\n", temp->dur);
                temp = temp->next;
                flag = 1;
            }
        }
    }
    if(flag == 0){
        puts("There is currently no vehicle\n");
        return;
    }
}

void update(){
    view();
    char choice[100];
    int flag = 0;
    printf("Name : ");
    scanf("%[^\n]", choice); gc
    for(int i = 0; i < size; i++){
        if(hash_table[i] == NULL){
            continue;
        }
        else{
            tnode* temp = hash_table[i];
            while(temp){
                if(strcmp(temp->name, choice)==0){
                    int change;
                    do{
                        printf("New storage duration: ");
                        scanf("%d", &change); gc
                    }while(change < 0);
                    temp->dur = change;
                    flag = 1;
                    return;
                }
            }
        }
    }
}

int main(){
    int choice = -1;
    do{
        do{
            printMenu();
            scanf("%d", &choice); gc
        }while(choice < 1 && choice > 4);

        switch(choice){
            case 1:
                insert();
                break;
            case 2:
                view();
                break;
            case 3:
                update();
                break;
            case 4:
                return 0;
        }
    }while(1);
}