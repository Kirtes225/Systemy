#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
 
#define MAX 13312 // rozmiar bufora
 
_Bool czytochar(char[], int);
 
void wyswietl(char[], int);
 
 
int main(int argc, char *argv[]){
    srand(time(NULL)); // do sprawdzenia znaku ASCII
   
    char buf[MAX]; // pozwala wczytac caly plik do bufora, jesli bedzie stosunkowo maly
   
    int skadpobrac;
    int gdziezapisac;
    int iloscbajtow;
   
       
    if (argc < 3) {
        printf("\nNie podales wszystkich parametrow\n");
        return 1;
    } // sprawdzenie czy uzytkownik podal miejsce odczytu i zapisu
   
    skadpobrac = open(argv[1], O_RDONLY); //O_RDONLY pozwala odczytac plik
 
    if (skadpobrac == -1) {
        printf("Nie udalo sie otworzyc pliku\n");
        return 1;
    } // jesli nie uda sie otworzyc pliku zwroci blad
 
    if((iloscbajtow = read(skadpobrac, buf, MAX)) > 0) {
       
        char pomocnicza[4]; // pomocnicza tablica 4 elementowa do zapisu bajtow 15-18
       
        for (int i = 0; i < 4; i++)
            pomocnicza[i] = buf[i+15];
 
        int iloscznakow = sizeof(pomocnicza) / sizeof(pomocnicza[0]); //okresla liczbe bajtow do sprawdzenia, tu 4
       
        if(czytochar(pomocnicza, iloscznakow)) {
            printf("\nZnak to char\n");
            wyswietl(pomocnicza, iloscznakow);
        } //jesli znak to char, to wypisze ten znak na ekran
        else{
            printf("\nZnak to liczba\n");
 
            for(int i = 0; i < iloscznakow; i++) {
                buf[i+15] = (rand()%10) + 48;
            } // wyznacza kod ASCII dla konkretnego elementu
 
 
            gdziezapisac = open(argv[2], O_RDWR | O_CREAT); //pozwala zapisywac do pliku i jesli on nie istnieje to utworzy go
           
            int deskryptor;
            if (deskryptor = (write(gdziezapisac, buf, iloscbajtow)) == -1){
                printf("Nie udalo sie zapisac [%i]\n", deskryptor);
                return 1;
            }
            // zapisuje deskryptor do pliku podanego przez uzytkownika
 
            if(close(gdziezapisac) || close(skadpobrac)) {
                printf("Nie udalo sie zamknac ktoregos z pliku");
            }
            // jesli nie udalo sie zamknac ktoregos z pliku zwroci blad
        }
    }
    return 0;
}
 
_Bool czytochar(char elementy[], int ileelementow){
    for(int i = 0; i < ileelementow; i++){
        if(elementy[i]<48 || elementy[i]>57)
            return true;
    }
 
    return false;
} // funkcja sprawdzajaca czy znaki nie sa cyframi
 
void wyswietl(char tablicaznakow[], int liczbaznakow){
    for (int i = 0; i < liczbaznakow; i++) {
        printf("%c", tablicaznakow[i]);
    }
 
    printf("\n\n");
} // funkcja wyswietlajaca na ekran znaki