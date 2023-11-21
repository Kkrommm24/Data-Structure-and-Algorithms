#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct SV
{
    char mssv[11];
    char hoten[31];
    float diemthi;
    struct SV *next;
} SV_t;

SV_t *first, *last;

// Ham tao thong tin cho sinh vien
SV_t *makeProfile(float diemthi, char *mssv, char *hoten)
{
    SV_t *node = (SV_t *)malloc(sizeof(SV_t));
    node->diemthi = diemthi;
    strcpy(node->mssv, mssv);
    strcpy(node->hoten, hoten);
    node->next = NULL;
    return node;
}

// Ham khoi tao danh sach lien ket
void initList()
{
    first = NULL;
    last = NULL;
}

// Ham kiem tra xem danh sach lien ket co rong khong?
int listEmpty()
{
    return (first == NULL && last == NULL);
}

// Ham chen them thong tin cua 1 sinh vien vao dau danh sach lien ket
void insertHead(float diemthi, char *mssv, char *hoten)
{
    SV_t *profile = makeProfile(diemthi, mssv, hoten);
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

// Ham tim kiem sinh vien theo MSSV
void find()
{
    char number[11];
    printf("Nhap MSSV ban muon tim kiem: ");
    scanf("%s", number);
    SV_t *profile = NULL;

    for (SV_t *p = first; p != NULL; p = p->next)
    {
        if (strcmp(p->mssv, number) == 0)
        {
            profile = p;
            break;
        }
    }

    if (profile == NULL)
    {
        printf("NOT FOUND profile has ID: %s!\n", number);
    }
    else
    {
        printf("FOUND profile: %s - %s - %.2f\n", profile->hoten, profile->mssv, profile->diemthi);
    }
}

// Ham xoa di 1 sinh vien trong danh sach
SV_t *removeProfile(SV_t *first, char *mssv)
{
    if (listEmpty())
        return NULL;

    if (strcmp(first->mssv, mssv) == 0)
    {
        SV_t *tmp = first->next;
        free(first);
        if (tmp == NULL)
            last = NULL;
        return tmp;
    }
    else
    {
        first->next = removeProfile(first->next, mssv);
        return first;
    }
}

// Ham tim sinh vien theo MSSV roi xoa di sinh vien do
void findtoremove()
{
    char number[11];
    printf("Nhap MSSV ban muon xoa: ");
    scanf("%s", number);
    SV_t *profile = NULL;

    for (SV_t *p = first; p != NULL; p = p->next)
    {
        if (strcmp(p->mssv, number) == 0)
        {
            profile = p;
            break;
        }
    }

    if (profile == NULL)
    {
        printf("CAN'T REMOVE profile has ID: %s!\n", number);
    }
    else
    {
        first = removeProfile(first, number);
        printf("REMOVE SUCCESSFUL!\n");
    }
}

// Ham in ra danh sach lien ket
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
    // SV_t *SV;
    // SV = (SV_t *)malloc(MAX * sizeof(SV_t));

    int m;
    while (1)
    {
        printf("       *** MENU ***         ");
        printf("\n   -------------------------------");
        printf("\n   1.Nhap thong tin cho sinh vien                     ");
        printf("\n   2.Tim kiem sinh vien theo MSSV                     ");
        printf("\n   3.Nhap MSSV ban muon xoa                           ");
        printf("\n   4.Thong tin sinh vien                              ");
        printf("\n   5.Thoat                                            ");
        printf("\n\nBan muon chon so: ");
        scanf("%d", &m);
        getchar();
        if (m == 5)
        {
            printf("\nChuong trinh ket thuc!");
            printf("\n");
            break;
        }
        else if (m == 1)
        {
            float DIEMTHI;
            char MSSV[11];
            char HOTEN[31];

            fflush(stdin);
            printf("Nhap ten cua sinh vien: ");
            fgets(HOTEN, 31, stdin);
            HOTEN[strlen(HOTEN) - 1] = '\0';

            fflush(stdin);
            printf("Nhap MSSV cua sinh vien: ");
            fgets(MSSV, 11, stdin);
            MSSV[strlen(MSSV) - 1] = '\0';

            printf("Nhap diem cua sinh vien: ");
            scanf("%f", &DIEMTHI);

            makeProfile(DIEMTHI, MSSV, HOTEN);
            insertHead(DIEMTHI, MSSV, HOTEN);
        }
        else if (m == 2)
        {
            find();
            printf("\n");
        }
        else if (m == 3)
        {
            findtoremove();
            printf("\n");
        }
        else if (m == 4)
        {
            printList();
            printf("\n");
        }
        else
        {
            printf("\nBan chon sai so. Xin hay chon lai!");
        }
    }

    // free(SV);
}