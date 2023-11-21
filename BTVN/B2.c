#include <stdio.h>
#include <string.h>

int main(){
    int length;
    int count_odd = 0;
    int count_even = 0;
    printf("input length of string: ");
    scanf("%d", &length);
    int a[length];
    printf("input string: ");
    for(int i = 0; i < length; i++){
        fflush(stdin);
        printf("a[%d] = ", i);
        scanf("%d",&a[i]);
    }
    for(int i = 0; i < length; i++){
        if(a[i] % 2 == 0){
            count_even++;
        }else{
            count_odd++;
        }
    }
    for(int i = 0; i < length; i++){
        if(a[i] % 2 != 0){
            printf("%d ", a[i]);
        }
    }
    printf("%d\n", count_odd);
    for(int i = 0; i < length; i++){
        if(a[i] % 2 == 0){
            printf("%d ", a[i]);
        }
    }
    printf("%d", count_even);
    return 0;
}