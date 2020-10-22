#pragma once
#include "commands.h"

int get_command(const char* command)
{
	if (strcmp(command, "AR") == 0)
		return AR;
	if (strcmp(command, "A") == 0)
		return A;
	if (strcmp(command, "SR") == 0)
		return SR;
	if (strcmp(command, "S") == 0)
		return S;
	if (strcmp(command, "MR") == 0)
		return MR;
	if (strcmp(command, "M") == 0)
		return M;
	if (strcmp(command, "DR") == 0)
		return DR;
	if (strcmp(command, "D") == 0)
		return D;
	if (strcmp(command, "CR") == 0)
		return CR;
	if (strcmp(command, "C") == 0)
		return C;
	if (strcmp(command, "J") == 0)
		return J;
	if (strcmp(command, "JZ") == 0)
		return JZ;
	if (strcmp(command, "JP") == 0)
		return JP;
	if (strcmp(command, "JN") == 0)
		return JN;
	if (strcmp(command, "L") == 0)
		return L;
	if (strcmp(command, "LR") == 0)
		return LR;
	if (strcmp(command, "LA") == 0)
		return LA;
	if (strcmp(command, "ST") == 0)
		return ST;

	fprintf(stderr, "Rozkaz %s nie istnieje!", command);
	exit(EXIT_FAILURE);
}

int get_command_size_num(int command)
{
	return command & BITMASK_COMMAND_SIZE;
}

int get_command_size(int command)
{
	int command_size_num;
	
	command_size_num = get_command_size_num(command);

	if (command_size_num == COMMAND_SHORT_NUM)
		return COMMAND_SHORT_SIZE;
	if (command_size_num == COMMAND_LONG_NUM)
		return COMMAND_LONG_SIZE;

	fprintf(stderr, "Rozkaz o kodzie %02X nie istnieje!", command);
	exit(EXIT_FAILURE);
}

int get_command_group(int command)
{
	return command & BITMASK_COMMAND_GROUP;
}

void write_command_short(FILE* output, int command, int reg1, int reg2)
{
	fprintf(output, "%02X", command);
	fprintf(output, "%01X", reg1);
	fprintf(output, "%01X\n", reg2);
}

void write_command_long(FILE* output, int command, int reg1, int reg2, int address)
{
	fprintf(output, "%02X", command);
	fprintf(output, "%01X", reg1);
	fprintf(output, "%01X", reg2);
	fprintf(output, "%04X\n", address);
}