#include <stdio.h>
#include <string.h>

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main(){
    int length;
    printf("input length of string: ");
    scanf("%d", &length);
    int a[length];
    printf("input string: ");
    for(int i = 0; i < length; i++){
        fflush(stdin);
        printf("a[%d] = ", i);
        scanf("%d",&a[i]);
    }
    for (int i = 0; i < length / 2; i++) {
        swap(&a[i], &a[length - i - 1]);
    }
    for(int i = 0; i < length; i++){
        printf("%d ", a[i]);
    }
    return 0;
}