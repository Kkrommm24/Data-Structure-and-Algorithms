#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y);
void quicksort(int arr[], int length);
void quicksort_recursion(int arr[], int low, int high);
int partition(int arr[], int low, int high);

int main(){
    int a[] = {10,11,23,44,8,15,3,9,12,45,56,45,45};
    int length = 13;
    
    quicksort(a, length);

    for (int i = 0; i < length; i++)
        printf("%d ", a[i]);
        printf("\n");
    return 0;
}

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void quicksort(int arr[], int length){
    srand(time(NULL));
    quicksort_recursion(arr, 0, length - 1);
}

void quicksort_recursion(int arr[], int low, int high){
    if (low < high){
        int pivot = partition(arr, low, high);
        quicksort_recursion(arr, low, pivot - 1);
        quicksort_recursion(arr, pivot + 1, high);
    }
}

int partition(int arr[], int low, int high){
    int pivot = low + (rand() % (high - low));

    if(pivot != high) 
        swap(&arr[pivot], &arr[high]);

    int pivot_value = arr[high];
    int i = low;

    for(int j = low; j < high; j++){
        if(arr[j] <= pivot_value){
            swap(&arr[i], &arr[j]);
            i++;
        }
    } 
    swap(&arr[i], &arr[high]);
    return i;
}