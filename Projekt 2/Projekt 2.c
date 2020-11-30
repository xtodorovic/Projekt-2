#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* Projekt 2
* autor: Patrik Malina
* cviciaca: Anna Považanová
* datum: 1.12.2020
*/

#define FILE_NAME "zvierata.txt"//meno suboru v ktorom sa nachadzaju zvierata
#define ANIMAL_NAME 51			//pocet karakterov pre meno zvierata
#define SPECIES 31				//pocet karakterov pre druh zvierata
#define MAX_HEIGHT 30000		//maksimalna vyska zvierata
#define HEIGHT_UNIT "cm"		//jednotka pre vysku
#define MAX_WEIGHT 3000000		//maksimalna vaha zvierata
#define WEIGHT_UNIT "kg"		//jednotka pre vahu
#define DATE_LENGHT 8			//pocet cislic v datume
#define DATE_FORMAT "RRRRMMDD"	//ako ma vyzerat tvar datumu
#define CAREGIVER_NAME 51		//pocet karakterov pre meno osetrovatela

typedef struct animal
{
	char name[ANIMAL_NAME];
	char species[SPECIES];
	int height;
	float weight;
	long int birht_date;
	long int last_feeding;
	char caregiver_name[CAREGIVER_NAME];
	struct animal* next_animal_in_line;
	struct animal* previus_animal_in_line;
}ANIMAL;

void deallocate_structures(ANIMAL* deallocate_this_structure)
{
	ANIMAL* next_structure = NULL;
	while (deallocate_this_structure)
	{
		if (deallocate_this_structure->next_animal_in_line != NULL)
			next_structure = deallocate_this_structure->next_animal_in_line;
		else
			break;
		free(deallocate_this_structure);
		deallocate_this_structure = NULL;
		deallocate_this_structure = next_structure;
	}
	deallocate_this_structure = NULL;
}

void print_the_structure(ANIMAL* print_this_structure, int animal_number)
{
	printf("%d.\n", animal_number);

	printf("Meno: %s\n", print_this_structure->name);

	printf("Druh: %s\n", print_this_structure->species);

	if (check_height(print_this_structure->height))
		printf("Vyska: %d %s\n", print_this_structure->height, HEIGHT_UNIT);
	else
		printf("Nekorektne zadana vyska!\n");

	if (check_weight(print_this_structure->weight))
		printf("Vaha: %.5f %s\n", print_this_structure->weight, WEIGHT_UNIT);
	else
		printf("Nekorektne zadana vaha!\n");

	if (check_date(print_this_structure->birht_date))
		printf("Datum narodenia: %ld\n", print_this_structure->birht_date);
	else
		printf("Nekorektne zadani datum!\n");

	if (check_date(print_this_structure->last_feeding))
		printf("Datum posledneho krmenia: %ld\n", print_this_structure->last_feeding);
	else
		printf("Nekorektne zadani datum!\n");

	printf("Meno osetrovatela: %s\n", print_this_structure->caregiver_name);
	printf("\n");
}

int finde_animal_name(ANIMAL* animal, char check_this_name[ANIMAL_NAME])
{
	char animal_name[ANIMAL_NAME], check_with_this_name[ANIMAL_NAME];
	int names_are_same = 0;

	strcpy(animal_name, animal->name);
	strcpy(check_with_this_name, check_this_name);

	_strupr(animal_name);
	_strupr(check_with_this_name);

	if (!strcmp(animal_name, check_with_this_name))
		names_are_same = 1;

	return names_are_same;
}

int check_date(long int date) //funckia na kontrolu spravnosti datumu
{
	int date_lenght = 0, true_or_fals = 0, month = date / 100 % 100, day = date % 100; //vyhladame mesiac a den
	date_lenght = snprintf(NULL, 0, "%li", date);   //vrati pocet karakterov 
	if (date_lenght == DATE_LENGHT && day > 0 && (month > 0 && month <= 12))
	{
		switch (month)
		{
		case 1: if (day <= 31) true_or_fals = 1; break;
		case 2: if (day <= 28) true_or_fals = 1; break;
		case 3: if (day <= 31) true_or_fals = 1; break;
		case 4: if (day <= 30) true_or_fals = 1; break;
		case 5: if (day <= 31) true_or_fals = 1; break;
		case 6: if (day <= 30) true_or_fals = 1; break;
		case 7: if (day <= 31) true_or_fals = 1; break;
		case 8: if (day <= 31) true_or_fals = 1; break;
		case 9: if (day <= 30) true_or_fals = 1; break;
		case 10: if (day <= 31) true_or_fals = 1; break;
		case 11: if (day <= 30) true_or_fals = 1; break;
		case 12: if (day <= 31) true_or_fals = 1; break;
		}
	}
	return true_or_fals;
}
int check_height(int height)
{
	int true_or_fals = 0;
	if (height > 0 && height <= MAX_HEIGHT)
		true_or_fals = 1;

	return true_or_fals;
}
int check_weight(float weight)
{
	int true_or_fals = 0;
	if (weight > 0 && weight <= MAX_WEIGHT)
		true_or_fals = 1;

	return true_or_fals;
}

ANIMAL* n(ANIMAL* first_animal, int* number_of_animals)
{
	FILE* fr = NULL;

	fr = fopen(FILE_NAME, "r");
	if (fr == NULL)
		printf("Zaznamy neboli nacitane!\n");
	else
	{
		char temp[ANIMAL_NAME] = "\0";
		int i = 0;

		rewind(fr);
		while (!feof(fr))
		{
			for (int j = 0; j < 8; j++)
				if (temp != 0)
					fgets(temp, ANIMAL_NAME - 1, fr);
				else
				{
					printf("Nastala chyba pri nacitavani suboru!\n");
					return first_animal;
				}
			i++;
		}

		*number_of_animals = i;
		if (first_animal != NULL)
		{
			deallocate_structures(first_animal);
			first_animal = NULL;
		}

		rewind(fr);
		ANIMAL* previus_animal = NULL;
		previus_animal = malloc(sizeof(ANIMAL));

		for (int j = 0; j < i; j++)
		{
			ANIMAL* new_animal = NULL;
			new_animal = malloc(sizeof(ANIMAL));

			if (new_animal != NULL)
			{

				fscanf(fr, "%s\n", temp);

				fgets(new_animal->name, ANIMAL_NAME - 1, fr);
				new_animal->name[strlen(new_animal->name) - 1] = '\0';

				fgets(new_animal->species, SPECIES - 1, fr);
				new_animal->species[strlen(new_animal->species) - 1] = '\0';

				fscanf(fr, "%d\n", &new_animal->height);

				fscanf(fr, "%f\n", &new_animal->weight);

				fscanf(fr, "%ld\n", &new_animal->birht_date);

				fscanf(fr, "%ld\n", &new_animal->last_feeding);

				fgets(new_animal->caregiver_name, CAREGIVER_NAME - 1, fr);
				if (new_animal->caregiver_name[strlen(new_animal->caregiver_name) - 1] == '\n')
					new_animal->caregiver_name[strlen(new_animal->caregiver_name) - 1] = '\0';

				if (first_animal != NULL)
				{
					previus_animal->next_animal_in_line = new_animal;
					new_animal->next_animal_in_line = NULL;
					new_animal->previus_animal_in_line = previus_animal;
					previus_animal = new_animal;
				}
				else
				{
					first_animal = new_animal;
					first_animal->next_animal_in_line = NULL;
					first_animal->previus_animal_in_line = NULL;
					previus_animal = first_animal;
				}
			}
			else
			{
				printf("Nepodarilo sa alokovat!\n");
				return first_animal;
			}

		}

		printf("Nacitalo sa %d zaznamov!\n", i);

	}

	return first_animal;
}

void v(ANIMAL* first_animal)
{
	if (first_animal == NULL)
	{
		printf("Zaznami este neboli nacitane!\n");
		return;
	}

	ANIMAL* animal = first_animal;
	int i = 1;

	while (animal)
	{
		print_the_structure(animal, i);

		i++;
		animal = animal->next_animal_in_line;
	}
}

ANIMAL* p(ANIMAL* first_animal, int* number_of_animals)
{
	if (first_animal == NULL)
	{
		printf("Zaznami este neboli nacitane!\n");
		return first_animal;
	}

	int new_animal_position = 0;
	while (1)
	{
		printf("Zadajte cislo na ktore chcete zapisat novi zaznam: ");
		scanf("%d", &new_animal_position);

		if (new_animal_position > 0)
			break;
		else
			printf("Cislo musi byt vacsie ako nula!\n");
	}

	ANIMAL* new_animal = NULL;
	new_animal = malloc(sizeof(ANIMAL));

	if (new_animal != NULL)
	{
		printf("Zadajte udaje pre novy zaznam!\n");

		getchar();
		printf("Meno: ");
		gets(new_animal->name);

		printf("Druh: ");
		gets(new_animal->species);

		while (1)
		{
			printf("Vyska (%s): ", HEIGHT_UNIT);
			scanf(" %d", &new_animal->height);

			if (check_height(new_animal->height))
				break;
			printf("Nekorektne zadana vyska!\n");
		}

		while (1)
		{
			printf("Vaha (%s): ", WEIGHT_UNIT);
			scanf(" %f", &new_animal->weight);
			if (check_weight(new_animal->weight))
				break;
			printf("Nekorektne zadana vaha!\n");
		}

		while (1)
		{
			printf("Datum narodenia (%s): ", DATE_FORMAT);
			scanf(" %ld", &new_animal->birht_date);

			if (check_date(new_animal->birht_date))
				break;
			printf("Nekorektne zadani datum!\n");
		}

		while (1)
		{
			printf("Datum posledneho krmenia (%s): ", DATE_FORMAT);
			scanf(" %ld", &new_animal->last_feeding);

			if (!check_date(new_animal->last_feeding))
				printf("Nekorektne zadani datum krmenia!\n");
			else if (new_animal->birht_date > new_animal->last_feeding)
			{
				printf("Nekorektne zadani datum krmenia!\n");
				printf("Datum krmenia nemoze byt mensi ako datum narodenia!\n");
			}
			else
				break;
		}

		getchar();
		printf("Meno osetrovatela: ");
		gets(new_animal->caregiver_name);

		new_animal->next_animal_in_line = NULL;
		new_animal->previus_animal_in_line = NULL;
		printf("\n");
	}

	ANIMAL* previus_animal = NULL, * current_animal = NULL, * next_animal = NULL;

	if (new_animal_position == 1)
	{
		new_animal->next_animal_in_line = first_animal;
		first_animal->previus_animal_in_line = new_animal;
		first_animal = new_animal;
	}
	else
	{

		if (new_animal_position >= *number_of_animals)
		{
			next_animal = first_animal;
			while (next_animal)
			{
				previus_animal = next_animal->previus_animal_in_line;
				next_animal = next_animal->next_animal_in_line;
			}
			if (new_animal_position > *number_of_animals)
			{
				previus_animal = previus_animal->next_animal_in_line;
				previus_animal->next_animal_in_line = new_animal;
				new_animal->previus_animal_in_line = previus_animal;
			}
			else
			{
				next_animal = previus_animal->next_animal_in_line;
				previus_animal->next_animal_in_line = new_animal;
				new_animal->previus_animal_in_line = previus_animal;
				new_animal->next_animal_in_line = next_animal;
				next_animal->previus_animal_in_line = new_animal;
			}
		}
		else
		{
			current_animal = first_animal;
			for (int i = 1; i < new_animal_position; i++)
			{
				if (current_animal->next_animal_in_line != NULL)
					current_animal = current_animal->next_animal_in_line;
			}
			previus_animal = current_animal->previus_animal_in_line;
			previus_animal->next_animal_in_line = new_animal;

			new_animal->next_animal_in_line = current_animal;
			new_animal->previus_animal_in_line = previus_animal;

			current_animal->previus_animal_in_line = new_animal;
		}
	}

	*number_of_animals = *number_of_animals + 1;

	return first_animal;
}

ANIMAL* z(ANIMAL* first_animal, int* number_of_animals)
{
	if (first_animal == NULL)
	{
		printf("Zaznami este neboli nacitane!\n");
		return first_animal;
	}

	char animal_to_look_for[ANIMAL_NAME];

	getchar();
	printf("Zadajte meno zvierata ktore chcete vymazat: ");
	gets(animal_to_look_for);

	int deleted = 0, first = 1;
	ANIMAL* current_animal = first_animal, * previus_animal = NULL, * next_animal = NULL;

	while (current_animal)
	{
		if (finde_animal_name(current_animal, animal_to_look_for))
		{
			if (current_animal->previus_animal_in_line == NULL || first == 1)
			{
				first_animal = current_animal->next_animal_in_line;
				first_animal->previus_animal_in_line = NULL;
			}
			else if (current_animal->next_animal_in_line == NULL)
			{
				previus_animal = current_animal->previus_animal_in_line;
				previus_animal->next_animal_in_line = NULL;
			}
			else
			{
				previus_animal = current_animal->previus_animal_in_line;
				next_animal = current_animal->next_animal_in_line;

				previus_animal->next_animal_in_line = current_animal->next_animal_in_line;
				next_animal->previus_animal_in_line = previus_animal;
			}

			next_animal = current_animal->next_animal_in_line;

			free(current_animal);
			current_animal = NULL;

			current_animal = next_animal;

			deleted++;

		}
		else
			current_animal = current_animal->next_animal_in_line;

		first++;
	}

	if (deleted >= 1)
		printf("Zviera s menom %s bolo vymazane!\n", animal_to_look_for);
	else
		printf("Zviera s menom %s neexistuje!\n", animal_to_look_for);

	*number_of_animals = *number_of_animals - deleted;
	return first_animal;
}

void h(ANIMAL* first_animal)
{
	if (first_animal == NULL)
	{
		printf("Zaznami este neboli nacitane!\n");
		return;
	}

	long int check_feeding = 0;

	while (1)
	{
		printf("Zadajte datum krmenia (%s): ", DATE_FORMAT);
		scanf(" %d", &check_feeding);

		if (check_date(check_feeding))
			break;
		else
			printf("Zadali ste nekorektny datum!\n");
	}

	ANIMAL* next_animal = NULL;
	next_animal = first_animal;

	int i = 1, exists = 0;

	while (next_animal)
	{
		if (next_animal->last_feeding <= check_feeding)
		{
			print_the_structure(next_animal, i);
			exists = 1;
		}

		i++;
		next_animal = next_animal->next_animal_in_line;
	}

	if (exists == 0)
		printf("Vsetky zvierata boli k datumu %ld nakrmene!\n", check_feeding);
}

void a(ANIMAL* first_animal)
{
	if (first_animal == NULL)
	{
		printf("Zaznami este neboli nacitane!\n");
		return;
	}

	char animal_to_look_for[ANIMAL_NAME];
	long int new_date_of_feeding = 0;

	getchar();
	printf("Zadajte meno zvierata ktore chcete upravit: ");
	gets(animal_to_look_for);

	while (1)
	{

		printf("Zadajte novy datum krmenia (%s): ", DATE_FORMAT);
		scanf(" %d", &new_date_of_feeding);

		if (check_date(new_date_of_feeding))
			break;
		else
			printf("Zadali ste nekorektny datum!\n");

	}

	ANIMAL* next_animal = NULL;
	next_animal = first_animal;

	int exists = 0;

	while (next_animal)
	{
		if (finde_animal_name(next_animal, animal_to_look_for))
		{
			next_animal->last_feeding = new_date_of_feeding;
			exists = 1;
		}
		next_animal = next_animal->next_animal_in_line;
	}

	if (exists == 1)
		printf("Zviera s menom %s bolo naposledy nakrmene dna %ld!\n", animal_to_look_for, new_date_of_feeding);
	else
		printf("Zviera s menom %s nebolo najdene!\n", animal_to_look_for);
}

void k(ANIMAL* first_animal)
{
	deallocate_structures(first_animal);
	first_animal = NULL;

	exit(0);
}

int main()
{
	char sub_program;

	int number_of_animals = 0;

	ANIMAL* first_animal = NULL;

	while (1)
	{

		printf("Zadajte vstup pre prikaz: ");
		scanf("%s", &sub_program);

		sub_program = tolower(sub_program);

		switch (sub_program)
		{
		case 'n':
			first_animal = n(first_animal, &number_of_animals); printf("\n"); break;
		case 'v':
			v(first_animal); printf("\n"); break;
		case 'p':
			first_animal = p(first_animal, &number_of_animals); printf("\n"); break;
		case 'z':
			first_animal = z(first_animal, &number_of_animals); printf("\n"); break;
		case 'h':
			h(first_animal); printf("\n"); break;
		case 'a':
			a(first_animal); printf("\n"); break;
		case 'k':
			k(first_animal); break;
		default:
			printf("Vstup neexistuje!\n"); break;
		}
	}

	return 0;
}