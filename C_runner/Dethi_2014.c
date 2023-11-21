#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node
{
    char username[100];
    char pass[100];
    float diem;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;

Node *root;

Node *makeNode(char *username, char *pass, float diem)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->username, username);
    strcpy(p->pass, pass);
    p->diem = diem;
    p->leftChild = NULL;
    p->rightChild = NULL;
}

Node *insert(Node *r, char *username, char *pass, float diem)
{
    if (r == NULL)
        return makeNode(username, pass, diem);
    int c = strcmp(username, r->username);
    if (c == 0)
    {
        printf("Student %s exists, do not insert\n", username);
        return r;
    }
    else if (c > 0)
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

void sinhvien(char *username, char *pass)
{
    int key1;
    Node *p = find(root, username);
    while (key1 != 3)
    {
        printf("       *** MENU SINH VIEN ***         ");
        printf("\n   -------------------------------");
        printf("\n   1. Xem diem                    ");
        printf("\n   2. Thay doi mat khau           ");
        printf("\n   3. Ghi vao file                ");
        printf("\n\nBan muon chon so: ");
        scanf("%d%*c", &key1);

        switch(key1){
            case 1:
                printf("Diem cua sinh vien: %.1f", p->diem);
                printf("\n");
                break;
            case 2: ;
                char new[100];
                char new1[100];
                printf("Nhap mat khau moi: ");
                scanf("%s", new);
                printf("Nhap lai mat khau moi: ");
                scanf("%s", new1);

                while (strcmp(new, new1) != 0){
                    printf("Mat khau khong khop! Moi nhap lai!\n");
                    printf("Nhap mat khau moi: ");
                    scanf("%s", new);
                    printf("Nhap lai mat khau moi: ");
                    scanf("%s", new1);
                }
                strcpy(p->pass, new);
                printf("Cap nhat mat khau thanh cong!\n");
                printf("\n");
                break;
            case 3: ;
                FILE *f = fopen("sinhvien.txt", "w");
                inOrderF(root, f);
                fclose(f);
                printf("Da ghi vao file! Thoat ve menu chinh!\n");
                break;    
            default: 
                printf("\nBan chon sai so.");
        }
    }
}

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


void quanli()
{   
    int key2;
    while (key2 != 4){
        printf("       *** MENU QUAN LI ***         ");
        printf("\n   ----------------------------------------");
        printf("\n   1. Them sinh vien                       ");
        printf("\n   2. In ra danh sach sinh vien            ");
        printf("\n   3. Xoa sinh vien                        ");
        printf("\n   4. Ghi thong tin vao file               ");
        printf("\n\nBan muon chon so: ");
        scanf("%d%*c", &key2);
        switch(key2){
        
        case 1: ;
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
            break;
        case 2: ;
            inOrder1(root);
            printf("\n");
            break;
        case 3: ;
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
            break;
        case 4: ;
            FILE *f = fopen("sinhvien.txt", "w");
            inOrderF(root, f);
            fclose(f);
            printf("Da ghi vao file! Thoat ve menu chinh!\n");
            break;    
        default:
            printf("\nBan chon sai so.");
        }
    }
}


int main(){
    int key;
    load("sinhvien.txt");
    do{
        printf("1. Dang nhap\n");
        printf("2. Thoat\n");
        printf("input key: "); scanf("%d%*c", &key);

        switch(key){
            case 1: ;
                int cnt = 0;
                char name[100];
                char pw[100];
                printf("Ten dang nhap: ");
                scanf("%s", name);
                printf("Mat khau: ");
                scanf("%s", pw);
                if (check(name, pw) == 1){
                    printf("Dang nhap thanh cong!\n");
                    if (strcmp(name, "Admin") != 0){
                        sinhvien(name, pw); break;
                        }else{
                            quanli(); break;
                        }
                }else{
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
                    if (cnt > 3){
                        printf("Da qua so lan thu!\n");
                        break;
                    }
                    else{
                        printf("Dang nhap thanh cong!\n");
                        if (strcmp(name, "Admin") != 0){
                            sinhvien(newname, newpw);
                            break;
                        }else{
                            quanli(); break;
                        }
                    }
                }
        }
    }while(key != 2);
    return 0;
}