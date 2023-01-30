#include <stdio.h>

#include <stdlib.h>

#include<time.h>

#include<locale.h>

#include<windows.h>

typedef struct Ogrenci {
    char ogrID[9];
    char ad[30];
    char soyad[30];
    int puan;
    struct Ogrenci * next;
    struct Ogrenci * prev;
}
OGRENCI;
typedef struct Yazar {
    int yazarID;
    char yazarAd[30];
    char yazarSoyad[30];
    struct Yazar * next;
}
YAZAR;
typedef struct KitapOrnek {
    char EtiketNo[20];
    char Durum[9];
    struct KitapOrnek * next;
}
KITAPORNEK;
typedef struct Kitap {
    char kitapAdi[30];
    char ISBN[14];
    int adet;
    struct Kitap * next;
    struct KitapOrnek * head;
}
KITAP;
typedef struct KitapYazar {
    char ISBN[14];
    int YazarID;
}
KITAPYAZAR;
typedef struct Tarih {
    unsigned int gun: 5;
    unsigned int ay: 4;
    unsigned int yil: 12;
}
TARIH;
typedef struct KitapOdunc {
    char EtiketNo[20];
    char ogrID[9];
    unsigned int islemTipi: 1;
    struct Tarih islemTarihi;
}
KITAPODUNC;
int ikiTarihArasiFark(TARIH, TARIH);

//func pointer
YAZAR * yazarBul(YAZAR * head, char * veri, int( * f)(YAZAR * , char * )) {
    YAZAR * temp = head;
    while (temp != NULL) {
        if (f(temp, veri) == 1) {
            return temp;
        } else temp = temp -> next;
    }
    return NULL;
}
int yazarAdiControl(YAZAR * head, char * veri) {
    if (strcmp(head -> yazarAd, veri) == 0) {
        return 1;
    }
    return 0;
}
int yazarSoyadiControl(YAZAR * head, char * veri) {
    if (strcmp(head -> yazarSoyad, veri) == 0) {
        return 1;
    }
    return 0;
}

//func pointer
OGRENCI * ogrenciBul(OGRENCI * head, char * veri, int( * f)(OGRENCI * , char * )) {

    OGRENCI * temp = head;
    while (temp != NULL) {
        if (f(temp, veri) == 1) {
            return temp;
        } else temp = temp -> next;
    }
    return NULL;
}
int adControl(OGRENCI * head, char * veri) {
    if (strcmp(head -> ad, veri) == 0) {
        return 1;
    }
    return 0;
}
int soyadControl(OGRENCI * head, char * veri) {
    if (strcmp(head -> soyad, veri) == 0) {
        return 1;
    }
    return 0;
}
int idControl(OGRENCI * head, char * veri) {
    if (strcmp(head -> ogrID, veri) == 0) {
        return 1;
    }
    return 0;
}

//func pointer
KITAP * KitapBul(KITAP * head, char * veri, int( * f)(KITAP * , char * )) {
    KITAP * temp = head;
    while (temp != NULL) {
        if (f(temp, veri) == 1) {
            return temp;
        } else temp = temp -> next;
    }
    return NULL;
}
int kitapAdiControl(KITAP * head, char * veri) {
    if (strcmp(head -> kitapAdi, veri) == 0) {
        return 1;
    }
    return 0;
}
int kitapISBNControl(KITAP * head, char * veri) {
    if (strcmp(head -> ISBN, veri) == 0) {
        return 1;
    }
    return 0;
}

void ogrenciBilgi(OGRENCI * head, KITAPODUNC ** kitapOdunc, int kitapOduncSize) {
    char * veri;
    char ** arr;
    int i;
    arr = (char ** ) malloc(sizeof(char * ) * 2);
    arr[0] = malloc(sizeof(char) * strlen("Odunc Alma") + 1);
    arr[1] = malloc(sizeof(char) * strlen("Teslim Etme") + 1);
    strcpy(arr[0], "Odunc Alma");
    strcpy(arr[1], "Teslim Etme");

    OGRENCI * ogrenci;
    printf("Isme gore arama icin 1'e basiniz, Soyisime gore arama icin 2'ye basiniz, ID'ye gore arama icin 3'e basiniz,Isim soyisim ile aramak icin 4 e basiniz: ");
    int secim;
    char *veri2;
    int control=1;
    scanf("%d", & secim);
    switch (secim) {
    case 1:
        printf("Aranacak ogrencinin adini giriniz: ");
        veri = (char * ) malloc(sizeof(char) * 31);
        scanf("%30s", veri);
        ogrenci = ogrenciBul(head, veri, adControl);
        break;
    case 2:
        printf("Aranacak ogrencinin soyadini giriniz: ");
        veri = (char * ) malloc(sizeof(char) * 31);
        scanf("%30s", veri);
        ogrenci = ogrenciBul(head, veri, soyadControl);
        break;
    case 3:
        printf("Aranacak ogrencinin ID'sini giriniz: ");
        veri = (char * ) malloc(sizeof(char) * 9);
        scanf("%8s", veri);
        ogrenci = ogrenciBul(head, veri, idControl);

        break;
    case 4:
        printf("Aranacak ogrencinin adini giriniz: ");
        veri = (char * ) malloc(sizeof(char) * 31);
        scanf("%30s", veri);
        printf("Silinecek ogrencinin soyadini giriniz: ");
        veri2 = (char * ) malloc(sizeof(char) * 31);
        scanf("%30s", veri2);
        ogrenci=head;
        while(ogrenci!=NULL&&control==1){
            if(strcmp(ogrenci->ad,veri)==0 && strcmp(ogrenci->soyad,veri2)==0){
                control=0;
            }
            else ogrenci=ogrenci->next;
        }
        if(control==1) printf("Aradiginiz ogrenci bulunamadi.");
        break;
    default:
        printf("Hatali secim yaptiniz.");
        break;
    }
    if (ogrenci != NULL) {
        printf("Ogrencinin ID'si: %s\n", ogrenci -> ogrID);
        printf("Ogrencinin Adi: %s\n", ogrenci -> ad);
        printf("Ogrencinin Soyadi: %s\n", ogrenci -> soyad);
        printf("Ogrencinin Puani: %d\n", ogrenci -> puan);
        printf("Ogrencinin kitap hareketleri: \n");
        for (i = 0; i < kitapOduncSize; i++) {

            if (strcmp(ogrenci -> ogrID, kitapOdunc[i] -> ogrID) == 0) {
                printf("Etiket %s---", kitapOdunc[i] -> EtiketNo);
                printf("%s Islemi---", arr[kitapOdunc[i] -> islemTipi]);
                printf("Kitap Odunc Islem Tarihi: %d/%d/%d\n", kitapOdunc[i] -> islemTarihi.gun, kitapOdunc[i] -> islemTarihi.ay, kitapOdunc[i] -> islemTarihi.yil);
            }
        }

    } else {
        printf("Aradiginiz ogrenci bulunamadi.");
    }

}

void ogrenciEkle(OGRENCI ** head) {
    OGRENCI * tmp = * head;
    OGRENCI * eklenecekOgrenci = (OGRENCI * ) malloc(sizeof(OGRENCI));
    if (eklenecekOgrenci == NULL) printf("Can't allocate memory\n");
    else {

        printf("Ogrencinin ID'si: ");
        scanf("%8s", eklenecekOgrenci -> ogrID);
        printf("Ogrencinin Adi: ");
        scanf("%30s", eklenecekOgrenci -> ad);
        printf("Ogrencinin Soyadi: ");
        scanf("%30s", eklenecekOgrenci -> soyad);
        printf("Ogrencinin Puani: ");
        scanf("%d", & eklenecekOgrenci -> puan);
        if ( * head == NULL) {
            * head = eklenecekOgrenci;
            eklenecekOgrenci -> next = NULL;
            eklenecekOgrenci -> prev = NULL;
        } else {
            while (tmp -> next != NULL) {
                tmp = tmp -> next;
            }
            tmp -> next = eklenecekOgrenci;
            eklenecekOgrenci -> prev = tmp;
            eklenecekOgrenci -> next = NULL;
        }

        printf("Ogrenci Ekleme Islemi Basariyla sonuclandi");
    }

}
void ogrenciSil(OGRENCI ** head) {
    char * veri;
    char* veri2;
    OGRENCI * silinecekOgr;
    printf("Isme gore arama icin 1'e basiniz, Soyisime gore arama icin 2'ye basiniz, ID'ye gore arama icin 3'e basiniz:, Isim Soyisim ile aramak icin 4'e basiniz: ");
    int secim;
    int control=1;
    scanf("%d", & secim);
    switch (secim) {
    case 1:
        printf("Silinecek ogrencinin adini giriniz: ");
        veri = (char * ) malloc(sizeof(char) * 31);
        scanf("%30s", veri);
        printf("ad: %s", veri);
        silinecekOgr = ogrenciBul( * head, veri, adControl);
        break;
    case 2:
        printf("Silinecek ogrencinin soyadini giriniz: ");
        veri = (char * ) malloc(sizeof(char) * 31);
        scanf("%30s", veri);
        silinecekOgr = ogrenciBul( * head, veri, soyadControl);
        break;
    case 3:
        printf("Silinecek ogrencinin ID'sini giriniz: ");
        veri = (char * ) malloc(sizeof(char) * 9);
        scanf("%8s", veri);
        silinecekOgr = ogrenciBul( * head, veri, idControl);
        break;
    case 4:
        printf("Silinecek ogrencinin adini giriniz: ");
        veri = (char * ) malloc(sizeof(char) * 31);
        scanf("%30s", veri);
        printf("Silinecek ogrencinin soyadini giriniz: ");
        veri2 = (char * ) malloc(sizeof(char) * 31);
        scanf("%30s", veri2);
        silinecekOgr=*head;
        while(silinecekOgr!=NULL&&control==1){
            if(strcmp(silinecekOgr->ad,veri)==0 && strcmp(silinecekOgr->soyad,veri2)==0){
                control=0;
            }
            else silinecekOgr=silinecekOgr->next;
        }
        if(control==1) printf("Aradiginiz ogrenci bulunamadi.");
        break;
        
    default:
        printf("Hatali secim yaptiniz.");
        break;
    }
    if (silinecekOgr -> next == NULL && silinecekOgr -> prev == NULL) {
        * head = NULL;
        free(silinecekOgr);

    } else if (silinecekOgr -> next == NULL) {
        silinecekOgr -> prev -> next = NULL;
        free(silinecekOgr);

    } else if (silinecekOgr -> prev == NULL) {
        silinecekOgr -> next -> prev = NULL;
        * head = silinecekOgr -> next;
        free(silinecekOgr);

    } else {
        silinecekOgr -> prev -> next = silinecekOgr -> next;
        silinecekOgr -> next -> prev = silinecekOgr -> prev;
        free(silinecekOgr);
    }
    printf("Ogrenci Silme Islemi Basariyla sonuclandi");

}
void ogrenciGuncelle(OGRENCI ** head) {

    printf("Ogrenciyi id ile arayip guncellemek icin 1'e basiniz, ad ile arayip guncellemek icin 2'ye basiniz, soyad ile arayip guncellemek icin 3'e basiniz: ");
    int secim;
    scanf("%d", & secim);
    char * veri;
    OGRENCI * guncellenecekOgr;
    switch (secim) {
    case 1:
        veri = (char * ) malloc(sizeof(char) * 9);
        printf("Guncellenecek Ogrencinin ID'si: ");
        scanf("%8s", veri);
        guncellenecekOgr = ogrenciBul( * head, veri, idControl);
        break;
    case 2:
        veri = (char * ) malloc(sizeof(char) * 31);
        printf("Guncellenecek Ogrencinin Adi: ");
        scanf("%30s", veri);
        guncellenecekOgr = ogrenciBul( * head, veri, adControl);
        break;
    case 3:
        veri = (char * ) malloc(sizeof(char) * 31);
        printf("Guncellenecek Ogrencinin Soyadi: ");
        scanf("%30s", veri);
        guncellenecekOgr = ogrenciBul( * head, veri, soyadControl);
        break;
    default:
        printf("Yanlis secim yaptiniz.");
        break;
    }

    if (guncellenecekOgr != NULL) {

        printf("Ogrencinin hangi bilgisini guncellemek istiyorsunuz?\n1-Ad\n2-Soyad\n3-Puan\n");
        int secim;
        scanf("%d", & secim);
        switch (secim) {
        case 1:
            printf("Ogrencinin yeni adi: ");
            scanf("%30s", guncellenecekOgr -> ad);
            printf("Guncelleme basariyla yapildi.");
            break;
        case 2:
            printf("Ogrencinin yeni soyadi: ");
            scanf("%30s", guncellenecekOgr -> soyad);
            printf("Guncelleme basariyla yapildi.");
            break;
        case 3:
            printf("Ogrencinin yeni puani: ");
            scanf("%d", & guncellenecekOgr -> puan);
            printf("Guncelleme basariyla yapildi.");
            break;
        default:
            printf("Yanlis secim yaptiniz.");
            break;
        }
        

    } else {
        printf("Ogrenci bulunamadi");
    }

}
void ogrenciListele(OGRENCI * head) {
    OGRENCI * tmp = head;
    while (tmp != NULL) {
        printf("%s,%s,%s,%d\n", tmp -> ogrID, tmp -> ad, tmp -> soyad, tmp -> puan);
        tmp = tmp -> next;
    }
}
OGRENCI * initializeOgrenci() {
    FILE * fp = fopen("Ogrenciler.csv", "r");
    OGRENCI * head = NULL;
    if (fp == NULL) printf("Can't open file\n");
    else {
        do {

            OGRENCI * yeni = (OGRENCI * ) malloc(sizeof(OGRENCI));
            if (yeni == NULL) printf("Can't allocate memory21\n");
            fscanf(fp, "%8[^,],%30[^,],%30[^,],%d\n", yeni -> ogrID, yeni -> ad, yeni -> soyad, & yeni -> puan);

            if (head == NULL) {
                head = yeni;
                head -> next = NULL;
                head -> prev = NULL;
            } else {
                OGRENCI * tmp = head;
                while (tmp -> next != NULL) {
                    tmp = tmp -> next;
                }
                tmp -> next = yeni;
                yeni -> prev = tmp;
                yeni -> next = NULL;
            }

        } while (!feof(fp));
        fclose(fp);

    }
    return head;
}
YAZAR * initializeYazar(int * yazarSayisi) {
    FILE * fp = fopen("Yazarlar.csv", "r");
    YAZAR * head = NULL;
    if (fp == NULL) printf("Can't open file\n");
    else {
        do {
            YAZAR * yeni = (YAZAR * ) malloc(sizeof(YAZAR));
            if (yeni == NULL) printf("Can't allocate memory\n");
            fscanf(fp, "%d,%30[^,],%30[^\n]\n", & yeni -> yazarID, yeni -> yazarAd, yeni -> yazarSoyad);

            * yazarSayisi = yeni -> yazarID;
            if (head == NULL) {
                head = yeni;
                head -> next = NULL;
            } else {
                YAZAR * tmp = head;
                while (tmp -> next != NULL) {
                    tmp = tmp -> next;
                }
                tmp -> next = yeni;
                yeni -> next = NULL;
            }

        } while (!feof(fp));
        fclose(fp);

    }
    return head;

}
KITAP * initializeKitap() {
    FILE * fp = fopen("Kitaplar.csv", "r");
    KITAP * head = NULL;

    int i;
    if (fp == NULL) printf("Can't open file\n");
    else {
        do {
            KITAPORNEK * headOrnek = NULL;

            KITAP * yeni = (KITAP * ) malloc(sizeof(KITAP));
            if (yeni == NULL) printf("Can't allocate memory80\n");

            fscanf(fp, "%30[^,], %13[^,], %d\n", yeni -> kitapAdi, yeni -> ISBN, & yeni -> adet);

            for (i = 1; i <= yeni -> adet; i++) {
                KITAPORNEK * yeniOrnek = (KITAPORNEK * ) malloc(sizeof(KITAPORNEK));
                if (yeniOrnek == NULL) printf("Can't allocate memory88\n");

                sprintf(yeniOrnek -> EtiketNo, "%s_%d", yeni -> ISBN, i);
                strcpy(yeniOrnek -> Durum, "Rafta");

                if (headOrnek == NULL) {
                    headOrnek = yeniOrnek;
                    headOrnek -> next = NULL;
                } else {
                    KITAPORNEK * tmp = headOrnek;
                    while (tmp -> next != NULL) {
                        tmp = tmp -> next;
                    }
                    tmp -> next = yeniOrnek;
                    yeniOrnek -> next = NULL;
                }

            }

            yeni -> head = headOrnek;

            if (head == NULL) {
                head = yeni;
                head -> next = NULL;
            } else {
                KITAP * tmp = head;
                while (tmp -> next != NULL) {
                    tmp = tmp -> next;
                }
                tmp -> next = yeni;
                yeni -> next = NULL;
            }

        } while (!feof(fp));
        fclose(fp);

    }

    return head;
}
KITAPYAZAR * initializeKitapYazar(int * size) {

    FILE * fp = fopen("KitapYazar.csv", "r");
    KITAPYAZAR * array = NULL;
    * size = 0;
    if (fp == NULL) printf("Can't open file\n");
    else {
        do {
            array = (KITAPYAZAR * ) realloc(array, (( * size) + 1) * sizeof(KITAPYAZAR));
            if (array == NULL) printf("Can't allocate memory\n");
            fscanf(fp, "%30[^,],%d\n", array[( * size)].ISBN, & array[( * size)].YazarID);
            ( * size) ++;
        } while (!feof(fp));
        fclose(fp);

    }
    return array;

}
void writeLinkedlistsToFiles(OGRENCI * headOgrenci, KITAP * headKitap, YAZAR * headYazar, KITAPYAZAR * arrayKitapYazar, int sizeofArray, int sizeOduncKitap, KITAPODUNC ** oduncKitap) {
    FILE * fp = fopen("Ogrenciler.csv", "w");
    if (fp == NULL) printf("Can't open file\n");
    else {
        OGRENCI * temp = headOgrenci;
        while (temp != NULL) {
            fprintf(fp, "%s,%s,%s,%d\n", temp -> ogrID, temp -> ad, temp -> soyad, temp -> puan);
            temp = temp -> next;
        }
        fclose(fp);
    }
    fp = fopen("Kitaplar.csv", "w");
    if (fp == NULL) printf("Can't open file\n");
    else {
        KITAP * temp = headKitap;
        while (temp != NULL) {
            fprintf(fp, "%s,%s,%d\n", temp -> kitapAdi, temp -> ISBN, temp -> adet);
            temp = temp -> next;
        }
        fclose(fp);
    }
    fp = fopen("Yazarlar.csv", "w");
    if (fp == NULL) printf("Can't open file\n");
    else {
        YAZAR * temp = headYazar;
        while (temp != NULL) {
            fprintf(fp, "%d,%s,%s\n", temp -> yazarID, temp -> yazarAd, temp -> yazarSoyad);
            temp = temp -> next;
        }
        fclose(fp);
    }
    fp = fopen("KitapYazar.csv", "w");
    if (fp == NULL) printf("Can't open file\n");
    else {
        int i;
        for (i = 0; i < sizeofArray; i++) {
            fprintf(fp, "%s,%d\n", arrayKitapYazar[i].ISBN, arrayKitapYazar[i].YazarID);
        }
        fclose(fp);
    }

    fp = fopen("KitapOdunc.csv", "w");
    if (fp == NULL) printf("Can't open file\n");
    else {
        int i;
        for (i = 0; i < sizeOduncKitap; i++) {
            fprintf(fp, "%s,%s,%d,%d.%d.%d\n", oduncKitap[i] -> EtiketNo, oduncKitap[i] -> ogrID, oduncKitap[i] -> islemTipi, oduncKitap[i] -> islemTarihi.gun, oduncKitap[i] -> islemTarihi.ay, oduncKitap[i] -> islemTarihi.yil);
        }
        fclose(fp);
    }
}
void kitapEkle(KITAP ** headKitap, KITAPYAZAR ** arrayKitapYazar, int * sizeofArray) {
    KITAP * yeni = (KITAP * ) malloc(sizeof(KITAP));
    if (yeni == NULL) printf("Can't allocate memory\n");
    printf("Kitap adi giriniz:");

    scanf("%*c");
    scanf("%30[^\n]", yeni -> kitapAdi);
    printf("ISBN giriniz:");
    scanf("%*c");
    scanf("%14[^\n]", yeni -> ISBN);
    printf("Adet giriniz:");
    scanf("%d", & yeni -> adet);

    KITAPORNEK * headOrnek = NULL;
    int i;
    for (i = 1; i <= yeni -> adet; i++) {
        KITAPORNEK * yeniOrnek = (KITAPORNEK * ) malloc(sizeof(KITAPORNEK));
        if (yeniOrnek == NULL) printf("Can't allocate memory88\n");

        sprintf(yeniOrnek -> EtiketNo, "%s_%d", yeni -> ISBN, i);
        strcpy(yeniOrnek -> Durum, "Rafta");

        if (headOrnek == NULL) {
            headOrnek = yeniOrnek;
            headOrnek -> next = NULL;
        } else {
            KITAPORNEK * tmp = headOrnek;
            while (tmp -> next != NULL) {
                tmp = tmp -> next;
            }
            tmp -> next = yeniOrnek;
            yeniOrnek -> next = NULL;
        }

    }
    yeni -> head = headOrnek;

    if ( * headKitap == NULL) {
        * headKitap = yeni;
        ( * headKitap) -> next = NULL;
    } else {
        KITAP * tmp = * headKitap;
        while (tmp -> next != NULL) {
            tmp = tmp -> next;
        }
        tmp -> next = yeni;
        yeni -> next = NULL;
    }

}
void kitapSil(KITAP ** headKitap, KITAPYAZAR ** arrayKitapYazar, int * sizeofArray) {
    KITAP * temp = * headKitap;
    KITAP * prev = NULL;
    KITAPORNEK* TMPORNEK;
    char ISBN[20];
    printf("Silmek istediginiz kitabin ISBN numarasini giriniz: ");
    scanf("%s", ISBN);
    int control = 0;
    int mainControl = 0;
    while (temp != NULL && control == 0&& mainControl == 0) {
        if (strcmp(temp -> ISBN, ISBN) == 0) {

            control = 1;
            TMPORNEK = temp -> head;
            while (TMPORNEK != NULL&&mainControl == 0) {
                if (strcmp(TMPORNEK -> Durum, "Rafta") != 0) {
                    mainControl = 1;
                    printf("Bu kitap silinemez, %s tarafindan odunc alinmis.\n",TMPORNEK -> Durum);
                    
                }
                TMPORNEK = TMPORNEK -> next;
            }
            if (mainControl == 0) {
            
                if (prev == NULL) {
                    * headKitap = temp -> next;
                    free(temp);

                } else {
                    prev -> next = temp -> next;
                    free(temp);
                }
            }
        }
        prev = temp;
        temp = temp -> next;
    }
    if (control == 0) {
        printf("Kitap bulunamadi\n");

    } else if(mainControl==0) {
        int i;
        for (i = 0; i < ( * sizeofArray); i++) {
            if (strcmp(( * arrayKitapYazar)[i].ISBN, ISBN) == 0) {
                ( * arrayKitapYazar)[i].YazarID = -1;

            }
        }

        printf("Kitap silindi\n");
    }

}
void kitapGuncelle(KITAP ** headKitap, KITAPYAZAR ** arrayKitapYazar, int * sizeofArray) {
    KITAP * temp = * headKitap;
    char ISBN[20];
    printf("Guncellemek istediginiz kitabin ISBN numarasini giriniz: ");
    scanf("%s", ISBN);
    int control = 0;
    char * kitapAdi;
    kitapAdi = (char * ) malloc(sizeof(char) * 30);
    while (control == 0) {
        if (temp == NULL) {
            printf("Kitap bulunamadi. Tekrar deneyiniz.\n");
            printf("Guncellemek istediginiz kitabin ISBN numarasini giriniz: ");
            scanf("%s", ISBN);
        } else if (strcmp(temp -> ISBN, ISBN) == 0) {
            printf("Kitap adi giriniz: ");
            scanf("%*c");
            scanf("%30[^\n]", kitapAdi);
            strcpy(temp -> kitapAdi, kitapAdi);
            control = 1;
        }

        temp = temp -> next;
    }
}
void kitapBilgisiGoruntule(KITAP * headKitap, KITAPYAZAR * arrayKitapYazar, int sizeofArray, YAZAR * headYazar) {
    KITAP * temp;
    YAZAR * tempYazar;
    KITAPORNEK * headornek;
    int control;
    printf("Kitabin ISBN numarasini girmek icin 1'e basiniz, kitabin adini girmek icin 2'ye basiniz: ");
    int secim;
    scanf("%d", & secim);
    char * veri;
    switch (secim) {
    case 1:
        veri = (char * ) malloc(sizeof(char) * 14);
        printf("Goruntulemek istediginiz kitabin ISBN numarasini giriniz: ");
        scanf("%s", veri);
        temp = KitapBul(headKitap, veri, kitapISBNControl);
        break;
    case 2:
        veri = (char * ) malloc(sizeof(char) * 30);
        printf("Goruntulemek istediginiz kitabin adini giriniz: ");
        scanf("%*c");
        scanf("%30[^\n]", veri);
        temp = KitapBul(headKitap, veri, kitapAdiControl);
        break;
    default:
        printf("Hatali secim\n");
        break;
    }

    if (temp != NULL) {
        printf("Kitap adi: %s\n", temp -> kitapAdi);
        printf("ISBN numarasi: %s\n", temp -> ISBN);
        printf("Kitap adedi: %d\n", temp -> adet);
        printf("Kitap yazarlari: ");
        int i;
        for (i = 0; i < sizeofArray; i++) {
            if (strcmp(arrayKitapYazar[i].ISBN, temp -> ISBN) == 0) {
                control = 0;
                tempYazar = headYazar;
                while (tempYazar != NULL && control == 0) {
                    if ((tempYazar -> yazarID == arrayKitapYazar[i].YazarID)) {
                        printf("%s %s, ", tempYazar -> yazarAd, tempYazar -> yazarSoyad);
                        control = 1;
                    } else {
                        tempYazar = tempYazar -> next;
                    }
                }
            }
        }
        printf("\n");

        printf("Kitap orneklerinin sahiplik bilgileri\n");
        headornek = temp -> head;
        for (i = 0; i < temp -> adet; i++) {
            printf("%s %s\n", headornek -> EtiketNo, headornek -> Durum);
            headornek = headornek -> next;

        }
    } else {
        printf("Kitap bulunamadi\n");
    }

}
void kitapOduncAl(OGRENCI * headOgrenci, KITAP * headKitap, KITAPYAZAR * arrayKitapYazar, int sizeOfArrayKitapYazar, int * sizeOfArrayOduncKitap, KITAPODUNC ** * arrayOduncKitap) {

    int gun, ay, yil;
    KITAPODUNC * tempOduncKitap = (KITAPODUNC * ) malloc(sizeof(KITAPODUNC));
    if (tempOduncKitap == NULL) printf("Can't allocate memory\n");
    KITAP * tempKitap = headKitap;
    OGRENCI * tempOgrenci = headOgrenci;
    TARIH * tempTarih = (TARIH * ) malloc(sizeof(TARIH));
    if (tempTarih == NULL) printf("Can't allocate memory\n");

    printf("Lutfen ogrID giriniz");
    char ogrID[9];
    scanf("%s", ogrID);
    int control = 1;
    while (tempOgrenci != NULL && control == 1) {
        if (strcmp(tempOgrenci -> ogrID, ogrID) == 0) {

            control = 0;
        } else {
            tempOgrenci = tempOgrenci -> next;

        }
    }

    if (control == 1) {
        printf("Ogrenci bulunamadi. Tekrar deneyiniz.\n");
    } else {

        if (tempOgrenci -> puan < 0) {
            printf("Cezali ogrenciler kitap odunc alamaz\n");

        } else {
            printf("Odunc almak istediginiz kitabin ISBN numarasini giriniz: ");
            char ISBN[20];
            scanf("%s", ISBN);
            while (control == 0 && tempKitap != NULL) {

                if (strcmp(tempKitap -> ISBN, ISBN) == 0) {
                    KITAPORNEK * tmpKitapOrnek = tempKitap -> head;
                    while (tmpKitapOrnek != NULL && control == 0) {

                        if (strcmp(tmpKitapOrnek -> Durum, "Rafta") == 0) {
                            strcpy(tmpKitapOrnek -> Durum, ogrID);

                            TARIH * teslimAlinmaTarih = (TARIH * ) malloc(sizeof(TARIH));
                            printf("Teslim alinma gununu giriniz");
                            scanf("%d", & gun);
                            printf("Teslim alinma ayini giriniz");
                            scanf("%d", & ay);
                            printf("Teslim alinma yilini giriniz");
                            scanf("%d", & yil);
                            teslimAlinmaTarih -> gun = gun;
                            teslimAlinmaTarih -> ay = ay;
                            teslimAlinmaTarih -> yil = yil;
                            tempOduncKitap -> islemTarihi = * teslimAlinmaTarih;
                            tempOduncKitap -> islemTipi = 0;
                            strcpy(tempOduncKitap -> ogrID, ogrID);
                            strcpy(tempOduncKitap -> EtiketNo, tmpKitapOrnek -> EtiketNo);

                            ( * arrayOduncKitap) = (KITAPODUNC ** ) realloc(( * arrayOduncKitap), (( * sizeOfArrayOduncKitap) + 1) * sizeof(KITAPODUNC * ));
                            if (( * arrayOduncKitap) == NULL) printf("Can't allocate memory\n");
                            ( * arrayOduncKitap)[( * sizeOfArrayOduncKitap)] = tempOduncKitap;
                            ( * sizeOfArrayOduncKitap) ++;

                            printf("Kitap odunc alindi\n");
                            control = 1;
                        } else {

                            tmpKitapOrnek = tmpKitapOrnek -> next;

                        }
                    }
                    if (control == 0) {
                        printf("Kitaplarin hepsi odunc alinmis\n");
                    }
                }
                tempKitap = tempKitap -> next;

            }
            if (control == 0) {
                printf("Kitap bulunamadi. Tekrar deneyiniz.\n");
            }

        }
    }

}
void kitapTeslimEt(OGRENCI * headOgrenci, KITAP * headKitap, KITAPYAZAR * arrayKitapYazar, int sizeOfArrayKitapYazar, int * sizeOfArrayOduncKitap, KITAPODUNC ** * arrayOduncKitap) {

    char * etiketToedit;
    int gun, ay, yil;
    KITAPODUNC * tempOduncKitap = (KITAPODUNC * ) malloc(sizeof(KITAPODUNC));
    if (tempOduncKitap == NULL) printf("Can't allocate memory\n");
    KITAP * tempKitap = headKitap;
    OGRENCI * tempOgrenci = headOgrenci;
    TARIH * tempTarih = (TARIH * ) malloc(sizeof(TARIH));
    if (tempTarih == NULL) printf("Can't allocate memory\n");

    printf("Lutfen ogrID giriniz");
    char ogrID[9];
    scanf("%s", ogrID);
    KITAPORNEK * tempKitapOrnek;
    char * currISBN;
    int maincontrol = 0;
    int control = 0;

    while (tempOgrenci != NULL && control == 0) {
        if (strcmp(tempOgrenci -> ogrID, ogrID) == 0) {
            control = 1;
        } else tempOgrenci = tempOgrenci -> next;
    }
    if (control == 0) {
        printf("Ogrenci bulunamadi\n");
    } else {
        printf("Teslim etmek istediginiz kitabin ISBN numarasini giriniz: ");

        char ISBN[20];
        scanf("%s", ISBN);

        KITAPODUNC * currrecord;
        int i;
        int j;
        KITAPODUNC * newrecord;
        for (i = 0; i < ( * sizeOfArrayOduncKitap); i++) {
            currrecord = ( * arrayOduncKitap)[i];
            control = 0;
            if (currrecord -> islemTipi == 0) {
                for (j = 0; j < ( * sizeOfArrayOduncKitap); j++) {
                    newrecord = ( * arrayOduncKitap)[j];
                    if (newrecord -> islemTipi == 1 && strcmp(currrecord -> ogrID, newrecord -> ogrID) == 0 && strcmp(currrecord -> EtiketNo, newrecord -> EtiketNo) == 0) {
                        control = 1;
                    }
                }

                if (control == 0) {
                    if (strcmp(currrecord -> ogrID, ogrID) == 0) {
                        etiketToedit = (char * ) malloc(sizeof(char) * 20);
                        strcpy(etiketToedit, (( * arrayOduncKitap)[i] -> EtiketNo));
                        currISBN = strtok(etiketToedit, "_");
                        if (strcmp(currISBN, ISBN) == 0) {
                            maincontrol = 1;
                        }
                    }

                }
            }

        }
        if (maincontrol == 0) {
            printf("Ogrenci bu kitabi odunc almamis\n");
        } else {

            control = 0;
            int i = 0;

            while (control == 0 && i < ( * sizeOfArrayOduncKitap)) {

                etiketToedit = (char * ) malloc(sizeof(char) * 20);
                strcpy(etiketToedit, (( * arrayOduncKitap)[i] -> EtiketNo));

                currISBN = strtok(etiketToedit, "_");

                if (strcmp(( * arrayOduncKitap)[i] -> ogrID, ogrID) == 0 && strcmp(currISBN, ISBN) == 0 && ((( * arrayOduncKitap)[i] -> islemTipi) == 0)) {

                    while (tempKitap != NULL && control == 0) {
                        if (strcmp(tempKitap -> ISBN, ISBN) == 0) {
                            tempKitapOrnek = tempKitap -> head;
                            control = 1;
                        } else {
                            tempKitap = tempKitap -> next;
                        }
                    }

                    control = 0;
                    while (tempKitapOrnek != NULL && control == 0) {
                        if (strcmp(tempKitapOrnek -> EtiketNo, (( * arrayOduncKitap)[i] -> EtiketNo)) == 0) {
                            strcpy(tempKitapOrnek -> Durum, "Rafta");
                            control = 1;
                        }
                        tempKitapOrnek = tempKitapOrnek -> next;

                    }

                    control = 0;

                    TARIH * teslimAlinmaTarih = (TARIH * ) malloc(sizeof(TARIH));
                    printf("Teslim edilme gununu giriniz");
                    scanf("%d", & gun);
                    printf("Teslim edilme ayini giriniz");
                    scanf("%d", & ay);
                    printf("Teslim edilme yilini giriniz");
                    scanf("%d", & yil);
                    teslimAlinmaTarih -> gun = gun;
                    teslimAlinmaTarih -> ay = ay;
                    teslimAlinmaTarih -> yil = yil;

                    ( * arrayOduncKitap) = (KITAPODUNC ** ) realloc(( * arrayOduncKitap), (( * sizeOfArrayOduncKitap) + 1) * sizeof(KITAPODUNC * ));
                    if (( * arrayOduncKitap) == NULL) printf("Can't allocate memory\n");
                    ( * arrayOduncKitap)[( * sizeOfArrayOduncKitap)] = tempOduncKitap;

                    strcpy(( * arrayOduncKitap)[( * sizeOfArrayOduncKitap)] -> ogrID, ogrID);
                    strcpy(( * arrayOduncKitap)[( * sizeOfArrayOduncKitap)] -> EtiketNo, (( * arrayOduncKitap)[i] -> EtiketNo));

                    ( * arrayOduncKitap)[( * sizeOfArrayOduncKitap)] -> islemTipi = 1;
                    ( * arrayOduncKitap)[( * sizeOfArrayOduncKitap)] -> islemTarihi = * teslimAlinmaTarih;

                    ( * sizeOfArrayOduncKitap) ++;

                    control = 1;
                    if (ikiTarihArasiFark((( * arrayOduncKitap)[i] -> islemTarihi), ( * teslimAlinmaTarih)) >= 15) {
                        printf("Kitap teslim edilme tarihinden 15 gun gecmistir -10 puan, ceza uygulanacaktir\n");
                        tempOgrenci -> puan -= 10;
                    } else {
                        printf("Zamaninda teslim ettiğiniz için teşekkür ederiz\n");

                    }

                    printf("Tebrikler! kitap basariyla teslim edilmistir\n");
                }

                i++;
            }
            if (control == 0) {
                printf("Kitap odunc alinmamis\n");
            }

        }

    }

}
void teslimEtmemisOgrenciler(int sizeOfArrayOduncKitap, KITAPODUNC ** arrayOduncKitap) {
    int i;
    int control = 0;
    KITAPODUNC * currrecord;
    KITAPODUNC * newrecord;
    int j;
    printf("Teslim Etmeyen Ogrenci                                   Teslim edilmeyen Kitap\n");

    for (i = 0; i < sizeOfArrayOduncKitap; i++) {
        currrecord = arrayOduncKitap[i];
        control = 0;
        if (currrecord -> islemTipi == 0) {
            for (j = 0; j < sizeOfArrayOduncKitap; j++) {
                newrecord = arrayOduncKitap[j];
                if (newrecord -> islemTipi == 1 && strcmp(currrecord -> ogrID, newrecord -> ogrID) == 0 && strcmp(currrecord -> EtiketNo, newrecord -> EtiketNo) == 0) {
                    control = 1;
                }
            }

            if (control == 0) {
                printf("%s                                                   %s\n", currrecord -> ogrID, currrecord -> EtiketNo);

            }
        }

    }
}
void cezaliOgrenciler(OGRENCI * head) {
    OGRENCI * currOgrenci = head;
    int control = 0;
    while (currOgrenci != NULL) {
        if (currOgrenci -> puan < 0) {
            printf("%s %s %s %d\n", currOgrenci -> ogrID, currOgrenci -> ad, currOgrenci -> soyad, currOgrenci -> puan);
            control = 1;
        }
        currOgrenci = currOgrenci -> next;
    }
    if (control == 0) {
        printf("Cezali ogrenci yok\n");
    }
}
void raftakiKitaplariListele(KITAP * headKitap) {
    KITAP * tmpkitap = headKitap;
    while (tmpkitap != NULL) {
        KITAPORNEK * tmpkitapornek = tmpkitap -> head;

        while (tmpkitapornek != NULL) {
            if (strcmp(tmpkitapornek -> Durum, "Rafta") == 0) {
                printf("%s\n", tmpkitapornek -> EtiketNo);
            }
            tmpkitapornek = tmpkitapornek -> next;
        }
        printf("\n");
        tmpkitap = tmpkitap -> next;
    }

}
void zamanindaTeslimEdilmeyenKitaplariListele(int sizeOfArrayOduncKitap, KITAPODUNC ** arrayOduncKitap) {
    int i;
    KITAPODUNC * currrecord;
    KITAPODUNC * newrecord;
    int j;

    for (i = 0; i < sizeOfArrayOduncKitap; i++) {
        currrecord = arrayOduncKitap[i];

        if (currrecord -> islemTipi == 0) {
            for (j = 0; j < sizeOfArrayOduncKitap; j++) {
                newrecord = arrayOduncKitap[j];
                if (newrecord -> islemTipi == 1 && strcmp(currrecord -> ogrID, newrecord -> ogrID) == 0 && strcmp(currrecord -> EtiketNo, newrecord -> EtiketNo) == 0) {
                    if (ikiTarihArasiFark(currrecord -> islemTarihi, newrecord -> islemTarihi) >= 15) {
                        printf("Ogrenci id: %s Kitap etiket no:%s\n\n", currrecord -> ogrID, currrecord -> EtiketNo);
                    }
                }
            }

        }

    }
}
int ikiTarihArasiFark(TARIH tarih1, TARIH tarih2) {
    int gun1, gun2, ay1, ay2, yil1, yil2;
    gun1 = tarih1.gun;
    gun2 = tarih2.gun;
    ay1 = tarih1.ay;
    ay2 = tarih2.ay;
    yil1 = tarih1.yil;
    yil2 = tarih2.yil;
    int fark = 0;
    fark = gun2 - gun1 + 30 * (ay2 - ay1) + 365 * (yil2 - yil1);
    return fark;
}
KITAPODUNC ** initializeOduncKitap(int * sizeOfArrayOduncKitap, KITAP * headKitap) {
    FILE * fp;
    fp = fopen("KitapOdunc.csv", "r");
    if (fp == NULL) {
        printf("Dosya acilamadi");
        exit(1);
    }
    
    char * currISBN;
    currISBN = (char * ) malloc(sizeof(char) * 20);
    int islemTipi, gun, ay, yil;
    KITAPODUNC ** arrayOduncKitap;
    arrayOduncKitap = (KITAPODUNC ** ) malloc(sizeof(KITAPODUNC * ));
    int i = 0;
    KITAP * tmpKitap = headKitap;
   
    do {
       
        tmpKitap = headKitap;
        arrayOduncKitap[i] = (KITAPODUNC * ) malloc(sizeof(KITAPODUNC));
     
        fscanf(fp, "%[^,],%[^,],%d,%d.%d.%d\n", arrayOduncKitap[i] -> EtiketNo, arrayOduncKitap[i] -> ogrID, & islemTipi, & gun, & ay, & yil);
   
        strcpy(currISBN, arrayOduncKitap[i] -> EtiketNo);
        currISBN = strtok(currISBN, "_");
    
        while (strcmp(currISBN, tmpKitap -> ISBN) != 0) {
        
            tmpKitap = tmpKitap -> next;
        }

        KITAPORNEK * tmpkitapornek = tmpKitap -> head;

        while (strcmp(tmpkitapornek -> EtiketNo, arrayOduncKitap[i] -> EtiketNo) != 0) {
            tmpkitapornek = tmpkitapornek -> next;
        }

        if (islemTipi == 1) {
            strcpy(tmpkitapornek -> Durum, "Rafta");

        } else if (islemTipi == 0) {
            strcpy(tmpkitapornek -> Durum, arrayOduncKitap[i] -> ogrID);
        }

        arrayOduncKitap[i] -> islemTarihi.gun = gun;
        arrayOduncKitap[i] -> islemTarihi.ay = ay;
        arrayOduncKitap[i] -> islemTarihi.yil = yil;
        arrayOduncKitap[i] -> islemTipi = islemTipi;
        i++;

        arrayOduncKitap = (KITAPODUNC ** ) realloc(arrayOduncKitap, sizeof(KITAPODUNC * ) * (i + 1));
         

    } while (!feof(fp));
    * sizeOfArrayOduncKitap = i;
    fclose(fp);
    return arrayOduncKitap;

}
void kitapYazarEslestir(KITAPYAZAR ** arrayKitapYazar, int * sizeOfArrayKitapYazar, KITAP * headKitap, YAZAR * headYazar, int * yazarCounter) {

    YAZAR * temp = headYazar;
    int flag = 0;
    printf("Eslestirmek istediginiz yazarin ID numarasini giriniz: ");
    int yazarID;
    scanf("%d", & yazarID);
    while (temp != NULL && flag == 0) {
        if (temp -> yazarID == yazarID) {

            flag=1;
        } else temp = temp -> next;
    }
    if (flag == 0) {
        printf("Yazar bulunamadi");
        return;
    }

    printf("Eslestirmek istediginiz kitabin ISBN numarasini giriniz: ");
    char * ISBN;
    ISBN = (char * ) malloc(sizeof(char) * 20);
    scanf("%s", ISBN);
    flag = 0;
    KITAP * temp2 = headKitap;
    while (temp2 != NULL && flag == 0) {
        if (strcmp(temp2 -> ISBN, ISBN) == 0) {
            flag = 1;

        } else temp2 = temp2 -> next;
    }
    if (flag == 0) {
        printf("Kitap bulunamadi");
        return;
    }

    int i;

    for (i = 0; i < * sizeOfArrayKitapYazar; i++) {
        if (strcmp(( * arrayKitapYazar)[i].ISBN, ISBN) == 0 && yazarID == ( * arrayKitapYazar)[i].YazarID) {
            printf("Bu kitap ve yazar zaten eslestirilmis");
            return;
        }
    }

    ( * arrayKitapYazar) = (KITAPYAZAR * ) realloc(( * arrayKitapYazar), sizeof(KITAPYAZAR) * ( * sizeOfArrayKitapYazar + 1));
    strcpy(( * arrayKitapYazar)[ * sizeOfArrayKitapYazar].ISBN, ISBN);
    ( * arrayKitapYazar)[ * sizeOfArrayKitapYazar].YazarID = yazarID;
    ( * sizeOfArrayKitapYazar) ++;
    printf("Eslestirme basarili");

}
void kitapYazarGuncelle(KITAPYAZAR ** arrayKitapYazar, int * sizeOfArrayKitapYazar, KITAP * headKitap, YAZAR * headYazar) {
    printf("Guncellemek istediginiz kitabin ISBN numarasini giriniz: ");
    char * ISBN;
    ISBN = (char * ) malloc(sizeof(char) * 20);
    scanf("%s", ISBN);
    int flag = 0;
    KITAP * temp2 = headKitap;
    while (temp2 != NULL && flag == 0) {
        if (strcmp(temp2 -> ISBN, ISBN) == 0) {
            flag = 1;

        } else temp2 = temp2 -> next;
    }
    if (flag == 0) {
        printf("Kitap bulunamadi");
        return;
    }
    printf("Degistirmek istediginiz yazarin idsini giriniz:");
    int yazarID;
    int yeniYazarID;
    scanf("%d", & yazarID);
    YAZAR * temp = headYazar;
    flag = 0;
    while (temp != NULL && flag == 0) {
        if (temp -> yazarID == yazarID) {
            flag = 1;

        } else temp = temp -> next;
    }
    if (flag == 0) {
        printf("Yazar bulunamadi");
        return;
    }
    int i;
    for (i = 0; i < * sizeOfArrayKitapYazar; i++) {
        if (strcmp(( * arrayKitapYazar)[i].ISBN, ISBN) == 0 && yazarID == ( * arrayKitapYazar)[i].YazarID) {
            printf("bu yazari hangi id'ye sahip yazarla degistirmek istiyorsunuz?");
            scanf("%d", & yeniYazarID);
            ( * arrayKitapYazar)[i].YazarID = yeniYazarID;
            printf("Guncelleme basarili");
        }
    }

}
void yazarEkle(YAZAR ** headYazar, int * yazarCounter) {
    YAZAR * temp = * headYazar;
    YAZAR * new = (YAZAR * ) malloc(sizeof(YAZAR));
    printf("Yazarin adini giriniz: ");
    scanf("%s", new -> yazarAd);
    printf("Yazarin soyadini giriniz: ");
    scanf("%s", new -> yazarSoyad);
    new -> yazarID = ( * yazarCounter) ++;
    new -> next = NULL;
    if (temp == NULL) {
        * headYazar = new;
        return;
    }
    while (temp -> next != NULL) {
        temp = temp -> next;
    }
    temp -> next = new;
    printf("Yazar ekleme basarili");
}
void yazarBilgisiGoruntule(YAZAR * headYazar, KITAPYAZAR * arrayKitapYazar, int sizeOfArrayKitapYazar, KITAP * headkitap) {
    printf("Yazarin adiyla islem yapmak icin 1, soyadiyal islem yapmak icin 2ye Ad ve Soyad ile islem yapmak icin 3 e basiniz");
    int secim;
    char * veri;
    char *veri2;
    YAZAR * temp;
    KITAP * tempkitap;
    int control=1;
    scanf("%d", & secim);
    switch (secim) {
    case 1:
        veri = (char * ) malloc(sizeof(char) * 20);
        printf("Yazarin adini giriniz: ");
        scanf("%s", veri);
        temp = yazarBul(headYazar, veri, yazarAdiControl);
        break;
    case 2:
        veri = (char * ) malloc(sizeof(char) * 20);
        printf("Yazarin soyadini giriniz: ");
        scanf("%s", veri);
        temp = yazarBul(headYazar, veri, yazarSoyadiControl);
        break;
    case 3:
        veri = (char * ) malloc(sizeof(char) * 20);
        veri2 = (char * ) malloc(sizeof(char) * 20);
        printf("Yazarin adini giriniz: ");
        scanf("%s", veri);
        printf("Yazarin soyadini giriniz: ");
        scanf("%s", veri2);
        temp=headYazar;
        while(temp!=NULL&&control==1){
            if(strcmp(temp->yazarAd,veri)==0 && strcmp(temp->yazarSoyad,veri2)==0){
                control=0;
            }
            else{
                temp=temp->next;    
            }
        }
        if(control==1){
            printf("Yazar bulunamadi");
            return;
        }

    default:
        printf("Hatali secim");
        return;
    }

    if (temp == NULL) {
        printf("Yazar bulunamadi");
        return;
    }

    printf("Yazarin adi: %s Yazarin soyadi: %s Yazarin ID numarasi: %d\n", temp -> yazarAd, temp -> yazarSoyad, temp -> yazarID);
    printf("Yazarin kitaplari\n\n");
    int i;
    for (i = 0; i < sizeOfArrayKitapYazar; i++) {
        if (arrayKitapYazar[i].YazarID == temp -> yazarID) {
            tempkitap = headkitap;
            while (tempkitap != NULL) {
                if (strcmp(arrayKitapYazar[i].ISBN, tempkitap -> ISBN) == 0) {
                    printf("Kitap Adi:%s, ISBN:%s\n", tempkitap -> kitapAdi, tempkitap -> ISBN);
                }

                tempkitap = tempkitap -> next;
            }

        }
    }

}
void yazarGuncelle(YAZAR ** headYazar) {
    YAZAR * temp = * headYazar;
    int flag = 0;
    printf("Guncellemek istediginiz yazarin ID numarasini giriniz: ");
    int yazarID;
    scanf("%d", & yazarID);
    while (temp != NULL && flag == 0) {
        if (temp -> yazarID == yazarID) {
            flag = 1;

        } else temp = temp -> next;
    }
    if (flag == 0) {
        printf("Yazar bulunamadi");
        return;
    }
    printf("Yazarin adini giriniz: ");
    scanf("%s", temp -> yazarAd);
    printf("Yazarin soyadini giriniz: ");
    scanf("%s", temp -> yazarSoyad);
    printf("Yazar guncelleme basarili");
}
void yazarSil(YAZAR ** headYazar, KITAPYAZAR ** arrayKitapYazar, int * sizeOfArrayKitapYazar) {
    YAZAR * temp = * headYazar;
    int flag = 0;
    printf("Silmek istediginiz yazarin ID numarasini giriniz: ");
    int yazarID;
    scanf("%d", & yazarID);
    if (temp -> yazarID == yazarID) {
        * headYazar = temp -> next;
        free(temp);
        printf("Yazar silme basarili");
    } else {
        while (temp != NULL && flag == 0) {
            if (temp -> next -> yazarID == yazarID) {
                flag = 1;

            } else temp = temp -> next;
        }
        if (flag == 0) {
            printf("Yazar bulunamadi");
            return;
        }
        free(temp -> next);

        temp -> next = temp -> next -> next;
        printf("Yazar silme basarili");

    }

    int i;
    for (i = 0; i < * sizeOfArrayKitapYazar; i++) {
        if (( * arrayKitapYazar)[i].YazarID == yazarID) {
            ( * arrayKitapYazar)[i].YazarID = -1;
        }

    }

}

void kitaplariYazdir(KITAP * head) {
    KITAP * tmp = head;
    while (tmp != NULL) {
        printf("%s,%s,%d\n", tmp -> kitapAdi, tmp -> ISBN, tmp -> adet);
        tmp = tmp -> next;
    }

}
void tumKitapOrnekleriniYazdir(KITAP * head) {
    KITAP * tmp = head;
    KITAPORNEK * tmp2;
    while (tmp != NULL) {
        tmp2 = tmp -> head;
        printf("Kitap: %s - %s\n\n", tmp -> kitapAdi, tmp -> ISBN);
        while (tmp2 != NULL) {
            printf("%s,%s\n", tmp2 -> EtiketNo, tmp2 -> Durum);
            tmp2 = tmp2 -> next;
        }
        printf("\n\n");
        tmp = tmp -> next;
    }

}

void yazarlariYazdir(YAZAR * head) {
    YAZAR * tmp = head;
    while (tmp != NULL) {
        printf("%d,%s,%s\n", tmp -> yazarID, tmp -> yazarAd, tmp -> yazarSoyad);
        tmp = tmp -> next;
    }

}
void kitapYazarlariYazdir(KITAPYAZAR * arrayKitapYazar, int sizeOfArrayKitapYazar) {
    int i;
    for (i = 0; i < sizeOfArrayKitapYazar; i++) {
        printf("%s,%d\n", arrayKitapYazar[i].ISBN, arrayKitapYazar[i].YazarID);
    }

}
void kitapOdunclariYazdir(KITAPODUNC ** arrayOduncKitap, int sizeOfArrayOduncKitap) {
    int i;
    for (i = 0; i < sizeOfArrayOduncKitap; i++) {
        printf("%s,%s,%d,%d.%d.%d\n", arrayOduncKitap[i] -> EtiketNo, arrayOduncKitap[i] -> ogrID, arrayOduncKitap[i] -> islemTipi, arrayOduncKitap[i] -> islemTarihi.gun, arrayOduncKitap[i] -> islemTarihi.ay, arrayOduncKitap[i] -> islemTarihi.yil);
    }
}
void freeKitap(KITAP * head) {
    KITAP * tmp = head;
    KITAP * tmp2;
    KITAPORNEK * tmp3;
    while (tmp != NULL) {
        tmp2 = tmp -> next;
        tmp3 = tmp -> head;
        while (tmp3 != NULL) {
            tmp -> head = tmp -> head -> next;
            free(tmp3);
            tmp3 = tmp -> head;
        }
        free(tmp);
        tmp = tmp2;
    }
}
void freeOgrenci(OGRENCI * head) {
    OGRENCI * tmp = head;
    OGRENCI * tmp2;
    while (tmp != NULL) {
        tmp2 = tmp -> next;
        free(tmp);
        tmp = tmp2;
    }
}
void freeYazar(YAZAR * head) {
    YAZAR * tmp = head;
    YAZAR * tmp2;
    while (tmp != NULL) {
        tmp2 = tmp -> next;
        free(tmp);
        tmp = tmp2;
    }

}
void freeKitapYazar(KITAPYAZAR * arrayKitapYazar, int sizeOfArrayKitapYazar) {
    free(arrayKitapYazar);
}

void freeKitapOdunc(KITAPODUNC ** arrayOduncKitap, int sizeOfArrayOduncKitap) {
    int i;
    for (i = 0; i < sizeOfArrayOduncKitap; i++) {
        free(arrayOduncKitap[i]);
    }
    free(arrayOduncKitap);

}
int main() {
    int tempChoice;
    int islem = 1;
    int sizeOfArrayKitapYazar = 0;

    KITAPODUNC ** arrayOduncKitap;

    int sizeOfArrayOduncKitap = 0;
    int yazarCounter;

    KITAP * headKitap = initializeKitap();
    OGRENCI * headOgrenci = initializeOgrenci();
    
    YAZAR * headYazar = initializeYazar( & yazarCounter);
    (yazarCounter) ++;
    KITAPYAZAR * arrayKitapYazar = initializeKitapYazar( & sizeOfArrayKitapYazar);
 
    arrayOduncKitap = initializeOduncKitap( & sizeOfArrayOduncKitap, headKitap);
  
    do {
        printf("\nOgrenci islemleri :1\nKitap islemleri: 2\nYazar islemleri:3\nGenel listeleme :4\nCikis:0\nInput: ");
        scanf("%d", & tempChoice);

        if(tempChoice==1)printf("OGRENCI ISLEMLERI\n\n1- Ogrenci Ekle\n2- Ogrenci Sil\n3- Ogrenci Guncelle\n4- Ogrenci Bilgisi Goruntule\n5- Kitap Teslim Etmemis Ogrencileri Listele\n6- Cezali Ogrencileri Listele\n7- Tum Ogrencileri Listele\n8- Kitap Odunc Al\n9- Kitap Teslim Et\nGeri:0\n");
        else if(tempChoice==2)printf("KITAP ISLEMLERI\n\n10- Kitap Ekle\n11- Kitap Sil\n12- Kitap Guncelle\n13- Kitap Bilgisi Goruntule\n14- Raftaki Kitaplari Listele\n15- Zamaninda Teslim Edilmeyen Kitaplari Listele\n16- Kitap-Yazar Eslestir\n17- Kitabin Yazarini Guncelle\nGeri:0\n\n");
        else if(tempChoice==3) printf("YAZAR ISLEMLERI\n18- Yazar Ekle\n19- Yazar Sil\n20- Yazar Guncelle\n21- Yazar Bilgisi Goruntule\n\nGeri:0\n\n");
        else if(tempChoice==4)  printf("LISTELEME ISLEMLERI\n22-Tum Kitaplari Listele\n23-Tum Kitap Ornek Durumlarini Listele\n24-Tum Yazarlari Listele\n25-Tum Kitap Yazar Iliskilerini Yazdir\n26-Tum kitap Odunc Iliskilerini Yazdir\nGeri:0\n");
        else if(tempChoice==0)printf("Cikis yapiliyor...\n");
        else printf("Hatali giris yaptiniz!\n");
        if(tempChoice>=1 && tempChoice<=4){
            printf("Yapmak istediginiz islemi seciniz:");
            scanf("%d", & islem);
            system("cls");
            switch (islem) {
            case 1:
                printf("Ogrenci Ekleme\n");
                ogrenciEkle( & headOgrenci);
                Sleep(1000);
                break;
            case 2:
                printf("Ogrenci Silme\n");
                ogrenciSil( & headOgrenci);
                Sleep(1000);
                break;
            case 3:
                printf("Ogrenci Guncelleme\n");
                ogrenciGuncelle( & headOgrenci);
                Sleep(1000);
                break;

            case 4:
                printf("Ogrenci Bilgisi Goruntuleme\n");
                ogrenciBilgi(headOgrenci, arrayOduncKitap, sizeOfArrayOduncKitap);
                Sleep(4000);
                break;
            case 5:
                printf("Kitap Teslim Etmemis Ogrencileri Listeleme\n");
                teslimEtmemisOgrenciler(sizeOfArrayOduncKitap, arrayOduncKitap);
                Sleep(4000);
                break;
            case 6:
                printf("Cezali Ogrencileri Listeleme\n");
                cezaliOgrenciler(headOgrenci);
                Sleep(4000);
                break;
            case 7:
                printf("Tum Ogrencileri Listeleme\n");
                ogrenciListele(headOgrenci);
                Sleep(4000);
                break;
            case 8:
                printf("Kitap Odunc Alma\n");
                kitapOduncAl(headOgrenci, headKitap, arrayKitapYazar, sizeOfArrayKitapYazar, & sizeOfArrayOduncKitap, & arrayOduncKitap);
                Sleep(4000);
                break;
            case 9:
                printf("Kitap Teslim Etme\n");
                kitapTeslimEt(headOgrenci, headKitap, arrayKitapYazar, sizeOfArrayKitapYazar, & sizeOfArrayOduncKitap, & arrayOduncKitap);
                Sleep(4000);
                break;
            case 10:
                printf("Kitap Ekleme  \n");
                kitapEkle( & headKitap, & arrayKitapYazar, & sizeOfArrayKitapYazar);
                Sleep(4000);
                break;
            case 11:
                printf("Kitap Silme\n");
                kitapSil( & headKitap, & arrayKitapYazar, & sizeOfArrayKitapYazar);
                Sleep(4000);
                break;
            case 12:
                printf("Kitap Guncelleme\n");
                kitapGuncelle( & headKitap, & arrayKitapYazar, & sizeOfArrayKitapYazar);
                Sleep(4000);

                break;

            case 13:
                printf("Kitap Bilgisi Goruntuleme\n");
                kitapBilgisiGoruntule(headKitap, arrayKitapYazar, sizeOfArrayKitapYazar, headYazar);
                Sleep(4000);
                break;
            case 14:
                printf("Raftaki Kitaplari Listeleme\n");
                raftakiKitaplariListele(headKitap);
                Sleep(4000);
                break;
            case 15:
                printf("Zamaninda Teslim Edilmeyen Kitaplari Listeleme\n");
                zamanindaTeslimEdilmeyenKitaplariListele(sizeOfArrayOduncKitap, arrayOduncKitap);
                Sleep(4000);
                break;

            case 16:
                printf("Kitap-Yazar Eslestirme\n");
                kitapYazarEslestir( & arrayKitapYazar, & sizeOfArrayKitapYazar, headKitap, headYazar, & yazarCounter);
                Sleep(4000);
                break;
            case 17:
                printf("Kitabin Yazar Guncelleme\n");
                kitapYazarGuncelle( & arrayKitapYazar, & sizeOfArrayKitapYazar, headKitap, headYazar);
                Sleep(4000);
                break;
            case 18:
                printf("Yazar Ekleme \n");
                yazarEkle( & headYazar, & yazarCounter);
                Sleep(4000);
                break;
            case 19:
                printf("Yazar Silme\n");
                yazarSil( & headYazar, & arrayKitapYazar, & sizeOfArrayKitapYazar);
                Sleep(4000);
                break;
            case 20:
                printf("Yazar Guncelleme\n");
                yazarGuncelle( & headYazar);
                Sleep(4000);
                break;
            case 21:
                printf("Yazar Bilgisi Goruntuleme\n");
                yazarBilgisiGoruntule(headYazar, arrayKitapYazar, sizeOfArrayKitapYazar, headKitap);
                Sleep(4000);
                break;
            case 22:
                printf("Tum Kitaplari Listeleme\n");
                kitaplariYazdir(headKitap);
                Sleep(4000);
                break;
            case 23:

                printf("Tum kitap ornek durumlarini listeleme\n");
                tumKitapOrnekleriniYazdir(headKitap);
                Sleep(4000);

                break;
            case 24:
                printf("Tum Yazarlari Listeleme\n");
                yazarlariYazdir(headYazar);
                Sleep(4000);
                break;
            case 25:
                printf("Tum Kitap Yazar Iliskilerini Yazdir\n");
                kitapYazarlariYazdir(arrayKitapYazar, sizeOfArrayKitapYazar);
                Sleep(4000);
                break;
            case 26:
                printf("Tum kitap Odunc Iliskilerini Yazdir\n");
                kitapOdunclariYazdir(arrayOduncKitap, sizeOfArrayOduncKitap);
                Sleep(4000);
                break;

            }
        }
    } while (tempChoice != 0);

    
      
    writeLinkedlistsToFiles(headOgrenci, headKitap, headYazar, arrayKitapYazar, sizeOfArrayKitapYazar, sizeOfArrayOduncKitap, arrayOduncKitap);
    freeKitap(headKitap);
    freeOgrenci(headOgrenci);
    freeYazar(headYazar);
    freeKitapYazar(arrayKitapYazar, sizeOfArrayKitapYazar);
    freeKitapOdunc(arrayOduncKitap, sizeOfArrayOduncKitap);
    printf("Tum veri yapilari free edildi. Cikiliyor..");
    return 0;
}
