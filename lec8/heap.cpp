// min heap = parent < child
// max heap = parent > child

#include <stdio.h>
#define max_heap_size 100


// min heap 

int heap[max_heap_size];
int heapSize = 0; 

int left(int n){
    return n*2+1;
}

int right(int n){
    return n*2+2;
}

int parent(int n){
    return (n-1)/2;
}

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

void insertHeap(int val){
    if(heapSize == max_heap_size){
        printf("Heap is full\n");
        return;
    }

    int n = heapSize++;

    heap[n] = val;
    while(n != 0 && heap[parent(n)] > heap[n]){
        swap(&heap[n], &heap[parent(n)]);
        n = parent(n);
    }
}

int popHead(){
    if(heapSize ==  0){
        printf("Heap is empty\n");
        return -1;
    }

    int toPop =  heap[0];
    heap[0] = heap[--heapSize];

    int n = 0;
    while(left(n) < heapSize){
        int t = left(n);
        if(right(n) < heapSize && heap[right(n)] < heap[t]){
            t = right(n);
        }
        if(heap[t] > heap[n]){
            swap(&heap[n], &heap[t]);
            n = t;
        }else{
            break;
        }
    }

    return toPop;
}

void printHeapArray(){
    for(int i = 0; i<heapSize; i++){
        printf("%d -> ", heap[i]);
    }
    puts("");
}

int main(){
    insertHeap(9);
    printHeapArray();
    insertHeap(19);
    printHeapArray();
    insertHeap(36);
    printHeapArray();
    insertHeap(8);
    printHeapArray();
    insertHeap(10);
    printHeapArray();
    insertHeap(12);
    printHeapArray();
    insertHeap(22);
    printHeapArray();
    insertHeap(12);
    printHeapArray();
    insertHeap(5);
    printHeapArray();

}