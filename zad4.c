#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _polinom* pozicija;
typedef struct _polinom {
	int koeficijent;
	int potencija;
	pozicija next;
}polinom;

int unosPrvi(pozicija p);
int unosDrugi(pozicija p);
int suma(pozicija p);
int produkt(pozicija p);
int ispis(pozicija p);

int main()
{
	polinom head1;
	head1.next = NULL;
	
	polinom head2;
	head2.next = NULL;

	polinom head3;
	head3.next= NULL;

	polinom head4;
	head4.next = NULL;

	unosPrvog(&head1);
	printf("Prvi polinom, p1: \n");
	ispis(head1.next);

	printf("Drugi polinom, p2: \n");
	ispis(head2.next);
	unosDrugog(&head2);

	suma(&head1, &head2, &head3);
	produkt(&head1, &head2, &head4);

	return 0;
}

int unosPrvog(pozicija p)
{
	FILE* dat = NULL;
	dat = fopen("Polinom1.txt", "r");
	if (dat == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return 1;
	}

	while (!feof(dat))
	{
		pozicija q = NULL;
		q = (pozicija)malloc(sizeof(polinom));

		if (q == NULL)
		{
			printf("Neuspjesna alokacija!\n");
			return 1;
		}

		pozicija prev, temp;
		temp = p->next;
		prev = p;

		fscanf(dat, "%d %d", &q->koeficijent, &q->potencija);
		while (temp != NULL && temp->potencija < q->potencija)
		{
			prev = temp;
			temp = temp->next;
		}

		prev->next = q;
		if (temp != NULL)
		{
			q->next = temp;
		}

		else
		{
			q->next;
		}
	}
	
	return 0;
}

int unosDrugog(pozicija p)
{
	FILE* dat = NULL;
	dat = fopen("Polinom2.txt", "r");
	if (dat == NULL)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return 1;
	}

	while (!feof(dat))
	{
		pozicija q = NULL;
		q = (pozicija)malloc(sizeof(polinom));

		if (q == NULL)
		{
			printf("Neuspjesna alokacija!\n");
			return 1;
		}

		pozicija prev, temp;
		temp = p->next;
		prev = p;

		fscanf(dat, "%d %d", &q->koeficijent, &q->potencija);
		while (temp != NULL && temp->potencija < q->potencija)
		{
			prev = temp;
			temp = temp->next;
		}

		prev->next = q;
		if (temp != NULL)
		{
			q->next = temp;
		}

		else
		{
			q->next;
		}
	}

	return 0;
}

int suma(pozicija p1, pozicija p2, pozicija p3)
{
	while (p1->next != NULL && p2->next != NULL)
	{
		pozicija q = NULL;
		q = (pozicija)malloc(sizeof(polinom));

		if (q == NULL)
		{
			printf("Neuspjesna alokacija!\n");
			return 1;
		}
		q->next = NULL;

		if (p1->potencija == p2->potencija)
		{
			q->potencija = p1->potencija; //ili q->potencija=p2->potencija
			q->koeficijent = p1->koeficijent + p2->koeficijent;
			p1 = p1->next;
			p2 = p2->next;

		}

		else if (p1->potencija > p2->potencija)
		{
			q->potencija = p1->potencija;
			q->koeficijent = p1->koeficijent;
			p1 = p1->next;
		}

		else
		{
			q->potencija = p2->potencija;
			q->koeficijent = p2->koeficijent;
			p2 = p2->next;
		}

		p3->next = q;
		p3 = q;

		
	}
	
	pozicija temp;
	
	if (p2->next == NULL)
	{
		temp = p1->next;
	}
	else temp = p2->next;

	while (temp != NULL)
	{
		pozicija q = NULL;
		q = (pozicija)malloc(sizeof(polinom));

		if (q == NULL)
		{
			printf("Neuspjesna alokacija!\n");
			return 1;
		}
		q->next = NULL;
		q->potencija = temp->potencija;
		q->koeficijent = temp->koeficijent;
		p3->next = q;
		p3 = q;
		temp = temp->next;
	}

	
	/* primjer sa int
	* while(p1->next || p2->next){
	* 
		if(p1->next==NULL&&p2->next!=NULL)
			{
				q->koeficijent=p2->koeficijent;
				q->potencija=p2->potencija;
				p2=p2->next;      
			}
			if(p2->next==NULL&&p1->next!=NULL)
			{
				q->koeficijent=p1->koeficijent;
				q->potencija=p1->potencija;
				p1=p1->next;
			}
			p3->next=q;
			p3=q;
			p3->next=NULL;
			}
		*/
	
	

	return 0;
}
int produkt(pozicija p1, pozicija p2, pozicija p3)
{
	pozicija pol1 = p1->next;
	pozicija pol2 = p2->next;

	pozicija q = NULL;
	q = (pozicija)malloc(sizeof(polinom));
	if (q == NULL)
	{
		printf("Neuspjesna alokacija!\n");
		return 1;
	}
	q->next = NULL;

	polinom rez;
	rez.next = q;

	while (pol1 != NULL)
	{
		pol2 = p2->next;
		while (pol2 != NULL)
		{
			q->koeficijent = pol1->koeficijent * pol2->koeficijent;
			q->potencija = pol1->potencija + pol2->potencija;
			zbroj(&rez, p3, p3);
			pol2 = pol2->next;
		}
		pol1 = pol1->next;
	}


	return 0;
}
int ispis(pozicija p)
{
	while (p != NULL)
	{
		printf("Koeficijent: %d\n", p->koeficijent);
		printf("Eksponent: %d\n", p->potencija);
		p = p->next;
	}
	return 0;
}