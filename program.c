#pragma once
#include "program.h"

void parse_directive(FILE* output, char* line)
{
	int asterisk = 0;
	int directive = 0;
	int count = 1;
	int value = 0;
	char* context = NULL;

	//Sprawdź czy w linii występuje znak '*'

	asterisk = (strchr(line, '*') != NULL);

	//Zignoruj nazwę zmiennej

	line = strtok_s(line, " \t", &context);
	line = strtok_s(NULL, " \t", &context);

	//Sprawdź numer dyrektywy

	directive = get_directive(line);

	//Jeśli w linii występuje znak '*' wczytaj liczbę po lewej znaku

	if (asterisk != 0)
	{
		line = strtok_s(NULL, " *\t", &context);
		if (line != NULL)
			count = atoi(line);
	}

	//Dyrektywa DC

	if (directive == DC)
	{
		//Wczytaj wartość zmiennej z nawiasów

		line = strtok_s(NULL, " INTEGER*()\t\n", &context);
		if (line != NULL)
			value = atoi(line);

		write_directive_DC(output, count, value);
	}
	else if (directive == DS) //Dyrektywa DS
	{
		write_directive_DS(output, count);
	}
}

void parse_command(FILE* output, char* line, struct label* labels, int label_count)
{
	int command = 0;
	int reg1 = 0;
	int reg2 = 0;
	int address = 0;
	int command_size_num = 0;
	int command_group = 0;
	char* context = NULL;
	struct label* label = NULL;

	//Jeśli pierwszy znak linii nie jest spacją ani tabulatorem zignoruj etykiete

	if (line[0] != ' ' && line[0] != '\t')
	{
		line = strtok_s(line, " \t", &context);
		line = strtok_s(NULL, " \t", &context);
	}
	else line = strtok_s(line, " \t", &context);

	//Sprawdź numer rozkazu

	command = get_command(line);

	//Sprawdź długość rozkazu (2/4 bajty)

	command_size_num = get_command_size_num(command);

	if (command_size_num == COMMAND_LONG_NUM) //Rozkaz 4 bajtowy
	{
		//Sprawdź do jakiej grupy należy rozkaz

		command_group = get_command_group(command);

		//Jeśli rozkaz jest operacją arytmetyczną lub zapisuje wartość sprawdź numer pierwszego rejestru

		if (command_group == COMMAND_ARITHMETIC || command_group == COMMAND_STORAGE)
		{
			line = strtok_s(NULL, " ,(\t", &context);
			reg1 = atoi(line);
		}

		line = strtok_s(NULL, ",( \t\n", &context);

		//Jeśli pierwszy znak nie jest cyfrą, to sprawdź etykietę

		if (isdigit(line[0]) == 0)
		{
			label = find_label(line, labels, label_count);

			address = label->address;
			reg2 = label->reg;
		}
		else //W przeciwnym wypadku wczytaj adres i numer rejestru
		{
			address = atoi(line);

			line = strtok_s(NULL, "()", &context);
			reg2 = atoi(line);
		}

		//Zapisz do pliku rozkaz 4 bajtowy

		write_command_long(output, command, reg1, reg2, address);
	}
	else if (command_size_num == COMMAND_SHORT_NUM) //Rozkaz 2 bajtowy
	{
		//Sprawdź numery rejestrów

		line = strtok_s(NULL, " ,\t", &context);
		reg1 = atoi(line);

		line = strtok_s(NULL, ", \n", &context);
		reg2 = atoi(line);

		//Zapisz do pliku rozkaz 2 bajtowy

		write_command_short(output, command, reg1, reg2);
	}
}

void compile_program(FILE* input)
{
	FILE* output = NULL;
	char line[MAX_LINE_SIZE];
	struct label* labels = NULL;
	int label_count = 0;

	//Stwórz etykiety

	labels = make_labels(input, &label_count);

	//Otwórz plik output

	if (fopen_s(&output, OUTPUT_FILENAME, "w") != 0)
	{
		perror("Nie mozna otworzyc pliku "OUTPUT_FILENAME"!");
		exit(EXIT_FAILURE);
	}

	//Przejdź po sekcji danych i zapisz dyrektywy do pliku

	while (fgets(line, MAX_LINE_SIZE, input) != NULL && line[0] != '\n' && line[0] != '#')
	{
		parse_directive(output, line);
	}

	if (output != NULL)
		fprintf(output, "\n");

	//Przejdź po sekcji rozkazów i zapisz rozkazy do pliku

	while (fgets(line, MAX_LINE_SIZE, input) != NULL)
	{
		if (line[0] == '#') continue;
		parse_command(output, line, labels, label_count);
	}

	if (labels != NULL)
		free(labels);

	if (output != NULL)
		fclose(output);
}