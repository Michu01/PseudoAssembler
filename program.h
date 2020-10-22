#pragma once
#include "constants.h"
#include "directives.h"
#include "commands.h"
#include "labels.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Zinterpretuj linię dyrektywy

void parse_directive(FILE* output, char* line);

//Zinterpretuj linię rozkazu

void parse_command(FILE* output, char* line, struct label* labels, int label_count);

//Skompiluj program i zapisz go w pliku

void compile_program(FILE* input);
