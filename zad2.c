#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Osoba;
typedef struct _Osoba* pozicija;

typedef struct _Osoba {
	char ime[20];
	char prezime[30];
	int godinaRoðenja;
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

	printf("Unesi godinu roðenja %s %s: \n", q->ime, q->prezime);
	scanf("%d", q->godinaRoðenja);

	q->next = p->next;
	p->next = q;

	return 0;

}
int ispis(pozicija p) //b
{
	while (p != NULL)
	{
		printf("%s %s, %d\n", p->ime, p->prezime, p->godinaRoðenja);
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

	pozicija q=NULL;
	q = (pozicija)malloc(sizeof(Osoba));

	printf("Unesi ime osobe: \n");
	scanf(" %s", q->ime);

	printf("Unesi prezime osobe: \n");
	scanf(" %s", q->prezime);

	printf("Unesi godinu roðenja %s %s: \n", q->ime, q->prezime);
	scanf("%d", q->godinaRoðenja);

	
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
	scanf(" %s", &zeljenoPrezime);
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

	else printf("Krivo slovo je uneseno!\n");


	return 0;
}
