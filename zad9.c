#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>

struct _cvor;
typedef struct _cvor* position;
typedef struct _cvor
{
	int broj;
	position left;
	position right;
}cvor;

struct _lista;
typedef struct _lista* posL;
typedef struct _lista
{
	int el;
	posL next;
}lista;

int inorder(position, posL);
position StvoriPrazno(position);
position insert(position, int);
position replace(position);
int suma(position);
position random(position);
int UmetniNaKraj(posL, int);
posL PronadiZadnji(posL);
int umetni(posL, int);
int ispisDat(posL, posL, posL, char*);

int main()
{
	position root = NULL;
	posL p1 = NULL;
	posL p2 = NULL;
	posL p3 = NULL;
	char ime[50] = "stablo.txt";

	root = StvoriPrazno(root);
	p1 = (posL)malloc(sizeof(lista));
	p1->next = NULL;
	p2 = (posL)malloc(sizeof(lista));
	p2->next = NULL;
	p3 = (posL)malloc(sizeof(lista));
	p3->next = NULL;

	root = insert(root, 2);
	root = insert(root, 5);
	root = insert(root, 7);
	root = insert(root, 8);
	root = insert(root, 11);
	root = insert(root, 1);
	root = insert(root, 4);
	root = insert(root, 2);
	root = insert(root, 3);
	root = insert(root, 7);

	inorder(root, p1);

	root = replace(root);
	inorder(root, p2);

	root = StvoriPrazno(root);
	root = random(root);
	inorder(root, p3);
	ispisDat(p1->next, p2->next, p3->next, ime);

	return 0;
}

position StvoriPrazno(position S)
{
	if (S != NULL)
	{
		S->left = StvoriPrazno(S->left);
		S->right = StvoriPrazno(S->right);
		free(S);
	}
	return NULL;
}

int inorder(position S, posL head)
{
	if (S == NULL)
		return 0;

	inorder(S->left, head);
	UmetniNaKraj(head, S->broj);
	inorder(S->right, head);

	return 0;
}

position insert(position S, int el)
{
	if (S == NULL)
	{
		S = (position)malloc(sizeof(cvor));
		S->broj = el;
		S->left = NULL;
		S->right = NULL;
	}
	else if (el >= S->broj)
	{
		S->left = insert(S->left, el);
	}
	else if (el <= S->broj)
	{
		S->right = insert(S->right, el);
	}

	return S;
}

int suma(position S)
{
	int suma1 = 0;
	if (S == NULL)
		return suma1;
	if (S->left != NULL)
		suma1 += S->left->broj + suma(S->left);
	if (S->right != NULL)
		suma1 += S->right->broj + suma(S->right);

	return suma1;
}
position replace(position S)
{
	if (S != NULL)
	{
		S->broj = suma(S);
		S->left = replace(S->left);
		S->right = replace(S->right);
	}
	return S;
}

position random(position S)
{
	int i = 0, broj = 0;

	srand(time(NULL));
	for (i = 0; i < 10; i++)
	{
		broj = (rand() % (90 - 10 + 1)) + 10;
		S = insert(S, broj);
	}

	return S;
}

int UmetniNaKraj(posL head, int broj)
{
	posL zadnji = NULL;
	zadnji = PronadiZadnji(head);
	umetni(zadnji, broj);
	return 0;
}

posL PronadiZadnji(posL head)
{
	while (head->next != NULL)
		head = head->next;

	return head;
}

int umetni(posL head, int broj)
{
	posL prvi = NULL;
	prvi = (posL)malloc(sizeof(lista));

	if (prvi == NULL)
		return -1;
	prvi->el = broj;
	prvi->next = head->next;
	head->next = prvi;

	return 0;
}

int ispisDat(posL p1, posL p2, posL p3, char* imeDat)
{
	FILE* f = NULL;
	f = fopen(imeDat, "w");
	if (f == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!");
		return -1;
	}


	while (p1 != NULL)
	{
		fprintf(f, "%d\t", p1->el);
		p1 = p1->next;
	}
	fprintf(f, "\n");
	while (p2 != NULL)
	{
		fprintf(f, "%d\t", p2->el);
		p2 = p2->next;
	}
	fprintf(f, "\n");
	while (p3 != NULL)
	{
		fprintf(f, "%d\t", p3->el);
		p3 = p3->next;
	}


	fclose(f);
	return 0;
}