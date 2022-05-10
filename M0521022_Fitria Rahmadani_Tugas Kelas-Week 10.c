#include <stdio.h>
#include <string.h>

struct mahasiswa
{
    unsigned int NIM;
    char nama[20];
    float ipk;
};
typedef struct mahasiswa mahasiswa;

int rawbyte();int seqdata();
void listdat(FILE *readPtr);void tambahdat(FILE *addPtr);void updatedat(FILE *updatePtr);void hapusdat(FILE *deletePtr);void pindahtxt(FILE *exportPtr);
void listtxt(FILE *readPtr);void tambahtxt(FILE *addPtr);void hapustxt(FILE *deletePtr);void pindahdat(FILE *exportPtr);

int main(void)
{
    int pilihmenu;
    while(1){
        printf("\nMasukkan pilihan data:\n");
        printf("1. Menggunakan sequential data(.txt)\n");
        printf("2. Menggunakan raw byte(.dat)\n");
        printf("3. Keluar program\n");
        printf("=> ");
        scanf("%d",&pilihmenu);
        if(pilihmenu==1){
            seqdata();
        }
        else if(pilihmenu==2){
            rawbyte();
        }
        else if(pilihmenu==3){
            break;
        }
        else{
            printf("Input salah.\n");
            continue;
        }
    }
}

int rawbyte()
{
    FILE *cfPtr;

    if ((cfPtr = fopen("mahasiswa.dat", "rb+")) == NULL)
    {
        if ((cfPtr = fopen("mahasiswa.dat", "wb")) == NULL)
        {
            puts("File tidak dapat dibuka.");
        }
        /*else
        {
            mahasiswa person = {0, "", 0.0};
            for (unsigned int i = 1; i <= 1000; ++i)
            {
                fwrite(&person, sizeof(mahasiswa), 1, cfPtr);
            }
            rawbyte();
        }*/
    }
    else
    {
        unsigned int pilih;

       while(1){
            printf("\nMasukkan pilihan menu dari raw byte data:\n");
            printf("1. List data mahasiswa\n");
            printf("2. Tambah data mahasiswa\n");
            printf("3. Update data mahasiswa\n");
            printf("4. Hapus data mahasiswa\n");
            printf("5. Pindah data mahasiswa ke Raw Byte\n");
            printf("6. Keluar program.\n");
            printf("=> ");
            scanf("%u",&pilih);
            switch(pilih){
                case 1:
                    listdat(cfPtr);
                    break;
                case 2:
                    tambahdat(cfPtr);
                    break;
                case 3:
                    updatedat(cfPtr);
                    break;
                case 4:
                    hapusdat(cfPtr);
                    break;
                case 5:
                    pindahtxt(cfPtr);
                    break;
                case 6:
                    break;
                default:
                    printf("Input salah.\n");
                    continue;
            }
            break;
        }
        fclose(cfPtr);
    }
}

int seqdata()
{
    FILE *cfPtr;

    if ((cfPtr = fopen("mahasiswa.txt", "a+")) == NULL)
    {
        puts("File tidak dapat dibuka.");
    }
    else
    {
        unsigned int pilih;
        while(1){
            printf("\nMasukkan pilihan menu dari sequential data:\n");
            printf("1. List data mahasiswa\n");
            printf("2. Tambah data mahasiswa\n");
            printf("3. Hapus data mahasiswa\n");
            printf("4. Pindah data mahasiswa ke Raw Byte\n");
            printf("5. Keluar program.\n");
            printf("=> ");
            scanf("%d",&pilih);
            switch(pilih){
                case 1:
                    listtxt(cfPtr);
                    break;
                case 2:
                    tambahtxt(cfPtr);
                    break;
                case 3:
                    hapustxt(cfPtr);
                    break;
                case 4:
                    pindahdat(cfPtr);
                    break;
                case 5:
                    break;
                default:
                    printf("Input salah.\n");
                    break;
            }
            break;
        }
        fclose(cfPtr);
    }
}

void listdat(FILE *readPtr)
{
    printf("%-10s %-20s %10s\n","NIM", "Nama", "IPK");

    rewind(readPtr);
    while (!feof(readPtr))
    {
        mahasiswa person = {0, "", 0};
        int result =
            fread(&person, sizeof(mahasiswa), 1, readPtr);

        if (result != 0 && person.NIM != 0)
        {
            printf("%-10d %-20s %10.2f\n",person.NIM, person.nama, person.ipk);
        }
    }
}

void tambahdat(FILE *addPtr)
{
    mahasiswa person = {0, "", 0};

    unsigned int nim;
    puts("Masukkan NIM (3 digit terakhir) : ");
    printf("=> ");
    scanf("%u", &nim);

    fseek(addPtr, (nim - 1) * sizeof(mahasiswa),SEEK_SET);

    fread(&person, sizeof(mahasiswa), 1, addPtr);
    if (person.NIM != 0)
    {
        printf("NIM %u telah digunakan.\n",person.NIM);
    }
    else
    {
        puts("Masukkan nama dan IPK: ");
        printf("=> ");
        scanf("%s %f", &person.nama, &person.ipk);

        person.NIM = nim;

        fseek(addPtr, (person.NIM - 1) * sizeof(mahasiswa), SEEK_SET);
        fwrite(&person,sizeof(mahasiswa), 1, addPtr);
    }
}

void updatedat(FILE *updatePtr)
{
    mahasiswa person = {0, "", 0};

    unsigned int nim;
    puts("Masukkan NIM (3 digit terakhir) : ");
    printf("=> ");
    scanf("%u", &nim);

    fseek(updatePtr, (nim - 1) * sizeof(mahasiswa),SEEK_SET);
    fread(&person, sizeof(mahasiswa), 1, updatePtr);

    if (person.NIM == 0)
    {
        printf("Tidak ada informasi atas NIM %u.\n", nim);
    }
    else
    {
        printf("%-10d %-20s %10.2f\n\n",
               person.NIM,person.nama,person.ipk);

        puts("Masukkan nama, IPK yang baru: ");
        printf("=> ");
        scanf("%s %f", &person.nama,&person.ipk);

        printf("%-10d %-20s %10.2f\n\n",person.NIM, person.nama,person.ipk);

        fseek(updatePtr, (nim - 1) * sizeof(mahasiswa),SEEK_SET);
        fwrite(&person, sizeof(mahasiswa), 1, updatePtr);
    }
}

void hapusdat(FILE *deletePtr)
{
    mahasiswa person = {0, "", 0};

    unsigned int nim;
    puts("Masukkan NIM yang akan dihapus (3 digit terakhir) : ");
    printf("=> ");
    scanf("%u", &nim);

    fseek(deletePtr, (nim - 1) * sizeof(mahasiswa),SEEK_SET);

    fread(&person, sizeof(struct mahasiswa), 1, deletePtr);

    if (person.NIM != nim)
    {
        printf("NIM %d tidak ditemukan.\n", nim);
    }
    else
    {
        fseek(deletePtr, (nim - 1) * sizeof(mahasiswa),SEEK_SET);
        person.NIM = 0;
        strcpy(person.nama, "");
        person.ipk = 0;

        fwrite(&person,sizeof(mahasiswa), 1, deletePtr);

        printf("Data dengan NIM %d telah dihapus\n", nim);
    }
}

void pindahtxt(FILE *exportPtr)
{
    FILE *txtPtr;

    if ((txtPtr = fopen("mahasiswa.txt", "w")) == NULL)
    {
        puts("File tidak dapat dibuka.");
    }
    else
    {
        rewind(exportPtr);

        while (!feof(exportPtr))
        {
            mahasiswa person = {0, "", 0};
            int result =
                fread(&person, sizeof(mahasiswa), 1, exportPtr);

            if (result != 0 && person.NIM != 0)
            {
                fprintf(txtPtr, "%-10d %-20s %10.2f\n",
                        person.NIM, person.nama, person.ipk);
            }
        }
        puts("File telah diubah menjadi mahasiswa.txt!");
        fclose(txtPtr);
    }
}

void listtxt(FILE *readPtr)
{
    mahasiswa person = {0, "", 0};
    printf("%-10s %-20s %-10s\n", "NIM", "Nama", "IPK");

    rewind(readPtr);

    fscanf(readPtr, "%d %s %f", &person.NIM, person.nama, &person.ipk);
    while (!feof(readPtr))
    {
        printf("%-10d %-20s %-10.2f\n", person.NIM, person.nama, person.ipk);
        fscanf(readPtr, "%d %s %f", &person.NIM, person.nama, &person.ipk);
    }
    fclose(readPtr);
}

void tambahtxt(FILE *addPtr)
{
    mahasiswa person = {0, "", 0};
    mahasiswa data = {0, "", 0};

    puts("Masukkan NIM, Nama, IPK (Masukkan EOF untuk berhenti) :");
    printf("=> ");
    scanf("%d %s %f", &person.NIM, person.nama, &person.ipk);
    rewind(addPtr);

    fscanf(addPtr, "%d %s %f", &person.NIM, person.nama, &person.ipk);
    while (!feof(stdin))
    {
        int stop=0;
        while (!feof(addPtr))
        {
            if (person.NIM == data.NIM)
            {
                printf("NIM %d sudah digunakan!\n", person.NIM);
                stop == 1;
                break;
            }
            fscanf(addPtr, "%d %s %f", &data.NIM, data.nama, &data.ipk);
        }
        printf("=> ");
        if (stop == 0)
        {
            fprintf(addPtr, "%-10d %-20s %10.2f\n", person.NIM, person.nama, person.ipk);
        }
        scanf("%d %s %lf", &person.NIM, person.nama, &person.ipk);
        rewind(addPtr);
        stop = 0;
    }
}

void hapustxt(FILE *deletePtr)
{
    mahasiswa person = {0, "", 0};
    unsigned int nim;
    printf("Masukkan NIM yang akan dihapus (3 digit terakhir) : ");
    scanf("%d", &nim);

    rewind(deletePtr);

    FILE *tempPtr;
    if ((tempPtr = fopen("temp.txt", "w")) == NULL)
    {
        puts("File tidak dapat dibuka.");
    }
    else
    {
        fscanf(deletePtr, "%d %s %f", &person.NIM, person.nama, &person.ipk);
        while (!feof(deletePtr))
        {
            if (person.NIM != nim)
            {
                fprintf(tempPtr, "%-10d %-20s %10.2f\n", person.NIM, person.nama, person.ipk);
            }
            fscanf(deletePtr, "%d %s %lf", &person.NIM, person.nama, &person.ipk);
        }

        fclose(deletePtr);
        fclose(tempPtr);

        remove("mahasiswa.txt");
        rename("temp.txt", "mahasiswa.txt");

        printf("NIM %d telah dihapus.\n", nim);
        deletePtr = fopen("mahasiswa.txt", "r+");
    }
}

void pindahdat(FILE *exportPtr)
{
    FILE *datPtr;

    mahasiswa person = {0, "", 0};

    if ((datPtr = fopen("mahasiswa.dat", "wb")) == NULL)
    {
        puts("File tidak dapat dibuka.");
    }
    else
    {
        rewind(exportPtr);

        while (!feof(exportPtr))
        {
            fscanf(exportPtr, "%d %s %f", &person.NIM, person.nama, &person.ipk);
            fseek(datPtr, (person.NIM - 1) * sizeof(mahasiswa), SEEK_SET);
            fwrite(&person, sizeof(mahasiswa), 1, datPtr);
        }
        puts("File telah diubah menjadi mahasiswa.dat!");
    }
    fclose(datPtr);
}
