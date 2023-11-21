#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct DateTime {
    int year, month, day; 
} DateTime;

DateTime currentDateTime() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    DateTime dt = {tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday};
    return dt;
}

typedef struct rooms{
    char ma_yc[8];
    int so_nguoi;
    int ma_phong;
    char ma_ks[4];
    DateTime dt;
    int treem;
    struct rooms *next;
}Rooms_t;
Rooms_t *first, *last;
Rooms_t *changeLogfirst = NULL;
Rooms_t *changeLog = NULL;

typedef struct Node{   
    char ma_yc[8];
    int so_nguoi;
    int ma_phong;
    char ma_ks[4];
    DateTime dt;
    int treem;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;
Node *root;
int soluong;
int cntlegit = 0;
//..............Chuc nang 1...............
void initList(){
    first = NULL; last = NULL;
}

int listEmpty(){
    return first == NULL && last == NULL;
}

Rooms_t *makeProfile(char *ma_yc, int so_nguoi, int ma_phong, char *ma_ks, DateTime dt, int treem){
    Rooms_t* node = (Rooms_t*)malloc(sizeof(Rooms_t));
    strcpy(node->ma_yc, ma_yc);
    node->so_nguoi = so_nguoi;
    node->ma_phong = ma_phong;
    strcpy(node->ma_ks, ma_ks);
    node->dt = dt;
    node->treem = treem;
    node->next = NULL;
    return node;
}


void insertLast(char *ma_yc, int so_nguoi, int ma_phong, char *ma_ks, DateTime dt, int treem){
    Rooms_t *profile = makeProfile(ma_yc,so_nguoi,ma_phong, ma_ks, dt, treem);
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

Node *makeNode(char *ma_yc, int so_nguoi, int ma_phong, char *ma_ks, DateTime dt, int treem){
    Node* p = (Node*)malloc(sizeof(Node));
    strcpy(p->ma_yc, ma_yc);
    p->so_nguoi = so_nguoi;
    p->ma_phong = ma_phong;
    strcpy(p->ma_ks, ma_ks);
    p->dt = dt;
    p->treem = treem;
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}
Node *insert(Node *r, char *ma_yc, int so_nguoi, int ma_phong, char *ma_ks, DateTime dt, int treem){
    if (r == NULL)
        return makeNode(ma_yc,so_nguoi,ma_phong, ma_ks, dt, treem);
    int c = strcmp(ma_yc,r->ma_yc);
    if (c > 0)
    {
        r->rightChild = insert(r->rightChild, ma_yc,so_nguoi,ma_phong, ma_ks, dt, treem);
        return r;
    }
    else if(c < 0){
        r->leftChild = insert(r->leftChild, ma_yc,so_nguoi,ma_phong, ma_ks, dt, treem);
        return r;
    }
}

Node *delete(Node *r, char *ma_yc) {
    if (r == NULL) return NULL;
    int cmp = strcmp(ma_yc, r->ma_yc);
    if (cmp > 0) r->rightChild = delete(r->rightChild, ma_yc);
    else if (cmp < 0) r->leftChild = delete(r->leftChild, ma_yc);
    else {
        if (r->leftChild != NULL && r->rightChild != NULL) {
            Node *p = r->rightChild;
            while (p->leftChild != NULL) p = p->leftChild;
            strcpy(r->ma_yc, p->ma_yc);
            r->dt = p->dt;
            r->rightChild = delete(r->rightChild, p->ma_yc);
        }else {
            Node *tmp = r;
            if (r->leftChild == NULL) r = r->rightChild;
            else r = r->leftChild;
            free(tmp);
        }
    }
    return r;
}

int countNodes(Node *r) {
    if (r == NULL) return 0;
    return 1 + countNodes(r->leftChild) + countNodes(r->rightChild);
}

void inOrder(Node *r){
    if (r == NULL)
        return;
    inOrder(r->leftChild);
        printf("%s %d %d %s %d-%d-%d %d\n", r->ma_yc, r->so_nguoi, r->ma_phong, r->ma_ks,
         r->dt.day, r->dt.month, r->dt.year, r->treem);
    inOrder(r->rightChild);
}

void inOrderF(Node *r, FILE *f){
    if (r == NULL)
        return;
    inOrderF(r->leftChild, f);
        fprintf(f, "%s %d %d %s %02d-%02d-%d %d\n", r->ma_yc, r->so_nguoi, r->ma_phong, r->ma_ks,
         r->dt.day, r->dt.month, r->dt.year, r->treem);
    inOrderF(r->rightChild, f);
}
void load(char* filename){
    FILE* f = fopen(filename,"r");
    if(f == NULL) printf("File khong ton tai\n");
    root = NULL;
    
    fscanf(f, "%d\n", &soluong);
    while(!feof(f)){
        char ma_yc[8];
        int so_nguoi;
        int ma_phong;
        char ma_ks[4];
        int day;
        int month;
        int year;
        int treem;
        fscanf(f,"%s %d %d %s %d-%d-%d %d", ma_yc, &so_nguoi, &ma_phong, ma_ks, &day, &month, &year, &treem);
        DateTime dt = {year, month, day};
        insertLast(ma_yc,so_nguoi,ma_phong, ma_ks, dt, treem);
        root = insert(root, ma_yc, so_nguoi, ma_phong, ma_ks, dt, treem);
        //insert(root, year, month, day, hour, minute, second, bsx, inout);
    }
    fclose(f);
    printf("Load file thanh cong!!!\n");
}

void printList(){
    printf("so luong phong: %d\n", soluong);
    for(Rooms_t* p = first; p != NULL; p = p->next){ 
        printf("%s %d %d %s %02d-%02d-%d %d\n", p->ma_yc, p->so_nguoi, p->ma_phong, p->ma_ks,
         p->dt.day, p->dt.month, p->dt.year, p->treem);
    }
}

//..............Chuc nang 2...............
int Check_legit(){
    int cnt = 0;
    for (Rooms_t *p = first; p != NULL; p = p->next) {
        if (p->treem > 0 && p->so_nguoi < p->treem){
            cnt++;
            cntlegit++;
        }
    }
    if(cnt == 0) return 0;
    if(cnt != 0) return 1;
}
void LegitCount(){
        printf("So yeu cau khong hop le la: %d", cntlegit);
}

//...............Chuc nang 3...............
Node *find(Node *r, char *ma_yc) {
    if (r == NULL) return NULL;
    int cmp = strcmp(ma_yc, r->ma_yc);
    if (cmp == 0){
        return r;
    }
    if (cmp > 0) return find(r->rightChild, ma_yc);
    return find(r->leftChild, ma_yc);
}
void ProcessFind(){
    char ma_yc[13];
    printf("\nNhap ma yeu cau: ");
    scanf("%s", ma_yc);
    Node *p = find(root, ma_yc);
    if (p == NULL)
    {
        printf("NOT FOUND");
        return;
    }
    else
    {
        printf("%s %d %d %s %d-%d-%d %d\n", p->ma_yc, p->so_nguoi, p->ma_phong, p->ma_ks,
         p->dt.day, p->dt.month, p->dt.year, p->treem); 
    }
    return;
}

//...............Chuc nang 4.................
void Update(){
    char ma_yc[13];
    int so_nguoi;
    int year;
    int month;
    int day;
    int treem;
    printf("\nNhap ma yeu cau: ");
    scanf("%s", ma_yc);
    Node *p = find(root, ma_yc);
    if (p == NULL)
    {
        printf("NOT FOUND\n");
        return;
    }
    else{ 
        printf("Nhap so nguoi:");
        scanf("%d", &so_nguoi);
        printf("Nhap ngay thang nam muon sua:");
        scanf("%d %d %d", &day, &month, &year);
        printf("Nhap so tre em:");
        scanf("%d", &treem);
        if(treem > 0 && so_nguoi <= treem) {printf("Invalid");}
        else{
        p->so_nguoi = so_nguoi;
        p->dt.day = day;
        p->dt.month = month;
        p->dt.year = year;
        p->treem = treem;
        printf("Update success\n");
        }

    }
}


//..................Chuc nang 5................
void Deletelog(){
    char ma_yc[13];
    printf("\nNhap ma yeu cau: ");
    scanf("%s", ma_yc);
    Node *p = find(root, ma_yc);
    if (p == NULL)
    {
        printf("NOT FOUND\n");
        return;
    }
    else{ 
        delete(root, p->ma_yc);
        printf("Delete success\n");
    }
}
//...................Chuc nang 6......................
void savePresentLog(char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Loi: khong the mo file %s.\n", filename);
        return;
    }

    inOrderF(root, f);
    printf("Da luu thanh cong ra file booking_orders.txt\n");
    soluong = countNodes(root);
    printf("So phong hien tai: %d", countNodes(root));
    fclose(f);
}
//...............Chuc nang 8.................
void freelist(){
    Rooms_t *tg = first, *temp;

    while (tg != NULL)
    {
        temp = tg->next;
        free(tg);
        tg = temp;
    }
}

void freeTree(Node *r){
    if (r == NULL)
        return;
    freeTree(r->leftChild);
    freeTree(r->rightChild);
    free(r);
}

int main(){
    int key;
    initList();
        do{
        printf("\n====CHUONG TRINH QUAN LY DAT PHONG KHACH SAN====\n");
        printf("Vui long chon mot trong cac chuc nang sau\n");
        printf("1) Doc du lieu tu file log \n");
        printf("2) Kiem tra so luong yeu cau khong hop le\n");
        printf("3) Tra cuu ma yeu cau\n");
        printf("4) Thay doi yeu cau\n");
        printf("5) Huy yeu cau\n");
        printf("6) Luu danh sach yeu cau ra file\n");
        printf("7) Thoat\n");
        printf("Lua chon cua ban la: "); scanf("%d%*c", &key);

        switch(key)
        {
          case 1: load("booking_orders.txt"); printList(); break;
          case 2: Check_legit(); LegitCount(); cntlegit = 0; break;
          case 3: ProcessFind(); break;
          case 4: Update(); break;
          case 5: Deletelog(); break;
          case 6: savePresentLog("booking_orders.txt"); break;
          case 7: freelist(); freeTree(root); break;
          default:
            printf("Ban can chon trong khoang 1-8!\n");
            break;
        }
        if(key == 8) break;
      }while(1);
    return 0;
}