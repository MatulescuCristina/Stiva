#include<stdio.h>
#include<malloc.h>

struct Oras
{
	char* denumire;
	int nrLocuitori;
	float suprafata;
};

struct Nod
{
	struct Oras info;
	struct Nod* next;
};

// inserare element in stiva
void push(struct Nod** stiva, struct Oras o)
{
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));

	nou->info.denumire = (char*)malloc((strlen(o.denumire) + 1) * sizeof(char));
	strcpy(nou->info.denumire, o.denumire);

	nou->info.nrLocuitori = o.nrLocuitori;
	nou->info.suprafata = o.suprafata;

	nou->next = NULL;

	if (*stiva == NULL)
	{
		*stiva = nou;
	}
	else
	{
		nou->next = *stiva;
		*stiva = nou;
	}
}

// extragere element din stiva
int pop(struct Nod** stiva, struct Oras* o)
{
	if (*stiva == NULL)
	{
		return -1;
	}
	else
	{
		(*o).denumire = (char*)malloc((strlen((*stiva)->info.denumire) + 1) * sizeof(char));
		strcpy((*o).denumire, (*stiva)->info.denumire);

		(*o).nrLocuitori = (*stiva)->info.nrLocuitori;
		(*o).suprafata = (*stiva)->info.suprafata;

		struct Nod* temp = *stiva;
		*stiva = (*stiva)->next;
		free(temp->info.denumire);
		free(temp);

		return 0;
	}
}

// afisare stiva
void afisare(struct Nod* stiva)
{
	struct Nod* aux = stiva;
	while (aux != NULL)
	{
		printf("Denumire oras: %s, nr locuitori: %d, suprafata: %5.2f\n",
			aux->info.denumire, aux->info.nrLocuitori, aux->info.suprafata);
		aux = aux->next;
	}
}

void main()
{
	int nr;
	struct Nod* stiva = NULL;
	struct Oras o;
	char buffer[20];

	FILE* f = fopen("oras.txt", "r");
	fscanf(f, "%d", &nr);

	for (int i = 0; i < nr; i++)
	{
		fscanf(f, "%s", buffer);
		o.denumire = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(o.denumire, buffer);

		fscanf(f, "%d", &o.nrLocuitori);
		fscanf(f, "%f", &o.suprafata);

		push(&stiva, o);
		free(o.denumire);
	}
	fclose(f);

	afisare(stiva);

	// eliminare element dupa denumire
	pop(&stiva, &o);
	printf("\n A fost sters orasul cu denumirea: %s \n", o.denumire);
	free(o.denumire);
	afisare(stiva);
}