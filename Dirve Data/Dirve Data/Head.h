#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

extern char *Num[10];
bool Read_File(int data[][2]);
int GetCurrentSecond(void);
void ParallPortWrite(unsigned char data);
void show(int n);
void stod(int n, char s[]);
