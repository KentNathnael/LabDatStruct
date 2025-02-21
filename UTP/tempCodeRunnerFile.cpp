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