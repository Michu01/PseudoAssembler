#pragma once
#include "directives.h"

int get_directive(const char* directive)
{
	if (strcmp(directive, "DC") == 0)
		return DC;
	if (strcmp(directive, "DS") == 0)
		return DS;

	fprintf(stderr, "Dyrektywa %s nie istnieje!", directive);
	exit(EXIT_FAILURE);
}

void write_directive_DC(FILE* output, int count, int value)
{
	int n;
	for (n = 0; n < count; ++n)
		fprintf(output, "%08X\n", value);
}

void write_directive_DS(FILE* output, int count)
{
	int n;
	for (n = 0; n < count; ++n)
		fprintf(output, "~~~~~~~~\n");
}

