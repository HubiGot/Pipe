#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(){

FILE *plik_wej;
int fd[2]; // deskryptory 0 i 1
int id;
char nazwa_pliku[100];
char bufor[1];
char odbior[1000];
int licz=0;

pipe(fd);
id=fork();
if(id==0) // kod dziecka
  {
    printf("Jestem dzieckiem - wykonuje kod dziecka \n");
    close(fd[1]);
    close(0); // zwalniamy 0
    dup(fd[0]); // duplikujemy fd[0], ktore jest teraz zerem
    while ((licz=read(fd[0], odbior, BUFSIZ)) > 0)
    {

    }
    execlp("display","",NULL);


  }
else if(id >0) // kod rodzica
  {
    printf("Jestem rodzicem - wykonuje kod rodzica \n");
    close(fd[0]);
    printf("Podaj nazwe pliku do otwarcia\n");
    scanf("%s", nazwa_pliku);
    plik_wej=fopen(nazwa_pliku,"r+b");
    if(plik_wej==NULL)
      {
        printf("Nie podano wlasciewgo uchwytu do pliku \n");
        return 0;
      }
      else
      {
        while(!feof(plik_wej))
        {

          bufor[0]=getc(plik_wej);
          write(fd[1],bufor,1);
        }
        sleep(5);
        close(fd[1]);
        fclose(plik_wej);

      }
  }
else
  {
    printf("Fork nie powidl sie :(");
    return 0;
  }




}
