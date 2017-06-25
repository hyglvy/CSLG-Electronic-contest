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
void stod(int n, char s[])
{
	int i = 0;
	memset(s, 32, 5);
	while (n){
		if (n % 2)
			s[i++] = '*';
		else
			s[i++] = ' ';
		n = n / 2;
	}
	s[4] = 0;
	_strrev(s);
}
void show_row(int n, int i)
{
	char *p = Num[n];
	char str[5];
	int H, L;
	H = (p[2 * i] >= 97) ? (p[2 * i] - 87) : (p[2 * i] - 48);
	stod(H, str);
	printf("%s",str);
	L = (p[2 * i + 1] >= 97) ? (p[2 * i + 1] - 87) : (p[2 * i + 1] - 48);
	stod(L, str);
	printf("%s", str);
}
void back(int n, int i)
{
	if (n >= 10){
		back(n / 10, i);
		show_row(n % 10, i);
	}
	else
		show_row(n, i);
}
void show(int n)
{
	for (int i = 0; i < 8; i++){
		back(n, i);
		printf("\n");
	}
}
int main()
{
	for (int i = 10; i <= 520; i++){
		show(i);
		printf("\n");
	}
	return 0;
}