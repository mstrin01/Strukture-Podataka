#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

struct _stablo;
typedef struct _stablo* pokazivac;
typedef struct _stablo
{
	char drzava[30];
	position lista;
	pokazivac left;
	pokazivac right;
}stablo;

struct _lista;
typedef struct _lista* position;
typedef struct _lista
{
	char grad[30];
	int brStan;
	position next;
}lista;

pokazivac citajDrzave(char*, pokazivac);
position trazi(position, char*);
position stvoriEl(position);
int sortiranaLista(position, char*, char*);
pokazivac citajGradove(pokazivac, char*);
pokazivac stvoriStablo(pokazivac, char*, int);
int ispis(position,int);
int ispisInorder(pokazivac);
pokazivac unosUStablo(pokazivac, char*, char*);
int stvoriListu(position, char*, int);
position stvoriElListe(position);
int ispisiListu(position);

int main()
{
	pokazivac root = NULL;
	pokazivac q = NULL;

	char imeDat = "drzave.txt";
	char drzava[30] = { 0 };

	root = stvoriEl(root);
	root = citajDrzave(root, imeDat);

	ispisInorder(root);

	q = trazi(root,drzava);
	if (q == NULL)
	{
		printf("Navedena drzava nije u datoteci\n");
	}

	int zeljeniBroj;
	printf("Unesi neki broj (stanovnika): \n");
	scanf("%d", &zeljeniBroj);
	printf("Gradovi s brojem stanovnika > od unesenog broja: \n");
	veciOd(q->lista, zeljeniBroj);

	return 0;
}

position stvoriElListe(position p)
{
	p = (position)malloc(sizeof(lista));
	if (p == NULL)
	{
		printf("Greska u alokaciji\n");
		return NULL;
	}

	strcpy(p->grad, "");
	p->brStan = 0;
	p->next = NULL;

	return p;
}

pokazivac stvoriEl(pokazivac p)  //odnosi se na stvaranje elementa stabla
{
	p = (position)malloc(sizeof(stablo));
	if (p == NULL)
	{
		printf("Greska u alokaciji!\n");
		return NULL;
	}

	strcpy(p->drzava, "");
	p->left = NULL;
	p->right = NULL;
	p->lista = NULL;
	
	return p;
}

pokazivac citajDrzave(char* imeDat, pokazivac p)
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
		p = unosUStablo(p, imeDrzave, drzavaPod);
	}

	fclose(fp);

	return p;
}
pokazivac unosUStablo(pokazivac p, char* imeDrzave, char* drzavaPod)
{
	if (p == NULL)
	{
		p = stvoriEl(p);
		p->lista = citajGradove;
		strcpy(p->drzava, imeDrzave);
	}

	else if (strcmp(p->drzava, imeDrzave) < 0)
	{
		p->right = unosUStablo(p->right, imeDrzave, drzavaPod);
	}
	
	else
	{
		p->left= unosUStablo(p->left, imeDrzave, drzavaPod);
	}

	return p;
}

position citajGradove(position p, char* imeDat)
{
	FILE* dat = NULL;
	dat = fopen(imeDat, "r");
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
		stvoriListu(p, imeGrada, brojStan);
	}

	fclose(dat);
	return p;
}

int stvoriListu(position p, char* imeGrada, int brojStan)
{
	position q = NULL;
	q = stvoriElListe(q);
	
	strcpy(q->grad, imeGrada);
	q->brStan = brojStan;

	while (p->next != NULL)
	{
		if (q->brStan < p->next->brStan);
			break;

		else if (q->brStan == p->next->brStan)
		{
			if (strcmp(q->grad, p->next->grad) < 0)
				break;
			else if (strcmp(q->grad, p->next->grad) > 0)
			{
				p = p->next;
				continue;
			}
		}
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}

int inorderIspis(pokazivac p)
{
	if (p == NULL)
		return 0;
	inorderIspis(p->left);
	printf(" %s ", p->drzava);
	ispisiListu(p->lista);
	inorderIspis(p->right);

	return 0;
}
int ispisiListu(position p)
{
	if (p == NULL)
	{
		return NULL;
	}
	else
	{
		p = p->next;
		while (p != NULL)
		{
			printf(" %s-%d ", p->grad, p->brStan);
			p = p->next;
		}
		return 0;
	}
}
pokazivac trazi(pokazivac p, char* imeDrz)
{
	if (p == NULL)
	{
		return NULL;
	}

	else if (strcmp(imeDrz, p->drzava) == 0)
	{
		return p;
	}

	else if (strcmp(imeDrz, p->drzava) > 0)
	{
		return trazi(p->drzava, imeDrz);

		return trazi(p->left, imeDrz);

	}
}
int ispis(position p, int n)
{
	while (p != NULL)
	{
		if (p->brStan > n)
		{
			printf(" %s-%d", p->grad, p->brStan);
		}
		p = p->next;
	}
	return 0;
}