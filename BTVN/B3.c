#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *x, int *y);
void quicksort(int arr[], int length);
void quicksort_recursion(int arr[], int low, int high);
int partition(int arr[], int low, int high);

int main(){
//aaaaa
    int n, m, count, k;
    int c[100];
    printf("input number of elements of string a: ");
    scanf("%d", &n);
    int a[n];
    printf("input number of elements of string b: ");
    scanf("%d", &m);
    int b[m];
    printf("input string: ");
    for(int i = 0; i < n; i++){
        fflush(stdin);
        printf("a[%d] = ", i);
        scanf("%d",&a[i]);
    }

    for(int i = 0; i < m; i++){
        fflush(stdin);
        printf("b[%d] = ", i);
        scanf("%d",&b[i]);
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(a[i] == b[j]){
                printf("%d ", a[i]);
                count++;
            }
        }
    }
    printf("%d\n", count);
//bbbbbb
    quicksort(a, n);
    quicksort(b, m);
    for(int i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
    for(int i = 0; i < m; i++){
        printf("%d ", b[i]);
    }
    printf("\n");
//ccccc
    for(int i = 0; i < n; i++){
        c[k] = a[i];
        k++;
    }
    k = n;
    for(int i = 0; i < m; i++){
        c[k] = b[i];
        k++;
    }
    quicksort(c, k);
    for(int i = 0; i < k; i++){
        printf("%d ", c[i]);
    }
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
