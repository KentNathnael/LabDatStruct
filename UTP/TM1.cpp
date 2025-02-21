#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define hash_size 100
#define gc getchar();

struct booking{
    char fullname[35];
    char phonenumber[20];
    int age;
    char roomType[10];
    int stayDur;
    char Id[10];
    booking* next;
}*bookings[hash_size]; // head

void printMenu(){
    puts("HOTEL GRASFASFAS");
    puts("1. Booking Hotel");
    puts("2. View Booking");
    puts("3. Delete Booking");
    puts("4. Exit");
    printf(">> ");
}

// bool awalnya false kalo kondisi return terpenuhi jadi true

bool validName(char* fullname){
    int len = strlen(fullname);
    return 3 <= len && len <= 30; // bener ketika kondisi di penuhi 
}

bool validnumber(char* phone){
    if(phone[0] != '+' && phone[1] != '6' && phone[2] != '2') return false;

    int space = 0;
    int len = strlen(phone);    
    for(int i = 0; i < len; i++){
        if(phone[i] == ' ') space++;
    }
    return space >= 1 && len-(space+3) == 11;
}

bool validAge(int age){
    return age >= 18;
}

bool validType(char* roomType){
    return strcmp(roomType, "Reguler") == 0 || strcmp(roomType, "Deluxe") == 0 || strcmp(roomType, "Suite") == 0;
}

bool validDur(int duration){
    return duration >= 1 && duration <= 30;
}

char toUpper(char x){
    // ternary
    // condition ? if true : if false  
    return 'a' <= x && x<='z' ? x - ('a'-'A') : x;
}

char* generateId(char* roomType){
    char* id = (char*)malloc(sizeof(char)*7);
    for(int i = 0; i<5; i++){
        id[i] =  i < 2? toUpper(id[i]): rand()%10+'0';
    }

    id[5] = '\0';
    return id;
}

int getHash(char* id){
    int x = 0;
    for(int i = 2; i<5;i++){
        x+=id[i]-'0';
    }
    return (x-1)%hash_size;
}
struct booking* newBooking(char* fullname, 
char* phone, int age, char* type, int dur){
    booking* curr = (booking*)malloc(sizeof(booking));
    char* id = generateId(type);
    strcpy(curr->fullname, fullname);
    strcpy(curr->phonenumber, phone);
    strcpy(curr->roomType, type);
    curr->age = age;
    curr->stayDur = dur;
    strcpy(curr->Id, id);

    curr->next = NULL;
    return curr;
}

void pushTail(booking* newData){
    int hash = getHash(newData->Id);

    if(bookings[hash] == NULL){
        bookings[hash] = newData;
    }
    else{
        struct booking* curr = bookings[hash];
        while(curr->next){
            curr = curr->next;
        }
        curr->next = newData;
    }
}

void createBook(){ // menu 1
    char fullname[35];
    char phonenumber[20];
    int age;
    char roomType[10];
    int stayDur;
    char Id[7];
    
    do{
    printf("Input Name: ");
    scanf("%[^\n]", fullname); gc
    }while(!validName(fullname));

    do{
    printf("Input Phone: ");
    scanf("%[^\n]", phonenumber); gc
    }while(!validnumber(phonenumber));
    
    do{
        printf("Input age: ");
        scanf("%d", &age); gc
    }while(!validAge(age));

    do{
        printf("Input room type: ");
        scanf("%[^\n]", roomType); gc
    }while(!validType(roomType));

    do{
        printf("Input stay duration: ");
        scanf("%d", &stayDur); gc
    }while(!validDur(stayDur));

    pushTail(newBooking(fullname,phonenumber,age,roomType,stayDur));

}



bool viewBooking(){
    bool found = false;
    for(int i = 0; i < hash_size;i++){
        booking* curr = bookings[i];
        while(curr){
            printf("booking ID : %s\n", curr->Id);
            curr = curr->next;
            found = true;
        }
    }
    if(!found){
        printf("Not Found\n");
    }
    return found;
}

bool pop(char* Id){
    int hash = getHash(Id);

    booking* curr = bookings[hash];
    if(strcmp(curr->Id , Id) == 0){
        bookings[hash] = curr->next;
        free(curr);
        return true;
    }
    else{
        while(curr->next){
            if(strcmp(curr->next->Id, Id)==0){
            booking* temp = curr->next;
            curr->next = temp->next;
            free(temp);
            return true;
            }
            curr = curr->next;
        }
    }
}

void deleteBooking(){
    if(!viewBooking()){
        return;
    }
    char id[7];
    printf("Input : ");
    scanf("%[^\n]", id);gc

    if(pop(id)){
        printf("Delete Booking %s\n", id);
    }
    else printf("Id not found\n");
}


int main(){
    srand(time(NULL));
    int menu = -1;
    do{
        printMenu();
        scanf("%d", &menu); gc
    
        switch(menu){
            case 1: 
                createBook();
                break;
            case 2:
                viewBooking();
                break;
            case 3:
                deleteBooking();
                break;
        }
    }while(menu!=4);

    return 0;
}