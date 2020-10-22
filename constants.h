#pragma once
//Nazwa pliku wyjściowego

#define OUTPUT_FILENAME "output.txt"

//Numery rejestrów

#define MEMORY_REGISTER 15
#define COMMAND_REGISTER 14

//Maksymalne długości ciągu znaków

#define MAX_PATH_SIZE 128
#define MAX_LINE_SIZE 128
#define MAX_LABEL_SIZE 64

//Rozmiar typu integer w bajtach

#define INTEGER_SIZE 4

//Kody dyrektyw

#define DC 0x1
#define DS 0x2

//Kody rozkazów

#define AR 0x10
#define A 0xD1
#define SR 0x12
#define S 0xD3
#define MR 0x14
#define M 0xD5
#define DR 0x16
#define D 0xD7
#define CR 0x18
#define C 0xD9
#define J 0xE0
#define JZ 0xE1
#define JP 0xE2
#define JN 0xE3
#define L 0xF0
#define LR 0x31
#define LA 0xF2
#define ST 0xF3

//Maski bitowe

#define BITMASK_COMMAND_SIZE 0b11000000
#define BITMASK_COMMAND_GROUP 0b110000

//Numery odpowiadające długościom komend

#define COMMAND_LONG_NUM 192
#define COMMAND_SHORT_NUM 0

//Długości komend

#define COMMAND_LONG_SIZE 4
#define COMMAND_SHORT_SIZE 2

//Numery grup rozkazów

#define COMMAND_ARITHMETIC 16
#define COMMAND_JUMP 32
#define COMMAND_STORAGE 48