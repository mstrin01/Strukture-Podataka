#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Stablo* position;
typedef struct _Stablo
{
	int el;
	position left;
	position right;
}Stablo;

position unosNovogEl(int, position);
void inorder(position);
void preorder(position);
void postorder(position);
position brisi(position);
position trazi(int, position);
position pronadiMin(position);



int  main()
{
	position root = NULL;
	position p = NULL;
	int noviEl;
	int brisiEl;
	int elem;
	int odabir;

	printf("Odaberi broj: \n");
	printf("1 - unos novog elementa u stablo \n");
	printf("2 - ispis elemenata ~ inorder \n");
	printf("3 - ispis elemenata ~ preorder \n");
	printf("4 - ispis elemenata ~ postorder \n");
	printf("5 - brisanje nekog elementa\n");
	printf("6 - trazenje nekog elementa \n");

	scanf("%d", &odabir);

	if (odabir == 1)
	{
		printf("Unesi element koji zelis unijeti:  \n");
		scanf("%d", &noviEl);
		root=unosNovogEl(noviEl, root);
	}

	else if (odabir == 2)
	{
		inorder(root);
	}

	else if (odabir == 3)
	{
		preorder(root);
	}

	else if (odabir == 4)
	{
		postorder(root);
	}

	else if (odabir == 5)
	{
		printf("Koji element zelis izbrisati? \n");
		scanf("%d", &brisiEl);
		root = (brisiEl, root);
	}

	else if (odabir == 6)
	{
		printf("Koji element zelis pronaci? \n");
		scanf("%d", &elem);
		p = trazi(elem, root);
	}

	else printf("Pogresan odabir!\n");

	return 0;
}

position unosNovogEl(int broj, position p)
{
	if (p == NULL)
	{
		p = (position)malloc(sizeof(Stablo));
		p->el = broj;
		p->left = NULL;
		p->right = NULL;

	}

	else if (broj < p->el)
	{
		p->left = unosNovogEl(broj, p->left);
	}

	else if (broj > p->el)
	{
		p->right = unosNovogEl(broj, p->right);
	}

	return p;
}

void inorder(position p)
{
	if (p != NULL)
	{
		inorder(p->left);
		printf("%d -> ", p->el);
		inorder(p->right);
	}
}

void preorder(position p)
{
	if (p != NULL)
	{
		printf("%d", p->el);
		preorder(p->left);
		preorder(p->right);
	}
}

void postorder(position p)
{
	if (p != NULL)
	{
		postorder(p->left);
		postorder(p->right);
		printf("%d", p->el);
	}
}

position trazi(int n, position p)
{
	if (p == NULL)
		return NULL;
	else
	{
		if (p->el > n)
			return trazi(p->left, n);
		else if (p->el < n)
			return trazi(p->right, n);
		else
			return p;
	}
}

position pronadiMin(position p)
{
	if (p == NULL)
		return p;
	else if (p->left == NULL)
		return p;
	else
		return pronadiMin(p->left);
}

position brisi(int n, position p)
{
	position temp;
	if (p == NULL)
		printf("Nema takvog elementa!\n");

	else if (p->el > n)
		p->left = brisi(n, p->left);
	else if (p->el < n)
		p->right = brisi(n, p->right);
	else
	{
		if (p->left != NULL && p->right != NULL)
		{
			temp = pronadiMin(p->right);
			p->el = temp->el;
			p->right = brisi(temp->el, p->right);
		}
		else
		{
			temp = p;
			if (p->left == NULL)
				p = p->right;
			else
				p = p->left;
			free(temp);
				
		}
	}

	return p;

}