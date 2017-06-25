#include "Head.h"
#include "winio.h"
unsigned char Num_Code[10] = { 0x3f, 0x06, 0xbb, 0xaf, 0x66, 0x6d, 0x7d, 0x87, 0x6f };
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
int main()
{
	int data[12][2] = { 0 }, flag = -1;
	if (Read_File(data) == false)
		return -1;
	while (1)
	{
		int second;
		second = GetCurrentSecond();
		for (int i = 0; i<12; i++){
			if (data[i][0] == second&&flag != i){
				system("cls");
				flag = i;
				show(data[i][1]);
				ParallPortWrite(Num_Code[data[i][1]]);
			}
		}
	}
	return 0;
}