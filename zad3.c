#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Osoba;
typedef struct _Osoba* pozicija;

typedef struct _Osoba {
	char ime[20];
	char prezime[30];
	int godinaRodenja;
	pozicija next;

}Osoba;

int unosP(pozicija p)  //a
{
	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(Osoba));

	printf("Unesi ime osobe: \n");
	scanf(" %s", q->ime);

	printf("Unesi prezime osobe: \n");
	scanf(" %s", q->prezime);

	printf("Unesi godinu ro�enja %s %s: \n", q->ime, q->prezime);
	scanf("%d", q->godinaRodenja);

	q->next = p->next;
	p->next = q;

	return 0;

}
int ispis(pozicija p) //b
{
	while (p != NULL)
	{
		printf("%s %s, %d\n", p->ime, p->prezime, p->godinaRodenja);
		p = p->next;
	}

	return 0;

}
int unosK(pozicija p) //c
{
	while (p->next != NULL)
	{
		p = p->next;
	}

	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(Osoba));

	printf("Unesi ime osobe: \n");
	scanf(" %s", q->ime);

	printf("Unesi prezime osobe: \n");
	scanf(" %s", q->prezime);

	printf("Unesi godinu ro�enja %s %s: \n", q->ime, q->prezime);
	scanf("%d", q->godinaRodenja);


	q->next = p->next;
	p->next = q;


	return 0;
}
int pronadiPrezime(pozicija p) //d
{
	char zeljenoPrezime[30];
	printf("Unesi prezime koje zelis pronaci: \n");
	scanf(" %s", &zeljenoPrezime);

	while (p != NULL && strcmp(zeljenoPrezime, p->prezime) != 0)
	{
		p = p->next;
	}

	if (p == NULL)
		printf("Nema osobe s tim prezimenom!\n");
	else
		printf("Adresa trazene osobe: %p\n", p);


	return 0;
}
int brisi(pozicija p) //e
{
	pozicija prethodni = NULL;
	char zeljenoPrezime[30];
	printf("Unesi prezime osobe koju zelis izbrisati:\n");
	scanf(" %s", zeljenoPrezime);
	while (p->next != NULL && strcmp(zeljenoPrezime, p->prezime) != 0)
	{
		prethodni = p;
		p = p->next;
	}
	if (prethodni != NULL && strcmp(zeljenoPrezime, p->prezime) == 0)
	{
		p = prethodni->next;
		prethodni->next = p->next;
	}

	return 0;
}

int dodajIza(pozicija p) //f, zad3 a)
{
	pozicija noviEl = NULL;
	noviEl = (pozicija)malloc(sizeof(Osoba));

	p = p->next;

	char zeljenoPrezime[30];
	printf("Unesi prezime iza kojeg zelis dodati novi element: \n");
	scanf(" %s", zeljenoPrezime);

	printf("Unesi ime (nove) osobe: \n");
	scanf(" %s", noviEl->ime);
	printf("Unesi prezime (nove) osobe: \n");
	scanf(" %s", noviEl->prezime);
	printf("Godina rođenja %s %s: \n", noviEl->ime, noviEl->prezime);
	scanf("%d", noviEl->godinaRodenja);

	while (p != NULL && p->prezime != zeljenoPrezime)
	{
		p = p->next;
	}

	if (p != NULL)
	{
		noviEl->next = p->next;
		p->next = noviEl;
	}

	else printf("Greska!\n");
	
	return 0;

}

int dodajIspred(pozicija p) //g, zad3 b)
{
	pozicija noviEl=NULL;
	noviEl= (pozicija)malloc(sizeof(Osoba));

	char zeljenoPrezime[30];
	printf("Unesi prezime iza kojeg zelis dodati novi element: \n");
	scanf(" %s", zeljenoPrezime);

	printf("Unesi ime (nove) osobe: \n");
	scanf(" %s", noviEl->ime);
	printf("Unesi prezime (nove) osobe: \n");
	scanf(" %s", noviEl->prezime);
	printf("Godina rođenja %s %s: \n", noviEl->ime, noviEl->prezime);
	scanf("%d", noviEl->godinaRodenja);

	while (p->next != NULL && p->next->prezime != zeljenoPrezime)
	{
		p = p->next;
	}

	if (p->next != NULL)
	{
		noviEl->next = p->next;
		p->next = noviEl;
	}

	else printf("Greska!\n");

	return 0;
}

int sortirajPoPrezimenima(pozicija p)  //h, 3c)
{
	pozicija i = p;
	pozicija j = NULL;
	pozicija preth_j = NULL;
	pozicija kraj = NULL;

	while (i->next != kraj)
	{
		preth_j = i;
		j = preth_j->next;
		while (j->next != kraj)
		{
			if (strcmp(j->prezime, j->next->prezime) > 0)
			{
				preth_j->next = j->next;
				j->next = j->next->next;
				preth_j->next->next = j;
				j = preth_j->next;
			}
			preth_j = j;
			j = j->next;
		}
	}
	kraj = j;
	

	return 0;
}

void upisUDat(pozicija p) //i, zad3 d)
{
		FILE* dat = NULL;
		dat = fopen("ListaOsobe", "w");

		if (dat == NULL)
		{
			printf("Greska!\n");
			return 1;
		}
		while (p != NULL)
		{
			fprintf(dat, "%s %s %d \n", p->ime, p->prezime, p->godinaRodenja);
			p = p->next;
		}
		fclose(dat);

}

void citajIzDat(pozicija p) //j, zad3 e)
{
	char imeDat[50];
	
	printf("Unesi ime datoteke iz koje zelis citati listu: \n");
	scanf(" %s", &imeDat);

	int brojac = 0;
	int i = 0;
	pozicija q = NULL;

	FILE* dat = NULL;
	dat = fopen(imeDat, "r");
	
	if (dat == NULL)
	{
		printf("Greska!\n");
		return 1;
	}

	while (!feof(dat))
	{
		if (fgetc(dat) == '\n')
		{
			brojac++;
		}
	}
	if(brojac!=0)
	{
		for (i = 0; i < brojac; i++)
		{
			q = (pozicija)malloc(sizeof(Osoba));
			fscanf(dat, "%s %s %d", q->ime, q->prezime, &q->godinaRodenja);
			q->next = p->next;
			p->next = q;
		
		}
	}
	fclose(dat);

}
int main()
{
	Osoba head;
	head.next = NULL;
	char x;

	printf("Odaberi a,b,c,d,e: x= ");
	scanf("%c", &x);
	puts("\n");

	if (x == 'a')
	{
		printf("a) UNOS NA POCETAK LISTE: \n");
		unosP(&head);
	}

	else if (x == 'b')
	{
		printf("b) ISPIS LISTE: \n");
		ispis(head.next);
	}

	else if (x == 'c')
	{
		printf("c) UNOS NA KRAJ LISTE: \n");
		unosK(&head);
	}

	else if (x == 'd')
	{
		printf("d) PRONADJI PO PREZIMENU: \n");
		pronadiPrezime(head.next);
	}

	else if (x == 'e')
	{
		printf("e) BRISANJE IZ LISTE: \n");
		brisi(&head);

	}
	// zadatak 3, nastavno na zad2
	else if (x == 'f')
	{
		printf("f) DODAVANJE NOVOG ELEMENTA IZA ODREĐENOG ELEMENTA: \n");
		dodajIza(&head);
	}

	else if (x == 'g')
	{
		printf("g) DODAVANJE NOVOG ELEMENTA ISPRED ODREĐENOG ELEMENTA: \n");
		dodajIspred(&head);
	}

	else if (x == 'h')
	{
		printf("h) SORTIRANJE LISTE PO PREZIMENIMA: \n");
		sortirajPoPrezimenima(&head);
	}

	else if (x == 'i')
	{
		printf("i) UPIS LISTE U DATOTEKU: \n");
		upisUDat(&head);
	}

	else if (x == 'j')
	{
		printf("j) CITANJE LISTE IZ DATOTEKE: \n");
		citajIzDat(&head);
	}




	else printf("Krivo slovo je uneseno!\n");


	return 0;
}
