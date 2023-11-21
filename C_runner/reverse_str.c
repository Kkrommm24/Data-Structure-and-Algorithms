#include <stdio.h>
#include <string.h>
int main(){
    int length;
    char temp[] = "hunghoang";
    printf("input length of string: ");
    scanf("%d", &length);
    char a[length];
    printf("input string: ");
        fflush(stdin);
        fgets(a, length + 1, stdin);
    printf("%c\n", a[length-1]);
    printf("%d", strlen(temp));
    for(int i = length; i >= 0; i--){
         printf("%c", a[i]);
    }
    return 0;
}