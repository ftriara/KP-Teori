//Fitria Rahmadani
//(M0521022)

#include <stdio.h>
#include <stdlib.h>

void displayBits(unsigned int value);

typedef enum makananfav{
    Soto = 1,Sate,Bakso,Rawon,Pecel,Rendang
}makananfav;

struct Person{
    char *nama;
    char *nama_panggilan;
    unsigned int usia;
    makananfav makanan;
    struct Person *Ayah;
    struct Person *Ibu;
};

typedef struct Person person;

int main(void)
{
    const char *namaMakanan[] = {" ", "Soto", "Sate", "Bakso", "Rawon", "Pecel", "Rendang"};

    person anak,ayah,ibu;
    anak.Ayah=&ayah;
    anak.Ibu=&ibu;

    anak.nama="Denny Sucipto";
    anak.nama_panggilan="Denny";
    anak.usia=17;
    anak.makanan=Bakso;

    anak.Ayah->nama="Benny Sucipto";
    anak.Ayah->nama_panggilan="Benny";
    anak.Ayah->usia=49;
    anak.Ayah->makanan=Rendang;

    anak.Ibu->nama="Dian Sucipto";
    anak.Ibu->nama_panggilan="Dian";
    anak.Ibu->usia=45;
    anak.Ibu->makanan=Rawon;

    printf("\n=====Data Keluarga=====\n\n");
    printf("Nama Anak        : %s\n", anak.nama);
    printf("Nama Panggilan   : %s\n", anak.nama_panggilan);
    printf("Usia Anak        : %u\n", anak.usia);
    printf("Makanan Favorit  : %s\n\n", namaMakanan[anak.makanan]);

    printf("Nama Ayah        : %s\n", anak.Ayah->nama);
    printf("Nama Panggilan   : %s\n", anak.Ayah->nama_panggilan);
    printf("Usia Ayah        : %u\n", anak.Ayah->usia);
    printf("Usia Ayah (bit)  : "); displayBits(anak.Ayah->usia);
    printf("Makanan Favorit  : %s\n\n", namaMakanan[anak.Ayah->makanan]);

    printf("Nama Ibu         : %s\n", anak.Ibu->nama);
    printf("Nama Panggilan   : %s\n", anak.Ibu->nama_panggilan);
    printf("Usia Ibu         : %u\n", anak.Ibu->usia);
    printf("Usia Ibu (bit)   : "); displayBits(anak.Ibu->usia);
    printf("Makanan Favorit  : %s\n\n", namaMakanan[ibu.makanan]);

    printf("Usia Ayah AND Usia Ibu\n");
    displayBits(anak.Ayah->usia & anak.Ibu->usia);printf("\n");
    printf("Usia Ayah OR Usia Ibu\n");
    displayBits(anak.Ayah->usia | anak.Ibu->usia);printf("\n");
    printf("Usia Ayah XOR Usia Ibu\n");
    displayBits(anak.Ayah->usia ^ anak.Ibu->usia);printf("\n");
}

void displayBits(unsigned int value)
{
    // declare displayMask and left shift 31 bits
    unsigned int displayMask = 1 << 31;

    printf("", value);

    // loop through bits
    for (unsigned int c = 1; c <= 32; ++c)
    {
        putchar(value & displayMask ? '1' : '0');
        value <<= 1; //shift value left by 1

        if (c % 8 == 0)
        {
            putchar(' ');
        }
    }

    putchar('\n');
}
