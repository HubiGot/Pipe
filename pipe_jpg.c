#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(){

FILE *plik_wej;
int fd[2];
int id;
char nazwa_pliku[100];
char bufor[1]; // bufor pomocniczy do przesylania po jednym znaku

pipe(fd);
id=fork();
if(id==0) // kod dziecka
  {
    printf("Jestem dzieckiem - wykonuje kod dziecka \n");
    close(fd[1]); // dziecko nie musi pisac do potoku
    close(0); // zwalniamy 0 bo display czyta z 0
    dup(fd[0]); // duplikujemy fd[0], ktore zajelo najmniejszy wolny numer - 0
    execlp("display","",NULL);
  }
else if(id >0) // kod rodzica
  {
    printf("Jestem rodzicem - wykonuje kod rodzica \n");
    close(fd[0]); // rodzic nie musi czytac z potoku
    printf("Podaj nazwe pliku do otwarcia\n");
    scanf("%s", nazwa_pliku);
    plik_wej=fopen(nazwa_pliku,"r+b");
    if(plik_wej==NULL)
      {
        printf("Nie podano wlasciewgo uchwytu do pliku \n");
        return -1;
      }
      else
      {
        while(!feof(plik_wej))
        {
          bufor[0]=getc(plik_wej);
          write(fd[1],bufor,1); // zapisujemy do potoku
        }
        fclose(plik_wej);
      }
  }
else
  {
    printf("Fork nie powidl sie :(");
    return -1;
  }

}
