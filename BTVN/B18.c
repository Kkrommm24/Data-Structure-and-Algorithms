#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct SV
{
    char mssv[11];
    char Hoten[31];
    float diemthi;
    struct SV *next;
}SV_t;

SV_t *first, *last;


void initList(){
    first = NULL; last = NULL;
}

int listEmpty(){
    return first == NULL && last == NULL;
}

SV_t* makeProfile(char* mssv, char* Hoten, float diemthi){
    SV_t* node = (SV_t*)malloc(sizeof(SV_t));
    strcpy(node->mssv,mssv);
    strcpy(node->Hoten,Hoten);
    node->diemthi=diemthi;
    node->next = NULL;
    return node;
}

void insertFirst(char *mssv, char *Hoten, float diemthi)
{
    SV_t *profile = makeProfile(mssv, Hoten, diemthi);
    if (listEmpty())
    {
        first = profile;
        last = profile;
    }
    else
    {
        profile->next = first;
        first = profile;
    }
}


void printList(){
    printf("***Thong tin sinh vien:\n");
    printf("%-31s  %-11s  %-6s\n", "Ho ten", "MSSV", "Diem");
    for(SV_t *p = first; p != NULL; p = p->next)
        printf("%-31s %-11s %-6.2f\n",p->mssv, p->Hoten, p->diemthi);
}

void load(char* filename){
    FILE* f = fopen(filename,"r");
    if(f == NULL) printf("Load data -> file not found\n");
    while(!feof(f)){
        char mssv[10], Hoten[30];
        float diemthi;
        fscanf(f,"%s%s%f",mssv, Hoten, &diemthi);
        insertFirst(mssv, Hoten, diemthi);
    }
    fclose(f);
}

/*void processLoad(){
    printf("Nhap ten file: ");
    char filename[256];
    scanf("%s",filename);
    load(filename);
}*/

void processStore(){
    char filename[256];
    printf("Nhap ten file muon luu vao: ");
    scanf("%s",filename);
    FILE* f = fopen(filename,"w");
    for(SV_t *p = first; p != NULL; p = p->next){
        fprintf(f,"%s %s %.2f",p->mssv,p->Hoten,p->diemthi);
        if(p->next != NULL) fprintf(f,"\n");
    }
    fclose(f);
}

void processInsert(){
    char mssv[11], Hoten[31];
    float diemthi;
    int n;
    do{
        printf("Nhap so sv: ");
        scanf("%d%*c",&n);
    }while(n<2 || n>10);
    printf("NHAP THONG TIN SINH VIEN\n");
    for(int i = 1; i <= n; i++){
        
        fflush(stdin);
        printf ("Nhap ma sinh vien : ");
        fgets(mssv, 11, stdin);
        mssv[strlen(mssv) - 1] = '\0';

        fflush(stdin);
        printf ("Nhap ten sinh vien : ");
        fgets(Hoten, 31, stdin);
        Hoten[strlen(Hoten) - 1] = '\0';

        printf("Nhap diem cua sinh vien: ");
        scanf("%f", &diemthi);
        while ((getchar()) != '\n'&& (getchar()) != EOF);
        insertFirst(mssv, Hoten,diemthi);
        printf("\n");
    }
}

int main(){
    int key;
    initList();
        do{
        printf("\nMenu:\n");
        printf("1. Nhap thong tin SV\n");
        printf("2. Tim kiem\n");
        printf("3. Xoa SV\n");
        printf("4. In thong tin\n");
        printf("5. Thoat\n");
        printf("input key: "); scanf("%d%*c", &key);

        switch(key)
        {
          case 1: /*processLoad();*/ processInsert(); processStore(); break;
          //case 2: processFind(); break;
          //case 3: processRemove(); break;
          case 4: printList(); break;
        }
      }while(key != 5);
    return 0;
}