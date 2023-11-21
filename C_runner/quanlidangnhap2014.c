#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
    char username[100];
    char pass[100];
    float diem;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

Node *root;

// Ham tao 1 node moi
Node *makeNode(char *username, char *pass, float diem)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->username, username);
    strcpy(p->pass, pass);
    p->diem = diem;
    p->leftChild = NULL;
    p->rightChild = NULL;
}

// Ham chen 1 node moi vao cay
Node *insert(Node *r, char *username, char *pass, float diem)
{
    if (r == NULL)
        return makeNode(username, pass, diem);
    int c = strcmp(r->username, username);
    if (c == 0)
    {
        printf("Student %s exists, do not insert\n", username);
        return r;
    }
    else if (c < 0)
    {
        r->rightChild = insert(r->rightChild, username, pass, diem);
        return r;
    }
    else
    {
        r->leftChild = insert(r->leftChild, username, pass, diem);
        return r;
    }
}

// Ham doc du lieu tu file
void load(char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
        printf("Load data -> file not found!\n");
    root = NULL;
    while (!feof(f))
    {
        char Username[100], Pass[100];
        float Diem;
        fscanf(f, "%s%s%f", Username, Pass, &Diem);
        root = insert(root, Username, Pass, Diem);
    }
    fclose(f);
}

// Ham tim kiem
Node *find(Node *r, char *username)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->username, username);
    if (c == 0)
        return r;
    if (c < 0)
        return find(r->rightChild, username);
    return find(r->leftChild, username);
}

// Inorder
void inOrder(Node *r)
{
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    printf("%-10s%-10s%-5.1f\n", r->username, r->pass, r->diem);
    inOrder(r->rightChild);
}

void inOrder1(Node *r)
{
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    if (strcmp(r->username, "Admin") != 0)
        printf("%-10s%-10s%-5.1f\n", r->username, r->pass, r->diem);
    inOrder(r->rightChild);
}

void inOrderF(Node *r, FILE *f)
{
    if (r == NULL)
        return;
    inOrderF(r->leftChild, f);
    fprintf(f, "%-10s%-10s%-5.1f\n", r->username, r->pass, r->diem);
    inOrderF(r->rightChild, f);
}
// Ham kiem tra dang nhap
int check(char *username, char *pass)
{
    Node *tmp = find(root, username);
    if (tmp != NULL && strcmp(tmp->pass, pass) == 0)
        return 1;
    if (tmp == NULL)
        return 0;
    if (tmp != NULL && strcmp(tmp->pass, pass) != 0)
        return 0;
}

// Menu con khi nguoi dang nhap la sinh vien
void sinhvien(char *username, char *pass)
{
    Node *p = find(root, username);
    int n;
    while (1)
    {
        printf("       *** MENU SINH VIEN ***         ");
        printf("\n   -------------------------------");
        printf("\n   1. Xem diem                    ");
        printf("\n   2. Thay doi mat khau           ");
        printf("\n   3. Ghi vao file                ");
        printf("\n\nBan muon chon so: ");
        scanf("%d", &n);

        if (n == 3)
        {
            FILE *f = fopen("sinhvien.txt", "w");
            inOrderF(root, f);
            fclose(f);
            printf("Da ghi vao file! Thoat ve menu chinh!\n");
            break;
        }
        else if (n == 1)
        {
            printf("Diem cua sinh vien: %.1f", p->diem);
            printf("\n");
        }
        else if (n == 2)
        {
            char new[100];
            char new1[100];
            printf("Nhap mat khau moi: ");
            scanf("%s", new);
            printf("Nhap lai mat khau moi: ");
            scanf("%s", new1);

            while (strcmp(new, new1) != 0)
            {
                printf("Mat khau khong khop! Moi nhap lai!\n");
                printf("Nhap mat khau moi: ");
                scanf("%s", new);
                printf("Nhap lai mat khau moi: ");
                scanf("%s", new1);
            }
            strcpy(p->pass, new);
            printf("Cap nhat mat khau thanh cong!\n");
            printf("\n");
        }
        else
        {
            printf("\nBan chon sai so.");
        }
    }
}

// Ham xoa di 1 node

Node *findMin(Node *r)
{
    if (r == NULL)
        return NULL;
    Node *lmin = findMin(r->leftChild);
    if (lmin != NULL)
        return lmin;
    return r;
}

Node *remove1(Node *r, char *username)
{
    if (r == NULL)
        return NULL;
    int c = strcmp(r->username, username);
    if (c > 0)

        r->leftChild = remove1(r->leftChild, username);
    else if (c < 0)
        r->rightChild = remove1(r->rightChild, username);
    else
    {
        if (r->leftChild != NULL && r->rightChild != NULL)
        {
            Node *tmp = findMin(r->rightChild);
            strcpy(r->username, tmp->username);
            strcpy(r->pass, tmp->pass);
            r->diem = tmp->diem;
            r->rightChild = remove1(r->rightChild, tmp->username);
        }
        else
        {
            Node *tmp = r;
            if (r->leftChild == NULL)
                r = r->rightChild;
            else
                r = r->leftChild;
            free(tmp);
        }
    }
    return r;
}

// Menu con khi nguoi dung la quan li
void quanli()
{
    int n;
    while (1)
    {
        printf("       *** MENU QUAN LI ***         ");
        printf("\n   ----------------------------------------");
        printf("\n   1. Them sinh vien                       ");
        printf("\n   2. In ra danh sach sinh vien            ");
        printf("\n   3. Xoa sinh vien                        ");
        printf("\n   4. Ghi thong tin vao file               ");
        printf("\n\nBan muon chon so: ");
        scanf("%d", &n);

        if (n == 4)
        {
            FILE *f = fopen("sinhvien.txt", "w");
            inOrderF(root, f);
            fclose(f);
            printf("Da ghi vao file! Thoat ve menu chinh!\n");
            break;
        }
        else if (n == 1)
        {
            char ten[100];
            char mk[100];
            float DIEM;
            printf("Username: ");
            scanf("%s", ten);
            printf("Password: ");
            scanf("%s", mk);
            printf("Diem: ");
            scanf("%f", &DIEM);
            root = insert(root, ten, mk, DIEM);
            printf("Them thanh cong!");
            printf("\n");
        }
        else if (n == 2)
        {
            inOrder1(root);
            printf("\n");
        }
        else if (n == 3)
        {
            char TEN[100];
            printf("Nhap username muon xoa: ");
            scanf("%s", TEN);
            while (strcmp(TEN, "Admin") == 0)
            {
                printf("Khong duoc xoa Admin! Moi nhap lai: ");
                scanf("%s",TEN);
            }
            Node *temp = find(root, TEN);
            printf("%s   %s   %1.f", temp->username, temp->pass, temp->diem);
            printf("\n");
            root = remove1(root, TEN);
            printf("Sinh vien da bi xoa!\n");
        }
        else
        {
            printf("\nBan chon sai so.");
        }
    }
}

int main()
{
    int m;
    load("sinhvien.txt");
    // inOrder(root);
    while (1)
    {
        printf("       *** MENU ***         ");
        printf("\n   -------------------------------");
        printf("\n   1. Dang nhap                   ");
        printf("\n   2. Thoat                       ");
        printf("\n\nBan muon chon so: ");
        scanf("%d", &m);

        if (m == 2)
        {
            printf("Da thoat!\n");
            break;
        }
        else if (m == 1)
        {
            int cnt = 0;
            char name[100];
            char pw[100];
            printf("Ten dang nhap: ");
            scanf("%s", name);
            printf("Mat khau: ");
            scanf("%s", pw);
            if (check(name, pw) == 1)
            {
                printf("Dang nhap thanh cong!\n");
                if (strcmp(name, "Admin") != 0)
                    sinhvien(name, pw);
                else
                    quanli();
            }

            else
            {
                char newname[100];
                char newpw[100];
                do
                {
                    printf("Ten dang nhap khong ton tai hoac ban nhap sai mat khau! Hay thu lai!\n");
                    printf("Ten dang nhap: ");
                    scanf("%s", newname);
                    printf("Mat khau: ");
                    scanf("%s", newpw);
                    cnt++;
                } while (check(newname, newpw) == 0 && cnt <= 3);
                if (cnt > 3)
                {
                    printf("Da qua so lan thu!\n");
                    break;
                }
                else
                {
                    printf("Dang nhap thanh cong!\n");
                    if (strcmp(name, "Admin") != 0)
                        sinhvien(newname, newpw);
                    else
                        quanli();
                }
            }
        }
    }
}