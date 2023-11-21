#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 800

// Khai bao cau truc du lieu
typedef struct CV
{
    char place[41];
    int gio;
    int phut;
    struct CV *next;
} CV;

CV *first, *last;

// Tao ra 1 profile moi
CV *makenode(char *place, int gio, int phut)
{
    CV *node = (CV *)malloc(sizeof(CV));
    strcpy(node->place, place);
    node->gio = gio;
    node->phut = phut;
    node->next = NULL;
    return node;
}

// Khoi tao
void initList()
{
    first = NULL;
    last = NULL;
}

// Kiem tra xem danh sach co rong khong?
int listEmpty()
{
    return (first == NULL && last == NULL);
}

// Chen them 1 profile vao cuoi danh sach
void insertToLast(char *place, int gio, int phut)
{
    CV *profile = makenode(place, gio, phut);
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

// Ham doc du lieu tu file "log.txt"
void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        printf("Load data -> file not found!\n");

    while (!feof(f))
    {
        char Place[41];
        int Gio;
        int Phut;
        fscanf(f, "%s", Place);
        fscanf(f, "%d%d", &Gio, &Phut);
        insertToLast(Place, Gio, Phut);
    }
    fclose(f);
}

// In thong tin cua danh sach
void printList()
{
    printf("%-50s%-10s%-10s\n", "Dia diem", "Gio", "Phut");
    for (CV *p = first; p != NULL; p = p->next)
    {
        printf("%-50s%-10d%-10d\n", p->place, p->gio, p->phut);
    }
}

// Chuc nang 3 tim kiem lich su di chuyen theo dia diem
void timtheodiadiem()
{
    // Nhap ten dia diem muon tim
    char name[256];
    printf("Nhap dia diem muon tra cuu: ");
    scanf("%s", name);
    int x = 0;
    int count = 0;
    for (CV *p = first; p != NULL; p = p->next)
    {
        if (strcmp(p->place, name) == 0)
        {
            count++;
        }
    }

    int j = 0;
    for (CV *p = first; p != NULL; p = p->next)
    {
        if (strcmp(p->place, name) == 0)
        {
            x = 1;
            j++;
            if (j != count)
                printf("%d : %d, ", p->gio, p->phut);
            else
                printf("%d : %d", p->gio, p->phut);
        }
    }
    if (x == 0)
        printf("Ban chua toi dia diem do !\n");
}

// Chuc nang 4 tim kiem thong tin di chuyen theo thoi gian
void timtheothoigian()
{
    int g, ph;
    do
    {
        scanf("%d%d", &g, &ph);
    } while (g < 0 || g > 24 || ph < 0 || ph > 60);
    int x = 0;

    CV *gancuoi = NULL;
    for (CV *p = first; p != NULL; p = p->next)
    {
        if (p->next == last)
            gancuoi = p;
    }

    if (last->gio == g && ph < last->phut)
        x = 1, printf("%s", gancuoi->place);
    else if (last->gio == g && ph > last->phut)
        x = 1, printf("%s", last->place);
    else if (last->gio < g)
        x = 1, printf("%s", last->place);

    else
    {
        for (CV *p = first; p != NULL; p = p->next)
        {
            if (p->gio == g && p->phut == ph)
            {
                x = 1;
                printf("%s", p->place);
            }
            if (p->gio == g && p->next->gio == g && p->phut < ph && p->next->phut > ph)
            {
                x = 1;
                printf("%s", p->place);
            }
            if (p->gio == g && p->next->gio > g && p->phut < ph)
            {
                x = 1;
                printf("%s", p->place);
            }
            if (p->gio < g && p->next->gio > g)
            {
                x = 1;
                printf("%s", p->place);
            }
            if (p->gio < g && p->next->gio == g && p->next->phut > ph)
            {
                x = 1;
                printf("%s", p->place);
            }
        }
    }
    if (x == 0)
        printf("KHONG tim thay lich su di chuyen !\n");
}

// Chuc nang 5 kiem tra tuy vet moi nhat
void kiemtra()
{
    char diadiem[41];
    int g, ph;
    scanf("%s%d%d", diadiem, &g, &ph);

    int x = 0;
    for (CV *p = first; p != NULL; p = p->next)
    {
        if (strcmp(diadiem, p->place) == 0 && p->gio == g && p->phut == ph)
        {
            x = 1;
            printf("Ban co kha nang bi lay Covid, can phai khai bao ngay lap tuc !\n");
        }
        if (strcmp(diadiem, p->place) == 0 && p->gio == g && p->next->gio == g && p->phut < ph && p->next->phut > ph)
        {
            x = 1;
            printf("Ban co kha nang bi lay Covid, can phai khai bao ngay lap tuc !\n");
        }
        if (strcmp(diadiem, p->place) == 0 && p->gio == g && p->next->gio > g && p->phut < ph)
        {
            x = 1;
            printf("Ban co kha nang bi lay Covid, can phai khai bao ngay lap tuc !\n");
        }
        if (strcmp(diadiem, p->place) == 0 && p->gio < g && p->next->gio > g)
        {
            x = 1;
            printf("Ban co kha nang bi lay Covid, can phai khai bao ngay lap tuc !\n");
        }
        if (strcmp(diadiem, p->place) == 0 && p->gio < g && p->next->gio == g && p->next->phut > ph)
        {
            x = 1;
            printf("Ban co kha nang bi lay Covid, can phai khai bao ngay lap tuc !\n");
        }
    }

    if (x == 0)
        printf("Lich su di chuyen cua ban OK!\n");
}

// chuc nang 6 giai phong bo nho
void freelist()
{
    CV *tg = first, *temp;

    while (tg != NULL)
    {
        temp = tg->next;
        free(tg);
        tg = temp;
    }
}

// Ham main
int main()
{
    initList();
    load("log1.txt");
    int m;

    while (1)
    {

        printf("       *** MENU ***         ");
        printf("\n   -------------------------------");
        printf("\n   1. Nap du lieu log lich su di chuyen                   ");
        printf("\n   2. In ra lich su di chuyen                             ");
        printf("\n   3. Tim kiem lich su di chuyen theo dia diem            ");
        printf("\n   4. Tim kiem thong tin di chuyen theo thoi gian         ");
        printf("\n   5. Kiem tra truy vet moi nhat                          ");
        printf("\n   6. Thoat                                               ");
        printf("\n\nBan muon chon so: ");
        scanf("%d", &m);
        getchar();
        if (m == 6)
        {
            freelist();
            printf("Chuong trinh ket thuc!");
            printf("\n");
            break;
        }
        else if (m == 1)
        {
            printf("Doc thanh cong du lieu!");
            printf("\n");
        }
        else if (m == 2)
        {
            printList();
            printf("\n");
        }
        else if (m == 3)
        {
            timtheodiadiem();
            printf("\n");
        }
        else if (m == 4)
        {
            timtheothoigian();
            printf("\n");
        }
        else if (m == 5)
        {
            kiemtra();
            printf("\n");
        }
        else
        {
            printf("\nBan chon sai so.");
        }
    }
}
