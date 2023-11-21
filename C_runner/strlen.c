#include<stdio.h>
#include <string.h>
int main(){
    int t=0;
    for (int a=1;a<10;a++){
        for (int b=1;b<10;b++){
            for (int c=1;c<10;c++){
                for (int d=1;d<10;d++){
                    if (7*a + 4*b+6*c+5*d==60 && a+b+c+d<=10){
                        t++;
                    }
                }
            }
        }
    }
    printf("%d",t);
    return 0;
}