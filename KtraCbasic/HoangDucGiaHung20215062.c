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

Covid_t *top;

void initStack(){
    top = NULL;
}


Covid_t *makeProfile(char *location, int hour, int min){
    Covid_t* node = (Covid_t*)malloc(sizeof(Covid_t));
    strcpy(node->location, location);
    node->hour = hour;
    node->min = min;
    node->next = NULL;
    return node;
}

void push(char *location, int hour, int min){
    Covid_t* p = makeProfile(location, hour, min);
    p->next = top; 
    top = p; 
}


void load(char* filename){
    FILE* f = fopen(filename,"r");
    if(f == NULL) printf("File khong ton tai\n");
    while(!feof(f)){
        char location[40];
        int hour;
        int min;
        fscanf(f,"%s %d %d", location, &hour, &min);
        fscanf(f, "\n");
        push(location, hour, min);
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

void printStack(){
    if (top == NULL) {
        printf("\nStack Underflow\n");
    } else {
        for(Covid_t* p = top; p != NULL; p = p->next)
            printf("%-50s %-10d %-10d\n",p->location, p->hour, p->min);     
        }
    /*for(Covid_t* p = top; p != NULL; p = p->next)
        printf("%-50s %-10d %-10d\n",p->location, p->hour, p->min);*/
}

void find_time()
{
    int cnt;
    char new_loc[40];
    printf("Nhap dia diem: ");
    scanf("%s", new_loc);
    Covid_t *profile = NULL;
    for (Covid_t *p = top; p != NULL; p = p->next)
    {
        if (strcmp(p->location, new_loc) == 0)
        {
            profile = p;
            cnt++;
        }
    }
    
    int j = 0;
    for (Covid_t *p = top; p != NULL; p = p->next)
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
    fflush(stdin);
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

    for (Covid_t *p = top; p != NULL; p = p->next)
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

void freeStack(){
    Covid_t *tg = top, *temp;

    while (tg != NULL)
    {
        temp = tg->next;
        free(tg);
        tg = temp;
    }
}


int main(){
    int key;
    initStack();
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
          case 2: printStack(); break;
          case 3: find_time();  break;
          case 4: find_location(); break;
          case 5: break;
          case 6: freeStack(); exit(0); break;
        }
        if(key == 6) break;
      }while(1);
    return 0;
}