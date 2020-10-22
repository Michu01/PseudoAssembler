#pragma once
#include "constants.h"
#include "commands.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Struktura przechowująca nazwę etykiety/zmiennej, jej adres i numer rejestru pamięci/rozkazów

struct label {
	char name[MAX_LABEL_SIZE];
	int address;
	int reg;
};

//Stwórz etykietę z nazwą zmiennej

struct label* make_label_variable(char* line, int* address);

//Stwórz etykietę z nazwą rozkazu

struct label* make_label_command(char* line, int* address);

//Stwórz etykiety

struct label* make_labels(FILE* input, int* label_count);

//Znajdź etykietę o podanej nazwie 

struct label* find_label(const char* name, struct label* labels, int label_count);