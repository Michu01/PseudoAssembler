#pragma once
#include "constants.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Zwróć kod dyrektywy

int get_directive(const char* directive);

//Zapisz w pliku dyrektywę typu DC

void write_directive_DC(FILE* output, int count, int value);

//Zapisz w pliku dyrektywę typu DS

void write_directive_DS(FILE* output, int count);