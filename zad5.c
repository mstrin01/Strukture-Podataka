#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _stog* position;
typedef struct _stog {
	int el;
	position next;
}stog;

int push(position, int);
int pop(position);

int main()
{
	stog head;
	
	int n = 0, broj = 0, duljina = 0;
	int a = 0, b = 0;
	int rez = 0;
	int brojac = 0;

	char ImeDat[50], znak;
	printf("Unesi ime datoteke: \n");
	scanf(" %s", ImeDat);

	FILE* datoteka = fopen(ImeDat, "r");
	if (!datoteka)
	{
		printf("Greska pri otvaranju datoteke!\n");
	}

	char* buffer = NULL;
	buffer = (char*)malloc(1024);

	fgets(buffer, 1024, datoteka);
	duljina = strlen(buffer);

	while (brojac <= duljina)
	{
		if (sscanf(buffer, "%d %n", &broj, &n) == 1)
			push(&head, broj);

		else if (sscanf(buffer, "%c %n", &znak, &n) == 1)
		{
			if (znak == '+')
			{
				b = pop(&head);
				a = pop(&head);
				rez = a + b;
				push(&head, rez);
			}
			else if (znak == '-')
			{
				b = pop(&head);
				a = pop(&head);
				rez = a - b;
				push(&head, rez);
			}
			else if (znak == '*')
			{
				b = pop(&head);
				a = pop(&head);
				rez = a * b;
				push(&head, rez);
			}
		}

		brojac += n;
		buffer += n;
	}
	printf("Rezultat je: %d \n", pop(&head));

	return 0;
}

int pop(position p)
{
	position q;
	if (p->next != NULL)
	{
		q = p->next;
		p->next = q->next;
		return q->el;
		free(q);
	}
	return 0;
}

int push(position p, int c)
{
	position q = (position)malloc(sizeof(stog));
	q->el = c;
	q->next = p->next;
	p->next = q;

	return 0;
}