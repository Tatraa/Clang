#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char imie[15];
    char nazwisko[25];
    int wiek;
    double zarobki;
} osoba;

int wczytaj_dane(osoba os[],char file[]){
     FILE *fin=fopen(file,"r");
     
  if (!fin)
    {
      printf ("blad otwarcia pliku do czytania!\n");
      exit (-1);
    }
    int n=0;
    while(fscanf(fin,"%s %s %d %lg", os[n].imie,os[n].nazwisko,&os[n].wiek,&os[n].zarobki)==4)
    n++;
    return n;
}

void wypisz_dane(osoba os[],int n){
    int i;
    
    printf("----------------------------------------------------------------------\n");
    printf("| lp | imie            | nazwisko             | wiek    | zarobki    |\n");
    printf("----------------------------------------------------------------------\n");
    
    for(i=0;i<n;i++)
        printf("| %2d | %-15s | %-20s | %7d | %10.2f |\n",i+1,os[i].imie,os[i].nazwisko,os[i].wiek,os[i].zarobki);
        
    return;    
}


void zapisz_dane(osoba os[], int n, char file[])
{
    FILE *fout=fopen(file, "w");
    
    if(!fout)
    {
        printf("blad otwarcia pliku do pisania !\n");
        exit(0);
    }
    
    int i;
    
    for(i=0;i<n;i++)
        fprintf(fout,"%s %s %d %g\n",os[i].imie,os[i].nazwisko,os[i].wiek,os[i].zarobki); 
    
    return;
}

int por_inwz(const void *px, const void *py){
    
    osoba x = *(osoba *)px;
    osoba y = *(osoba *)py;
    
    int n = strcmp(x.imie,y.imie);
    if(n) return n;
    
    n = strcmp(x.nazwisko,y.nazwisko);
    if(n) return n;
    
    n = x.wiek-y.wiek;
    if(n) return n;
    
    return(int)(x.zarobki*100)-(int)(y.zarobki*100);
}

void sortuj_inwz(osoba os[],int n){
    
    qsort((void *)os, n, sizeof(osoba), por_inwz);
    return;
    
}

int por_niwz(const void *px, const void *py){
    
    osoba x = *(osoba *)px;
    osoba y = *(osoba *)py;
    
    int n = strcmp(x.nazwisko,y.nazwisko);
    if(n) return n;
    
    n = strcmp(x.imie,y.imie);
    if(n) return n;
    
    n = x.wiek-y.wiek;
    if(n) return n;
    
    return(int)(x.zarobki*100)-(int)(y.zarobki*100);
}

void sortuj_niwz(osoba os[],int n){
    
    qsort((void *)os, n, sizeof(osoba), por_niwz);
    return;
    
}

int por_wniz(const void *px, const void *py){
    
    osoba x = *(osoba *)px;
    osoba y = *(osoba *)py;
    
    int n = x.wiek-y.wiek;
    if(n) return n;
    
    n = strcmp(x.nazwisko,y.nazwisko);
    if(n) return n;
    
    n = strcmp(x.imie,y.imie);
    if(n) return n;
    
    return(int)(x.zarobki*100)-(int)(y.zarobki*100);
}

void sortuj_wniz(osoba os[],int n){
    
    qsort((void *)os, n, sizeof(osoba), por_wniz);
    return;
    
}

void usun_rekord(osoba os[],int n,int k){  //k-numer rekordu
    while(k<n){
        strcpy(os[k-1].imie,os[k].imie);
        strcpy(os[k-1].nazwisko,os[k].nazwisko);
        os[k-1].wiek=os[k].wiek;
        os[k-1].zarobki=os[k].zarobki;
        k++;
        }
}

int por_zniw(const void *px, const void *py){
    
    osoba x = *(osoba *)px;
    osoba y = *(osoba *)py;
    
    int n;
    return(int)(x.zarobki*100)-(int)(y.zarobki*100);
    
    n = x.wiek-y.wiek;
    if(n) return n;
    
    n = strcmp(x.nazwisko,y.nazwisko);
    if(n) return n;
    
    n = strcmp(x.imie,y.imie);
    if(n) return n;
    
}

void sortuj_zniw(osoba os[],int n){
    
    qsort((void *)os, n, sizeof(osoba), por_zniw);
    return;
    
}

void dodaj_rekord(int n,osoba os[],char i[15],char na[20],int w,double z){
        strcpy(os[n].imie,i);
        strcpy(os[n].nazwisko,na);
        os[n].wiek=w;
        os[n].zarobki=z;
}


void edytuj_rekord(osoba os[],int e,char i[15],char na[20],int w,double z){
    e=e-1;
        strcpy(os[e].imie,i);
        strcpy(os[e].nazwisko,na);
        os[e].wiek=w;
        os[e].zarobki=z;
    
    
}



char menu ()
{
    printf("\n***MENU***\n");
    printf("1. Wczytaj dane z pliku \n");
    printf("2. Zapisz dane do pliku \n");
    printf("3. Sortuj dane \n");
    printf("4. Dodaj rekord do pliku \n");
    printf("5. Usuń rekord z pliku \n");
    printf("6. Edytuj rekord \n");
    printf("7. Koniec programu \n");
   
    char c;
   
    printf("Wybierz opcje: \n");
    scanf("%s", &c);
    return c;
}

int main ()
{
    osoba os[50];
    
    while(1)
   
        switch (menu())
        {
            case '1':
                printf("Wybrano opcję 1 \n\n");
                int n = wczytaj_dane(os,"dane.txt");
                printf("wczytano dane %d osob\n", n);
                wypisz_dane(os,n);
            break;
       
           
            case '2':
                printf("Wybrano opcję 2 \n\n");
                wypisz_dane(os,n);
                zapisz_dane(os,n,"zapisane.out");   //nie dziala
            break;
           
           
            case '3':
            
                printf("Wybrano opcję 3 \n\n");
                printf("a.nazwisko imie wiek zarobki\n");
                printf("b.imie nazwisko wiek zarobki\n");
                printf("c.wiek nazwisko imie zarobki\n");
                printf("d.zarobki nazwisko imie wiek\n");
                printf("Wybierz opcję:");
                char s;
                scanf("%s",&s);
                
            if(s=='a'){
                sortuj_niwz(os,n);
                printf("\n");
                wypisz_dane(os,n); 
                } 
            
            if(s=='b'){
                sortuj_inwz(os,n);
                printf("\n");
                wypisz_dane(os,n); 
                
            }
            
            if(s=='c'){
                sortuj_wniz(os,n);
                printf("\n");
                wypisz_dane(os,n); 
                }
            
            if(s=='d'){
                 sortuj_zniw(os,n);
                 printf("\n");
                 wypisz_dane(os,n);
                }
                
            break;
           
           
            case '4':
                printf("Wybrano opcję 4 \n\n");
                char imie1[15];char nazwisko1[20];int wiek1;double zarobki1;
                printf("podaj imie,nazwisko,wiek,zarobki:");
                 scanf("%s %s %d %lg", imie1,nazwisko1,&wiek1,&zarobki1);
                 dodaj_rekord(n,os,imie1,nazwisko1,wiek1,zarobki1);
                 printf("\n");
                 n++;
                 wypisz_dane(os,n);
            break;
           
           
            case '5':
                printf("Wybrano opcję 5 \n\n");
                 int k;
                printf("podaj numer rekordu,który chcesz usunąć:");
                 scanf("%d", &k);
                 usun_rekord(os,n,k);
                 printf("\n");
                 n--;
                 wypisz_dane(os,n);
            break;
            
             case '6':
                printf("Wybrano opcję 6 \n\n");
                int e;char imie2[15],nazwisko2[20];int wiek2;double zarobki2;
                printf("podaj numer rekordu,który chcesz edytowac:\n");
                scanf("%d", &e);
                printf("podaj poprawne imie,nazwisko, wiek i zarobki:\n");
                scanf("%s %s %d %lg",imie2,nazwisko2,&wiek2,&zarobki2);
                 edytuj_rekord(os,e,imie2,nazwisko2,wiek2,zarobki2);
                 wypisz_dane(os,n);
                
            break;
            
             case '7':                          //dziala
                printf("Koniec programu \n\n");
            exit (0);
           

            default:
            printf("Nie ma takiej opcij \n\n"); //dziala
        }
}