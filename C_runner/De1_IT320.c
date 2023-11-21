#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct PC{
    int id;
    char CPU[3];
    char RAM[3];
    struct PC *next;
}PC_t;

PC_t *first, *last;
int cnt;

void print_amount(int amount){
    printf("So may vua them moi: %d\n", amount);
}

void initList(){
    first = NULL; last = NULL;
}

int listEmpty(){
    return first == NULL && last == NULL;
}

PC_t *makeProfile(int id, char *CPU, char *RAM){
    PC_t* node = (PC_t*)malloc(sizeof(PC_t));
    node->id = id;
    strcpy(node->CPU, CPU);
    strcpy(node->RAM, RAM);
    node->next = NULL;
    return node;
}

void insertLast(int id, char *CPU, char *RAM){
    PC_t *profile = makeProfile(id, CPU, RAM);
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
    int amount;
    fscanf(f,"%d\n",&amount);
    for (int i = 0; i < amount; i++){
        int id;
        if(cnt == 0){
            id = 0;
        }else{
            id = cnt;
        }
        id++;
        char CPU[3];
        char RAM[3];
        fscanf(f,"%d%*c", &id);
        //fgets(CPU,3,f); chon cnay hoac fscanf() deu dc
        /*CPU[strlen(CPU) - 1] = '\0';*/
        fscanf(f,"%s %s", CPU, RAM);
        insertLast(id, CPU, RAM);
        cnt++;
        if(cnt >= 20){
            printf("Danh sach da day, khong them duoc\n");
            print_amount(i+1);
            break;
        }
    }
    if(cnt < 20) print_amount(amount);
    fclose(f);
}

void processLoad(){
    printf("Nhap ten file: ");  
    char filename[256];
    scanf("%s",filename);
    //filename[strlen(filename) - 1] = '\0';
    load(filename);
}

/*void processStore(){
    char filename[256];
    scanf("%s",filename);
    FILE* f = fopen(filename,"w");
    for(PC_t* p = first; p != NULL; p = p->next){
        fprintf(f,"%s %s",p->CPU,p->RAM);
        if(p->next != NULL) fprintf(f,"\n");
    }
    fclose(f);
}
*/
void printList(){
    for(PC_t* p = first; p != NULL; p = p->next)
        printf("%d %s %s\n",p->id, p->CPU, p->RAM);
}

void updateCPU(int a){
    char *stop = "STOP";
    char new_CPU[5];
    printf("Nhap ID: ");
    do{
        scanf("%d%*c", &a);
        fflush(stdin);
        if(a > 0 && a <= cnt) break;
        else printf("Nhap lai ID: ");
    }while(1);
    for (PC_t *p = first; p != NULL; p = p->next)
    {
        if (p->id >= a )
        {   
            do{
                printf("Nhap CPU muon thay vao: ");
                scanf("%s",new_CPU); //ko dung fgets() do fgets() bat phai nhap du ki tu
                fgetc(stdin);
                //strupr(new_CPU);
                if(strcmp(new_CPU,"I3")==0 || strcmp(new_CPU,"I5")==0 || 
                strcmp(new_CPU,"I7")==0 || strcmp(new_CPU,"i3")==0 || 
                strcmp(new_CPU,"i5")==0 || strcmp(new_CPU,"i7")==0){
                    strcpy(p->CPU,new_CPU);
                    break;
                }else{
                    printf("Nhap lai:\n");
                }
            
            }while(strcmp(new_CPU,stop) != 0);
            if(strcmp(new_CPU,stop) == 0) return;
        }
        
    }
}

void updateRAM(int x){
    char *stop = "STOP";
    char new_RAM[5];
    printf("Nhap ID: ");
    do{
        scanf("%d%*c", &x);
        fflush(stdin);
        if(x > 0 && x <= cnt) break;
        else printf("Nhap lai ID: ");
    }while(1);
    for (PC_t *p = first; p != NULL; p = p->next)
    {
        if (p->id >= x )
        {   
            do{
                printf("Nhap RAM muon thay vao: ");
                scanf("%s",new_RAM); //ko dung fgets() do fgets() bat phai nhap du ki tu
                fgetc(stdin);
                if(strcmp(new_RAM,"1")==0 || strcmp(new_RAM,"2")==0 || 
                strcmp(new_RAM,"4")==0 || strcmp(new_RAM,"8")==0 || 
                strcmp(new_RAM,"16")==0 || strcmp(new_RAM,"32")==0){
                    strcpy(p->RAM,new_RAM);
                    break;
                }else{
                    printf("Nhap lai:\n");
                }
            
            }while(strcmp(new_RAM,stop) != 0);
            if(strcmp(new_RAM,stop) == 0) return;
        }
        
    }
}

void find(){
    char find_CR[3];
    printf("Nhap CPU hoac RAM ban muon tim kiem: ");
    scanf("%s", find_CR);
    PC_t *profile = NULL;
    if(strcmp(find_CR,"I3")==0 || strcmp(find_CR,"I5")==0 || 
    strcmp(find_CR,"I7")==0 || strcmp(find_CR,"i3")==0 || 
    strcmp(find_CR,"i5")==0 || strcmp(find_CR,"i7")==0){

        for (PC_t *p = first; p != NULL; p = p->next){
            if (strcmp(p->CPU, find_CR) == 0){
                profile = p;
                printf("FOUND profile: %s %s\n", p->CPU, p->RAM);
            }
        }
    }else if(strcmp(find_CR,"1")==0 || strcmp(find_CR,"2")==0 || 
    strcmp(find_CR,"4")==0 || strcmp(find_CR,"8")==0 || 
    strcmp(find_CR,"16")==0 || strcmp(find_CR,"32")==0){

        for (PC_t *p = first; p != NULL; p = p->next){
            if (strcmp(p->RAM, find_CR) == 0){
                profile = p;
                printf("FOUND profile: %s %s\n", p->CPU, p->RAM);
            }
        }
    }

    if (profile == NULL)
    {
        printf("Gia tri tim kiem khong hop le!\n");
    }
}


int main(){
    int key;
    int a, x;
    initList();
        do{
        printf("\n====Program for management computers====\n");
        printf("1) Load Data Files:\n");
        printf("2) Update CPU info:\n");
        printf("3) Update Ram info:\n");
        printf("4) Search:\n");
        printf("5) Quit\n");
        printf("input key: "); scanf("%d%*c", &key);

        switch(key)
        {
          case 1: processLoad(); printList();  /*processStore();*/ break;
          case 2: updateCPU(a); printList(); break;
          case 3: updateRAM(x); printList(); break;
          case 4: find(); break;
        }
      }while(key != 5);
    return 0;
}