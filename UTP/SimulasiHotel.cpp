#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define size 100
#define gc getchar();

struct tnode{
    char name[100];
    char phone[100];
    int age;
    char type[100];
    int dur;
    char id[100];
    tnode* next;
}*hash_table[size];

void printMenu(){
    puts("Hotel");
    puts("=====");
    puts("1. Booking");
    puts("2. View");
    puts("3. Delete");
    puts("4. Exit");
}

int findIndex(char* id){
    char num[5] = {id[2], id[3], id[4], '\0'};
    int key = 0;
    for(int i = 0; i < strlen(id); i++){
        key += num[i];
    }
    key -= 1;
    return key % size;
}

void push(char* name, char* phone, char* type, int dur, char* id){
    tnode* c = (tnode*)malloc(sizeof(tnode));
    strcpy(c->name, name);
    strcpy(c->phone, phone);
    strcpy(c->type, type);
    strcpy(c->id, id);
    c->dur = dur;
    c->next = NULL;

    int index = findIndex(id);

    if(hash_table[index]==NULL){
        hash_table[index] = c;
    }
    else{
        tnode* temp = hash_table[index];
        while(temp != NULL){
            temp = temp->next;
        }
        temp->next = c;
    }
}


void booking(){
    char name[100];
    char phone[100];
    int age;
    char type[100];
    int dur;
    char id[100] = "";

    do{
        printf("Input full name [3.30] : ");
        scanf("%[^\n]", name); gc
        if(strlen(name)< 3 || strlen(name) > 30){
            puts("Full name must be between 3 to 30");
        }
    }while(strlen(name)< 3 || strlen(name) > 30);

    do{
        printf("Input phone number : ");
        scanf("%[^\n]", phone); gc
        if(!(strncmp(phone, "+62 ", 4) == 0 && strlen(phone) == 15)){
            puts("Phone number must be begin with '+62', contain 1 space and length must be 11 exclude +62 and space");
        }
    }while(!(strncmp(phone, "+62 ", 4) == 0 && strlen(phone) == 15));

    do{
        printf("Input age [ min 18] : ");
        scanf("%d", &age); gc
        if(age < 18){
            puts("minimum 18");
        }
    }while(age < 18);

    do{
        printf("Input room type [Reguler | Deluxe | Suite ] : ");
        scanf("%[^\n]", type); gc
        if(strcmp(type, "Reguler")!= 0 && strcmp(type, "Deluxe")!= 0 && strcmp(type, "Suite")!= 0){
            puts("Select from the type");
        }
    }while(strcmp(type, "Reguler")!= 0 && strcmp(type, "Deluxe")!= 0 && strcmp(type, "Suite")!= 0);

    do{
        printf("Input how many night : ");
        scanf("%d", &dur); gc
        if(dur < 1 || dur > 30){
            puts("less than 1 night or more than 30 night");
        }
    }while(dur < 1 || dur > 30);
    
    sprintf(id, "%c%c%d%d%d", toupper(type[0]), toupper(type[1]), rand()%10 + 0, rand()%10 + 0, rand()%10 + 0);
    printf("%s", id);

    push(name, phone, type, dur, id);
}

void view(){
    int flag = 0;
    for(int i = 0; i < size; i++){
        if(hash_table[i]==NULL){
            continue;
        }
        else{
            tnode* temp = hash_table[i];
            while(temp != NULL){
                printf("ID : %s\n", temp->id);
                printf("name : %s\n", temp->name);
                printf("phone : %s\n", temp->phone);
                printf("type : %s\n", temp->type);
                printf("dur : %d\n", temp->dur);
                temp = temp->next;
                flag =1;
            }
        }
    }
    if(flag == 0){
        puts("There is no booking");
        return;
    }
}

void Del(){
    view();
    char id[100];
    printf("Input ID : ");
    scanf("%s", id); gc
    int flag = 0;
    for(int i = 0; i < size; i++){
        if(hash_table[i]==NULL){
            continue;
        }
        else{
            tnode* temp = hash_table[i];
            if(strcmp(hash_table[i]->id, id )== 0){
                hash_table[i] = hash_table[i]->next;
                printf("Booking %s succesfully deleted\n", temp->name);
                free(temp);
                flag = 1;
                return;
            }
            else{
                while(temp->next){
                    if(strcmp(id, temp->next->id)==0){
                        tnode* toPop = temp->next;
                        temp->next = toPop->next;
                        printf("Booking %s succesfully deleted\n", toPop->name);
                        free(toPop);
                        flag = 1;
                        return;
                    }
                    temp = temp->next;
                }
            }
        }
    }
    if(flag == 0){
        puts("Failed to delete, there is no Data!");
    }
}


int main(){
    srand(time(NULL));
    int choice = -1;
    do{
        do{
            printMenu();
            scanf("%d", &choice); gc
        }while(choice < 1 && choice < 5);

        switch (choice){
            case 1:
                booking();
                break;
            case 2: 
                view();
                break;
            case 3:
                Del();
                break;
            case 4:
                return 0;
        }
    }while(1);
}
