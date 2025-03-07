#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

#define MAX 100

struct Data{
    char name[105];
    char phone[105];
    int age;
    char type[105];
    int dur;
    char id[105];
    struct Data* next;
}*h[MAX];

struct Data* createnode(char name[], char phone[], int age, char type[], int dur, char id[]){
    struct Data* c = (Data*)malloc(sizeof(Data));
    strcpy(c->name, name);
    strcpy(c->phone, phone);
    c->age = age;
    strcpy(c->type, type);
    c->dur = dur;
    strcpy(c->id, id);
    c->next = NULL;

    return c;
}

int hash(char* id){
    int sum = 0;
    for(int i = 2; i < strlen(id); i++){
        sum += id[i];
    }
    return sum % MAX;
}

void push(char name[], char phone[], int age, char type[], int dur, char id[]){
    Data* c = createnode(name, phone, age, type, dur, id);
    int index = hash(id);

    if(h[index]==NULL){
        h[index] = c;
    }
    else{
        Data* temp = h[index];
        while(temp->next!= NULL){
            temp = temp->next;
        }
        temp->next = c;
    }
}

void pop(char id[]){
    // int index = hash(id);
    // int flag = 0;
    // if(h[index] == NULL){
    //     puts("There is no booking");
    //     return;
    // }else{
    //     Data* temp = h[index];
    //     while(temp->next != NULL){
    //         if(strcmp(temp->next->id, id) == 0){
    //             printf("BookingID %s is Successfully Deleted!", temp->id);
    //             temp->next = temp->next->next;
    //             free(temp);
    //             flag = 1;
    //         }
    //         temp = temp->next;
    //     }
    // }
    // if(flag == 0){
    //     puts("Failed to Delete");
    // }
    int flag = 0;
    for(int i = 0; i < MAX; i++){
        if(h[i]==NULL){
            continue;
        }
        else{
            Data* temp = h[i];
            if(strcmp(temp->id,id)==0){
                printf("Booking %s deleted\n", temp->id);
                if(temp->next == NULL){
                    h[i] == NULL;
                    return;
                }
                else{
                    h[i] = temp->next;
                    free(temp);
                }
            }
            else{
                while(temp->next != NULL){
                    if(strcmp(temp->next->id,id)==0){
                        printf("Booking %s deleted\n", temp->id);
                        if(temp->next->next == NULL){
                            Data* curr = temp->next;
                            temp->next =  NULL;
                            free(curr);
                        }
                        temp->next = temp->next->next;
                        free(temp->next);
                        return;
                    }
                    temp = temp->next;
                }
            }
        }
    }
    if(flag == 0){
        printf("Failed to delete");
    }
}

void book(){
    char name[105];
    char phone[105];
    int age;
    char type[105];
    int dur;
    char id[105];

    do{
        printf("Input Full Name [3-30]: ");
        scanf("%[^\n]", name); getchar();
        if(strlen(name) < 3 || strlen(name) > 30){
            printf("Full name length must between 3 and 30\n");
        }
    }while(strlen(name) < 3 || strlen(name) > 30);
    
    do{
        printf("Input Phone Number: ");
        scanf("%s", phone); getchar();
        if(strlen(phone) < 11){
            printf("Phone number must begin with '+62', contains with at least 1 space and the length msut be 11 (Exclude +62 and space)\n");
        }
    }while(strlen(phone) < 11);

    do{
        printf("Input Age [Minimum 18]: ");
        scanf("%d", &age); getchar();
        if(age < 18){
            puts("Age must be minimum 18");
        }
    }while(age < 18);

    do{
        printf("Input Room Type [Regular | Deluxe | Suite]: ");
        scanf("%s", type); getchar();
        if(strcmp(type, "Regular") != 0 && strcmp(type, "Deluxe") != 0 && strcmp(type, "Suite") != 0){
            puts("Room type must be either Regular or Deluxe or Suite (Case Sensitive)");
        }
    }while(strcmp(type, "Regular") != 0 && strcmp(type, "Deluxe") != 0 && strcmp(type, "Suite") != 0);

    do{
        printf("Input How Many Night You Will Stay [1-30]: ");
        scanf("%d", &dur); getchar();
        if(dur < 1 || dur > 30){
            puts("You can't stay less than 1 night or more than 30 nights");
        }
    }while(dur < 1 || dur > 30);

    sprintf(id, "%c%c%d%d%d", toupper(type[0]), toupper(type[1]), rand()%10, rand()%10, rand()%10);

    push(name, phone, age, type, dur, id);
}

void view(){
    for(int i = 0; i < MAX; i++){
        if(h[i] == NULL){
            continue;
        }else{
            Data* temp = h[i];
            printf("Booking ID: %s\n", temp->id);
            printf("Full Name: %s\n", temp->name);
            printf("Phone Number: %s\n", temp->phone);
            printf("Room Type: %s\n", temp->type);
            printf("Night Stay: %d night(s)\n", temp->dur);
        }
    }
}

void del(){
    char ID[105];
    printf("Input Booking ID (Case Sensitive): ");
    scanf("%s", ID); getchar();
    pop(ID);
}

int main(){
    do{
        int input = -1;
        do{
            puts("Hotel GrAnsylvania");
            puts("========================");
            puts("1. Booking Hotel");
            puts("2. View Bookings");
            puts("3. Delete Bookings");
            puts("4. Exit");
            printf(">> ");
            scanf("%d", &input); getchar();
        }while(input < 1 || input > 4);
        switch(input){
            case 1:
                book();
                break;
            case 2:
                view();
                break;
            case 3:
                del();
                break;
            case 4:
                return 0;
                break;
        }
    }while(1);
}