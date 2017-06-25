#include <stdio.h>
#include <string.h>
char *Num[10] = {
	"3c4242424242423c\0", 
	"1818181818181818\0",
	"1824040810203c00\0",
	"1824040808042418\0",
	"040c1424447c0404\0",
	"3e20203c02022418\0",
	"0c10203824242418\0",
	"7e02020408102040\0",
	"1824241818242418\0", 
	"1824241808101010\0"
};
void show(int n);
void stod(int n, char s[]);
int main()
{
	for (int i = 0; i < 10; i++){
		show(i);
		printf("\n\n");
	}
	return 0;
}
void show(int n)
{
	char *p = Num[n];
	for (int i = 0; i < 8; i++){
		int H, L;
		H = (*p >= 97) ? (*p - 87) : (*p - 48);
		p++;
		L = (*p >= 97) ? (*p - 87) : (*p - 48);
		p++;
		char str[5];
		stod(H, str);
		for (int i=0; i < 4; i++){
			if (str[i] == '1')
				printf("*");
			else
				printf(" ");
		}
		stod(L, str);
		for (int i=0; i < 4; i++){
			if (str[i] == '1')
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}
void stod(int n,char s[])
{
	int i = 0;
	memset(s, 48, 5);
	while (n){
		if (n % 2)
			s[i++] = '1';
		else
			s[i++] = '0';
		n = n / 2;
	}
	s[4] = 0;
	_strrev(s);
}