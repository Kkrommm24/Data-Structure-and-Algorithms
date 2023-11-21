#define _GNU_SOURCE
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>
#include<stdio_ext.h>
#include<ctype.h>
#include <stdlib.h>

typedef struct{
    char Name[5];
    float Dientich;
    int Dieuhoa;
}Phongtro_t;

Phongtro_t a[100];
int PhongCount=0;
int soPhong=0;

void in4Phong(){
    int n;
    Phongtro_t Phongtro;
    printf("Nhap so luong phong: ");
    while(1){
        scanf("%d%*c", &n);
        if(n+soPhong<=100 && n+soPhong>0){
            soPhong+=n;
            break;
        }else{
           printf("Nhap lai so luong phong: "); 
        }
    }
    printf("Nhap thong tin phong:");
    for(int i=0;i<n;i++){
        do{
            printf("\nNhap Ten phong:");fgets(Phongtro.Name,5,stdin);
            fgetc(stdin);
            if (strpbrk(Phongtro.Name, "0123456789' '") == NULL) break;
            printf("Nhap lai cho dung format!!");
        }while(strlen(Phongtro.Name)>5 || strpbrk(Phongtro.Name, "0123456789' '") != NULL );
        do{
            printf("Nhap Dien tich:");scanf("%f",&Phongtro.Dientich);
            while ((getchar()) != '\n'&& (getchar()) != EOF);
            if(Phongtro.Dientich>=10 && Phongtro.Dientich<=40) break;
            printf("Dien tich phai >10 va <=40\n");
        }while(Phongtro.Dientich<10 || Phongtro.Dientich>40);
        do{
            printf("Co dieu hoa hay khong: ");scanf("%d",&Phongtro.Dieuhoa);
            while ((getchar()) != '\n'&& (getchar()) != EOF);
            if(Phongtro.Dieuhoa==0||Phongtro.Dieuhoa==1) break;
            printf("Nhap sai format, nhap lai: ");
        }while(Phongtro.Dieuhoa!=0 || Phongtro.Dieuhoa!=1);
        a[PhongCount]=Phongtro;
        PhongCount++;
    }
}


void Inttin(){
    printf("%-1s     %-3s     %-5s\n","Ten phong","Dien tich","Dieu hoa");
    for(int i=0;i<PhongCount;i++){
        if(a[i].Dieuhoa==1){
        printf("%-1s       %8.1f     %8s\n",a[i].Name,a[i].Dientich,"Co");
        }else{
            printf("%-1s       %8.1f     %10s\n",a[i].Name,a[i].Dientich,"Khong");
        }
    }
}

void searchS(){
    float p,q;
    bool isFound = false;
    float dt;
    printf("Nhap Dien tich phong muon tim:");
    scanf("%f",&dt);
    p=dt-5;
    q=dt+5;
    for(int i=0;i<PhongCount;i++){
        if(a[i].Dientich >=p && a[i].Dientich <=q){
            isFound=true;
        }
    }
    if(isFound==true){
        printf("%-1s     %-3s     %-5s\n","Ten phong","Dien tich","Dieu hoa");
        for(int i=0;i<PhongCount;i++){
            if(a[i].Dientich >=p && a[i].Dientich <=q){
                if(a[i].Dieuhoa==1){
                    printf("%-1s       %8.1f     %8s\n",a[i].Name,a[i].Dientich,"Co");
                }else{
                    printf("%-1s       %8.1f     %10s\n",a[i].Name,a[i].Dientich,"Khong");
                } 
            }  
        }
    }else if(isFound==false){
        printf("Khong co phong voi dien tich da tim\n");
}
}

void sapxep(){
    Phongtro_t tmp;
    printf("Cac phong sau khi xep theo dien tich:\n");
    for(int i = 0; i<PhongCount; i++){
        for(int j = i+1; j<PhongCount; j++){
            if(a[i].Dientich<a[j].Dientich){
                tmp=a[i];
                a[i]=a[j];
                a[j]=tmp;
            }
        }
    }
    Inttin();
}

void themDhoa(){
    int count=0;
    int count1=0;
    int count2=0;
    int count3=0;
    for(int i=0;i<PhongCount;i++){
        if(a[i].Dieuhoa==0){
            if(a[i].Dientich<15){
                count++;
            }else if(a[i].Dientich>=15 && a[i].Dientich<22){
                count1++;
            }else if(a[i].Dientich>=22 && a[i].Dientich<30){
                count2++;
            }else if(a[i].Dientich>=30 && a[i].Dientich<40){
                count3++;
            }
        }
    }
    printf("So luong dieu hoa can mua la:\n");
    printf("9000BTU:%d\n",count);
    printf("12000BTU:%d\n",count1);
    printf("18000BTU:%d\n",count2);
    printf("21000BTU:%d\n",count3);
}
int main(){
    int key;
    do{
        printf("\nMenu:\n");
        printf("1. Nhap thong tin Phong\n");
        printf("2. In thong tin phong\n");
        printf("3. Tim kiem theo dien tich\n");
        printf("4. Sap xep\n");
        printf("5. So luong dieu hoa can bo sung\n");
        printf("6. Thoat\n");
        printf("input key: "); scanf("%d%*c", &key);

        switch(key)
        {
          case 1: in4Phong(); break;
          case 2: Inttin(); break;
          case 3: searchS(); break;
          case 4: sapxep(); break;
          case 5: themDhoa(); break;
        }
      }while(key != 6);
    return 0;
}