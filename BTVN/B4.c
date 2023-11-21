#include<stdio.h>

#include<string.h>

int DoiXung(char s[]) {

            int i,ok=1;

            for(i=0; i<strlen(s)/2; i++) {

                        if(s[i] != s[strlen(s)-i-1]) {

                                    ok = 0;

                                    break;

                        }

            }

            if(ok == 1)

                        printf("Chuoi: %s doi xung",s);

            else

                        printf("Chuoi: %s khong doi xung",s);

}

int main() {

            char s[100];

            printf("Nhap chuoi ban dau: ");

            gets(s);

            DoiXung(s);

            return 0;

}

 