#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define max 100
#define gc getchar();

struct tnode{
    char name[100];
    char labId[100];
    char title[100];
    int dur;
    char borrowId[100];
    tnode* next;
}*hash[max];

void printMenu(){
    puts("BookHaven");
    puts("==========");
    puts("1. Borrow");
    puts("2. View");
    puts("3. Return");
    puts("4. exit");
    puts("============");
    printf("Enter your choicie");
}


int hashing(char* borrowId){
    char loc[5];

    sprintf(loc, "%c%c%c", borrowId[2], borrowId[3], borrowId[4]);

    int key = atoi(loc);

    key *= key;

    char temp[100];

    sprintf(temp, "%d", key);

    if(strlen(temp)%2==0){
        sprintf(loc, "%c%c", temp[strlen(temp)/2], temp[strlen(temp)/2+1]);

        key = atoi(loc);

        return key % max;
    }
    else{
        sprintf(loc, "%c", temp[strlen(temp)/2]);

        key = atoi(loc);

        return key % max;
    }
}

void push(char* name, char* labId, char* title, int dur, char* borrowId){
    int index = hashing(borrowId);
    tnode* c = (tnode*)malloc(sizeof(tnode));
    strcpy(c->name, name);
    strcpy(c->labId, labId);
    strcpy(c->title, title);
    c->dur = dur;
    strcpy(c->borrowId, borrowId);
    c->next = NULL;

    if(hash[index] == NULL){
        hash[index] = c;
    }
    else{
        tnode* temp = hash[index];
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = c;
    }
}

void borrow(){
    char name[100];
    char labId[100];
    char title[100];
    int dur;
    char borrowId[100];

    do{
        printf("Enter your name: ");
        scanf("%[^\n]", name); gc
        if(strlen(name) < 3 || strlen(name) > 30){
            printf("name must be 3-30 char");
        }
    }while(strlen(name) < 3 || strlen(name) > 30);

    do{
        printf("Enter your Library Id (LIB-XXXXX): ");
        scanf("%[^\n]", labId); gc
        if(labId[0] != 'L' && labId[1] != 'I' && labId[2] != 'B' && labId[3] != '-' || (strlen(labId)-4) != 5){
            printf("Enter with format");
        }
    }while(labId[0] != 'L' && labId[1] != 'I' && labId[2] != 'B' && labId[3] != '-' || (strlen(labId)-4) != 5);

    do{
        printf("Enter your book title: ");
        scanf("%[^\n]", title); gc
        if(strlen(title) < 3 || strlen(title) > 50){
            printf("title must be 3-50 char");
        }
    }while(strlen(title) < 3 || strlen(title) > 50);

    do{
        printf("Enter borrowing duration: ");
        scanf("%d", &dur); gc
        if(dur < 1 || dur > 30){
            printf("duration must be 1 -30 days");
        }
    }while(dur < 1 || dur > 30);

    sprintf(borrowId, "%c%c%d%d%d", toupper(title[0]), toupper(title[1]), rand()%10 + 0, rand()%10 + 0, rand()%10 + 0);
    printf("%s", borrowId);

    push(name, labId, title, dur, borrowId);
}

void view(){
    int flag = 0;
        for(int i = 0; i < max; i++){
            if(hash[i] == NULL){
                continue;
            }
            else{
                tnode* temp = hash[i];
                while(temp != NULL){
                    printf("Borrow ID : %s\n", temp->borrowId);
                    printf("Borrow name : %s\n", temp->name);
                    printf("Lib Id : %s\n", temp->labId);
                    printf("Book title : %s\n", temp->title);
                    printf("duration : %d\n", temp->dur);
                    flag = 1;
                    temp = temp->next;
                }
            }
        }
        if(flag == 0) printf("No book\n");
    }

void Return(){
    view();
    char id[100];
    printf("Enter Borrowing IDto return: ");
    scanf("%s", id); gc
    int key =  hashing(id);
    if(hash[key] == NULL){
        puts("No book");
    }
    else{
        tnode* temp = hash[key];
        if(strcmp(id, temp->borrowId)==0){
            hash[key] = temp->next;
            free(temp);
        }
        else{
            while(temp->next != NULL && strcmp(id, temp->next->borrowId) != 0){
                temp = temp->next;
            }
            tnode* toPop = temp->next;
            temp->next = toPop->next;
            printf("Book succesfully returned %s", toPop->borrowId);
            free(toPop);
        }
    }
}

int main(){
    srand(time(NULL));
    int choice = -1;
    do{
        do{
            printMenu();
            scanf("%d", &choice); gc
        }while(choice < 1 && choice > 4);
        
        switch(choice){
            case 1:
                borrow();
                break;
            case 2:
                view();
                break;
            case 3:
                Return();
                break;
            case 4:
                puts("Bye Bye");
                return 0;
        }
    }while(1);
}