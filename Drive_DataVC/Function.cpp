#include "Head.h"
#include "Winio.h"
bool Read_File(int data[][2])
{
	FILE *fp;
	if ((fp = fopen("TimeData.txt", "r")) == NULL){
		printf("File open error!\n");
		return false;
	}
	for (int i = 0; i<12; i++){
		for (int j = 0; j<2; j++){
			fscanf(fp, "%d", &data[i][j]);
		}
	}
	return true;
}
int GetCurrentSecond(void)
{
	return time((time_t*)NULL) % 60;
}

void ParallPortWrite(unsigned char data)
{
	bool bResult;
	printf("debug:并口打开:\n");
	bResult = InitializeWinIo();			//并口初始化WINIO
	if (bResult)
	{
		//此处可修改或添加代码
		SetPortVal(0x378, data, 1);		//向地址为0x378的并口输出一个字节数据（1的段码0x06）
		printf("debug:0x%x\n", data);		//向屏幕输出并口数据提示信息
		ShutdownWinIo();					//并口关闭WINIO
		printf("debug:并口关闭:\n");
	}
	else
	{
		printf("Error during initialization of WinIo.\n");
		exit(1);
	}

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
		printf("%s",str);
		stod(L, str);
		printf("%s\n",str);
	}
}
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