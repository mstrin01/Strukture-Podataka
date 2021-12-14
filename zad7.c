#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _dir* position;
typedef struct _dir {

	char ime[30];
	position child;
	position next;

}dir;

typedef struct _stog* pozicija;
typedef struct _stog {

	position el;
	pozicija next;

}stog;

position stvori(int);
pozicija stvoriDrugi(int);
int push(position, pozicija);
int unesiPodatke(position);
int md(position, pozicija);
position cd(position);
int print(position);
position TraziDir(position, char*);
position cdt(pozicija);


int main()
{
	position root = NULL;
	root = stvori(1);

	position current = root;

	pozicija  s = NULL;
	s = stvoriDrugi(1);

	int odabir;

	printf("Odaberi broj: \n");
	printf("1 - md \n");
	printf("2 - cd \n");
	printf("3 - ispis direktorija\n");
	printf("4 - vracanje u prethodni direktorij\n");
	printf("5 - izlaz\n");

	if (odabir == 1)
		md(current, s);
	else if (odabir == 2)
		cd(current);
	else if (odabir == 3)
		print(current);
	else if (odabir == 4)
		cdt(s);
	else
		printf("Greska!\n");

	return 0;
}

position stvori(int N)
{
	position q = NULL;
	q = (position)malloc(N * sizeof(dir));
	if (q == NULL)
	{
		printf("Greska u alokaciji!\n");
		return NULL;

	}

	q->next = NULL;
	q->child = NULL;

	return q;
}

pozicija stvoriDrugi(int N)
{
	pozicija q = NULL;
	q = (pozicija)malloc(N * sizeof(stog));

	if (q == NULL)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	q->next = NULL;
	q->el = NULL;

	return q;
}

int unesiPodatke(position q)
{	
	printf("Unesi ime direktorija: \n");
	scanf(" %s", q->ime);

	return 0;
}

int push(position current, pozicija s)
{
	pozicija q = NULL;
	q = stvoriDrugi(1);
	
	q->el = current;
	q->next = s->next;
	s->next = q;

	return 0;
}

int md(position current, pozicija s)
{
	position q = NULL;
	if (current == NULL)
	{
		printf("Ne postoji!\n");
		return -1;
	}

	q = stvori(1);
	unesiPodatke(q);

	push(current, s);
	
	if (current->child == NULL)
	{
		current->child = q;
		return 0;
	}

	current = current->child;

	while (current->next != NULL)
	{
		current = current->next;
	}

	q->next = current->next;
	current->next = q;

	return 0;

}

position TraziDir(position p, char* imeDir)
{
	if (p == NULL)
	{
		printf("Greska!\n");
		return NULL;
	}
	
	p = p->child;
	while (p != NULL && strcmp(p->ime, imeDir) != 0)
	{
		p = p->next;
	}

	if (p == NULL)
	{
		printf("Direktorij koji trazite ne postoji!\n");
		return NULL;
	}

	else
		printf("Pronadjen je direktorij: %s\n", p->ime);

	return p;
	
		
}

position cd(position current)
{
	position q = NULL;
	q = stvori(1);
	char imeDir[20];

	printf("Unesi ime direktorija: \n");
	scanf(" %s", imeDir);

	q = TraziDir(current, imeDir);

	return q;
}

int print(position current)
{
	if (current == NULL)
	{
		printf("Ne postoji!\n");
		return -1;
	}
	
	current = current->child;
	if (current == NULL)
	{
		return 1;
	}

	while (current != NULL)
	{
		printf(" %s\n", current->ime);
		current = current->next;
	}

	return 0;
}

position cdt(pozicija s)
{
	pozicija pom = NULL;
	position q = NULL;
	
	q = stvori(1);
	pom = s->next;
	q = pom->el;
	s->next = pom->next;
	free(pom);

	return q;
}