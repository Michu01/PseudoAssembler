#pragma once
#include "labels.h"

struct label* make_label_variable(char* line, int* address)
{
	char* context = NULL;
	struct label* label = NULL;
	int asterisk = 0;
	int count = 1;

	//Sprawdź czy w linii występuje znak '*'

	asterisk = (strchr(line, '*') != NULL);

	label = malloc(sizeof(struct label));
	if (label == NULL) exit(EXIT_FAILURE);

	line = strtok_s(line, " \t", &context);

	//Stwórz etykietę zmiennej

	strcpy_s(label->name, MAX_LABEL_SIZE, line);
	label->address = *address;
	label->reg = MEMORY_REGISTER;

	//Zwiększ adres o rozmiar typu integer razy ilość zmiennych

	if (asterisk != 0)
	{
		line = strtok_s(NULL, " DCS*\t", &context);
		count = atoi(line);
	}

	*address += INTEGER_SIZE * count;

	return label;
}

struct label* make_label_command(char* line, int* address)
{
	int command = 0;
	int command_size = 0;
	int add_label = 0;
	char* context = NULL;
	struct label* label = NULL;

	add_label = (line[0] != ' ' && line[0] != '\t');

	line = strtok_s(line, " \t", &context);

	//Stwórz etykietę rozkazu

	if (add_label != 0)
	{
		label = malloc(sizeof(struct label));
		if (label == NULL) exit(EXIT_FAILURE);

		if (strcpy_s(label->name, MAX_LABEL_SIZE, line) != 0)
		{
			perror("");
			exit(EXIT_FAILURE);
		}

		label->address = *address;
		label->reg = COMMAND_REGISTER;

		line = strtok_s(NULL, " \t", &context);
	}

	//Zwiększ adres o rozmiar rozkazu

	command = get_command(line);
	command_size = get_command_size(command);
	*address += command_size;

	if (add_label != 0)
		return label;
	return NULL;
}

struct label* make_labels(FILE* input, int* label_count)
{
	char line[MAX_LINE_SIZE];
	struct label* labels = NULL;
	struct label* labels_temp = NULL;
	struct label* label_temp = NULL;
	int memory_address = 0;
	int command_address = 0;

	//Przejdź po sekcji danych i stwórz etykiety zmiennych

	while (fgets(line, MAX_LINE_SIZE, input) != NULL && line[0] != '\n' && line[0] != '#')
	{
		labels_temp = realloc(labels, ++*label_count * sizeof(struct label));
		if (labels_temp == NULL) exit(EXIT_FAILURE);
		labels = labels_temp;
		labels[*label_count - 1] = *make_label_variable(line, &memory_address);
	}

	//Przejdź po sekcji rozkazów i stwórz etykiety rozkazów

	while (fgets(line, MAX_LINE_SIZE, input) != NULL)
	{
		if (line[0] == '#') continue;

		//Jeśli wskaźnik na etykietę nie jest NULL dodaj etykietę

		label_temp = make_label_command(line, &command_address);
		if (label_temp != NULL)
		{
			labels_temp = realloc(labels, ++ * label_count * sizeof(struct label));
			if (labels_temp == NULL) exit(EXIT_FAILURE);
			labels = labels_temp;
			labels[*label_count - 1] = *label_temp;
		}
	}

	//Przewiń do początku pliku

	rewind(input);

	return labels;
}

struct label* find_label(const char* name, struct label* labels, int label_count)
{
	int n;
	for (n = 0; n < label_count; ++n)
		if (strcmp(name, labels[n].name) == 0) //Porównaj nazwę zmiennej z podaną nazwą
			return &labels[n];

	fprintf(stderr, "Etykieta %s nie istnieje!", name);
	exit(EXIT_FAILURE);
}