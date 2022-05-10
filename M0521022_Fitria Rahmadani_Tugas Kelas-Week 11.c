//Fitria Rahmadani
//M0521022
//Informatika A
//Tugas Week 11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mahasiswa {
    int nim;
    char nama[50];
    char fakul[10];
    float ipk;
    struct mahasiswa *next;
    struct mahasiswa *left;
    struct mahasiswa *right;
};
typedef struct mahasiswa Mahasiswa;
typedef Mahasiswa *MahasiswaPtr;

void linkedlist();
void write(MahasiswaPtr *sPtr, int nim,char nama[50],char fakul[10],float ipk);
int deletedata(MahasiswaPtr *sPtr, int nim);
void printList(MahasiswaPtr currentPtr);
int isEmpty(MahasiswaPtr sPtr);

void stack();
void printStack (MahasiswaPtr currentPtr);
void push (MahasiswaPtr *topPtr, int nim,char nama[50],char fakul[10],float ipk);
int pop (MahasiswaPtr *topPtr, int nim);

void queue();
void enqueue (MahasiswaPtr *headPtr, MahasiswaPtr *tailPtr, int nim,char nama[50],char fakul[10],float ipk);
void dequeue (MahasiswaPtr *headPtr, MahasiswaPtr *tailPtr);
void printQueue (MahasiswaPtr currentPtr);

void binaryTree();
void insertItem(MahasiswaPtr *treePtr, int nim, char nama[50], char fakul[10], float ipk);
void inOrder (MahasiswaPtr treePtr);
void preOrder (MahasiswaPtr treePtr);
void postOrder (MahasiswaPtr treePtr);

int main()
{
    printf("\n===Pilihan Program===\n");
    printf("1. Linked List\n");
    printf("2. Stack\n");
    printf("3. Queue\n");
    printf("4. Binary Tree\n");
    printf("5. Keluar Program\n\n");

    while(1) {
        int pilih;
        printf("Masukkan pilihan menu : ");
        scanf("%d",&pilih);
        switch(pilih) {
            case 1 :
                linkedlist();
                break;
            case 2 :
                stack();
                break;
            case 3 :
                queue();
                break;
            case 4 :
                binaryTree();
                break;
            case 5 :
                printf("Program Selesai.\n");
                break;
            default :
                printf("Pilihan anda salah. Masukkan lagi!!\n");
                continue;
                break;
        }break;
    }
}

void linkedlist()
{
    int pilihan;
    MahasiswaPtr start = NULL;
    int nimUser;
    char namaUser[50];
    char fakulUser[10];
    float ipkUser;

    printf("\n==Linked List==\n");
    printf("1. Tambah Data\n");
    printf("2. Hapus Data\n");
    printf("3. Print Data\n");
    printf("4. Selesai\n");

    while(1) {
        int choice;
        printf("Masukkan pilihan anda : ");
        scanf("%d",&choice);
        switch(choice) {
            case 1 :
                printf("NIM (3 digit)    : ");
                scanf("%d", &nimUser);
                printf("Nama             : ");
                scanf("\n%[^\n]", namaUser);
                printf("Fakultas         : ");
                scanf("%s", fakulUser);
                printf("IPK              : ");
                scanf("%f", &ipkUser);
                write(&start, nimUser,namaUser,fakulUser,ipkUser);
                printList(start);
                continue;
                break;
            case 2 :
                if (!isEmpty(start)) {
                    printf("NIM yang ingin dihapus : ");
                    scanf("%d", &nimUser);
                    if (deletedata(&start, nimUser)) {
                        printf("Data dengan NIM %d telah berhasil dihapus!\n", nimUser);
                        printList(start);
                    } else {
                        printf("Data dengan NIM %d tidak ditemukan!\n", nimUser);
                    }
                } else {
                    puts("Data kosong.\n");
                }
                continue;
                break;
            case 3 :
                printList(start);
                continue;
                break;
            case 4 :
                printf("Program Selesai.\n");
                break;
            default :
                printf("Pilihan anda salah. Masukkan lagi!!\n");
                continue;
                break;
        }break;
    }
}

void write(MahasiswaPtr *sPtr, int nim,char nama[50],char fakul[10],float ipk)
{
    MahasiswaPtr newPtr = malloc(sizeof(Mahasiswa));

    if (newPtr != NULL) {
        newPtr->nim = nim;
        strcpy(newPtr->nama,nama);
        strcpy(newPtr->fakul,fakul);
        newPtr->ipk = ipk;
        newPtr->next = NULL;

        MahasiswaPtr prevPtr = NULL;
        MahasiswaPtr currPtr = *sPtr;

        while (currPtr != NULL && nim > currPtr->nim) {
            prevPtr = currPtr;
            currPtr = currPtr->next;
        }

        if (prevPtr == NULL) {
            newPtr->next = *sPtr;
            *sPtr = newPtr;
        }else {
            prevPtr->next = newPtr;
            newPtr->next = currPtr;
        }
    } else {
        printf("NIM %d tidak dapat ditambahkan!\n", nim);
    }
}

int deletedata(MahasiswaPtr *sPtr, int nim)
{
    if (nim == (*sPtr)->nim) {
        MahasiswaPtr tempPtr = *sPtr;
        *sPtr = (*sPtr)->next;
        free(tempPtr);
        return nim;
    }else {
        MahasiswaPtr prevPtr = *sPtr;
        MahasiswaPtr currPtr = (*sPtr)->next;

        while (currPtr != NULL && currPtr->nim != nim) {
            prevPtr = currPtr;
            currPtr = currPtr->next;
        }
        if (currPtr != NULL) {
            MahasiswaPtr tempPtr = currPtr;
            prevPtr->next = currPtr;
            free(tempPtr);
            return nim;
        }
    }
}

int isEmpty(MahasiswaPtr sPtr)
{
    return sPtr == NULL;
}

void printList(MahasiswaPtr currentPtr)
{
    if (isEmpty(currentPtr)) {
        puts("Data tidak tersedia.\n");
    } else {
        printf("\n%-15s %-30s %-15s %10s\n","NIM","Nama","Fakultas","IPK");
        while (currentPtr != NULL) {
            printf("%-15d %-30s %-15s %10.2f\n", currentPtr->nim, currentPtr->nama, currentPtr->fakul, currentPtr->ipk);
            currentPtr = currentPtr->next;
        }
    }
}

void stack()
{
    int pilihan;
    MahasiswaPtr stackPtr = NULL;
    int nimUser;
    char namaUser[50];
    char fakulUser[10];
    float ipkUser;

    printf("\n====Stack====\n");
    printf("1. Tambah Data\n");
    printf("2. Hapus Data\n");
    printf("3. Selesai\n");

    while(1) {

        int choice;
        printf("Masukkan pilihan anda : ");
        scanf("%d",&choice);
        switch(choice) {
            case 1 :
                printf("NIM (3 digit)    : ");
                scanf("%d", &nimUser);
                printf("Nama             : ");
                scanf("\n%[^\n]", namaUser);
                printf("Fakultas         : ");
                scanf("%s", fakulUser);
                printf("IPK              : ");
                scanf("%f", &ipkUser);
                push(&stackPtr, nimUser,namaUser,fakulUser,ipkUser);
                printStack(stackPtr);
                continue;
                break;
            case 2 :
                if (!isEmpty(stackPtr)) {
                   pop(&stackPtr,nimUser);
                   printf("Data telah dihapus\n");
                }
                printStack(stackPtr);
                continue;
                break;
            case 3 :
                printf("Program Selesai.\n");
                break;
            default :
                printf("Pilihan anda salah. Masukkan lagi!!\n");
                continue;
                break;
        }break;
    }
}

void printStack (MahasiswaPtr currentPtr)
{
    if (currentPtr == NULL) {
        puts("Data tidak tersedia.\n");
    }else {
        while (currentPtr != NULL) {
            printf("%-10d %-30s %-10s %10.2f\n", currentPtr->nim,currentPtr->nama,currentPtr->fakul,currentPtr->ipk);
            printf("-------->\n");
            currentPtr = currentPtr->next;
        }
        puts("NULL\n");
    }
}

void push (MahasiswaPtr *topPtr, int nim,char nama[50],char fakul[10],float ipk)
{
    MahasiswaPtr newPtr = malloc(sizeof(Mahasiswa));

    if (newPtr != NULL) {
        newPtr->nim = nim;
        strcpy(newPtr->nama,nama);
        strcpy(newPtr->fakul,fakul);
        newPtr->ipk = ipk;
        newPtr->next = *topPtr;
        *topPtr = newPtr;
    }else {
        printf("Data tidak dapat ditambahkan!\n");
    }
}

int pop (MahasiswaPtr *topPtr, int nim)
{
    MahasiswaPtr tempPtr = *topPtr;
    nim = (*topPtr)->nim;
    *topPtr = (*topPtr)->next;
    free(tempPtr);
    return nim;
}

void queue()
{
    MahasiswaPtr headPtr = NULL;
    MahasiswaPtr tailPtr = NULL;

    int pilihan;
    int nimUser;
    char namaUser[50];
    char fakulUser[10];
    float ipkUser;

    printf("\n====Queue====\n");
    printf("1. Tambah Data\n");
    printf("2. Hapus Data\n");
    printf("3. Selesai\n");

    while(1) {

        int choice;
        printf("Masukkan pilihan anda : ");
        scanf("%d",&choice);
        switch(choice) {
            case 1 :
                printf("NIM (3 digit)    : ");
                scanf("%d", &nimUser);
                printf("Nama             : ");
                scanf("\n%[^\n]", namaUser);
                printf("Fakultas         : ");
                scanf("%s", fakulUser);
                printf("IPK              : ");
                scanf("%f", &ipkUser);
                enqueue(&headPtr, &tailPtr, nimUser,namaUser,fakulUser,ipkUser);
                printQueue(headPtr);
                continue;
                break;
            case 2 :
                if (!isEmpty(headPtr)) {
                   dequeue(&headPtr, &tailPtr);
                   printf("Data telah dihapus.\n");
                }
                printQueue(headPtr);
                continue;
                break;
            case 3 :
                printf("Program Selesai.\n");
                break;
            default :
                printf("Pilihan anda salah. Masukkan lagi!!\n");
                continue;
                break;
        }break;
    }
}

void enqueue (MahasiswaPtr *headPtr, MahasiswaPtr *tailPtr, int nim,char nama[50],char fakul[10],float ipk)
{
    MahasiswaPtr newPtr = malloc(sizeof(Mahasiswa));

    if(newPtr != NULL) {
        newPtr->nim = nim;
        strcpy(newPtr->nama,nama);
        strcpy(newPtr->fakul,fakul);
        newPtr->ipk = ipk;
        newPtr->next = NULL;

        if(isEmpty(*headPtr)) {
            *headPtr = newPtr;
        }else {
            (*tailPtr)->next = newPtr;
        }

        *tailPtr = newPtr;
    }else {
        printf("Data tidak dapat ditambahkan!\n");
    }
}

void dequeue (MahasiswaPtr *headPtr, MahasiswaPtr *tailPtr)
{
    int nim;
    nim = (*headPtr)->nim;
    MahasiswaPtr temp = *headPtr;
    *headPtr = (*headPtr)->next;

    if (*headPtr == NULL) {
        *tailPtr = NULL;
    }

    free(temp);
}

void printQueue (MahasiswaPtr currentPtr)
{
    if (currentPtr == NULL) {
        puts("Data tidak tersedia!\n");
    }else {
        while (currentPtr != NULL) {
            printf("%-10d %-30s %-10s %10.2f\n", currentPtr->nim,currentPtr->nama,currentPtr->fakul,currentPtr->ipk);
            printf("-------->\n");
            currentPtr = currentPtr->next;
        }
        puts("NULL\n");
    }
}

void binaryTree()
{
    int nimUser;
    char namaUser[50];
    char fakulUser[10];
    float ipkUser;
    int item;
    MahasiswaPtr rootPtr = NULL;

    printf("Jumlah input    : ");
    scanf("%d",&item);
    for (int i=0; i<item; i++) {
        printf("NIM (3 digit)    : ");
        scanf("%d", &nimUser);
        printf("Nama             : ");
        scanf("\n%[^\n]", namaUser);
        printf("Fakultas         : ");
        scanf("%s", fakulUser);
        printf("IPK              : ");
        scanf("%f", &ipkUser);
        printf("\n");
        insertItem(&rootPtr,nimUser,namaUser,fakulUser,ipkUser);
    }

    puts("\nUrutan IPK secara PreOrder : ");
    preOrder(rootPtr);

    puts("\nUrutan IPK secara InOrder : ");
    inOrder(rootPtr);

    puts("\nUrutan IPK secara PostOrder : ");
    postOrder(rootPtr);
}

void insertItem(MahasiswaPtr *treePtr, int nim, char nama[50], char fakul[10], float ipk)
{
    if(*treePtr == NULL) {
        *treePtr = malloc(sizeof(Mahasiswa));

        if (*treePtr != NULL) {
            (*treePtr)->nim = nim;
            strcpy((*treePtr)->nama,nama);
            strcpy((*treePtr)->fakul,fakul);
            (*treePtr)->ipk = ipk;
            (*treePtr)->left = NULL;
            (*treePtr)->right = NULL;
        }else {
            printf("Data tidak dapat ditambahkan!\n");
        }
    }else {
        if (ipk < (*treePtr)->ipk) {
            insertItem(&((*treePtr)->left),nim,nama,fakul,ipk);
        }else if (ipk > (*treePtr)->ipk) {
            insertItem(&((*treePtr)->right),nim,nama,fakul,ipk);
        }else {
            printf("dup\n");
        }
    }
}

void inOrder (MahasiswaPtr treePtr)
{
    if (treePtr != NULL) {
        inOrder(treePtr->left);
        printf("%-10d %-30s %-10s %10.2f\n", treePtr->nim,treePtr->nama,treePtr->fakul,treePtr->ipk);
        inOrder(treePtr->right);
    }
}

void preOrder (MahasiswaPtr treePtr)
{
    if (treePtr != NULL) {
        printf("%-10d %-30s %-10s %10.2f\n", treePtr->nim,treePtr->nama,treePtr->fakul,treePtr->ipk);
        inOrder(treePtr->left);
        inOrder(treePtr->right);
    }
}

void postOrder (MahasiswaPtr treePtr)
{
    if (treePtr != NULL) {
        inOrder(treePtr->left);
        inOrder(treePtr->right);
        printf("%-10d %-30s %-10s %10.2f\n", treePtr->nim,treePtr->nama,treePtr->fakul,treePtr->ipk);
    }
}
