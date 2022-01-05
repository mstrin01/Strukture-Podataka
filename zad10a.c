#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

struct _stablo;
typedef struct _stablo* pokazivac;
typedef struct _stablo
{
	char grad[30];
	int brStanovnika;
	pokazivac left;
	pokazivac right;
}stablo;

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	char drzava[30];
	position next;
	pokazivac stablo;
}lista;


int citajDrzave(char*,position);
position trazi(position, char*);
position stvoriEl(position);
int sortiranaLista(position, char*, char*);
pokazivac citajGradove(pokazivac, char*);
pokazivac stvoriStablo(pokazivac, char*, int);
int ispis(position);
int ispisInorder(pokazivac);

int main()
{
	position head = NULL;
	char imeDat="drzave.txt";
	char drzava[30] = { 0 };

	head = stvoriEl(head);
	
	citajDrzave(imeDat,head);
	ispis(head->next);

	printf("Odaberi drzavu: \n");
	scanf(" %s", drzava);
	
	position q = NULL;
	q = trazi(head, drzava);
	if (q == NULL)
	{
		printf("Navedena drzava nije u datoteci\n");
	}

	int zeljeniBroj;
	printf("Unesi neki broj (stanovnika): \n");
	scanf("%d", &zeljeniBroj);
	printf("Gradovi s brojem stanovnika > od unesenog broja: \n");
	veciOd(q->stablo, zeljeniBroj);


	return 0;
}

position stvoriEl(position p)
{
	p = (position)malloc(sizeof(lista));
	if (p == NULL)
	{
		printf("Greska u alokaciji!\n");
		return -1;
	}

	strcpy(p->drzava, "");
	p->next = NULL;
	p->stablo = NULL;

}
position trazi(position p, char* drzava)
{
	while (p->next != NULL && strcmp(drzava, p->drzava) != 0)
		p = p->next;

	return p;
}

int citajDrzave(char* imeDat, position p)
{
	char imeDrzave[30] = { 0 };
	char drzavaPod[30] = { 0 };

	FILE* fp = NULL;
	fp = open(imeDat, "r");
	if (fp == NULL)
	{
		printf("Greska!\n");
		return -2;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s %s", imeDrzave, drzavaPod);
		sortiranaLista(p, imeDrzave, drzavaPod);
	}

	fclose(fp);
	return 0;
}

int sortiranaLista(position p, char* imeDrzave, char* drzavaPod)
{
	position q = NULL;
	q = (position)malloc(sizeof(lista));
	if (q == NULL)
	{
		printf("Greska u alokaciji!\n");
		return -3;
	}

	strcpy(q->drzava,imeDrzave);
	q->stablo = citajGradove(q->stablo, drzavaPod);
	
	char temp[30] = { 0 };
	strcpy(temp, imeDrzave);

	while (p != NULL)
	{
		if (p->next == NULL)
		{
			p->next = q;
			q->next = NULL;
		}
		else if (strcmp(temp, p->next->drzava) < 0)
		{
			q->next = p->next;
			p->next = q;
		}
		p = p->next;

	}

	return 0;
}

pokazivac citajGradove(pokazivac root, char* drzavaPod)
{
	FILE* dat = NULL;
	dat = fopen(drzavaPod, "r");
	if (dat == NULL)
	{
		printf("Greska!\n");
		return -2;
	}

	char imeGrada[30] = { 0 };
	int brojStan = 0;

	while (!feof(dat))
	{
		fscanf(dat, " %s %d\n", imeGrada, &brojStan); 
		root = stvoriStablo(root, imeGrada, brojStan);
	}

	fclose(dat);
	return root;
}

pokazivac stvoriStablo(pokazivac p, char* imeGrada, int brojStan)
{
	if (p == NULL)
	{
		p = (pokazivac)malloc(sizeof(stablo));
		if (p == NULL)
		{
			printf("Greska u alokaciji!\n");
			return NULL;
		}

		strcpy(p->grad, imeGrada);
		p->brStanovnika = brojStan;
		p->left = NULL;
		p->right = NULL;
		
	}
	else if (brojStan == p->brStanovnika)
	{
		if (strcmp(imeGrada, p->grad) < 0)
			p->left = stvoriStablo(p->left, imeGrada, brojStan);
		else if (strcmp(imeGrada, p->grad) > 0)
			p->right = stvoriStablo(p->right, imeGrada, brojStan);
	}
	else
	{
		if (brojStan < p->brStanovnika)
			p->left = stvoriStablo(p->left, imeGrada, brojStan);
		else
			p->right = stvoriStablo(p->right, imeGrada, brojStan);
	}

	return p;
}

int ispis(position p)
{
	while (p != NULL)
	{
		printf(" %s\n", p->drzava);
		inorderIspis(p->stablo);
		p = p->next;
	}

	return 0;
}

int inorderIspis(pokazivac p)
{
	if (p == NULL)
		return 0;
	inorderIspis(p->left);
	printf(" %s %d\n", p->grad, p->brStanovnika);
	inorderIspis(p->right);

	return 0;
}

int veciOd(pokazivac p, int n)
{
	if (p == NULL)
		return 0;

	veciOd(p->left, n);

	if (n < p->brStanovnika)
	{
		printf("%s %d\n", p->grad, p->brStanovnika);
	}

	veciOd(p->right, n);

	return 0;
}
