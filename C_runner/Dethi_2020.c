#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Covid{
    char location[40];
    int hour;
    int min;
    struct Covid *next;
}Covid_t;

Covid_t *first, *last;

void initList(){
    first = NULL; last = NULL;
}

int listEmpty(){
    return first == NULL && last == NULL;
}

Covid_t *makeProfile(char *location, int hour, int min){
    Covid_t* node = (Covid_t*)malloc(sizeof(Covid_t));
    strcpy(node->location, location);
    node->hour = hour;
    node->min = min;
    node->next = NULL;
    return node;
}

void insertLast(char *location, int hour, int min){
    Covid_t *profile = makeProfile(location, hour, min);
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

void load(char* filename){
    FILE* f = fopen(filename,"r");
    if(f == NULL) printf("File khong ton tai\n");
    while(!feof(f)){
        char location[40];
        int hour;
        int min;
        fscanf(f,"%s %d %d", location, &hour, &min);
        insertLast(location, hour, min);
    }
    fclose(f);
}

void processLoad(){
    printf("Nhap ten file: ");  
    char filename[256];
    scanf("%s",filename);
    //filename[strlen(filename) - 1] = '\0';
    load(filename);
}

void printList(){
    for(Covid_t* p = first; p != NULL; p = p->next)
        printf("%-50s %-10d %-10d\n",p->location, p->hour, p->min);
}

void find_time()
{
    int cnt;
    char new_loc[40];
    printf("Nhap dia diem: ");
    scanf("%s", new_loc);
    Covid_t *profile = NULL;

    for (Covid_t *p = first; p != NULL; p = p->next)
    {
        if (strcmp(p->location, new_loc) == 0)
        {
            profile = p;
            cnt++;
        }
    }
    
    int j = 0;
    for (Covid_t *p = first; p != NULL; p = p->next)
    {
        if (strcmp(p->location, new_loc) == 0)
        {
            j++;
            if (j != cnt)
                printf("%d:%d, ", p->hour, p->min);
            else
                printf("%d:%d", p->hour, p->min);
        }
    }

    if (profile == NULL)
    {
        printf("Ban chua toi dia diem do");
    }
}

void find_location()
{
    int new_hour;
    int new_min;
    printf("Nhap thoi gian: ");
    do{
        scanf("%d %d", &new_hour, &new_min);
        if(new_hour < 0 || new_hour >= 24 || new_min < 0 || new_min >= 60){
            printf("Nhap lai: ");
        }else{
            break;
        }
        
    }while(1);
    
    Covid_t *profile = NULL;

    for (Covid_t *p = first; p != NULL; p = p->next)
    {
        if (p->hour == new_hour && p->min == new_min)
        {
            profile = p;
            printf("%s", p->location);
        }
    }

    if (profile == NULL)
    {
        printf("KHONG tim thay lich su di chuyen!");
    }
}

int check_covid(char *check_loc, int check_hour, int check_min){
    int a, b;
    long result;
    long check_result = check_hour*3600 + check_min*60;;
    Covid_t *profile = NULL;
    for (Covid_t *p = first; p != NULL; p = p->next){
        a = p->hour;
        b = p->min;
        result = a*3600 + b*60;
        check_result = check_hour*3600 + check_min*60;
        if (strcmp(check_loc, p->location) == 0 && (result <= check_result)){
            return 1;
        }
    }
    return 0;
}

void truyvet(){
    char check_loc[40];
    int check_hour, check_min;
    printf("Nhap dia diem va thoi gian: ");
    scanf("%s %d %d", check_loc, &check_hour, &check_min);
    if(check_covid(check_loc, check_hour, check_min) == 1){
        printf("Ban co kha nang bi lay Covid, can phai khai bao y te ngay lap tuc!");
    }else{
        printf("Lich su di chuyen cua ban OK");
    }
}

void freelist(){
    Covid_t *tg = first, *temp;

    while (tg != NULL)
    {
        temp = tg->next;
        free(tg);
        tg = temp;
    }
}

int main(){
    int key;
    initList();
        do{
        printf("\n====CHUONG TRINH TRUY VET COVID19====\n");
        printf("1) Nap file log lich su di chuyen\n");
        printf("2) In ra lich su di chuyen\n");
        printf("3) Tim kiem lich su theo dia diem\n");
        printf("4) Tim kiem lich su theo thoi gian\n");
        printf("5) Kiem tra truy vet moi nhat\n");
        printf("6) Thoat\n");
        printf("input key: "); scanf("%d%*c", &key);

        switch(key)
        {
          case 1: processLoad(); break;
          case 2: printList(); break;
          case 3: find_time();  break;
          case 4: find_location(); break;
          case 5: truyvet(); break;
          case 6: freelist();
        }
        if(key == 6) break;
      }while(1);
    return 0;
}