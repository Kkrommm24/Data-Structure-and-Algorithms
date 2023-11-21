#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SV
{
    char mssv[11];
    char hoten[31];
    float diemthi;
    struct SV *next;
} SV_t;

SV_t *first, *last;

SV_t *makeProfile(float diemthi, char *mssv, char *hoten)
{
    SV_t *node = (SV_t *)malloc(sizeof(SV_t));
    node->diemthi = diemthi;
    strcpy(node->mssv, mssv);
    strcpy(node->hoten, hoten);
    node->next = NULL;
    return node;
}

void initList()
{
    first = NULL;
    last = NULL;
}

int listEmpty()
{
    return (first == NULL && last == NULL);
}

void insertLast(float diemthi, char *mssv, char *hoten)
{
    SV_t *profile = makeProfile(diemthi, mssv, hoten);
    if (listEmpty())
    {
        first = profile;
        last = profile;
    }
    else
    {
        last->next = profile;
        last = profile;
    }
}

void printList()
{
    printf("***Thong tin sinh vien:\n");
    printf("%-31s  %-11s  %-6s\n", "Ho ten", "MSSV", "Diem");
    for (SV_t *p = first; p != NULL; p = p->next)
    {
        printf("%-31s  %-11s  %-6.2f\n", p->hoten, p->mssv, p->diemthi);
    }
}

int main()
{
    initList();
    int n;
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);

    SV_t *SV;
    SV = (SV_t *)malloc(n * sizeof(SV_t));

    printf("***Nhap thong tin cho cac sinh vien:\n");
    for (int i = 1; i <= n; i++)
    {
        // printf("Nhap diem cua sinh vien %d: ",i);
        // scanf("%f", &SV[i].diemthi);

        // printf("Nhap MSSV cua sinh vien %d: ",i);
        // scanf("%s", SV[i].mssv);
        // printf("Nhap ten cua sinh vien %d: ",i);
        // scanf("%s", SV[i].hoten);
        fflush(stdin);
        printf("Nhap ten cua sinh vien thu %d: ",i);
        fgets(SV[i].hoten, 31, stdin);
        SV[i].hoten[strlen(SV[i].hoten) - 1] = '\0';

        fflush(stdin);
        printf("Nhap MSSV cua sinh vien thu %d: ",i);
        fgets(SV[i].mssv, 11, stdin);
        SV[i].mssv[strlen(SV[i].mssv) - 1] = '\0';

        printf("Nhap diem cua sinh vien thu %d: ",i);
        scanf("%f", &SV[i].diemthi);

        makeProfile(SV[i].diemthi, SV[i].mssv, SV[i].hoten);
        insertLast(SV[i].diemthi, SV[i].mssv, SV[i].hoten);
        printf("\n");
    }

    printList();

    free(SV);
}
