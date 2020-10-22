#pragma once
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Zwróć numer rozkazu

int get_command(const char* command);

//Zwróć numer odpowiadający długości rozkazu

int get_command_size_num(int command);

//Zwróć długość rozkazu

int get_command_size(int command);

//Zwróć numer grupy rozkazu

int get_command_group(int command);

//Zapisz w pliku rozkaz 2-bajtowy

void write_command_short(FILE* output, int command, int reg1, int reg2);

//Zapisz w pliku rozkaz 4-bajtowy

void write_command_long(FILE* output, int command, int reg1, int reg2, int address);
