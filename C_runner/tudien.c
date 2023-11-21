#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 800

typedef struct Node
{
    char tu[256];
    char nghia[256];
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

Node *root;
char word[MAX][30];
int tmp;
// Ham tao ra 1 node (1 cap tu - nghia moi)
Node *makeNode(char *tu, char *nghia)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->tu, tu);
    strcpy(p->nghia, nghia);
    p->leftChild = NULL;
    p->rightChild = NULL;
}

// Ham chen 1 node moi vao cay
Node *insert(Node *r, char *tu, char *nghia)
{
    if (r == NULL)
        return makeNode(tu, nghia);
    int c = strcmp(tu,r->tu);
    if (c == 0)
    {
        printf("Word %s exists, do not insert\n", tu);
        return r;
    }
    else if (c > 0)
    {
        r->rightChild = insert(r->rightChild, tu, nghia);
        return r;
    }
    else
    {
        r->leftChild = insert(r->leftChild, tu, nghia);
        return r;
    }
}

// Ham tim kiem
Node *find(Node *r, char *tu)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->tu, tu);
    if (c == 0)
        return r;
    if (c < 0)
        return find(r->rightChild, tu);
    return find(r->leftChild, tu);
}

// Ham duyet giua
void inOrder(Node *r)
{
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    printf("%s\t%s\n", r->tu, r->nghia);
    inOrder(r->rightChild);
}

// Ham doc du lieu tu file roi ghi vao cay BST
void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        printf("Load data -> file not found!\n");
    root = NULL;
    while (!feof(f))
    {
        char Tu[256], Nghia[256];
        fscanf(f, "%s%s", Tu, Nghia);
        root = insert(root, Tu, Nghia);
    }
    fclose(f);
}

// Ham doc du lieu roi ghi ra
void load1(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        printf("Load data -> file not found!\n");
    root = NULL;
    while (!feof(f))
    {
        char Tu[256], Nghia[256];
        fscanf(f, "%s%s", Tu, Nghia);
        printf("%s\t%s\n", Tu, Nghia);
    }
    fclose(f);
}

// Chuc nang 3 them sua nghia cua tu
void themsua()
{
    char m[256];
    printf("Enter a new E/l word: ");
    scanf("%s", m);
    if (find(root, m) == NULL)
    {
        printf("Enter its meaning: ");
        char mean[256];
        scanf("%s", mean);
        root = insert(root, m, mean);
    }
    else
    {
        Node *p = find(root, m);
        int u;
        printf("Word exists! Do u want to change its meaning?:\n1.Yes\n2.No\n");
        scanf("%d", &u);
        if (u == 1)
        {
            char hh[256];
            scanf("%s", hh);
            strcpy(p->nghia, hh);
        }
    }
}

// Ham tach tu tu cau
void tach(char *str)
{
    int j = 0, k = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != ' ')
        {
            word[j][k] = tolower(str[i]);
            k++;
        }
        else
        {
            word[j][k] = '\0';
            k = 0;
            j++;
        }
    }
    tmp = j;
    for (int i = 0; i <= j; i++)
        printf("%s\n", word[i]);
}

// Ham tim kiem nghia cua 1 tu
void findmean1word(char s[])
{
    Node *p = find(root, s);
    if (p == NULL)
    {
        // printf("the word does not exist, if you want, enter it in function 3 !\n");
        printf("<Thieu tu> ");
        return;
    }
    else
    {
        printf("%s ", p->nghia);
    }
}

void dich(char *s)
{
    tach(s);
    for (int i = 0; i <= tmp; i++)
    {
        findmean1word(word[i]);
    }
}

// Ham giai phong bo nho
void freeTree(Node *r)
{
    if (r == NULL)
        return;
    freeTree(r->leftChild);
    freeTree(r->rightChild);
    free(r);
}


// Ham main
int main()
{
    load("tudien.txt");
    int w;

    while (1)
    {

        printf("       *** MENU ***         ");
        printf("\n   -------------------------------");
        printf("\n   1. Nap tu dien                 ");
        printf("\n   2. Noi dung tu dien            ");
        printf("\n   3. Them/Sua tu                 ");
        printf("\n   4. Dich cau Anh - Viet         ");
        printf("\n   5. Thoat                       ");
        printf("\n\nBan muon chon so: ");
        scanf("%d", &w);
        getchar();
        if (w == 5)
        {
            freeTree(root);
            printf("Chuong trinh ket thuc!");
            printf("\n");
            break;
        }
        else if (w == 1)
        {
            printf("*Noi dung file:\n");
            load1("tudien.txt");
            load("tudien.txt");
            // inOrder(root);
            printf("\n");
        }
        else if (w == 2)
        {
            printf("*Noi dung tu dien:\n");
            // load("tudien.txt");
            inOrder(root);
            printf("\n");
        }
        else if (w == 3)
        {
            themsua();
            printf("\n");
        }
        else if (w == 4)
        {
            char sen[256];
            printf("Enter a sentence: ");
            gets(sen);
            dich(sen);
            printf("\n");
        }
        else
        {
            printf("\nBan chon sai so.");
        }
    }
}