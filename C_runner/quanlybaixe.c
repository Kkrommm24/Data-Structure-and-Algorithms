#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct DateTime {
    int year, month, day, hour, minute, second; 
} DateTime;

DateTime currentDateTime() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    DateTime dt = {tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec};
    return dt;
}

typedef struct cars{
    DateTime dt;
    char bsx[13];
    int inout;
    struct cars *next;
}Cars_t;
Cars_t *first, *last;
Cars_t *changeLogfirst = NULL;
Cars_t *changeLog = NULL;

typedef struct Node{   
    DateTime dt;
    char bsx[13];
    int inout;
    struct Node *leftChild;
    struct Node *rightChild;
} Node;
Node *root;

//..............Chuc nang 1...............
void initList(){
    first = NULL; last = NULL;
}

int listEmpty(){
    return first == NULL && last == NULL;
}

Cars_t *makeProfile(DateTime dt, char *bsx, int inout){
    Cars_t* node = (Cars_t*)malloc(sizeof(Cars_t));
    node->dt = dt;
    strcpy(node->bsx, bsx);
    node->inout = inout;
    node->next = NULL;
    return node;
}


void insertLast(DateTime dt, char *bsx, int inout){
    Cars_t *profile = makeProfile(dt, bsx, inout);
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

Node *makeNode(DateTime dt, char *bsx, int inout){
    Node* p = (Node*)malloc(sizeof(Node));
    p->dt = dt;
    strcpy(p->bsx, bsx);
    p->inout = inout;
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}
Node *insert(Node *r, DateTime dt, char *bsx, int inout){
    if (r == NULL)
        return makeNode(dt, bsx, inout);
    int c = strcmp(bsx,r->bsx);
    if (c > 0)
    {
        r->rightChild = insert(r->rightChild, dt, bsx, inout);
        return r;
    }
    else if(c < 0){
        r->leftChild = insert(r->leftChild, dt, bsx, inout);
        return r;
    }
}

Node *delete(Node *r, char *bsx) {
    if (r == NULL) return NULL;
    int cmp = strcmp(bsx, r->bsx);
    if (cmp > 0) r->rightChild = delete(r->rightChild, bsx);
    else if (cmp < 0) r->leftChild = delete(r->leftChild, bsx);
    else {
        if (r->leftChild != NULL && r->rightChild != NULL) {
            Node *p = r->rightChild;
            while (p->leftChild != NULL) p = p->leftChild;
            strcpy(r->bsx, p->bsx);
            r->dt = p->dt;
            r->rightChild = delete(r->rightChild, p->bsx);
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

void inOrder(Node *r)
{
    if (r == NULL)
        return;
    inOrder(r->leftChild);
    if (r->inout == 1 ){
        printf("%d-%d-%-10d %02d:%02d:%02d %-15s\n", r->dt.year, r->dt.month, r->dt.day,
            r->dt.hour, r->dt.minute, r->dt.second, r->bsx);
    }
    inOrder(r->rightChild);
}

void inOrderF(Node *r, FILE *f)
{
    if (r == NULL)
        return;
    inOrderF(r->leftChild, f);
    if (r->inout == 1 ){
        fprintf(f, "%d-%d-%-10d %02d:%02d:%02d %s\n", r->dt.year, r->dt.month, r->dt.day,
            r->dt.hour, r->dt.minute, r->dt.second, r->bsx);
    }
    inOrderF(r->rightChild, f);
}

void load(char* filename){
    FILE* f = fopen(filename,"r");
    if(f == NULL) printf("File khong ton tai\n");
    root = NULL;
    while(!feof(f)){
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        char bsx[13];
        int inout;
        fscanf(f,"%d-%d-%d %d:%d:%d %s %d", &year, &month, &day, &hour,
            &minute, &second, bsx, &inout);
        DateTime dt = {year, month, day, hour, minute, second};
        insertLast(dt, bsx, inout);
        if (inout == 1){
               root = insert(root, dt, bsx, inout);
           }else{
                root = delete(root, bsx);
        }
        //insert(root, year, month, day, hour, minute, second, bsx, inout);
    }
    fclose(f);
    printf("Load file thanh cong!!!\n");
}

void printList(){
    for(Cars_t* p = first; p != NULL; p = p->next){ 
        printf("%d-%d-%-10d %02d:%02d:%02d %-15s\n", p->dt.year, p->dt.month, p->dt.day,
            p->dt.hour, p->dt.minute, p->dt.second, p->bsx);
    }
}
//...............Chuc nang 2..............
void processCheck_day(){
    int day,month,year;
    int vao = 0, ra = 0;
    int total = 0;
    printf("Nhap ngay muon tra cuu: ");
    scanf("%d-%d-%d",&year,&month,&day);
    Cars_t* profile = NULL;
    for(Cars_t* p = first; p != NULL; p = p->next){
        if((p->dt.year == year) && (p->dt.month == month) && (p->dt.day == day)){
            profile = p; 
            if (p->inout == 1)
            {
               vao++;
            }else ra++;
            

        } 
    }
    total = vao + ra;
    printf("\nDate %d-%d-%d Total %d, In %d, Out %d",profile->dt.year, profile->dt.month, profile->dt.day, total, vao, ra);
    if(profile == NULL){
        printf("NOT FOUND profile \n");
    }
}

//...............Chuc nang 3.................
void printInfo() {
    printf("\nTong so xe hien co: %d\n", countNodes(root));
    printf("%-15s %15s\n", "Bien so", "Thoi gian gui");
    inOrder(root);
}

//...............Pre-chuc nang 6.............
void insertLast6(DateTime dt, char *bsx, int inout){
    Cars_t *profile = makeProfile(dt, bsx, inout);
    if (changeLog == NULL)
    {
        changeLogfirst = profile;
        changeLog = profile;
    }
    else
    {
        changeLog->next = profile;
        changeLog = profile;
    }
}

//...............Chuc nang 4.................
Node *find(Node *r, char *bsx) {
    if (r == NULL) return NULL;
    int cmp = strcmp(bsx, r->bsx);
    if (cmp == 0) return r;
    if (cmp > 0) return find(r->rightChild, bsx);
    return find(r->leftChild, bsx);
}
void addVehicle(){
    char bsx[13];
    printf("\nNhap bien so xe: ");
    scanf("%s", bsx);
    if (find(root, bsx) != NULL) {
        printf("Xe da co trong bai!\n");
        return;
    }

    DateTime dt = currentDateTime();
    root = insert(root, dt, bsx, 1);
    insertLast(dt, bsx, 1);
    insertLast6(dt, bsx, 1);
    printf("Da gui xe thanh cong!\n");
}

//...............Chuc nang 5.................
void removeVehicle() {
    char bsx[13];
    printf("\nNhap bien so xe: ");
    scanf("%s", bsx);

    Node *p = find(root, bsx);
    if (p == NULL) {
        printf("Xe khong co trong bai!\n");
        return;
    }

    printf("Thoi diem gui xe: %d-%02d-%02d %02d:%02d:%02d\n", 
        p->dt.year, p->dt.month, p->dt.day, p->dt.hour, p->dt.minute, p->dt.second);
    DateTime dt = currentDateTime();
    root = delete(root, bsx);
    insertLast(dt, bsx, 0);
    insertLast6(dt, bsx, 0);
    printf("Da lay xe thanh cong!\n");
}

//...............Chuc nang 6.................
void saveFile(char* filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Loi: khong the mo file %s.\n", filename);
        return;
    }
    for (Cars_t *p = changeLogfirst; p != NULL; p = p->next) {
        fprintf(f, "%d-%02d-%02d %02d:%02d:%02d %s %d\n", 
            p->dt.year, p->dt.month, p->dt.day, p->dt.hour, p->dt.minute, p->dt.second,
            p->bsx, p->inout);
    }

    printf("Da ghi log moi ra change_log.txt\n");
    fclose(f);
}

//...............Chuc nang 7.................
void savePresentLog(char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Loi: khong the mo file %s.\n", filename);
        return;
    }

    inOrderF(root, f);
    printf("Da luu thanh cong ra file log_present.txt\n");
    fclose(f);
}

//...............Chuc nang 8.................
void trace() {
    char bsx[13];
    printf("\nNhap bien so xe: ");
    scanf("%s", bsx);
    int cnt = 0;
    for (Cars_t *p = first; p != NULL; p = p->next) {
        if (strcmp(p->bsx, bsx) == 0) {
            cnt++;
            if (cnt == 1) printf("Lich su cua xe %s:\n", bsx);
            if (p->inout == 1) printf("Gui xe: ");
            else printf("Lay xe: ");
            printf("%d-%02d-%02d %02d:%02d:%02d\n", 
                p->dt.year, p->dt.month, p->dt.day, p->dt.hour, p->dt.minute, p->dt.second);
        }
    }

    if (cnt == 0) printf("Xe chua tung gui tai bai xe\n");
}

//...............Chuc nang 9.................
void freelist(){
    Cars_t *tg = first, *temp;

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
        printf("\n====CHUONG TRINH QUAN LY BAI GUI XE====\n");
        printf("Vui long chon mot trong cac chuc nang sau\n");
        printf("1) Doc du lieu tu file log \n");
        printf("2) Tra cuu so luong xe gui/lay theo ngay trong qua khu\n");
        printf("3) Thong tin cac xe trong bai hien tai\n");
        printf("4) Gui them xe moi\n");
        printf("5) Tra xe\n");
        printf("6) Cap nhat log du lieu\n");
        printf("7) Luu danh sach xe dang co trong bai ra file\n");
        printf("8) Tra cuu lich su gui xe\n");
        printf("9) Thoat\n");
        printf("Lua chon cua ban la: "); scanf("%d%*c", &key);

        switch(key)
        {
          case 1: load("log_input.txt"); printList(); break;
          case 2: processCheck_day();  break;
          case 3: printInfo(); break;
          case 4: addVehicle(); break;
          case 5: removeVehicle();break;
          case 6: saveFile("change_log.txt"); break;
          case 7: savePresentLog("log_present.txt"); break;
          case 8: trace(); break;
          case 9: freelist(); freeTree(root); break;
          default:
            printf("Ban can chon trong khoang 1-9!\n");
            break;
        }
        if(key == 9) break;
      }while(1);
    return 0;
}