#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

typedef struct{
  char ime[MAX_SIZE];
  char prezime[MAX_LINE];
  double bodovi;
}student;

int ProcitajBrojRedakaIzDat(char* imeDat)
{
  int brojac=0;
  FILE* dat=NULL;
  char buffer[MAX_LINE]={0};

  dat=fopen(imeDat,"r");
  if(!dat)
  {
    printf("Neuspjesno otvaranje datoteke!\n");
    return -1;
  }
  
  while(!feof(dat))
  {
    fgets(buffer,MAX_LINE,dat);
    brojac++;
  }
  
  fclose(dat);
  
  return brojac;

}

student* ProcitajMemorijuIAlocirajStudente(int brojStudenata, char* imeDat)
{
  int brojac=0;
  FILE* dat=NULL;
  student* stud=NULL;
  
  stud=(student*)malloc(brojStudenata*sizeof(student));
  dat=fopen(imeDat,"r");
  
  if(!dat)
  {
    printf("Neuspjesna alokacija!\n");
    return -1;
  }
  
  while(!feof(dat))
  {
    fscanf(dat," %s %s %lf",stud[brojac].ime,stud[brojac].prezime,&stud[brojac].bodovi);
    brojac++;
  }
  
  fclose(dat);
  return stud;
}

int main()
{
  int i;
  int brojStudenata=ProcitajBrojRedakaIzDat("Rezultati.txt");
  student* stud=ProcitajMemorijuIAlocirajStudente(brojStudenata,"Rezultati.txt");
  
  printf("IME\t PREZIME\t BODOVI\n");
  for(i=0;i<brojStudenata;i++)
  {
    printf("%s %s %lf\n",stud[i].ime,stud[i].prezime,stud[i].bodovi);
  }
  
  double relBodovi[brojStudenata]; //max bodovi=30
  printf("Relativni bodovi od: \n");
  for(i=0;i<brojStudenata;i++)
  {
    relBodovi[i]=stud[i].bodovi/30*100;
    printf("%s %s = %lf\n",stud[i].ime,stud[i].prezime,relBodovi[i]);
  }
  
  return 0;
}

